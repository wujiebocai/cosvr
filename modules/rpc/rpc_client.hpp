#pragma once

#include <bnet.hpp>
#include <async_simple/coro/Lazy.h>
#include <util/utils.hpp>
#include "util.hpp"
#include "protocol/rpc_protocol.hpp"
#include "config.hpp"

namespace modules {
namespace rpc {

using namespace bnet;

class rpc_client : public rpc_cli<protocol::rpc_proto> {
public:
    using super_type = rpc_cli<protocol::rpc_proto>;
    using session_ptr_type = typename super_type::session_ptr_type;
    using protocol_type = protocol::rpc_proto;

    explicit rpc_client(const rpc_client_config& cfg)  : super_type(cfg) {
        this->bind(event::connect, &rpc_client::connect_cb, this);
        this->bind(event::disconnect, &rpc_client::disconnect_cb, this);
    }

    template<auto func, class... Args>
    inline async_simple::coro::Lazy<rpc_result<decltype(get_return_type<func>())>>
    call(Args&&... args) {
        using func_ret_type = decltype(get_return_type<func>());
        using ret_type = rpc_result<func_ret_type>;

        static_check<func, Args...>();

        auto sptr = this->globalctx().sessions_.rand_get();
        if (!sptr || !sptr->is_started()) AS_UNLIKELY {
            std::cerr << "rpc client has been closed, please wait re-connect" << std::endl;
            co_return ret_type{
                unexpect_t{}, 
                error{
                    io_error,
                    "rpc client has been closed, please wait re-connect"}
            };
        }
        
        ret_type fret{};
        auto funcid = func_id<func>();
        auto ec = co_await coro_request(sptr, fret, funcid, std::forward<Args>(args)...);
        if (ec) {
            co_return ret_type{ 
                unexpect_t{}, 
                error{ io_error, ec.message()}
            };
        }

        co_return fret;
    }

    template <auto func, typename... Args>
    rpc_result<decltype(get_return_type<func>())> sync_call(Args &&...args) {
        return async_simple::coro::syncAwait(
            call<func>(std::forward<Args>(args)...));
    }

    inline async_simple::coro::Lazy<error>
    start() {
        auto pool_size = this->globalctx().cli_cfg_.pool_size;
        auto host = this->globalctx().cli_cfg_.host;
        auto port = this->globalctx().cli_cfg_.port;
        super_type::start();

        for (size_t i = 0; i < pool_size; i++) {
            auto err = co_await this->add(host, port);
            if (err) {
                co_return err;
            }
        }

        co_return no_error;
    }

private:
    template<typename Ret, typename... Args>
    inline async_simple::coro::Lazy<std::error_code>
    coro_request(const session_ptr_type& sptr, rpc_result<Ret>& ret, Args&&... args) {
        callback_awaitor<std::error_code> awaitor;
        co_return co_await awaitor.await_resume([&](auto handler) {
            sptr->request([&, handler](const session_ptr_type& ptr, error_code ec, const protocol_type::rsp_header& header, const std::string_view& s) {
                if (!ec) AS_UNLIKELY {
                    if constexpr (!std::is_void_v<Ret>) {
                        Ret r;
                        if (!protocol_type::deserialize(s, r)) AS_UNLIKELY {
                            ec = asio::error::invalid_argument; //std::errc::invalid_argument;
                        }
                        ret = r;
                    }
                }

                handler.set_value_then_resume(ec);
            }, std::forward<Args>(args)...);
        });
    }

    inline async_simple::coro::Lazy<error>
    add(std::string_view host, std::string_view port) {
        callback_awaitor<error> awaitor;
        co_return co_await awaitor.await_resume([&](auto handler) {
            super_type::template add(host, port, [handler](std::exception_ptr ex, error_code ec) { 
				handler.set_value_then_resume(error(std::move(ec)));
    	    });
        });
    }

    inline void connect_cb([[maybe_unused]]session_ptr_type& ptr) {
		std::cout << "rpc client connect success" << std::endl;
	}

    inline void disconnect_cb([[maybe_unused]]session_ptr_type& ptr, error_code ec) {
		std::cout << "rpc client disconnect" << ec.message() << std::endl;
	}
};

}   // rpc
}   // modules