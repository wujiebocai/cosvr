#pragma once

#include <bnet.hpp>
#include <async_simple/coro/Lazy.h>
#include <async_simple/coro/SyncAwait.h>
#include <util/utils.hpp>
namespace modules {
namespace rds {

using namespace bnet;

template<typename SessionType>
class execute_imp {
public:
    using session_ptr_type = std::shared_ptr<SessionType>;
    using session_weakptr_type = std::weak_ptr<SessionType>;
    
    explicit execute_imp(const session_ptr_type& sptr, const std::string& host, const std::string& port,
                        const std::string& username, const std::string& password, int protocol_version)  
        : sptr_(sptr)
        , host_(host)
        , port_(port)
        , username_(username)
        , password_(password)
        , protocol_version_(protocol_version) {}

    ~execute_imp() { sptr_->stop(); }

    template<class... Args>
    inline async_simple::coro::Lazy<object>
    execute(Args... args) {
        constexpr auto args_num = sizeof...(args); 

        object objret;
        if constexpr (args_num <= 0) {
            co_return objret.set_err(invalid_param);
        }

        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY {
            std::cout << "redis client has been closed, please wait re-connect" << std::endl;
            if (auto ret = co_await this->session_ready(); ret != com_errors::success) {
                co_return objret.set_err(ret);
            }
        }

        // ((std::cout << "cmd: " << args << std::endl), ...); 
        std::string cmd;
        pack_args(cmd, std::forward<Args>(args)...);
        auto ec = co_await request(sptr_, objret, cmd);
        if (ec) {
            co_return objret.set_err(io_error);
        }

        co_return objret;
    }

    inline async_simple::coro::Lazy<object>
    execute(const std::vector<std::string>& args) {
        const auto args_num = args.size(); 

        object objret;
        if (args_num <= 0) {
            co_return objret.set_err(invalid_param);
        }

        if (!sptr_ || !sptr_->is_started()) AS_UNLIKELY {
            std::cout << "redis client has been closed, please wait re-connect" << std::endl;
            if (auto ret = co_await this->session_ready(); ret != com_errors::success) {
                co_return objret.set_err(ret);
            }
        }

        // ((std::cout << "cmd: " << args << std::endl), ...); 
        std::string cmd;
        resp_parse::encode(args, cmd);
        auto ec = co_await request(sptr_, objret, cmd);
        if (ec) {
            co_return objret.set_err(io_error);
        }

        co_return objret;
    }

    inline async_simple::coro::Lazy<com_errors>
    session_ready() {
        if (!sptr_) {
            co_return invalid_data;
        }

        if (sptr_->is_started()) {
            co_return success;
        }

        if (!sptr_->is_stopped()) {
            co_return connecting_unable_operate;
        }
        
        auto ec = co_await session_start(sptr_);
        if (ec) {
            co_return connect_fail;
        }
        if (auto ret = co_await this->auth(sptr_); !ret) {
            co_return auth_fail;
        }
        if (auto ret = co_await this->switch_resp(sptr_); !ret) {
            co_return switch_protocol_fail;
        }
        co_return success;
    }

private:
    template<typename... Args>
    inline async_simple::coro::Lazy<std::error_code>
    request(const session_ptr_type& sptr, object& ret, Args&&... args) {
        callback_awaitor<std::error_code> awaitor;
        co_return co_await awaitor.await_resume([&](auto handler) {
            sptr->request([&, handler](const session_ptr_type& ptr, error_code ec, const rds::object& result) {
                if (!ec) {
                    ret = std::move(result);
                }
                handler.set_value_then_resume(ec);
            }, std::forward<Args>(args)...);
        });
    }

    inline async_simple::coro::Lazy<std::error_code>
    session_start(const session_ptr_type& sptr) {
        callback_awaitor<std::error_code> awaitor;
        co_return co_await awaitor.await_resume([&](auto handler) {
            sptr->template start(host_, port_, [handler](std::exception_ptr ex, error_code ec) { 
				handler.set_value_then_resume(ec);
    	    });
        });
    }

    inline async_simple::coro::Lazy<bool>
    auth(const session_ptr_type& sptr) {
        if (password_.size() <= 0) {
            co_return true;
        }
        
        object obj;
        if (username_.size() <= 0) {
            obj = co_await this->execute("auth", password_);
        }
        else {
            obj = co_await this->execute("auth", username_, password_);
        }

        if (!obj.is_valide()) {
            std::cerr << "auth fail. errmsg: " << obj.errmsg() << std::endl;
            co_return false;
        }
        
        if ((std::string&)obj != "OK") AS_UNLIKELY {
            std::cerr << "auth fail. obj: " << (std::string&)obj << std::endl;
            co_return false;
        }
        
        co_return true;
    }

    inline async_simple::coro::Lazy<bool>
    switch_resp(const session_ptr_type& sptr) {
        if (protocol_version_ == 3) {
            auto ret = co_await this->execute("hello", 3);
            if (!ret.is_valide()) {
                std::cerr << "switch resp fail. errmsg: " << ret.errmsg() << std::endl;
                co_return false;
            }
        }

        co_return true;
    }

private:
    session_ptr_type sptr_;
    std::string host_;
    std::string port_;
    std::string username_;
    std::string password_;
    int protocol_version_;
};

} // namespace rds
} // namespace modules