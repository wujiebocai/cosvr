#pragma once

#include <functional>
#include <memory>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>
#include <async_simple/coro/Lazy.h>
#include "util/md5_constexpr.hpp"
#include "util/function_name.hpp"
#include "util/type_traits.hpp"
#include "rpc_execute.hpp"

namespace modules {

namespace rpc {
template <typename T, auto func>
concept has_gen_register_key = requires() {
    T::template gen_register_key<func>();
};

template <typename Protocol, typename ContextDataType>
class rpc_router {
    using router_handler_t = std::function<std::optional<std::string>(
        std::string_view, ContextDataType& context_data)>;

    using coro_router_handler_t = std::function<async_simple::coro::Lazy<std::optional<std::string>>(
        std::string_view, ContextDataType& context_data)>;

    using route_key = typename Protocol::route_key_t;
    std::unordered_map<route_key, router_handler_t> handlers_;
    std::unordered_map<route_key, coro_router_handler_t> coro_handlers_;
    std::unordered_map<route_key, std::string> id2name_;

private:
    const std::string &get_name(const route_key &key) {
        static std::string empty_string;
        if (auto it = id2name_.find(key); it != id2name_.end()) {
            return it->second;
        }
        else return empty_string;
    }

    // See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=100611
    // We use this struct instead of lambda for workaround
    template <auto Func, typename Self>
    struct execute_visitor {
        std::string_view data;
        ContextDataType& context_data;
        Self *self;
        async_simple::coro::Lazy<std::optional<std::string>> operator()() {
            return execute_coro<Protocol, Func>(data, context_data, self);
        }
    };

    template <auto Func>
    struct execute_visitor<Func, void> {
        std::string_view data;
        ContextDataType& context_data;
        async_simple::coro::Lazy<std::optional<std::string>> operator()() {
            return execute_coro<Protocol, Func>(data, context_data);
        }
    };

    template <auto func, typename Self>
    void regist_one_handler(Self *self) {
        if (self == nullptr) AS_UNLIKELY { 
            std::cerr << "null connection!" << std::endl; 
        }

        route_key key{};

        if constexpr (has_gen_register_key<Protocol, func>) {
            key = Protocol::template gen_register_key<func>();
        }
        else {
            key = auto_gen_register_key<func>();
        }

        regist_one_handler_impl<func>(self, key);
    }

    template <auto func>
    static constexpr route_key auto_gen_register_key() {
        constexpr auto name = get_func_name<func>();
        constexpr auto id = MD5::MD5Hash32Constexpr(name.data(), name.length());
        return id;
    }

    template <auto func, typename Self>
    void regist_one_handler_impl(Self *self, const route_key &key) {
        if (self == nullptr) AS_UNLIKELY { 
            std::cerr << "null connection!" << std::endl; 
        }

        constexpr auto name = get_func_name<func>();
        using return_type = function_return_type_t<decltype(func)>;
        if constexpr (is_specialization_v<return_type, async_simple::coro::Lazy>) {
            auto it = coro_handlers_.emplace(
                key,
                [self](std::string_view data, ContextDataType& context_data) {
                    execute_visitor<func, Self> visitor{data, context_data, self};
                    return std::visit(visitor);
                });
            if (!it.second) {
                std::cerr << "duplication function " << name.data() << " register!" << std::endl;
            }
        }
        else {
            auto it = handlers_.emplace(
                key,
                [self](std::string_view data, ContextDataType& context_data) {
                return std::visit(
                    [data, &context_data, self]() mutable {
                        return execute<Protocol, func>(data, context_data, self);
                });
            });
            if (!it.second) {
                std::cerr << "duplication function " << name.data() << " register!" << std::endl;
            }
        }

        id2name_.emplace(key, name);
    }

    template <auto func>
    void regist_one_handler() {
        route_key key{};
        if constexpr (has_gen_register_key<Protocol, func>) {
            key = Protocol::template gen_register_key<func>();
        }
        else {
            key = auto_gen_register_key<func>();
        }
        regist_one_handler_impl<func>(key);
    }

    template <auto func>
    void regist_one_handler_impl(const route_key &key) {
        static_assert(!std::is_member_function_pointer_v<decltype(func)>,
            "register member function but lack of the parent object");
        using return_type = function_return_type_t<decltype(func)>;

        constexpr auto name = get_func_name<func>();
        if constexpr (is_specialization_v<return_type, async_simple::coro::Lazy>) {
            auto it = coro_handlers_.emplace(
                key,
                [](std::string_view data, ContextDataType& context_data) {
                execute_visitor<func, void> visitor{data, context_data};
                return std::visit(visitor);
            });
            if (!it.second) {
                std::cerr << "duplication function " << name.data() << " register!" << std::endl;
            }
        }
        else {
            auto it = handlers_.emplace(
                key,
                [](std::string_view data, ContextDataType& context_data) {
                    return std::visit([data, &context_data]() mutable {
                        return execute<Protocol, func>(data, context_data);
                    });
                });
            if (!it.second) {
                std::cerr << "duplication function " << name.data() << " register!" << std::endl;
            }
        }
        id2name_.emplace(key, name);
    }

public:
    router_handler_t *get_handler(uint32_t id) {
        if (auto it = handlers_.find(id); it != handlers_.end()) {
            return &it->second;
        }
        return nullptr;
    }

    coro_router_handler_t *get_coro_handler(uint32_t id) {
        if (auto it = coro_handlers_.find(id); it != coro_handlers_.end()) {
            return &it->second;
        }
        return nullptr;
    }

