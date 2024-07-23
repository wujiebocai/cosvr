#pragma once

#include <unordered_map>
#include <async_simple/coro/Lazy.h>
#include <async_simple/coro/SyncAwait.h>
#include "util/utils.hpp"
#include "util/crc16.hpp"
#include "util/format.hpp"
#include "net.hpp"
#include "config.hpp"
#include "common/error.hpp"
#include "execute.hpp"

namespace modules {
namespace rds {
using exe_type = execute_imp<session_type>;
using exe_ptr_type = std::unique_ptr<execute_imp<session_type>>;

class cluster_policy_single_node {
public:
    explicit cluster_policy_single_node(rds_net_type* net, const redis_config& cfg)  
        : net_(net)
        , cfg_(cfg) { }

    inline async_simple::coro::Lazy<com_errors>
    init() {
        if (cfg_.addrs.size() <= 0) {
            std::cerr << "cluster_policy_single_node init error: the redis server address needs to be configured" << std::endl;
            co_return com_errors::config_error;
        }

        auto address = cfg_.addrs[0];
        auto host_port = bnet::tool::split(address, ":");
        if (host_port.size() < 2) {
            std::cerr << "cluster_policy_single_node init error: invalid redis server address" << std::endl;
            co_return com_errors::config_error;
        }

        for (size_t i = 0; i < cfg_.pool_size; i++) {
            auto sptr = net_->make_session();
            auto exe_ptr = std::make_unique<exe_type>(sptr, host_port[0], host_port[1], cfg_.username, cfg_.password, cfg_.protocol_version);
            auto ret = co_await exe_ptr->session_ready();
            if (ret != com_errors::success) {
                std::cerr << "cluster_policy_single_node init error: connect fail. url: " << address << ", " << get_com_err_message(ret) << std::endl;
                co_return ret;
            }
            pools_.emplace_back(std::move(exe_ptr));
        }

        co_return com_errors::success;
    }

    template<class... Args>
    inline async_simple::coro::Lazy<object>
    execute(Args&&... args) {
        auto exe = this->get_exe();
        return exe->execute(std::forward<Args>(args)...);
    }

    const redis_config& get_config() { return cfg_; }
private:
    exe_type* get_exe() {
        auto idx = next_exe_.fetch_add(1, std::memory_order::relaxed);
        auto *ret = pools_[idx % pools_.size()].get();
        return ret;
    }

private:
    rds_net_type* net_;
    redis_config cfg_;
    std::vector<exe_ptr_type> pools_;
    std::atomic<std::size_t> next_exe_ = 0;
};

// ---------------------------------------------------------------------------

using slot_index_type = int32_t; 
using slot_range_type = std::pair<slot_index_type, slot_index_type>; // begin-end

struct cluster_node;
struct cluster_slot {
    slot_range_type range;
    cluster_node* node; // master that this slot region belong to 
};

struct cluster_slot_comparator {
    bool operator()(const cluster_slot& a, const cluster_slot& b) const {
        return a.range.first < b.range.first;
    }
};

struct copen_slot {
    uint32_t slot_num;  // slot number
    int migrate;        // migrating or importing?
    std::string remote_name;    // name of node this slot migrating to/importing from
    cluster_node *node; // master that this slot belong to
};

struct cluster_node {
    e_cluster_node_type type;
    std::list<cluster_slot> slots;
    std::list<std::unique_ptr<cluster_node>> slaves;
    std::string host;
    std::string port;
    std::string address;
    std::string name;

    std::vector<copen_slot> migrating;
    std::vector<copen_slot> importing;

    std::unique_ptr<exe_type> exeptr;
};

template<typename T>
inline T& get_second_arg(T&& last) {
    return last;
}

template<typename T, typename U, typename... Args>
inline U& get_second_arg(T&& first, U&& second, Args&&... args) {
    return second;
}

class cluster_policy_hash_slot {
public:
    explicit cluster_policy_hash_slot(rds_net_type* net, const redis_config& cfg)  
        : net_(net)
        , cfg_(cfg) {}

