#pragma once

#include <optional>
#include <async_simple/coro/Lazy.h>
#include <async_simple/coro/SyncAwait.h>
#include <util/utils.hpp>
#include "net.hpp"
#include "resp.hpp"

// https://redis.io/commands/subscribe/
// subscribe session only execute:  subscribe, ssubscribe, psubscribe, unsubscribe, sunsubscribe, punsubscribe, ping, reset, quit.
// if RESP3 is used (see HELLO) it is possible for a client to issue any commands while in subscribed state.

namespace modules {
namespace rds {
using sub_cbfunc_type = std::function<void(const std::string&, const object&)>;

class pubsub {
public:
    pubsub(const session_ptr_type& ptr, std::string_view host, std::string_view port) 
        : sptr_(std::move(ptr)) 
        , host_(host)
        , port_(port) {}

    ~pubsub() {
        this->stop();
    }

    /*!
     * Subscribes the client to the specified channels.
     *
     * Once the client enters the subscribed state it is not supposed to issue any other commands, 
     * except for additional SUBSCRIBE, SSUBSCRIBE, PSUBSCRIBE, UNSUBSCRIBE, SUNSUBSCRIBE, PUNSUBSCRIBE, PING, RESET and QUIT commands. 
     * However, if RESP3 is used (see HELLO) it is possible for a client to issue any commands while in subscribed state.
     * 
     * >= 6.2.0: RESET can be called to exit subscribed state.
     * 
     * When successful, this command doesn't return anything. Instead, for each channel, 
     * one message with the first element being the string subscribe is pushed as a confirmation that the command succeeded.
    */
    template<typename... Args>
    inline async_simple::coro::Lazy<com_errors>
    subscribe(const sub_cbfunc_type& f, Args&&... args) {
        constexpr auto args_num = sizeof...(args); 
        if (!f || args_num <= 0) {
            co_return invalid_param;
        }

        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY { 
            co_return connect_fail;
        }

        std::vector<std::string> vecs;
        args_to_vec(vecs, "subscribe", std::forward<Args>(args)...);
        auto* sub_pre = get_sub_pre("subscribe");
        if (!sub_pre) {
            co_return invalid_data;
        }
        for(size_t idx = 1; idx < vecs.size(); idx++) {
            (*sub_pre)[vecs[idx]] = f;
        }
        std::string cmd;
        resp_parse::encode(vecs, cmd);
        auto ret = co_await this->send(cmd);
        if (ret) {
            co_return io_error;
        }
        sptr_->monitor();

        co_return success;
    }

    /*!
     * Unsubscribes the client from the given channels, or from all of them if none is given.
     * When no channels are specified, the client is unsubscribed from all the previously subscribed channels. 
     * In this case, a message for every unsubscribed channel will be sent to the client.
    */
    template<class... Args>
    inline async_simple::coro::Lazy<com_errors>
    unsubscribe(Args&&... args) {
        constexpr auto args_num = sizeof...(args); 
        if (args_num <= 0) {
            co_return invalid_param;
        }

        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY { 
            co_return connect_fail;
        }

        std::string cmd;
        pack_args(cmd, "unsubscribe", std::forward<Args>(args)...);
        auto ret = co_await this->send(cmd);
        if (ret) {
            co_return io_error;
        }

        co_return success;
    }

