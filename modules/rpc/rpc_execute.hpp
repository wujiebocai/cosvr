#pragma once
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include "util/type_traits.hpp"
#include "util.hpp"
#include "rpc_context.hpp"

namespace modules::rpc {
// TODO: remove this later
template <bool is_conn, typename First>
auto get_return_type() {
    if constexpr (is_conn) {
        using T = typename First::return_type;
        if constexpr (std::is_void_v<T>) {
            return;
        }
        else {
            return T{};
        }
    }
    else {
        return First{};
    }
}

template <typename Protocol, auto func, typename ContextDataType, typename Self = void>
inline std::optional<std::string> 
execute(std::string_view data, ContextDataType& context_data, Self *self = nullptr) {
    using T = decltype(func);
    using param_type = function_parameters_t<T>;
    using return_type = function_return_type_t<T>;

    if constexpr (!std::is_void_v<param_type>) {
        using First = std::tuple_element_t<0, param_type>;
        constexpr bool is_conn = requires { typename First::return_type; };
        if constexpr (is_conn) {
            static_assert(std::is_void_v<return_type>,
                    "The return_type must be void");
            context_data.is_delay_ = true;
        }

        using conn_return_type = decltype(get_return_type<is_conn, First>());
        constexpr bool has_coro_conn_v =
            std::is_convertible_v<rpc_context_tpl<conn_return_type, ContextDataType>,
            First>;
        auto args = get_args<has_coro_conn_v, param_type>();

        bool is_ok = true;
        constexpr size_t size = std::tuple_size_v<decltype(args)>;
        if constexpr (size > 0) {
            is_ok = Protocol::deserialize(data, std::get<0>(args));
        }

        if (!is_ok) AS_UNLIKELY { return std::nullopt; }

        if constexpr (std::is_void_v<return_type>) {
            if constexpr (std::is_void_v<Self>) {
                if constexpr (has_coro_conn_v) {
                    // call void func(coro_conn, args...)
                    std::apply(func, std::tuple_cat(
                                std::forward_as_tuple(
                                    rpc_context_tpl<conn_return_type, ContextDataType>(context_data)),
                                std::move(args)));
                }
                else {
                    // call void func(args...)
                    std::apply(func, std::move(args));
                }
            }
            else {
                auto &o = *self;
                if constexpr (has_coro_conn_v) {
                    // call void o.func(coro_conn, args...)
                    std::apply(func, std::tuple_cat(
                                std::forward_as_tuple(
                                    o, rpc_context_tpl<conn_return_type, ContextDataType>(context_data)),
                                std::move(args)));
                }
                else {
                    // call void o.func(args...)
                    std::apply(func, std::tuple_cat(std::forward_as_tuple(o), std::move(args)));
                }
            }
        }
        else {
            bnet::dynamic_buffer<> buffer;
            if constexpr (std::is_void_v<Self>) {
                // call return_type func(args...)
                Protocol::serialize(buffer, std::apply(func, std::move(args)));
                return std::string(buffer.rd_buf(), buffer.rd_size());
            }
            else {
                auto &o = *self;
                // call return_type o.func(args...)
                Protocol::serialize(buffer, std::apply(
                    func, std::tuple_cat(std::forward_as_tuple(o), std::move(args))));
                return std::string(buffer.rd_buf(), buffer.rd_size());
            }
        }
    }
    else {
        if constexpr (std::is_void_v<return_type>) {
            if constexpr (std::is_void_v<Self>) {
                func();
            }
            else {
                (self->*func)();
            }
        }
        else {
            bnet::dynamic_buffer<> buffer;
            if constexpr (std::is_void_v<Self>) {
                Protocol::serialize(buffer, func());
                return std::string(buffer.rd_buf(), buffer.rd_size());
            }
            else {
                Protocol::serialize(buffer, (self->*func)());
                return std::string(buffer.rd_buf(), buffer.rd_size());
            }
        }
    }
    //return Protocol::serialize();
    return "";
}

template <typename Protocol, auto func, typename ContextDataType, typename Self = void>
inline async_simple::coro::Lazy<std::optional<std::string>> 
execute_coro(std::string_view data, ContextDataType& context_data, Self *self = nullptr) {
    using T = decltype(func);
    using param_type = function_parameters_t<T>;
    using return_type = typename get_type_t<typename function_return_type_t<T>::ValueType>::type;

    if constexpr (!std::is_void_v<param_type>) {
        using First = std::tuple_element_t<0, param_type>;
        constexpr bool is_conn = requires { typename First::return_type; };
        if constexpr (is_conn) {
            static_assert(std::is_void_v<return_type>,
                    "The return_type must be void");
            context_data.is_delay_ = true;
        }

        using conn_return_type = decltype(get_return_type<is_conn, First>());
        constexpr bool has_coro_conn_v =
            std::is_same_v<rpc_context_tpl<conn_return_type, ContextDataType>, First>;
        auto args = get_args<has_coro_conn_v, param_type>();

        bool is_ok = true;
        constexpr size_t size = std::tuple_size_v<decltype(args)>;
        if constexpr (size > 0) {
            is_ok = Protocol::deserialize(data, std::get<0>(args));
        }

        if (!is_ok) AS_UNLIKELY { co_return std::nullopt; }

        if constexpr (std::is_void_v<return_type>) {
            if constexpr (std::is_void_v<Self>) {
                if constexpr (has_coro_conn_v) {
                    // call void func(coro_conn, args...)
                    co_await std::apply(func, std::tuple_cat(
                                std::forward_as_tuple(
                                    rpc_context_tpl<conn_return_type, ContextDataType>(context_data)),
                                std::move(args)));
                }
                else {
                    // call void func(args...)
                    co_await std::apply(func, std::move(args));
                }
            }
            else {
                auto &o = *self;
                if constexpr (has_coro_conn_v) {
                    // call void o.func(coro_conn, args...)
                    co_await std::apply(func, std::tuple_cat(
                        std::forward_as_tuple(
                            o, rpc_context_tpl<conn_return_type, ContextDataType>(context_data)),
                        std::move(args)));
                }
                else {
                    // call void o.func(args...)
                    co_await std::apply(
                        func, std::tuple_cat(std::forward_as_tuple(o), std::move(args)));
                }
            }
        }
        else {
            bnet::dynamic_buffer<> buffer;
            if constexpr (std::is_void_v<Self>) {
                // call return_type func(args...)
                Protocol::serialize(buffer, co_await std::apply(func, std::move(args)));
                co_return std::string(buffer.rd_buf(), buffer.rd_size());
            }
            else {
                auto &o = *self;
                // call return_type o.func(args...)
                Protocol::serialize(buffer, co_await std::apply(
                    func, std::tuple_cat(std::forward_as_tuple(o), std::move(args))));
                co_return std::string(buffer.rd_buf(), buffer.rd_size());
            }
        }
    }
    else {
        if constexpr (std::is_void_v<return_type>) {
            if constexpr (std::is_void_v<Self>) {
                co_await func();
            }
            else {
                // clang-format off
                co_await (self->*func)();
                // clang-format on
            }
        }
        else {
            bnet::dynamic_buffer<> buffer;
            if constexpr (std::is_void_v<Self>) {
                Protocol::serialize(buffer, co_await func());
                co_return std::string(buffer.rd_buf(), buffer.rd_size());
            }
            else {
                // clang-format off
                Protocol::serialize(buffer, co_await (self->*func)());
                co_return std::string(buffer.rd_buf(), buffer.rd_size());
                // clang-format on
            }
        }
    }
    //co_return Protocol::serialize();
    co_return "";
}

}   // namespace modules::rpc 