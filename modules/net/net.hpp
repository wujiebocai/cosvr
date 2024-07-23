#pragma once

#include <optional>
#include <async_simple/Executor.h>
#include <async_simple/coro/Lazy.h>
#include <async_simple/coro/SyncAwait.h>
#include <bnet.hpp>
#include "util/format.hpp"
#include "protocol/net_protocol.hpp"
#include "common/define.hpp"
#include "stream.hpp"
#include "proxy.hpp"
#include "event.hpp"

namespace modules {
// server cluster information
struct server_cluster_info {
    std::string id;
    std::string type;
    std::string host;
    std::string port;
    uint32_t instance_id;
};

template<typename PortType>
std::string get_svr_key(std::string_view f, PortType s) {
    return std::format("server/{}/{}", f, s);
}

template<typename PortType>
std::string get_cli_key(std::string_view f, PortType s) {
    return std::format("client/{}/{}", f, s);
}

inline uint32_t get_hash_key(std::string_view key) {
    return modules::hash32(key);
}

namespace net {
template<typename ClientStreamType, typename SvrverStreamType>
class net_stream {
public:
    using s_session_type = typename SvrverStreamType::session_type;
    using s_session_ptr_type = typename SvrverStreamType::session_ptr_type;
    using s_session_weakptr_type = typename SvrverStreamType::session_weakptr_type;
    using c_session_type = typename ClientStreamType::session_type;
    using c_session_ptr_type = typename ClientStreamType::session_ptr_type;
    using c_session_weakptr_type = typename ClientStreamType::session_weakptr_type;
    using header_type = typename ClientStreamType::header_type;

    struct server_info {
        server_cluster_info info_;
        c_session_weakptr_type sptr_;
    };
    using server_info_ptr_type = std::shared_ptr<server_info>;
    using server_info_weakptr_type = std::weak_ptr<server_info>;
public:
    explicit net_stream(const server_cluster_info& info, const bnet::svr_cfg& scfg, const bnet::cli_cfg& ccfg)
    : svr_(scfg)
    , cli_(ccfg)
    , cluster_info_(info) {
        svr_.start();
        cli_.start();

        init_cb();
    }

    ~net_stream() {
        svr_.stop();
        cli_.stop();
    }

    // Called when listening for a new server node; to be optimized
    inline async_simple::coro::Lazy<std::optional<server_info_ptr_type>>
    add_server(const server_cluster_info& info) {
        if (cluster_info_.instance_id == info.instance_id) {
            co_return std::nullopt; 
        }

        c_session_ptr_type sptr;
        auto ret = co_await connect(info.host, info.port, sptr);
        if (ret) {
            co_return std::nullopt;
        }

        auto nptr = std::make_shared<server_info>();
        nptr->info_ = info;
        nptr->sptr_ = sptr;
        {
            std::shared_lock shared_lock{mutex_};
            svrs_[info.type][info.id] = nptr;
            svr_instance_ids_[info.instance_id] = nptr;
        }
        //sptr->user_data(nptr);

        co_return nptr;
    }

    template <typename... Args>
    inline auto
    sync_add_server(Args &&...args) {
        return async_simple::coro::syncAwait(add_server(std::forward<Args>(args)...));
    }

    // Called when deleting a server node; to be optimized
    bool remove_server(const server_cluster_info& info) {
        c_session_ptr_type sptr;
        {
            std::shared_lock shared_lock{mutex_};
            auto itr = svr_instance_ids_.find(info.instance_id);
            if (itr != svr_instance_ids_.end()) {
                sptr = itr->second->sptr_.lock();
                svr_instance_ids_.erase(itr);
            }
            svrs_[info.type].erase(info.id);
        }
        
        if (sptr) {
            sptr->stop();
        }

        return true;
    }

    // Select a service at random
    inline std::optional<server_info_ptr_type> get_svrinfo_by_random(const std::string& svr_type) {
        std::shared_lock shared_lock{mutex_};
        auto& svr_infos = svrs_[svr_type];
        if (svr_infos.size() <= 0) {
			return std::nullopt;
		}
			
		std::random_device rd;
    	std::mt19937 gen(rd());

    	std::uniform_int_distribution<int> distribution(0, svr_infos.size() - 1); 
		auto random_it = std::next(std::begin(svr_infos), distribution(gen));
		if (random_it == svr_infos.end()) return std::nullopt;
        return random_it->second.lock();
    }