    inline async_simple::coro::Lazy<com_errors>
    init() {
        if (cfg_.addrs.size() <= 1) {
            std::cerr << "cluster_policy_hash_slot init error: multiple redis server addresses need to be configured for the cluster" << std::endl;
            co_return config_error;
        }

        for (auto &&addr : cfg_.addrs) {
            auto host_port = bnet::tool::split(addr, ":");
            if (host_port.size() < 2) {
                std::cerr << "cluster_policy_hash_slot init error: invalid redis server address" << std::endl;
                co_return config_error;
            }

            auto master = make_cluster_node(host_port[0], host_port[1], CLUSTER_NODE_MASTER);
            auto ret = co_await master->exeptr->session_ready();
            if (ret != com_errors::success) {
                std::cerr << "cluster_policy_hash_slot init error: connect fail. url: " << addr << ", " << get_com_err_message(ret) << std::endl;
                co_return ret;
            }
            this->nodes_[addr] = std::move(master);
        }

        co_return co_await cluster_update_route();
    }

    template<class... Args>
    inline async_simple::coro::Lazy<object>
    execute(Args&&... args) {
        constexpr auto args_num = sizeof...(args); 
        if (args_num < 1) {
            co_return object{}.set_err(invalid_param);
        }

        if (!is_ready) {
            co_return object{}.set_err(cluster_is_not_ready);
        }

        auto exe = this->get_exe_by_key(get_second_arg(std::forward<Args>(args)...));
        if (!exe) {
            co_return object{}.set_err(operation_failure);
        }

        co_return co_await this->execute(exe, std::forward<Args>(args)...);
    }

    // eval script numkeys [key [key ...]] [arg [arg ...]]
    template<class... Args>
    inline async_simple::coro::Lazy<object>
    eval_exe(const std::string& eval_cmd, const std::string& script, uint32_t key_num, Args&&... args) {
        constexpr auto args_num = sizeof...(args); 
        if (args_num < key_num) {
            co_return object{}.set_err(invalid_param);
        }

        if (!is_ready) {
            co_return object{}.set_err(cluster_is_not_ready);
        }

        std::vector<std::string> vecs;
        args_to_vec(vecs, std::move(eval_cmd), std::move(script), key_num, std::forward<Args>(args)...);

        uint32_t slot_num = 0;
        if (key_num > 0) {
            auto& key = vecs[3];
            slot_num = key_hash_slot(key.c_str(), key.size());
        }

        //for (size_t i = 0; i < key_num; i++) {
        //    auto key = vecs[i+3];
        //    auto slot_num_t = key_hash_slot(key.c_str(), key.size());
        //    if (slot_num == 0) slot_num = slot_num_t;
        //    else if (slot_num != slot_num_t){
        //        co_return object{}.set_err(keys_at_diffrent_slot);
        //    }
        //}
        
        auto exe = this->get_exe_by_table(slot_num);
        if (!exe) {
            co_return object{}.set_err(operation_failure);
        }
        
        co_return co_await exe->execute(vecs);
    }

    inline const redis_config& get_config() { return cfg_; }
    inline void set_option_parse_flag(int flag) { flags_ = flag; }
private:
    template<class... Args>
    inline async_simple::coro::Lazy<object>
    execute(exe_type* exeptr, Args&&... args) {
        constexpr auto args_num = sizeof...(args); 
        if (exeptr == nullptr || args_num < 1) {
            co_return object{}.set_err(invalid_param);
        }

        auto obj = co_await exeptr->execute(std::forward<Args>(args)...);
        auto err_type = cluster_reply_error_type(obj);
        if (err_type <= CLUSTER_NOT_ERR || err_type >= CLUSTER_ERR_SENTINEL) {
            co_return obj;
        }

        switch (err_type) {
        case CLUSTER_ERR_MOVED: {
            if (auto update_ret = co_await cluster_update_route(); update_ret != com_errors::success) {
                co_return obj.set_err(update_ret);
            }
            else {
                co_return co_await this->execute(std::forward<Args>(args)...);
            }
        }
        case CLUSTER_ERR_ASK: {
            if (auto ask_ret = co_await hanle_ask_error(obj, exeptr); ask_ret != com_errors::success) {
                co_return obj.set_err(ask_ret);
            }
            else {
                co_return co_await this->execute(exeptr, std::forward<Args>(args)...);
            }
        }
        case CLUSTER_ERR_TRYAGAIN:
        case CLUSTER_ERR_CLUSTERDOWN: {
            co_return co_await this->execute(std::forward<Args>(args)...);
        }
        default:
            break;
        }

        co_return obj.set_err(operation_failure);
    }

    com_errors cluster_slot_ref_node(cluster_slot& slot, cluster_node& node) {
        if (node.type != e_cluster_node_type::CLUSTER_NODE_MASTER) {
            return com_errors::data_type_error;
        }

        slot.node = &node;
        node.slots.emplace_back(std::move(slot));

        return com_errors::success;
    }