    async_simple::coro::Lazy<std::pair<std::errc, std::string>> 
    route_coro(auto handler, std::string_view data, ContextDataType& context_data, const typename Protocol::route_key_t& route_key) {
        using namespace std::string_literals;
        if (handler) AS_LIKELY {
            try {
#ifndef NDEBUG
                std::cout << "route function name: " << get_name(route_key).data() << std::endl;
#endif
                // clang-format off
                auto res = co_await (*handler)(data, context_data);
                // clang-format on
                if (res.has_value()) AS_LIKELY {
                    co_return std::make_pair(std::errc{}, std::move(res.value()));
                }
                else {  // deserialize failed
                    std::cerr << "payload deserialize failed in rpc function: " << get_name(route_key).data() << std::endl;
                    co_return std::make_pair(std::errc::invalid_argument,
                                     "invalid rpc function arguments"s);
                }
            } catch (const std::exception &e) {
                std::cerr << "exception: " << e.what() << "in rpc function: " << get_name(route_key).data() << std::endl;
                co_return std::make_pair(std::errc::interrupted, e.what());
            } catch (...) {
                std::cerr << "unknown exception in rpc function: " << get_name(route_key).data() << std::endl;
                co_return std::make_pair(std::errc::interrupted, "unknown exception"s);
            }
        }
        else {
            std::ostringstream ss;
            ss << route_key;
            std::cerr << "the rpc function not registered, function ID: " << ss.str().data() << std::endl;
            co_return std::make_pair(std::errc::function_not_supported,
                                "the rpc function not registered"s);
        }
    }

    std::pair<std::errc, std::string> 
    route(auto handler, std::string_view data, ContextDataType& context_data, const typename Protocol::route_key_t& route_key) {
        using namespace std::string_literals;
        if (handler) AS_LIKELY {
            try {
#ifndef NDEBUG
                std::cout << "route function name: " << get_name(route_key).data() << std::endl;
#endif
                auto res = (*handler)(data, context_data);
                if (res.has_value()) AS_LIKELY {
                    return std::make_pair(std::errc{}, std::move(res.value()));
                }
                else {  // deserialize failed
                    std::cerr << "payload deserialize failed in rpc function: " << get_name(route_key).data() << std::endl;
                    return std::make_pair(std::errc::invalid_argument, "invalid rpc function arguments"s);
                }
            } catch (const std::exception &e) {
                std::cerr << "exception: " << e.what() << " in rpc function: " << get_name(route_key).data() << std::endl;
                return std::make_pair(std::errc::interrupted, e.what());
            } catch (...) {
                std::cerr << "unknown exception in rpc function: " << get_name(route_key).data() << std::endl;
                return std::make_pair(std::errc::interrupted,
                                "unknown rpc function exception"s);
            }
        }
        else {
            std::ostringstream ss;
            ss << route_key;
            std::cerr << "the rpc function not registered, function ID: " << ss.str().data() << std::endl;
            return std::make_pair(std::errc::function_not_supported,
                            "the rpc function not registered"s);
        }
    }

  /*!
   * Register RPC service functions (member function)
   *
   * Before RPC server started, all RPC service functions must be registered.
   * All you need to do is fill in the template parameters with the address of
   * your own RPC functions. If RPC function is registered twice, the program
   * will be terminate with exit code `EXIT_FAILURE`.
   *
   * Note: All functions must be member functions of the same class.
   *
   * ```cpp
   * class test_class {
   *  public:
   *  void plus_one(int val) {}
   *  std::string get_str(std::string str) { return str; }
   * };
   * int main() {
   *   test_class obj{};
   *   // register member functions
   *   register_handler<&test_class::plus_one, &test_class::get_str>(&obj);
   *   return 0;
   * }
   * ```
   *
   * @tparam first the address of RPC function. e.g. `&foo::bar`
   * @tparam func the address of RPC function. e.g. `&foo::bar`
   * @param self the object pointer corresponding to these member functions
   */

    template <auto first, auto... func>
    void register_handler(class_type_t<decltype(first)> *self) {
        regist_one_handler<first>(self);
        (regist_one_handler<func>(self), ...);
    }

    template <auto func>
    void register_handler(class_type_t<decltype(func)> *self,
                        const route_key &key) {
        regist_one_handler_impl<func>(self, key);
    }

  /*!
   * Register RPC service functions (non-member function)
   *
   * Before RPC server started, all RPC service functions must be registered.
   * All you need to do is fill in the template parameters with the address of
   * your own RPC functions. If RPC function is registered twice, the program
   * will be terminate with exit code `EXIT_FAILURE`.
   *
   * ```cpp
   * // RPC functions (non-member function)
   * void hello() {}
   * std::string get_str() { return ""; }
   * int add(int a, int b) {return a + b; }
   * int main() {
   *   register_handler<hello>();         // register one RPC function at once
   *   register_handler<get_str, add>();  // register multiple RPC functions at
   * once return 0;
   * }
   * ```
   *
   * @tparam first the address of RPC function. e.g. `foo`, `bar`
   * @tparam func the address of RPC function. e.g. `foo`, `bar`
   */

    template <auto first, auto... func>
    void register_handler() {
        regist_one_handler<first>();
        (regist_one_handler<func>(), ...);
    }

    template <auto func>
    void register_handler(const route_key &key) {
        regist_one_handler_impl<func>(key);
    }
};

}  // namespace protocol
}  // namespace coro_rpc