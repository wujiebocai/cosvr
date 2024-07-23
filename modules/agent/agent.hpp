#pragma once

#include "util/singleton.hpp"
#include "app/iopool.hpp"
#include "actor.hpp"
#include "protocol/net_protocol.hpp"
#include "router.hpp"
#include "common/error.hpp"

namespace modules {
// Agentid consists of a 32-bit server real column id and a 32-bit agent identifier. 
// The server real column can route the protocol to the corresponding server process, 
// and the identifier can find the corresponding agent in the process, so that agents can 
// communicate with each other.
// The implementation details hide the communication mechanism between agents, so users do 
// not have to care about the communication mechanism and network programming between AGnets.
inline uint64_t gen_agent_id(uint32_t high, uint32_t low) {
    return ((static_cast<uint64_t>(high) << 32) | low);
}

inline uint32_t get_high_by_agent_id(uint64_t agent_id) {
    return static_cast<uint32_t>((agent_id >> 32) & 0xFFFFFFFF);
}

inline uint32_t get_low_by_agent_id(uint64_t agent_id) {
    return static_cast<uint32_t>(agent_id & 0xFFFFFFFF);
}

using router_key_type = uint32_t;
using agent_router_type = agt::msg_router_imp<protocol::net_proto<>, router_key_type, async_simple::coro::Lazy<>>;

namespace agt {
class agent;
using agent_ptr_type = agent*; //std::shared_ptr<agent>;

class agent : public actor, public std::enable_shared_from_this<agent> {
public:
    explicit agent(uint64_t agentid, uint32_t type, executor_wrapper<>* exe, agent_router_type& router) 
        : actor(agentid, type, exe)
        , router_(router) {

        }

    virtual ~agent() {}

    /// @brief Push the protocol to the agent
    /// @param msgid message id
    /// @param data message body
    /// @param from sending source
    /// @param is_strand parallel processing or not 
    /// @return 
    virtual com_errors enqueue(router_key_type msgid, const std::string& data, const agent_ptr_type& from, bool is_strand = true) {
        auto ret = this->router_.check(msgid);
        if (!ret) {
            return com_errors::msg_is_not_exist;
        }

        if (!is_strand) {
            ret = actor::enqueue([self = this->shared_from_this(), msgid, data = std::move(data), from = std::move(from)]() mutable {
                return self->router_.call(msgid, data, self, from);
            });
        }
        else {
            ret = actor::enqueue_strand([self = this->shared_from_this(), msgid, data = std::move(data), from = std::move(from)]() mutable {
                return self->router_.call(msgid, data, self, from);
            });
        }
        if (!ret) {
            return com_errors::enqueue_msg_fail;
        }
        return com_errors::success;
    }

    /// @brief Push the protocol to the agent
    /// @param msgid message id
    /// @param data message body
    /// @param from_id sending source
    /// @param is_strand parallel processing or not 
    /// @return 
    virtual com_errors enqueue(router_key_type msgid, const std::string& data, uint64_t from_id, bool is_strand = true) {
        auto ret = this->router_.check(msgid);
        if (!ret) {
            return com_errors::msg_is_not_exist;
        }

        if (!is_strand) {
            ret = actor::enqueue([self = this->shared_from_this(), msgid, data = std::move(data), from_id]() mutable {
                return self->router_.call(msgid, std::move(data), self, from_id);
            });
        }
        else {
            ret = actor::enqueue_strand([self = this->shared_from_this(), msgid, data = std::move(data), from_id]() mutable {
                return self->router_.call(msgid, std::move(data), self, from_id);
            });
        }
        if (!ret) {
            return com_errors::enqueue_msg_fail;
        }
        return com_errors::success;
    }
    
    virtual bool cancel() { return true; }
private:
    agent_router_type& router_;
    agent_ptr_type next_ = nullptr;
};

template<class T>
concept is_agent_category = std::is_base_of_v<agent, modules::unqualified_t<T>>;

template<is_agent_category T>
inline T* agent_ptr_cast(agent_ptr_type agent) {
    return dynamic_cast<T*>(agent);
}

class agent_mgr {
public:
    /// @brief Push the protocol to the agent
    /// @tparam MsgType (protobuf, json, pod struct)
    /// @param to sending target
    /// @param from sending source
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<is_coder MsgType>
    com_errors enqueue(const agent_ptr_type& to, const agent_ptr_type& from, router_key_type msgid, const MsgType& msg, bool is_strand = true) {
        if (!to) {
            return com_errors::invalid_param;
        }

        std::string buffer;
        if (auto ret = modules::coder::serialize(msg, buffer); !ret) {
            return com_errors::protocol_format_err;
        }

        return to->enqueue(msgid, buffer, from, is_strand);
    }

    com_errors enqueue(const agent_ptr_type& to, const agent_ptr_type& from, router_key_type msgid, const std::string& data, bool is_strand = true) {
        if (!to || msgid <= 0) {
            return com_errors::invalid_param;
        }

        return to->enqueue(msgid, data, from, is_strand);
    }