    com_errors parse_cluster_slots(object& obj, int flags, std::unordered_map<std::string, std::unique_ptr<cluster_node>>& nodes) {
        std::vector<object>* arr = obj;
        if (!arr || arr->size() <= 0) {
            std::cerr << "Command(cluster slots) responde error: obj is not an correct array" << std::endl;
            return data_type_error;
        }

        cluster_node* master = nullptr;
        for (auto&& itr : *arr) {
            std::vector<object>* elem_slots = itr;
            if (!elem_slots || elem_slots->size() < 3) {
                std::cerr << "Command(cluster slots) responde error: first element is not an correct array" << std::endl;
                return data_type_error;
            }

            cluster_slot slot;
            for (size_t idx = 0; idx < elem_slots->size(); idx++) {
                if (idx == 0) {
                    int64_t* begin = (*elem_slots)[idx];
                    if (!begin) {
                        std::cerr << "Command(cluster slots) responde error: slot begin is not an integer" << std::endl;
                        return data_type_error;
                    }
                    slot.range.first = (slot_index_type)(*begin);
                }
                else if (idx == 1) {
                    int64_t* end = (*elem_slots)[idx];
                    if (!end) {
                        std::cerr << "Command(cluster slots) responde error: slot end is not an integer" << std::endl;
                        return data_type_error;
                    }
                    slot.range.second = (slot_index_type)(*end);

                    if (slot.range.first > slot.range.second) {
                        std::cerr << "Command(cluster slots) responde error: slot begin is bigger than slot end" << std::endl;
                        return logic_error;
                    }
                }
                else {
                    std::vector<object>* elem_nodes = (*elem_slots)[idx];
                    if (!elem_nodes || elem_nodes->size() < 2) {
                        std::cerr << "Command(cluster slots) responde error: nodes data is not an correct array" << std::endl;
                        return data_type_error;
                    }

                    std::string* host = (*elem_nodes)[0];
                    int64_t* port = (*elem_nodes)[1];
                    if (!host || !port) {
                        std::cerr << "Command(cluster slots) responde error: master host or port is not correct" << std::endl;
                        return data_type_error;
                    }

                    if (host->size() <= 0 || *port < 1 || *port > UINT16_MAX) {
                        std::cerr << "Command(cluster slots) responde error: node host or port is not valid" << std::endl;
                        return invalid_data;
                    }

                    // this is master.
                    if (idx == 2) {
                        auto address = std::format("{}:{}", *host, *port);
                        // master already exists, break to the next slots region.
                        auto itr = nodes.find(address);
                        if (itr == nodes.end()) {
                            auto masterptr = make_cluster_node(*host, std::to_string(*port), CLUSTER_NODE_MASTER);
                            master = masterptr.get();
                            nodes[address] = std::move(masterptr);
                        }
                        else {
                            master = itr->second.get();
                        }

                        if (auto ret = cluster_slot_ref_node(slot, *master); ret != com_errors::success) {
                            return ret;
                        }
                    }
                    else if(flags & HIRCLUSTER_FLAG_ADD_SLAVE) {
                        auto slaveprt = make_cluster_node(*host, std::to_string(*port), CLUSTER_NODE_SLAVE);
                        master->slaves.push_back(std::move(slaveprt));
                    }
                }
            }
        }
        
        return com_errors::success;
    }