    /*!
     * Subscribes the client to the specified shard channels.
     *
     * In a Redis cluster, shard channels are assigned to slots by the same algorithm used to assign keys to slots. 
     * Client(s) can subscribe to a node covering a slot (primary/replica) to receive the messages published. 
     * All the specified shard channels needs to belong to a single slot to subscribe in a given SSUBSCRIBE call, 
     * A client can subscribe to channels across different slots over separate SSUBSCRIBE call.
     * 
     * When successful, this command doesn't return anything. Instead, for each shard channel, 
     * one message with the first element being the string 'ssubscribe' is pushed as a confirmation that the command succeeded. 
     * @note that this command can also return a -MOVED redirect.
    */
    template<typename... Args>
    inline async_simple::coro::Lazy<com_errors>
    ssubscribe(const sub_cbfunc_type& f, Args&&... args) {
        constexpr auto args_num = sizeof...(args); 
        if (!f || args_num <= 0) {
            co_return invalid_param;
        }

        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY { 
            co_return connect_fail;
        }

        std::vector<std::string> vecs;
        args_to_vec(vecs, "ssubscribe", std::forward<Args>(args)...);
        auto* sub_pre = get_sub_pre("ssubscribe");
        if (!sub_pre) {
            co_return invalid_data;
        }
        for(size_t idx = 1; idx < vecs.size(); idx++) {
            (*sub_pre)[vecs[idx]] = f;
        }
        std::string cmd;
        resp_parse::encode(vecs, cmd);
        auto ret = co_await this->send(cmd);
        if (ret) {
            co_return io_error;
        }
        sptr_->monitor();

        co_return success;
    }

    /*!
     * Unsubscribes the client from the given shard channels, or from all of them if none is given.
     *
     * When no shard channels are specified, the client is unsubscribed from all the previously subscribed shard channels. 
     * In this case a message for every unsubscribed shard channel will be sent to the client.
     * @note The global channels and shard channels needs to be unsubscribed from separately.
     * 
     * When successful, this command doesn't return anything. Instead, for each shard channel, 
     * one message with the first element being the string sunsubscribe is pushed as a confirmation that the command succeeded.
    */
    template<class... Args>
    inline async_simple::coro::Lazy<com_errors>
    sunsubscribe(Args&&... args) {
        constexpr auto args_num = sizeof...(args); 
        if (args_num <= 0) {
            co_return invalid_param;
        }

        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY { 
            co_return connect_fail;
        }

        std::string cmd;
        pack_args(cmd, "sunsubscribe", std::forward<Args>(args)...);
        auto ret = co_await this->send(cmd);
        if (ret) {
            co_return io_error;
        }

        co_return success;
    }

    /*!
     * Subscribes the client to the given patterns.
     *
     * Supported glob-style patterns:
     * h?llo subscribes to hello, hallo and hxllo
     * h*llo subscribes to hllo and heeeello
     * h[ae]llo subscribes to hello and hallo, but not hillo
     * Use \ to escape special characters if you want to match them verbatim.
     * 
     * Once the client enters the subscribed state it is not supposed to issue any other commands, 
     * except for additional SUBSCRIBE, SSUBSCRIBE, PSUBSCRIBE, UNSUBSCRIBE, SUNSUBSCRIBE, PUNSUBSCRIBE, PING, RESET and QUIT commands. 
     * However, if RESP3 is used (see HELLO) it is possible for a client to issue any commands while in subscribed state.
     * 
     * >= 6.2.0: RESET can be called to exit subscribed state.
     * 
     * When successful, this command doesn't return anything. Instead, for each pattern, 
     * one message with the first element being the string psubscribe is pushed as a confirmation that the command succeeded.
     * @note Do not use this interface for the time being. Pattern matching is yet to be implemented
    */
    template<typename... Args>
    inline async_simple::coro::Lazy<com_errors>
    psubscribe(const sub_cbfunc_type& f, Args&&... args) {
        constexpr auto args_num = sizeof...(args); 
        if (!f || args_num <= 0) {
            co_return invalid_param;
        }

        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY { 
            co_return connect_fail;
        }

        std::vector<std::string> vecs;
        args_to_vec(vecs, "psubscribe", std::forward<Args>(args)...);
        auto* sub_pre = get_sub_pre("psubscribe");
        if (!sub_pre) {
            co_return invalid_data;
        }
        for(size_t idx = 1; idx < vecs.size(); idx++) {
            (*sub_pre)[vecs[idx]] = f;
        }
        std::string cmd;
        resp_parse::encode(vecs, cmd);
        auto ret = co_await this->send(cmd);
        if (ret) {
            co_return io_error;
        }
        sptr_->monitor();

        co_return success;
    }

