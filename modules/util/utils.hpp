#pragma once

#include <async_simple/Executor.h>
#include "function_name.hpp"
#include "magic_names.hpp"
#include "md5_constexpr.hpp"

namespace modules {
template <typename Arg, typename Derived>
class callback_awaitor_base {
private:
    template <typename Op>
    class callback_awaitor_impl {
    public:
        callback_awaitor_impl(Derived &awaitor, const Op &op) noexcept
            : awaitor(awaitor), op(op) {}
        constexpr bool await_ready() const noexcept { return false; }
        void await_suspend(std::coroutine_handle<> handle) noexcept {
            awaitor.coro_ = handle;
            op(awaitor_handler{&awaitor});
        }
        auto coAwait(async_simple::Executor *executor) const noexcept {
            return *this;
        }
        decltype(auto) await_resume() noexcept {
            if constexpr (std::is_void_v<Arg>) {
                return;
            }
            else {
                return std::move(awaitor.arg_);
            }
        }

    private:
        Derived &awaitor;
        const Op &op;
    };

public:
    class awaitor_handler {
    public:
        awaitor_handler(Derived *obj) : obj(obj) {}
        awaitor_handler(awaitor_handler &&) = default;
        awaitor_handler(const awaitor_handler &) = default;
        awaitor_handler &operator=(const awaitor_handler &) = default;
        awaitor_handler &operator=(awaitor_handler &&) = default;
        template <typename... Args>
        void set_value_then_resume(Args &&...args) const {
            set_value(std::forward<Args>(args)...);
            resume();
        }
        template <typename... Args>
        void set_value(Args &&...args) const {
            if constexpr (!std::is_void_v<Arg>) {
                obj->arg_ = {std::forward<Args>(args)...};
            }
        }
        void resume() const { obj->coro_.resume(); }
    private:
        Derived *obj;
    };
    template <typename Op>
    callback_awaitor_impl<Op> await_resume(const Op &op) noexcept {
        return callback_awaitor_impl<Op>{static_cast<Derived &>(*this), op};
    }

private:
    std::coroutine_handle<> coro_;
};

template <typename Arg>
class callback_awaitor
    : public callback_awaitor_base<Arg, callback_awaitor<Arg>> {
    friend class callback_awaitor_base<Arg, callback_awaitor<Arg>>;

private:
    Arg arg_;
};

template <>
class callback_awaitor<void>
    : public callback_awaitor_base<void, callback_awaitor<void>> {};
    
template <auto func>
consteval auto func_id() {
  constexpr auto name = get_func_name<func>();
  constexpr auto id =
      MD5::MD5Hash32Constexpr(name.data(), name.length());
  return id;
}

inline auto hash32(const std::string_view str) {
    return MD5::MD5Hash32Constexpr(str.data(), str.length());
}

}  // namespace modules