    com_errors parse_cluster_nodes(object& obj, int flags, std::unordered_map<std::string, std::unique_ptr<cluster_node>>& nodes) {
        std::string* str = obj;
        if (!str || str->size() <= 0) {
            std::cerr << "Command(cluster nodes) responde error: obj is not an correct string" << std::endl;
            return data_type_error;
        }

        std::string node_type;
        cluster_node *master = nullptr; // *slave = nullptr;

        auto splits = bnet::tool::split(*str, '\n');
        if (splits.size() <= 0) {
            std::cerr << "Command(cluster nodes) responde error: invalid data. str: " << *str << std::endl;
            return invalid_data;
        }

        //for (auto &&line : splits) {
        //    std::cout << "cluster info: " << line << std::endl;
        //}

        std::unordered_map<std::string, std::list<std::unique_ptr<cluster_node>>> slave_nodes;

        for (auto &&line : splits) {
            auto part = bnet::tool::split(line, " ");
            if (part.size() < 8) {
                std::cerr << "Command(cluster nodes) responde error: split cluster nodes error" << std::endl;
                return invalid_data;
            }

            // the address string is ":0", skip this node.
            if (part[1].size() == 2 && part[1] == ":0") {
                continue;
            }

            if (part[2].size() >= 7 && std::memcmp(part[2].c_str(), "myself,", 7) == 0) {
                node_type = part[2].substr(7);
            }
            else {
                node_type = part[2];
            }

            cluster_slot slot;

            // add master node
            if (node_type.size() >= 6 && std::memcmp(node_type.c_str(), "master", 6) == 0) {
                auto name = part[0];
                auto address = part[1];
                std::string host, port;
                const char* c_address = address.c_str();
                if (auto p = std::strrchr(c_address, ':'); p == nullptr) {
                    std::cerr << "Command(cluster nodes) responde error: server address is incorrect, port separator missing" << std::endl;
                    return invalid_data;
                }
                else {
                    host = std::string(c_address, p - c_address);
                    p++; // remove found separator character
                    // Strip away cport if given by redis
                    size_t port_len;
                    if (auto pt = std::strchr(p, '@'); pt == nullptr) {
                        port_len = std::strlen(p);
                    } else {
                        port_len = pt - p;
                    }

                    port = std::string(p, port_len);
                }

                auto masterptr = make_cluster_node(host, port, CLUSTER_NODE_MASTER, name);
                master = masterptr.get();
                nodes[master->address] = std::move(masterptr);

                for (size_t i = 8; i < part.size(); i++) {
                    auto slot_range = bnet::tool::split(part[i], "-");
                    auto slot_range_len = slot_range.size();

                    if (slot_range_len == 1) {
                        auto val = bnet::tool::to_numeric<slot_index_type>(slot_range[0]);
                        slot.range.first = val;
                        slot.range.second = val;
                    }
                    else if (slot_range_len == 2) {
                        slot.range.first = bnet::tool::to_numeric<slot_index_type>(slot_range[0]);
                        slot.range.second = bnet::tool::to_numeric<slot_index_type>(slot_range[1]);
                    }
                    else {
                        // add open slot for master
                        if (flags & HIRCLUSTER_FLAG_ADD_OPENSLOT &&
                            slot_range_len == 3 &&
                            slot_range[0].size() > 1 &&
                            slot_range[1].size() == 1 &&
                            slot_range[2].size() > 1 &&
                            slot_range[0][0] == '[' &&
                            slot_range[2][slot_range[2].size() - 1] == ']') {
                            copen_slot oslot;
                            slot_range[0] = slot_range[0].substr(1);
                            slot_range[2] = slot_range[2].substr(0, slot_range[2].size() - 1);

                            if (slot_range[1][0] == '>') {
                                oslot.slot_num = bnet::tool::to_numeric<uint32_t>(slot_range[0]);
                                oslot.remote_name = slot_range[2];
                                oslot.node = master;
                                oslot.migrate = 1;
                                master->migrating.push_back(oslot);
                            }
                            else if (slot_range[1][0] == '<') {
                                oslot.slot_num = bnet::tool::to_numeric<uint32_t>(slot_range[0]);
                                oslot.remote_name = slot_range[2];
                                oslot.node = master;
                                oslot.migrate = 0;
                                master->importing.push_back(oslot);
                            }
                        }

                        slot.range.first = -1;
                        slot.range.second = -1;
                    }

                    if (slot.range.first < 0 || slot.range.second < 0 || 
                        slot.range.first > slot.range.second || slot.range.second > REDIS_CLUSTER_SLOTS) {
                        continue;
                    }

                    if (auto ret = cluster_slot_ref_node(slot, *master); ret != com_errors::success) {
                        return ret;
                    }
                }
                
            }
            // add slave node
            else if ((flags & HIRCLUSTER_FLAG_ADD_SLAVE) && (node_type.size() >= 5 && std::memcmp(node_type.c_str(), "slave", 5) == 0)) {
                auto name = part[0];
                auto address = part[1];
                std::string host, port;
                const char* c_address = address.c_str();
                if (auto p = std::strrchr(c_address, ':'); p == nullptr) {
                    std::cerr << "Command(cluster nodes) responde error: parse host fail" << std::endl;
                    return invalid_data;
                }
                else {
                    host = std::string(c_address, p - c_address);
                    p++; // remove found separator character
                    // Strip away cport if given by redis
                    size_t port_len;
                    if (auto pt = std::strchr(p, '@'); pt == nullptr) {
                        port_len = std::strlen(p);
                    } else {
                        port_len = pt - p;
                    }

                    port = std::string(p, port_len);
                }

                auto master_name = part[3];
                slave_nodes[master_name].emplace_back(make_cluster_node(host, port, CLUSTER_NODE_SLAVE, name));
            }
        }

        if (flags & HIRCLUSTER_FLAG_ADD_SLAVE) {
            for (auto &&itr : nodes) {
                auto sitr = slave_nodes.find(itr.second->name);
                if (sitr != slave_nodes.end()) {
                    itr.second->slaves.swap(sitr->second);
                }
            }
        }
        
        return com_errors::success;
    }

