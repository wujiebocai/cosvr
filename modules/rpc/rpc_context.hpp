#pragma once

#include <memory>
#include <async_simple/coro/Lazy.h>

namespace modules {
namespace rpc {
template <typename session_ptr_type>
struct context_data {
    constexpr static size_t body_default_size_ = 256;
    session_ptr_type conn_;
    //typename Protocol::req_header req_head_;
    //std::vector<char> body_;
    std::atomic<bool> has_response_ = false;
    bool is_delay_ = false;
    context_data(session_ptr_type conn)
        : conn_(std::move(conn)) {}
};

template <typename RetType, typename ContextDataType>
class rpc_context_tpl {
public:
    rpc_context_tpl(ContextDataType& context_info)
        : ctx_info_(context_info) {
        //if (ctx_info_->conn_) {
        //  ctx_info_->conn_->set_call_type(
        //      coro_connection::call_type::callback_started);
        //}
        ctx_info_.has_response_ = false;
    };
    rpc_context_tpl() = default;

    using return_type = RetType;

    template <typename... Args>
    void response(Args &&...args) {
        auto old_flag = ctx_info_.has_response_.exchange(true);
        if (old_flag != false) AS_UNLIKELY {
            std::cerr << "response message more than one time" << std::endl;
            return;
        }

        if (!is_started()) AS_UNLIKELY {
            std::cout << "response_msg failed: connection has been closed" << std::endl;
            return;
        }

        if constexpr (std::is_same_v<RetType, void>) {
            static_assert(sizeof...(args) == 0, "illegal args");

            ctx_info_.conn_->template response(std::errc{}, "");
        }
        else {
            static_assert(
                requires { RetType{std::forward<Args>(args)...}; },
                "constructed RetType failed by illegal args");
            RetType ret{std::forward<Args>(args)...};

            ctx_info_.conn_->template response(ret);
        }
    }

    bool is_started() const { return ctx_info_.conn_->is_started(); }

    void is_delay() { return ctx_info_.is_delay_; }
    void is_delay(bool isdelay) { ctx_info_.is_delay_ = isdelay; }

    template <typename T>
    inline void user_data(T &&tag) {
        ctx_info_.conn_->user_data(std::forward<T>(tag));
    }

    template <typename T>
    inline auto user_data() { return ctx_info_.conn_->template user_data<T>(); }
protected:
    ContextDataType& ctx_info_;
};

}   // rpc
}   // modules