    // Select a service based on the hash value
    inline std::optional<server_info_ptr_type> get_svrinfo_by_hash(const std::string& svr_type, uint32_t hash) {
        std::shared_lock shared_lock{mutex_};
        auto& svr_infos = svrs_[svr_type];
        if (svr_infos.size() <= 0) {
			return std::nullopt;
		}
			
		auto offset = hash % svr_infos.size();
		auto itr = std::next(std::begin(svr_infos), offset);
		if (itr == svr_infos.end()) return std::nullopt;
        return itr->second.lock();
    }

    // Select a service based on the server id
    inline std::optional<server_info_ptr_type> get_svrinfo_by_svrid(const std::string& svr_type, const std::string& svr_id) {
        std::shared_lock shared_lock{mutex_};
        auto& svr_infos = svrs_[svr_type];
        auto itr = svr_infos.find(svr_id);
        if (itr == svr_infos.end()) {
            return std::nullopt;
        } 
        return itr->second.lock();
    }

    // Select a service based on the server instance id to optimize the query speed
    inline std::optional<server_info_ptr_type> get_svrinfo_by_svr_instanceid(uint32_t instanceid) {
        std::shared_lock shared_lock{mutex_};
        auto itr = svr_instance_ids_.find(instanceid);
        if (itr == svr_instance_ids_.end()) {
            return std::nullopt;
        }
        return itr->second;
    }

    template<typename Fun>
    inline bool broadcast_handle(const std::string& svr_type, Fun&& f) {
        std::shared_lock shared_lock{mutex_};
        if (svr_type.size() <= 0) { // handle all
            for (auto &&i : svr_instance_ids_) {
                f(i);
            }
        }
        else {
            auto& svr_infos = svrs_[svr_type];
            for (auto &&i : svr_infos) {
                f(i);   
            }
        }
        return true;
    }
    template<typename Fun>
    inline bool broadcast_handle(const std::vector<uint32_t> instances, Fun&& f) {
        std::shared_lock shared_lock{mutex_};
        for (auto &&i : instances) {
            auto itr = svr_instance_ids_.find(i);
            if (itr == svr_instance_ids_.end()) {
                continue;
            }
            f(itr->second.lock());
        }
        return true;
    }
    
    inline async_simple::coro::Lazy<std::error_code>
    connect(std::string_view host, std::string_view port, c_session_ptr_type& sptr) {
        callback_awaitor<std::error_code> awaitor;
        co_return co_await awaitor.await_resume([&](auto handler) {
            cli_.template add(host, port, [handler](std::exception_ptr ex, error_code ec) { 
				handler.set_value_then_resume(ec);
    	    }, &sptr);
        });
    }

    inline auto& get_svr_stream() { return svr_; }
    inline auto& get_cli_stream() { return cli_; }
    inline auto& get_agent_mgr() { return agent_mgr_; }
    inline auto& get_cluster_info() { return cluster_info_; }
    inline auto& get_user_event() { return user_event_; }
protected:
    void init_cb() {
        svr_.bind(event::connect, [this](const s_session_ptr_type& sptr) mutable {
            return this->handle_connect(sptr);
        });
        svr_.bind(event::disconnect, [this](const s_session_ptr_type& sptr) mutable {
            return this->handle_disconnect(sptr);
        });
        svr_.set_handle_message([this](header_type& head, const s_session_ptr_type& sptr, const std::string& data) {
            return this->handle_message(head, sptr, data);
        });
        cli_.bind(event::connect, [this](const c_session_ptr_type& sptr) mutable {
            return this->handle_connect<c_session_type, false>(sptr);
        });
        cli_.bind(event::disconnect, [this](const c_session_ptr_type& sptr) mutable {
            return this->handle_disconnect(sptr);
        });
        cli_.set_handle_message([this](header_type& head, const c_session_ptr_type& sptr, const std::string& data) {
            return this->handle_message(head, sptr, data);
        });
    }

