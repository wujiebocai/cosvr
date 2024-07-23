#pragma once

#include "bnet.hpp"
#include "protocol/rpc_protocol.hpp"
#include "rpc_router.hpp"
#include "config.hpp"
#include "error/error.hpp"

namespace modules {
namespace rpc {

using namespace bnet;

class rpc_server : public rpc_svr<protocol::rpc_proto> {
public:
    using super_type = rpc_svr<protocol::rpc_proto>;
    using session_ptr_type = typename super_type::session_ptr_type;
    using key_type = typename super_type::session_type::key_type;
    using protocol_type = protocol::rpc_proto;
    using context_data_type = context_data<session_ptr_type>;
    using context_data_ptr_type = std::shared_ptr<context_data_type>;
    
    explicit rpc_server(const rpc_server_config& cfg)  : super_type(cfg) {
        this->bind(event::connect, &rpc_server::connect_cb, this);
        this->bind(event::disconnect, &rpc_server::disconnect_cb, this);
        this->bind(event::recv, &rpc_server::recv_cb, this);
    }

    template <auto first, auto... functions>
    void register_handler(class_type_t<decltype(first)> *self) {
        this->router_.template register_handler<first, functions...>(self);
    }

    template <auto first>
    void register_handler(class_type_t<decltype(first)> *self, const auto &key) {
        this->router_.template register_handler<first>(self, key);
    }

    template <auto... functions>
    void register_handler() {
        this->router_.template register_handler<functions...>();
    }

    template <auto func>
    void register_handler(const auto &key) {
        this->router_.template register_handler<func>(key);
    }

    inline async_simple::coro::Lazy<error>
    start() {
        callback_awaitor<error> awaitor;
        co_return co_await awaitor.await_resume([&](auto handler) {
            super_type::template start([handler](std::exception_ptr ex, bool ret) { 
                com_errors err = success;
                if (!ret) {
                    err = init_error;
                }
				handler.set_value_then_resume(err);
    	    });
        });
    }

private:
    inline void connect_cb([[maybe_unused]]session_ptr_type& ptr) {
		std::cout << "rpc server connect success" << std::endl;
	}

    inline void disconnect_cb([[maybe_unused]]session_ptr_type& ptr, error_code ec) {
		std::cout << "rpc server disconnect" << ec.message() << std::endl;
	}

    inline void recv_cb([[maybe_unused]]session_ptr_type& ptr, error_code ec, const protocol_type::req_header& header, std::string_view&& s) {
		handle_recv(ptr, ec, header, std::move(s)).start([](async_simple::Try<void> out){});
	}

    inline async_simple::coro::Lazy<void>
    handle_recv(session_ptr_type& ptr, error_code ec, const protocol_type::req_header& header, std::string_view&& payload) {
        context_data_type context_data(ptr);

        auto key = header.function_id;
        auto handler = router_.get_handler(key);

        std::pair<std::errc, std::string> ret;
        if (!handler) {
            auto coro_handler = router_.get_coro_handler(key);
            ret = co_await router_.route_coro(coro_handler, payload, context_data, key);
        }
        else {
            ret = router_.route(handler, payload, context_data, key);
        }

        if (context_data.is_delay_) co_return;
        
        auto &[resp_err, resp_buf] = ret;
        ptr->response(resp_err, resp_buf);
    }

private:
    // context_data_type and rpc_context_tpl template parameters need to be changed together
    rpc_router<protocol::rpc_proto, context_data_type> router_;
};

}   // namespace rpc
}   // namespace modules