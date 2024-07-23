#pragma once

#include <string>
#include "config.hpp"
#include "net/net.hpp"
#include "uuid/uuid.hpp"

namespace modules {
using protocol_type = protocol::net_proto<>;
using header_type = typename protocol_type::header_type;
using server_stream_type = net::stream<bnet::tcp_svr, protocol_type, bnet::svr_cfg>;
using client_stream_type = net::stream<bnet::tcp_cli, protocol_type, bnet::cli_cfg>;
using s_session_ptr_type = typename server_stream_type::session_ptr_type;
using s_session_weakptr_type = typename server_stream_type::session_weakptr_type;
using c_session_ptr_type = typename client_stream_type::session_ptr_type;
using c_session_weakptr_type = typename client_stream_type::session_weakptr_type;
using net_stream_type = net::net_stream<client_stream_type, server_stream_type>;
using cli_net_stream_type = net::net_stream<client_stream_type, void>;

class app {
public:
    explicit app(std::string_view svr_type, const app_cfg& cfg)
        : app_cfg_(std::move(cfg)) 
        , svr_type_(svr_type) {
        svr_id_ = gen_uuid(); 
        auto cluster_info = get_server_cluster_info();
        bnet::svr_cfg scfg {
            host: cfg.host,
            port: cfg.port,
            thread_num: cfg.thread_num,
        };
        bnet::cli_cfg ccfg;
        net_ = std::make_shared<net_stream_type>(cluster_info, scfg, ccfg);
    }

    /// @brief Communication between agent  (local or remote, thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param to sending target
    /// @param from sending source
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<typename MsgType>
    inline bool send(const agent_ptr_type& to, const agent_ptr_type& from, uint32_t msgid, MsgType&& msg, bool is_strand = true) {
        return (net_->get_agent_mgr().enqueue(to, from, msgid, msg, is_strand) == com_errors::success);
    }

    /// @brief Communication between agent  (local or remote, thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param to sending target
    /// @param from_id sending source agentid
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<typename MsgType>
    inline bool send(const agent_ptr_type& to, uint64_t from_id, uint32_t msgid, MsgType&& msg, bool is_strand = true) {
        return (net_->get_agent_mgr().enqueue(to, from_id, msgid, msg, is_strand) == com_errors::success);
    }
    
    /// @brief Communication between agent  (local or remote, thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param to_id sending target agentid
    /// @param from_id sending source agentid
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<typename MsgType>
    inline bool send(uint64_t to_id, uint64_t from_id, uint32_t msgid, MsgType&& msg, bool is_strand = true) {
        // 0 indicates that you send the protocol to yourself
        if (to_id == 0) {
            to_id = from_id;
        }

        auto ret = net_->get_agent_mgr().enqueue(to_id, from_id, msgid, msg, is_strand);
        if (ret == com_errors::agent_is_not_exist) {
            auto instance_id = get_high_by_agent_id(to_id);
            return this->send_by_svr_instanceid(instance_id, msgid, msg, to_id, from_id);
        }

        return (ret == com_errors::success);
    }

    /// @brief Communication between agent  (local or remote, thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param to_id sending target agentid
    /// @param from sending source
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<typename MsgType>
    inline bool send(uint64_t to_id, const agent_ptr_type& from, uint32_t msgid, MsgType&& msg, bool is_strand = true) {
        // 0 indicates that you send the protocol to yourself
        if (to_id == 0) {
            return net_->get_agent_mgr().enqueue(from, from, msgid, msg, is_strand);
        }

        auto ret = net_->get_agent_mgr().enqueue(to_id, from, msgid, msg, is_strand);
        if (ret == com_errors::agent_is_not_exist) {
            auto instance_id = get_high_by_agent_id(to_id);
            return this->send_by_svr_instanceid(instance_id, msgid, msg, to_id, from->id());
        }

        return (ret == com_errors::success);
    }

    /// @brief Select a service communication at random based on the service type   (thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param svr_type target server type
    /// @param msgid message id
    /// @param msg message
    /// @param to_id sending target agentid
    /// @param from_id sending source agentid
    /// @return 
    template<typename MsgType>
    inline bool send_by_rand(const std::string& svr_type, uint32_t msgid, MsgType&& msg, uint64_t to_id = 0, uint64_t from_id = 0) {
        auto server_info_ptr = net_->get_svrinfo_by_random(svr_type);
        if (!server_info_ptr) {
            return false;
        }

        auto ptr = server_info_ptr.value()->sptr_.lock();
        if (!ptr) {
            return false;
        }

        header_type head {
            msg_id: msgid,
            to_id: to_id,
            from_id: from_id,
        };
		return net_->get_cli_stream().send(ptr, head, std::forward<MsgType>(msg));
	}