    template<typename SessionType, bool SvrOrCli = true> 
    inline void handle_connect(const std::shared_ptr<SessionType>& sptr) {
        auto exe = std::make_unique<executor_wrapper<>>(sptr->cio().context().get_executor());

        uint64_t agent_id = 0;
        // When you need to communicate with the remote Agent, a local Agent Agent is 
        // created, and the Agent ID of this agent corresponds to the ID of the actual remote agent.
        if constexpr (SvrOrCli) {
            auto hash = get_hash_key(get_cli_key(sptr->remote_address(), sptr->remote_port()));
            agent_id = gen_agent_id(cluster_info_.instance_id, hash);
        }
        else {
            auto svr_hash = get_hash_key(get_svr_key(sptr->remote_address(), sptr->remote_port()));
            auto cli_hash = get_hash_key(get_cli_key(sptr->local_address(), sptr->local_port()));
            agent_id = gen_agent_id(svr_hash, cli_hash);
        }
        auto* agent = agent_mgr_.add_agent<proxy>(agent_id, AGENT_TYPE_PROXY, exe.get());
        agent->set_exe(exe);
        sptr->user_data(agent);
        agent->set_transfer([this, wptr = std::weak_ptr<SessionType>(std::move(sptr))](uint64_t to_id, uint64_t from_id, uint32_t msgid, const std::string& data) {
            header_type head {
                msg_id: msgid,
                to_id: to_id,
                from_id: from_id,
            };
            if constexpr (SvrOrCli) return svr_.send(wptr.lock(), head, data);
            else return cli_.send(wptr.lock(), head, data);
        });
        agent->set_cancel([wptr = std::weak_ptr<SessionType>(std::move(sptr))]() {
            auto sptr = wptr.lock();
            if (sptr) sptr->stop();
            return true;
        });

        if (user_event_.connect_) user_event_.connect_(agent);
    }

    template<typename SessionType>
    inline void handle_disconnect(const std::shared_ptr<SessionType>& sptr) {
        auto* ret = sptr->template user_data<proxy*>();
        if (!ret) {
            return;
        }
        auto* agent = *ret;
        if (user_event_.disconnect_) user_event_.disconnect_(agent);
        agent_mgr_.remove_agent(agent->id());
    }

    template<typename SessionType>
    inline void handle_message(header_type& head, const std::shared_ptr<SessionType>& sptr, const std::string& data) {
        agent_ptr_type to;
        auto to_id = head.to_id;
        if (to_id == 0) {
            auto* dataptr = sptr->template user_data<proxy*>();
            if (!dataptr) {
                std::cerr << "get agent ptr fail" << " , agent_id " <<  to_id << ", msgid " 
                    << head.msg_id << ", svr type " << cluster_info_.type << std::endl;
                return;
            }
            to = *dataptr;
        }
        else {
            to = agent_mgr_.get_agent(to_id);
        }

        if (to) {
            auto ret = agent_mgr_.enqueue(to, head.from_id, head.msg_id, data);
            if (ret == com_errors::success) {
                return;
            }
            std::cerr << "handle msg fail" << " , agent_id " << to_id << ", msgid " 
                << head.msg_id << ", svr type " << cluster_info_.type << ", ret " << ret << std::endl;
            return;
        }
        else {
            auto instance_id = get_high_by_agent_id(to_id);
            auto subid = get_low_by_agent_id(to_id);
            auto svr_info = get_svrinfo_by_svr_instanceid(instance_id);
            if (!svr_info) {
                std::cerr << "get svr info fail" << " , agent_id " << to_id << ", msgid " 
                    << head.msg_id << ", svr type " << cluster_info_.type << std::endl;
                return;
            }
            auto ptr = svr_info.value()->sptr_.lock();
            if (!ptr) {
                std::cerr << "info session is invalid" << " , agent_id " << to_id << ", msgid " 
                    << head.msg_id << ", svr type " << cluster_info_.type << std::endl;
                return;
            }
            auto ret = this->get_cli_stream().send(ptr, head, data);
            if (!ret) {
                std::cerr << "forward transaction failure" << " , instance_id " <<  instance_id 
                    << ", subid " << subid << ", svr type " << cluster_info_.type << std::endl;
                return;
            }
        }
    }

private:
    SvrverStreamType svr_;
    ClientStreamType cli_;
    server_cluster_info cluster_info_;
    agent_mgr_type agent_mgr_;
    std::shared_mutex mutex_;
    typedef std::unordered_map<std::string, server_info_weakptr_type> SvrInfosType;
    typedef std::unordered_map<std::string, SvrInfosType> SvrsType;
    SvrsType svrs_;
    std::unordered_map<uint32_t, server_info_ptr_type> svr_instance_ids_;