    /*!
     * Unsubscribes the client from the given patterns, or from all of them if none is given.
     * When no patterns are specified, the client is unsubscribed from all the previously subscribed patterns. 
     * In this case, a message for every unsubscribed pattern will be sent to the client.
     * 
     * When successful, this command doesn't return anything. Instead, for each pattern, 
     * one message with the first element being the string punsubscribe is pushed as a confirmation that the command succeeded.
     * @note Do not use this interface for the time being. Pattern matching is yet to be implemented
    */
    template<class... Args>
    inline async_simple::coro::Lazy<com_errors>
    punsubscribe(Args&&... args) {
        constexpr auto args_num = sizeof...(args); 
        if (args_num <= 0) {
            co_return invalid_param;
        }

        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY { 
            co_return connect_fail;
        }

        std::string cmd;
        pack_args(cmd, "punsubscribe", std::forward<Args>(args)...);
        auto ret = co_await this->send(cmd);
        if (ret) {
            co_return io_error;
        }

        co_return success;
    }

    inline async_simple::coro::Lazy<com_errors>
    ping() {
        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY { 
            co_return connect_fail;
        }

        std::string cmd;
        pack_args(cmd, "ping");
        auto ret = co_await this->send(cmd);
        if (ret) {
            co_return io_error;
        }

        co_return success;
    }

    inline async_simple::coro::Lazy<com_errors>
    reset() {
        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY { 
            co_return connect_fail;
        }

        std::string cmd;
        pack_args(cmd, "reset");
        auto ret = co_await this->send(cmd);
        if (ret) {
            co_return io_error;
        }

        co_return success;
    }

    inline async_simple::coro::Lazy<com_errors>
    quit() {
        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY { 
            co_return connect_fail;
        }

        std::string cmd;
        pack_args(cmd, "quit");
        auto ret = co_await this->send(cmd);
        if (ret) {
            co_return io_error;
        }

        co_return success;
    }
    
private:
    friend class pubsub_mgr;

    // handling the events
    inline bool monitor(const object& obj) {
        if (!obj.is_valide() || obj.type_ != REDIS_TYPE_ARRAY) {
            std::cout << "is not the result of a publish-subscribe operation. type_: " << static_cast<int>(obj.type_) << std::endl;
            return false;
        }
        const std::vector<object>& arr = obj;
        if (arr.size() != 3 && arr.size() != 4) {
            std::cerr << "redis pubsub data invalid. size: " << arr.size() << std::endl;
            return false;
        }
        const std::string& event = arr[0];
        const std::string& channal = arr[1];
        const object& val = arr.back();
        auto* sub_pre = get_sub_pre(event);
        if (!sub_pre) {
            return false;
        }
        auto* sub_ctx = get_sub_ctx(event);
        if (!sub_ctx) {
            return false;
        }
        if (event == "subscribe" || event == "ssubscribe" || event == "psubscribe") {
            auto snum = val.value<int>();
            if (const auto& itr = sub_pre->find(channal); itr != sub_pre->end()) {
                (*sub_ctx)[channal] = std::move(itr->second);
                sub_pre->erase(channal);
                std::cout << event << " " << channal << " success. current subscript num: " << snum << std::endl;
            }
            else if (const auto& itr = sub_ctx->find(channal); itr != sub_ctx->end()) {
                std::cout << event << " " << channal << " repeat subscription. current subscript num: " << snum << std::endl;
            }
            else {
                std::cerr << event << " " << channal << " error. current subscript num: " << snum << std::endl;
            }
            return true;
        }
        else if (event == "unsubscribe" || event == "sunsubscribe" || event == "punsubscribe") {
            auto snum = val.value<size_t>();
            if (const auto& itr = sub_pre->find(channal); itr != sub_pre->end()) {
                std::cout << event << " " << channal << " success. current subscript num: " << snum << std::endl;
                sub_pre->erase(channal);
            }
            else if (const auto& itr = sub_ctx->find(channal); itr != sub_ctx->end()) {
                std::cout << event << " " << channal << " success. current subscript num: " << snum << std::endl;
                sub_ctx->erase(channal);
            }
            else {
                std::cout << event << " " << channal << " success; this channel is not subscribed, no need to unsubscribe. current subscript num: " << snum << std::endl;
            }
            return true;
        }
        else if (event == "message" || event == "smessage" || event == "pmessage") {
            if (const auto& itr = sub_ctx->find(channal); itr != sub_ctx->end()) {
                itr->second(channal, val);
            }
            else {
                std::cout << event << " " << channal << "  error. not subscribed, error" << std::endl;
            }
            return true;
        }
        else {
            // std::cerr << event << " event is not currently handled, channel " << channal << std::endl;
            return false;
        }
    }