    /// @brief Select a service communication based on the hash value   (thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param svr_type target server type
    /// @param hash hash value
    /// @param msgid message id
    /// @param msg message
    /// @param to_id sending target agentid
    /// @param from_id sending source agentid
    /// @return 
    template<typename MsgType>
    inline bool send_by_hash(const std::string& svr_type, uint32_t hash, uint32_t msgid, MsgType&& msg, uint64_t to_id = 0, uint64_t from_id = 0) {
        auto server_info_ptr = net_->get_svrinfo_by_hash(svr_type, hash);
        if (!server_info_ptr) {
            return false;
        }

        auto ptr = server_info_ptr.value()->sptr_.lock();
        if (!ptr) {
            return false;
        }

        header_type head {
            msg_id: msgid,
            to_id: to_id,
            from_id: from_id,
        };
		return net_->get_cli_stream().send(ptr, head, std::forward<MsgType>(msg));
	}

    /// @brief Select service communications based on the service id    (thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param svr_type target server type
    /// @param svr_id target server id
    /// @param msgid message id
    /// @param data message
    /// @param to_id sending target agentid
    /// @param from_id sending source agentid
    /// @return 
    template<typename MsgType>
    inline bool send_by_svrid(const std::string& svr_type, const std::string& svr_id, uint32_t msgid, MsgType&& msg, uint64_t to_id = 0, uint64_t from_id = 0) {
        auto server_info_ptr = net_->get_svrinfo_by_svrid(svr_type, svr_id);
        if (!server_info_ptr) {
            return false;
        }

        auto ptr = server_info_ptr.value()->sptr_.lock();
        if (!ptr) {
            return false;
        }

        header_type head {
            msg_id: msgid,
            to_id: to_id,
            from_id: from_id,
        };
		return net_->get_cli_stream().send(ptr, head, std::forward<MsgType>(msg));
	}

    /// @brief Select service communications based on the instanceid    (thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param instance_id target server instanceid
    /// @param msgid message id
    /// @param data message body
    /// @param to_id sending target agentid
    /// @param from_agent_id sending source agentid
    /// @return 
    template<typename MsgType>
    inline bool send_by_svr_instanceid(uint32_t instance_id, uint32_t msgid, MsgType&& msg, uint64_t to_id = 0, uint64_t from_id = 0) {
        auto server_info_ptr = net_->get_svrinfo_by_svr_instanceid(instance_id);
        if (!server_info_ptr) {
            return false;
        }

        auto ptr = server_info_ptr.value()->sptr_.lock();
        if (!ptr) {
            return false;
        }

        header_type head {
            msg_id: msgid,
            to_id: to_id,
            from_id: from_id,
        };
		return net_->get_cli_stream().send(ptr, head, std::forward<MsgType>(msg));
	}

    template<typename SessionPtrType, typename MsgType>
    inline bool send_by_session(const SessionPtrType& sptr, uint32_t msgid, MsgType&& msg, uint64_t to_id = 0, uint64_t from_id = 0) {
        if (!sptr) {
            return false;
        }

        header_type head {
            msg_id: msgid,
            to_id: to_id,
            from_id: from_id,
        };
        
        if constexpr (std::is_same_v<SessionPtrType, s_session_ptr_type>) {
            return net_->get_svr_stream().send(sptr, head, std::forward<MsgType>(msg));
        }
        else {
            return net_->get_cli_stream().send(sptr, head, std::forward<MsgType>(msg));
        }
	}

    /// @brief Register protocol handlers
    /// @tparam ...Args 
    /// @param ...args 
    template<typename... Args>
    inline void register_handle(Args&&... args) {
        net_->get_agent_mgr().register_handle(std::forward<Args>(args)...);
    }

    inline auto& get_agent_mgr() { return net_->get_agent_mgr(); }
    inline auto& get_user_event() { return net_->get_user_event(); }

    template<agt::is_agent_category T, typename... Args>
    inline T* create_agent(uint32_t id, uint32_t type, executor_wrapper<>* exe, Args&&... args) {
        auto agent_id = modules::gen_agent_id(net_->get_cluster_info().instance_id, id);
        auto* agent = this->get_agent_mgr().add_agent<T>(agent_id, type, exe, std::forward<Args>(args)...);
        return agent;
    }