    // Update route with the "cluster nodes" or "cluster slots" command reply.
    inline async_simple::coro::Lazy<com_errors>
    cluster_update_route_by_addr(cluster_node* node, int flags) {
        if (!node || !node->exeptr) {
            std::cerr << "cluster updata route error: host or port error" << std::endl;
            co_return com_errors::invalid_param;
        }
        
        std::unordered_map<std::string, std::unique_ptr<cluster_node>> nodes;
        if (flags & HIRCLUSTER_FLAG_ROUTE_USE_SLOTS) {
            auto ret = co_await node->exeptr->execute("cluster", "slots");
            if (auto r = parse_cluster_slots(ret, flags, nodes); r != com_errors::success) {
                co_return r;
            }
        }
        else {
            auto ret = co_await node->exeptr->execute("cluster", "nodes");
            if (auto r = parse_cluster_nodes(ret, flags, nodes); r != com_errors::success) {
                co_return r;
            }
        }

        std::vector<cluster_slot> slots;
        for (auto &&itr : nodes) {
            auto master = itr.second.get();
            if (master->type != CLUSTER_NODE_MASTER) {
                std::cerr << "cluster updata route error: node type must be master" << std::endl;
                co_return data_type_error;
            }

            auto nitr = nodes_.find(itr.first);
            if (nitr != nodes_.end()) {
                master->exeptr.swap(nitr->second->exeptr);
            }
            else {
                auto ret = co_await master->exeptr->session_ready();
                if (ret != com_errors::success) {
                    std::cerr << "cluster updata route error: connect fail. url: " << itr.first << ", " << get_com_err_message(ret) << std::endl;
                    co_return ret;
                }
            }

            if (master->slots.size() <= 0) {
                continue;
            }

            for (auto &&slot : master->slots) {
                if (slot.range.first > slot.range.second || slot.range.second >= REDIS_CLUSTER_SLOTS) {
                    std::cerr << "cluster updata route error: slot region for node is error" << std::endl;
                    co_return logic_error;
                }

                slots.push_back(std::move(slot));
            }
        }

        std::fill(table_.begin(), table_.end(), nullptr);
        std::sort(slots.begin(), slots.end(), cluster_slot_comparator{});
        for (auto &&slot : slots) {
            for (auto k = slot.range.first; k <= slot.range.second; k++) {
                if (table_[k] != nullptr) {
                    std::cerr << "cluster updata route error: different node holds same slot" << std::endl;
                    co_return logic_error;
                }
                table_[k] = slot.node;
            }  
        }

        nodes_.swap(nodes);
        
        route_version_++;

        co_return com_errors::success;
    }

    inline async_simple::coro::Lazy<com_errors>
    cluster_update_route() {
        if (nodes_.size() <= 0) {
            std::cerr << "cluster updata route error: no server address" << std::endl;
            co_return com_errors::logic_error;
        }

        is_ready = false;
        
        for (auto &&itr : nodes_) {
            auto ret = co_await cluster_update_route_by_addr(itr.second.get(), flags_);
            if (ret == com_errors::success) {
                is_ready = true;
                co_return ret;
            }
        }

        std::cerr << "cluster updata route error: no valid server address" << std::endl;
        
        co_return com_errors::invalid_address;
    }

    inline std::unique_ptr<cluster_node> make_cluster_node(const std::string& host, const std::string& port, e_cluster_node_type type, const std::string& name = "") {
        auto address = std::format("{}:{}", host, port);
        auto node = std::make_unique<cluster_node>();
        node->address = address;
        node->host = host;
        node->port = port;
        node->type = type;
        node->name = name;
        auto sptr = net_->make_session();
        node->exeptr = std::make_unique<exe_type>(sptr, host, port, cfg_.username, cfg_.password, cfg_.protocol_version);
        return node;
    }

