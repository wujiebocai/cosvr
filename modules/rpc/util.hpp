#pragma once

#include <async_simple/coro/Lazy.h>
#include "util/type_traits.hpp"
#include "util/expected.hpp"
#include "rpc_context.hpp"
#include "error/error.hpp"

namespace modules {
namespace rpc {

template <typename T>
using rpc_result = expected<T, error>;

template <typename T>
struct get_type_t {
    using type = T;
};

template <typename T>
struct get_type_t<async_simple::coro::Lazy<T>> {
    using type = T;
};

template <auto func>
inline auto get_return_type() {
    using T = decltype(func);
    using param_type = function_parameters_t<T>;
    using return_type = typename get_type_t<function_return_type_t<T>>::type;
    if constexpr (std::is_void_v<param_type>) {
        if constexpr (std::is_void_v<return_type>) {
            return;
        }
        else {
            return return_type{};
        }
    }
    else {
        using First = std::tuple_element_t<0, param_type>;
        constexpr bool is_conn = is_specialization<First, rpc_context_tpl>::value;
        if constexpr (is_conn) {
            using U = typename First::return_type;
            if constexpr (std::is_void_v<U>) {
                return;
            }
            else {
                return U{};
            }
        }
        else if constexpr (!std::is_same_v<void, return_type>) {
            return return_type{};
        }
        else {
            return;
        }
    }
}

template <auto func, typename... Args>
void static_check() {
    using Function = decltype(func);
    using param_type = function_parameters_t<Function>;
    if constexpr (!std::is_void_v<param_type>) {
        using First = std::tuple_element_t<0, param_type>;
        constexpr bool is_conn = requires { typename First::return_type; };

        if constexpr (std::is_member_function_pointer_v<Function>) {
            using Self = class_type_t<Function>;
            if constexpr (is_conn) {
                static_assert(std::is_invocable<Function, Self, First, Args...>::value,
                    "called function and arguments are not match");
            }
            else {
                static_assert(std::is_invocable<Function, Self, Args...>::value,
                    "called function and arguments are not match");
            }
        }
        else {
            if constexpr (is_conn) {
                static_assert(std::is_invocable<Function, First, Args...>::value,
                    "called function and arguments are not match");
            }
            else {
                static_assert(std::is_invocable<Function, Args...>::value,
                    "called function and arguments are not match");
            }
         }
    }
    else {
        if constexpr (std::is_member_function_pointer_v<Function>) {
            using Self = class_type_t<Function>;
            static_assert(std::is_invocable<Function, Self, Args...>::value,
                "called function and arguments are not match");
        }
        else {
            static_assert(std::is_invocable<Function, Args...>::value,
                "called function and arguments are not match");
        }
    }
}

}
}