    template<agt::is_agent_category T>
    inline T* get_agent(uint64_t agentid) {
        auto agent = this->get_agent_mgr().get_agent(agentid);
        if (agent) {
            return agent_ptr_cast<T>(agent);
        }

        return nullptr;
    }

    inline void remove_agent(uint64_t agentid) {
        this->get_agent_mgr().remove_agent(agentid);
    }

    server_cluster_info get_server_cluster_info() {
        return server_cluster_info {
            id: svr_id_,
            type: svr_type_,
            host: app_cfg_.host,
            port: app_cfg_.port,
            instance_id: get_hash_key(get_svr_key(app_cfg_.host, app_cfg_.port)),
        };
    }

    inline std::string gen_uuid() {
        auto uuid = uuid_t::random();
        return to_string(uuid);
    }

    inline auto& get_net() { return net_; }
private:
    std::string game_name_;
    std::string zone_;
    std::string version_;

    app_cfg app_cfg_;
    std::string svr_type_;
    std::string svr_id_;
    std::shared_ptr<net_stream_type> net_;
};

// Mainly used for testing robots
class client_app {
public:
    explicit client_app(const bnet::cli_cfg& cfg) {
        net_ = std::make_shared<cli_net_stream_type>(cfg);
    }

    inline async_simple::coro::Lazy<std::error_code>
    connect(cli_net_stream_type::conn_params& p) {
        return net_->connect(p);
    }

    template <typename... Args>
    inline auto
    sync_connect(Args &&...args) {
        return net_->sync_connect(std::forward<Args>(args)...);
    }

    /// @brief Register protocol handlers
    /// @tparam ...Args 
    /// @param ...args 
    template<typename... Args>
    inline void register_handle(Args&&... args) {
        net_->get_agent_mgr().register_handle(std::forward<Args>(args)...);
    }

    /// @brief Communication between agent  (local or remote, thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param to sending target
    /// @param from sending source
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<typename MsgType>
    inline bool send(const agent_ptr_type& to, const agent_ptr_type& from, uint32_t msgid, MsgType&& msg, bool is_strand = true) {
        return (net_->get_agent_mgr().enqueue(to, from, msgid, msg, is_strand) == com_errors::success);
    }

    /// @brief Communication between agent  (local or remote, thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param to sending target
    /// @param from_id sending source agentid
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<typename MsgType>
    inline bool send(const agent_ptr_type& to, uint64_t from_id, uint32_t msgid, MsgType&& msg, bool is_strand = true) {
        return (net_->get_agent_mgr().enqueue(to, from_id, msgid, msg, is_strand) == com_errors::success);
    }
    
    /// @brief Communication between agent  (local or remote, thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param to_id sending target agentid
    /// @param from_id sending source agentid
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<typename MsgType>
    inline bool send(uint64_t to_id, uint64_t from_id, uint32_t msgid, MsgType&& msg, bool is_strand = true) {
        // 0 indicates that you send the protocol to yourself
        if (to_id == 0) {
            to_id = from_id;
        }
        return (net_->get_agent_mgr().enqueue(to_id, from_id, msgid, msg, is_strand) == com_errors::success);
    }

    /// @brief Communication between agent  (local or remote, thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param to_id sending target agentid
    /// @param from sending source
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<typename MsgType>
    inline bool send(uint64_t to_id, const agent_ptr_type& from, uint32_t msgid, MsgType&& msg, bool is_strand = true) {
        if (to_id == 0) {
            return (net_->get_agent_mgr().enqueue(from, from, msgid, msg, is_strand) == com_errors::success);
        }
        return (net_->get_agent_mgr().enqueue(to_id, from, msgid, msg, is_strand) == com_errors::success);
    }

    /// @brief Communication base on session  (local or remote, thread-safe)
    /// @tparam MsgType (protobuf, json, pod struct, string)
    /// @param ptr session pointer
    /// @param msgid message id
    /// @param msg message
    /// @param to_id sending target agentid
    /// @param from_id sending source agentid
    /// @return 
    template<typename MsgType>
    inline bool send(const c_session_ptr_type& ptr, uint32_t msgid, MsgType&& msg, uint64_t to_id = 0, uint64_t from_id = 0) {
        if (!ptr) {
            return false;
        }
        
        header_type head {
            msg_id: msgid,
            to_id: to_id,
            from_id: from_id,
        };
        return net_->get_cli_stream().send(ptr, head, std::forward<MsgType>(msg));
    }
    
protected:
    std::shared_ptr<cli_net_stream_type> net_;
};

}   // namespace modules