    inline exe_type* get_exe_by_node(cluster_node *node) {
        if (!node) {
            return nullptr;
        }

        return node->exeptr.get();
    }

    inline exe_type* get_exe_by_table(uint32_t slot_num) {
        if (slot_num >= REDIS_CLUSTER_SLOTS) {
            return nullptr;
        }

        auto* node = this->table_[slot_num];
        if (!node || !node->exeptr) {
            return nullptr;
        }

        return node->exeptr.get();
    }

    inline exe_type* get_exe_by_nodes(const std::string& address) {
        auto itr = nodes_.find(address);
        if (itr == nodes_.end()) {
            return nullptr;
        }

        return itr->second->exeptr.get();
    }

    inline exe_type* get_exe_by_key(const std::string& key) {
        if (key.size() <= 0) {
            return nullptr;
        }

        auto slot_num = key_hash_slot(key.c_str(), key.size());

        return get_exe_by_table(slot_num);
    }

    inline async_simple::coro::Lazy<com_errors>
    hanle_ask_error(object& obj, exe_type* exeptr) {
        if (!obj.is_valide()) {
            std::cerr << "hanle_ask_error: invalid param" << std::endl;
            co_return invalid_param;
        }

        auto err_type = cluster_reply_error_type(obj);
        if (err_type != CLUSTER_ERR_ASK) {
            std::cerr << "hanle_ask_error: object is not ask error" << std::endl;
            co_return data_type_error;
        }

        const std::string* errstr = obj;
        auto part = bnet::tool::split(*errstr, " ");
        if (part.size() != 3) {
            std::cerr << "hanle_ask_error: ask error reply parse error" << std::endl;
            co_return invalid_data;
        }

        auto host_port = bnet::tool::split(part[2], ":");
        if (host_port.size() != 2) {
            std::cerr << "hanle_ask_error: ask error address part parse error!" << std::endl;
            co_return invalid_data;
        }

        exeptr = get_exe_by_nodes(part[2]);
        if (!exeptr) {
            auto master = make_cluster_node(host_port[0], host_port[1], CLUSTER_NODE_MASTER);
            exeptr = master->exeptr.get();
            nodes_[part[2]] = std::move(master);
        }
        
        auto ret = co_await exeptr->execute("asking");
        if (!ret.is_valide()) {
            std::cerr << "hanle_ask_error: asking failure, errmsg: " << ret.errmsg() << std::endl;
            co_return asking_failure;
        }

        co_return com_errors::success;
    }

    inline static unsigned int key_hash_slot(const char *key, int keylen) {
        int s, e;
        for (s = 0; s < keylen; s++)
            if (key[s] == '{') break;

        if (s == keylen) return crc16(key, keylen) & 0x3FFF;

        for (e = s + 1; e < keylen; e++)
            if (key[e] == '}') break;

        if (e == keylen || e == s + 1) return crc16(key, keylen) & 0x3FFF;

        return crc16(key + s + 1, e - s - 1) & 0x3FFF;
    }

    inline static e_cluster_err_type cluster_reply_error_type(object& obj) {
        if (obj.err_code_ == server_rsp_error) {
            const std::string& errstr = obj.errmsg();
            if (errstr.find(REDIS_ERROR_MOVED) == 0) {
                return CLUSTER_ERR_MOVED;
            } else if (errstr.find(REDIS_ERROR_ASK) == 0) {
                return CLUSTER_ERR_ASK;
            } else if (errstr.find(REDIS_ERROR_TRYAGAIN) == 0) {
                return CLUSTER_ERR_TRYAGAIN;
            } else if (errstr.find(REDIS_ERROR_CLUSTERDOWN) == 0) {
                return CLUSTER_ERR_CLUSTERDOWN;
            } else {
                return CLUSTER_ERR_SENTINEL;
            }
        }

        return CLUSTER_NOT_ERR;
    }
private:
    rds_net_type* net_;
    redis_config cfg_;
    int flags_ = HIRCLUSTER_FLAG_NULL; // HIRCLUSTER_FLAG_ROUTE_USE_SLOTS | HIRCLUSTER_FLAG_ADD_SLAVE;

    std::unordered_map<std::string, std::unique_ptr<cluster_node>> nodes_; // address-node
    std::array<cluster_node*, REDIS_CLUSTER_SLOTS> table_{nullptr};

    std::atomic<bool> is_ready{false};
    std::atomic<uint64_t> route_version_ = 0;
};

} // namespace rds

} // namespace modules