    inline async_simple::coro::Lazy<com_errors>
    session_ready(const std::string& username, const std::string& password, int protocol_version) {
        if (!sptr_) {
            co_return invalid_param;
        }
        
        auto ec = co_await session_start();
        if (ec) {
            co_return connect_fail;
        }
        if (auto ret = co_await this->auth(username, password); !ret) {
            co_return auth_fail;
        }
        //if (auto ret = co_await this->switch_resp(protocol_version); !ret) {
        //    co_return switch_protocol_fail;
        //}
        co_return success;
    }

    template<typename... Args>
    inline async_simple::coro::Lazy<std::error_code>
    request(object& ret, Args&&... args) {
        callback_awaitor<std::error_code> awaitor;
        co_return co_await awaitor.await_resume([&](auto handler) {
            sptr_->request([&, handler](const session_ptr_type& ptr, error_code ec, const rds::object& result) {
                if (!ec) {
                    ret = std::move(result);
                }
                handler.set_value_then_resume(ec);
            }, std::forward<Args>(args)...);
        });
    }

    template<typename... Args>
    inline async_simple::coro::Lazy<std::error_code>
    send(Args&&... args) {
        callback_awaitor<std::error_code> awaitor;
        co_return co_await awaitor.await_resume([&](auto handler) {
            sptr_->send([&, handler](error_code ec) {
                handler.set_value_then_resume(ec);
            }, std::forward<Args>(args)...);
        });
    }

    inline async_simple::coro::Lazy<std::error_code>
    session_start() {
        callback_awaitor<std::error_code> awaitor;
        co_return co_await awaitor.await_resume([&](auto handler) {
            sptr_->template start(host_, port_, [handler](std::exception_ptr ex, error_code ec) { 
				handler.set_value_then_resume(ec);
    	    });
        });
    }

    inline void stop(const error_code& ec = ec_ignore) {
        sptr_->stop(ec);
        if (stop_callback_) {
            stop_callback_(sptr_->hash_key());
        }
    }

    inline async_simple::coro::Lazy<bool>
    auth(const std::string& username, const std::string& password) {
        if (password.size() <= 0) {
            co_return true;
        }
        
        object obj;
        std::string cmd;
        if (username.size() <= 0) {
            pack_args(cmd, "auth", password);
        }
        else {
            pack_args(cmd, "auth", username, password);
        }

        auto ec = co_await this->request(obj, cmd);
        if (ec) {
            co_return false;
        }

        if (!obj.is_valide()) {
            std::cerr << "auth fail. " << std::endl;
            co_return false;
        }
        
        if ((std::string&)obj != "OK") AS_UNLIKELY {
            std::cerr << "auth fail. obj: " << (std::string&)obj << std::endl;
            co_return false;
        }
        
        co_return true;
    }