    /// @brief Push the protocol to the agent
    /// @tparam MsgType (protobuf, json, pod struct)
    /// @param to_id sending target
    /// @param from_id sending source agent id
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<is_coder MsgType>
    com_errors enqueue(const agent_ptr_type& to, uint64_t from_id, router_key_type msgid, const MsgType& msg, bool is_strand = true) {
        if (!to) {
            return com_errors::invalid_param;
        }

        std::string buffer;
        if (auto ret = modules::coder::serialize(msg, buffer); !ret) {
            return com_errors::protocol_format_err;
        }

        return to->enqueue(msgid, buffer, from_id, is_strand);
    }

    com_errors enqueue(const agent_ptr_type& to, uint64_t from_id, router_key_type msgid, const std::string& data, bool is_strand = true) {
        if (!to || msgid <= 0) {
            return com_errors::invalid_param;
        }

        return to->enqueue(msgid, data, from_id, is_strand);
    }

    /// @brief Push the protocol to the agent
    /// @tparam MsgType (protobuf, json, pod struct)
    /// @param to_id sending target agent id
    /// @param from_id sending source agent id
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<is_coder MsgType>
    com_errors enqueue(uint64_t to_id, uint64_t from_id, router_key_type msgid, const MsgType& msg, bool is_strand = true) {
        auto to = get_agent(to_id);
        if (!to) {
            return com_errors::agent_is_not_exist;
        }

        std::string buffer;
        if (auto ret = modules::coder::serialize(msg, buffer); !ret) {
            return com_errors::protocol_format_err;
        }

        return to->enqueue(msgid, buffer, from_id, is_strand);
    }

    com_errors enqueue(uint64_t to_id, uint64_t from_id, router_key_type msgid, const std::string& data, bool is_strand = true) {
        if (msgid <= 0) {
            return com_errors::invalid_param;
        }

        auto to = get_agent(to_id);
        if (!to) {
            return com_errors::agent_is_not_exist;
        }

        return to->enqueue(msgid, data, from_id, is_strand);
    }

    /// @brief Push the protocol to the agent
    /// @tparam MsgType (protobuf, json, pod struct)
    /// @param to_id sending target agent id
    /// @param from sending source
    /// @param msgid message id
    /// @param msg message
    /// @param is_strand parallel processing or not 
    /// @return 
    template<is_coder MsgType>
    com_errors enqueue(uint64_t to_id, const agent_ptr_type& from, router_key_type msgid, const MsgType& msg, bool is_strand = true) {
        auto to = get_agent(to_id);
        if (!to) {
            return com_errors::agent_is_not_exist;
        }

        std::string buffer;
        if (auto ret = modules::coder::serialize(msg, buffer); !ret) {
            return com_errors::protocol_format_err;
        }

        return to->enqueue(msgid, buffer, from, is_strand);
    }

    com_errors enqueue(uint64_t to_id, const agent_ptr_type& from, router_key_type msgid, const std::string& data, bool is_strand = true) {
        if (msgid <= 0) {
            return com_errors::invalid_param;
        }

        auto to = get_agent(to_id);
        if (!to) {
            return com_errors::agent_is_not_exist;
        }

        return to->enqueue(msgid, data, from, is_strand);
    }

    //template <typename F, typename T>
    //void register_handle(F&&f, T&& self) {
    //    auto key = func_id<f>();
    //    this->router_.template bind(key, std::forward<F>(f), std::forward<T>(self));
    //}

    template <typename F, typename T>
    void register_handle(const router_key_type &key, F&& f, T&& self) {
        this->router_.template bind(key, std::forward<F>(f), std::forward<T>(self));
    }

    template <typename F>
    void register_handle(F&& f) {
        auto key = func_id<f>();
        this->router_.template bind(key, std::forward<F>(f));
    }

    template <typename F>
    void register_handle(const router_key_type &key, F&& f) {
        this->router_.template bind(key, std::forward<F>(f));
    }

    template<is_agent_category T, typename... Args>
    inline T* add_agent(uint64_t id, uint32_t type, executor_wrapper<>* exe, Args&&... args) {
        if (!exe) {
            exe = get_global_executor();
        }
        std::unique_lock lock(mutex_);
        auto itr = agents_.find(id);
        if (itr == agents_.end()) {
            auto ptr = std::make_shared<T>(id, type, exe, router_, std::forward<Args>(args)...);
            agents_[id] = ptr;
            return ptr.get();
        }

        return agent_ptr_cast<T>(itr->second.get());
    }

    void remove_agent(uint64_t id) {
        std::unique_lock lock(mutex_);
        agents_.erase(id);
    }

    inline agent_ptr_type get_agent(uint64_t id) {
        std::unique_lock lock(mutex_);
        auto itr = agents_.find(id);
        if (itr == agents_.end()) {
            return nullptr;
        }

        return itr->second.get();
    }

    inline auto& router() { return router_; }
private:
    std::unordered_map<uint64_t, std::shared_ptr<agent>> agents_;
    agent_router_type router_;
    std::mutex mutex_;
};

} // namespace agt

using agent_type = typename agt::agent;
using agent_ptr_type = typename agt::agent_ptr_type;
using agent_mgr_type = typename agt::agent_mgr;

} // namespace modules