    user_event user_event_;
};

template<typename ClientStreamType>
class net_stream<ClientStreamType, void> {
public:
    using c_session_ptr_type = typename ClientStreamType::session_ptr_type;
    using c_session_weakptr_type = typename ClientStreamType::session_weakptr_type;
    using header_type = typename ClientStreamType::header_type;

    // In gcc12, expanding parameters in a coroutine function causes an exception, 
    // so this struct is defined to pass the parameters
    struct conn_params {
        c_session_ptr_type sptr;
        std::string host;
        std::string port;
    };
public:
    explicit net_stream(const bnet::cli_cfg& cfg)
        : cli_(cfg) {
        cli_.start();
        init_cb();
    }

    ~net_stream() {
        cli_.stop();
    }

    inline async_simple::coro::Lazy<std::error_code>
    connect(conn_params& p) {
        callback_awaitor<std::error_code> awaitor;
        co_return co_await awaitor.await_resume([&](auto handler) {
            cli_.template add(p.host, p.port, [handler](std::exception_ptr ex, error_code ec) { 
				handler.set_value_then_resume(ec);
    	    }, &p.sptr);
        });
    }

    template <typename... Args>
    inline std::error_code
    sync_connect(Args &&...args) {
        return async_simple::coro::syncAwait(connect(std::forward<Args>(args)...));
    }

    inline auto& get_cli_stream() { return cli_; }
    inline auto& get_agent_mgr() { return agent_mgr_; }

protected:
    void init_cb() {
        cli_.bind(event::connect, [this](const c_session_ptr_type& sptr) {
            auto exe = std::make_unique<executor_wrapper<>>(sptr->cio().context().get_executor());
            // The ip address and address of the peer party may not 
            // be obtained on the cloud, and needs to be optimized later.
            auto svr_hash = get_hash_key(get_svr_key(sptr->remote_address(), sptr->remote_port()));
            auto cli_hash = get_hash_key(get_cli_key(sptr->local_address(), sptr->local_port()));
            auto agent_id = gen_agent_id(svr_hash, cli_hash);
		    auto* agent = agent_mgr_.add_agent<proxy>(agent_id, AGENT_TYPE_PROXY, exe.get());
            agent->set_exe(exe);
            agent->set_transfer([this, wptr = c_session_weakptr_type(std::move(sptr))](uint64_t to_id, uint64_t from_id, uint32_t msgid, const std::string& data) {
                header_type head {
                    msg_id: msgid,
                    to_id: to_id,
                    from_id: from_id,
                };
                return cli_.send(wptr.lock(), head, data);
            });
            sptr->user_data(agent);
        });
        cli_.bind(event::disconnect, [this](const c_session_ptr_type& sptr) {
            auto* ret = sptr->template user_data<proxy*>();
            if (!ret) {
                return;
            }
            auto* agent = *ret;
            agent_mgr_.remove_agent(agent->id());
        });
        cli_.set_handle_message([this](header_type& head, const c_session_ptr_type& sptr, const std::string& data) {
            agent_ptr_type to;
            auto to_id = head.to_id;
            if (to_id == 0) {
                auto* dataptr = sptr->template user_data<proxy*>();
                if (!dataptr) {
                    std::cerr << "cli get agent ptr fail" << " , agent_id " <<  to_id << ", msgid " 
                        << head.msg_id << std::endl;
                    return;
                }
                to = *dataptr;
            }
            else {
                to = agent_mgr_.get_agent(to_id);
            }
            
            if (!to) {
                std::cerr << "cli get agent fail" << " , agent_id " <<  to_id << ", msgid " 
                    << head.msg_id << std::endl;
                return;
            }
            auto ret = agent_mgr_.enqueue(to, head.from_id, head.msg_id, data);
            if (ret == com_errors::success) {
                return;
            }
            std::cerr << "cli handle msg failure" << " , agent_id " << to_id << ", msgid " 
                    << head.msg_id << ", ret " << ret << std::endl;
            return;
        });
    }
private:
    agent_mgr_type agent_mgr_;
    ClientStreamType cli_;
};

} // namespace net
} // namespace modules