    inline async_simple::coro::Lazy<bool>
    switch_resp(int protocol_version) {
        if (protocol_version == 3) {
            object obj;
            std::string cmd;
            pack_args(cmd, "hello", 3);
            auto ec = co_await this->request(obj, cmd);
            if (ec) {
                std::cerr << "switch resp fail." << std::endl;
                co_return false;
            }
        }

        co_return true;
    }

    using stop_callback_type = std::function<void(const key_type& key)>;
    void set_stop_callback(stop_callback_type callback) {
        stop_callback_ = std::move(callback);
    }

    inline int32_t event_to_idx(const std::string_view event) {
        if (event == "subscribe" || event == "unsubscribe" || event == "message") return 0;
        if (event == "ssubscribe" || event == "sunsubscribe" || event == "smessage") return 1;
        if (event == "psubscribe" || event == "punsubscribe" || event == "pmessage") return 2;

        return -1;
    }

    typedef std::unordered_map<std::string, sub_cbfunc_type> sub_ctx_map_type;
    typedef std::array<sub_ctx_map_type, 3> all_sub_ctx_map_type;
    sub_ctx_map_type* get_sub_ctx(const std::string_view event) {
        auto idx = event_to_idx(event);
        if (idx < 0) return nullptr;

        return &sub_ctxs_[idx];
    }

    sub_ctx_map_type* get_sub_pre(const std::string_view event) {
        auto idx = event_to_idx(event);
        if (idx < 0) return nullptr;

        return &sub_pres_[idx];
    }
private:
    const session_ptr_type sptr_;
    const std::string host_;
    const std::string port_;
    all_sub_ctx_map_type sub_ctxs_;
    all_sub_ctx_map_type sub_pres_;
    stop_callback_type stop_callback_;
};

class pubsub_mgr {
public:
    using pubsub_ptr_type = std::shared_ptr<pubsub>;
    using pubsub_weak_ptr_type = std::weak_ptr<pubsub>;

    explicit pubsub_mgr(rds_net_type* net, const redis_config& cfg)  
        : net_(net)
        , cfg_(cfg) {
        net_->bind(event::recv, &pubsub_mgr::recv_cb, this);
    }

    inline async_simple::coro::Lazy<std::optional<pubsub_ptr_type>>
    get_pubsub() {
        const auto& ptr = net_->make_session();
        if (!ptr) {
            co_return std::nullopt;
        }

        if (cfg_.addrs.size() <= 0) {
            std::cerr << "redis pubsub error: the redis server address needs to be configured" << std::endl;
            co_return std::nullopt;
        }

        auto address = cfg_.addrs[0];
        auto host_port = bnet::tool::split(address, ":");
        if (host_port.size() < 2) {
            std::cerr << "redis pubsub error: invalid redis server address" << std::endl;
            co_return std::nullopt;
        }

        auto psptr = std::make_shared<pubsub>(ptr, host_port[0], host_port[1]);
        auto ec = co_await psptr->session_ready(cfg_.username, cfg_.password, cfg_.protocol_version);
        if (ec) {
            std::cout << "redis pubsub error, client connettion fail, errmsg: " << get_com_err_message(ec) << std::endl;
            co_return std::nullopt;
        }

        psptr->set_stop_callback([this](const key_type& key) {
            this->remove_pubsub(key);
        });

        psptrs_[ptr->hash_key()] = psptr;

        co_return psptr;
    }

private:
    inline void remove_pubsub(key_type key) {
        psptrs_.erase(key);
    }

    inline void recv_cb(const session_ptr_type& ptr, const rds::object& obj) {
        const auto& itr = psptrs_.find(ptr->hash_key());
        if (itr != psptrs_.end()) {
            auto psptr = itr->second.lock();
            if (psptr && psptr->monitor(obj)) {
                return;  
            }
        }
        print_object(obj);
	}
private:
    rds_net_type* net_;
    redis_config cfg_;
    std::unordered_map<key_type, pubsub_weak_ptr_type> psptrs_;
};

}   // namespace rds
}   // namespace modules