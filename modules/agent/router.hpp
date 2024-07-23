#pragma once

#include <memory>

#include <async_simple/coro/Lazy.h>
#include "util/type_traits.hpp"
#include "coder/coder.hpp"

namespace modules {
namespace agt {
#define CHECK_POINT(p)	\
	if (!p) {			\
		return false;	\
	}					\

template<typename T1, typename T2>
constexpr bool is_same_category = std::is_class_v<T1> && std::is_same_v<T1, T2>;
template<class T1, class T2>
concept c_is_same_category = is_same_category<std::decay_t<std::remove_pointer_t<T1>>, std::decay_t<std::remove_pointer_t<T2>>>;

template <typename T>
struct get_type_t {
    using type = T;
};

template <typename T>
struct get_type_t<async_simple::coro::Lazy<T>> {
    using type = T;
};

template<typename ProtoType, typename KeyType, typename RetType = void>
class msg_router_imp {
class handle_msg_base {
public:
    handle_msg_base() = default;
	virtual ~handle_msg_base() {}
};

template<class Ret, class... Args>
class handle_msg : public handle_msg_base {
public:
    using func_type = std::function<Ret(std::string_view, Args...)>;
	using args_type = std::tuple<Args...>;
    using result_type = Ret;
	
	explicit handle_msg(const func_type& fn) : fn_(fn) {}
	explicit handle_msg(func_type&& fn) : fn_(std::move(fn)) {}
	explicit handle_msg(const handle_msg<Ret, Args...>& other) : fn_(other.fn_) {}
	explicit handle_msg(handle_msg<Ret, Args...>&& other) : fn_(std::move(other.fn_)) {}
	template<class F, class Proto, class ...C>
	explicit handle_msg(F&& f, Proto&& pcg, C&&... c) {
		constexpr std::size_t argc = sizeof...(C);
		static_assert(argc == 0 || argc == 1, "c can only be none or one");
		this->bind(std::forward<F>(f), std::forward<Proto>(pcg), std::forward<C>(c)...);
	}

	template<typename F, typename Proto>
	inline void bind(F&& f, Proto&& pcg) requires (!is_specialization_v<RetType, async_simple::coro::Lazy>) {
		using unqualified_proto_type = modules::unqualified_t<std::remove_pointer_t<modules::unqualified_t<Proto>>>;
		constexpr bool is_point = std::is_pointer_v<std::decay_t<Proto>>;
		this->fn_ = [this, fn = std::move(f)](std::string_view data, Args&&... args) mutable {
			bool isparse = false;
			unqualified_proto_type p;
			if constexpr (modules::is_coder<unqualified_proto_type>) {
				isparse = ProtoType::deserialize(p, data);
			}
			if constexpr (is_point) {
				if (isparse) return fn(&p, std::forward<Args>(args)...);
				else return fn(nullptr, std::forward<Args>(args)...);
			}
			else {
				if (!isparse) { /* throw exception ? */ }
				return fn(p, std::forward<Args>(args)...);
			}
		};
	}

	template<typename F, typename Proto, typename C>
	inline void bind(F&& f, Proto&& pcg, C&& c) requires (!is_specialization_v<RetType, async_simple::coro::Lazy>) {
		using unqualified_proto_type = modules::unqualified_t<std::remove_pointer_t<modules::unqualified_t<Proto>>>;
		constexpr bool is_point = std::is_pointer_v<std::decay_t<Proto>>;
		if constexpr (std::is_pointer_v<std::decay_t<C>> || is_shared_ptr_v<std::decay_t<C>>) {
			this->fn_ = [this, fn = std::move(f), s = c](std::string_view data, Args&&... args) mutable -> RetType {
				bool isparse = false;
				unqualified_proto_type p;
				if constexpr (modules::is_coder<unqualified_proto_type>) {
					isparse = ProtoType::deserialize(p, data);
				}
				if constexpr (is_point) {
					if (isparse) return ((*s).*fn)(&p, std::forward<Args>(args)...);
					else return ((*s).*fn)(nullptr, std::forward<Args>(args)...);
				}
				else {
					if (!isparse) { /* throw exception ? */ }
					return ((*s).*fn)(p, std::forward<Args>(args)...);
				}
			};
		}
		else {
			this->fn_ = [this, fn = std::move(f), s = c](std::string_view data, Args&&... args) mutable -> RetType {
				bool isparse = false;
				unqualified_proto_type p;
				if constexpr (modules::is_coder<unqualified_proto_type>) {
					isparse = ProtoType::deserialize(p, data);
				}
				if constexpr (is_point) {
					if (isparse) return ((s).*fn)(&p, std::forward<Args>(args)...);
					else return ((s).*fn)(nullptr, std::forward<Args>(args)...);
				}
				else {
					if (!isparse) { /* throw exception ? */ }
					return ((s).*fn)(p, std::forward<Args>(args)...);
				}
			};
		}
	}

	template<typename F, typename Proto>
	inline void bind(F&& f, Proto&& pcg) requires (is_specialization_v<RetType, async_simple::coro::Lazy>) {
		using unqualified_proto_type = modules::unqualified_t<std::remove_pointer_t<modules::unqualified_t<Proto>>>;
		constexpr bool is_point = std::is_pointer_v<std::decay_t<Proto>>;
		this->fn_ = [this, fn = std::move(f)](std::string_view data, Args&&... args) mutable -> RetType {
			bool isparse = false;
			unqualified_proto_type p;
			if constexpr (modules::is_coder<unqualified_proto_type>) {
				isparse = ProtoType::deserialize(p, data);
			}
			if constexpr (is_point) {
				if (isparse) co_return co_await fn(&p, std::forward<Args>(args)...);
				else co_return co_await fn(nullptr, std::forward<Args>(args)...);
			}
			else {
				if (!isparse) { /* throw exception ? */ }
				co_return co_await fn(p, std::forward<Args>(args)...);
			}
		};
	}

	template<typename F, typename Proto, typename C>
	inline void bind(F&& f, Proto&& pcg, C&& c) requires (is_specialization_v<RetType, async_simple::coro::Lazy>) {
		using unqualified_proto_type = modules::unqualified_t<std::remove_pointer_t<modules::unqualified_t<Proto>>>;
		constexpr bool is_point = std::is_pointer_v<std::decay_t<Proto>>;
		if constexpr (std::is_pointer_v<std::decay_t<C>> || is_shared_ptr_v<std::decay_t<C>>) {
			this->fn_ = [this, fn = std::move(f), s = c](std::string_view data, Args&&... args) mutable -> RetType {
				bool isparse = false;
				unqualified_proto_type p;
				if constexpr (modules::is_coder<unqualified_proto_type>) {
					isparse = ProtoType::deserialize(p, data);
				}
				if constexpr (is_point) {
					if (isparse) co_return co_await ((*s).*fn)(&p, std::forward<Args>(args)...);
					else co_return co_await ((*s).*fn)(nullptr, std::forward<Args>(args)...);
				}
				else {
					if (!isparse) { /* throw exception ? */ }
					co_return co_await ((*s).*fn)(p, std::forward<Args>(args)...);
				}
			};
		}
		else {
			this->fn_ = [this, fn = std::move(f), s = c](std::string_view data, Args&&... args) mutable -> RetType {
				bool isparse = false;
				unqualified_proto_type p;
				if constexpr (modules::is_coder<unqualified_proto_type>) {
					isparse = ProtoType::deserialize(p, data);
				}
				if constexpr (is_point) {
					if (isparse) co_return co_await ((s).*fn)(&p, std::forward<Args>(args)...);
					else co_return co_await ((s).*fn)(nullptr, std::forward<Args>(args)...);
				}
				else {
					if (!isparse) { /* throw exception ? */ }
					co_return co_await ((s).*fn)(p, std::forward<Args>(args)...);
				}
			};
		}
	}

	inline auto operator()(std::string_view data, Args&&... args) {
		return this->fn_(data, std::forward<Args>(args)...);
	}

	inline func_type& get_fn() { return fn_; }

protected:
	func_type fn_;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
public:
	template<class... Args>
	inline RetType call(KeyType evt, std::string_view data, Args&&... args) {
		using handle_msg_type = handle_msg<RetType, Args...>;
		handle_msg_type* fp_ptr = static_cast<handle_msg_type*>(this->route_[evt].get());
		return (*fp_ptr)(data, std::forward<Args>(args)...);
	}

	inline bool check(KeyType evt) {
		const auto& item = this->route_.find(evt);
		if (item != this->route_.end()) {
			return true;
		}
		return false;
	}

	template<class Ret, class Proto, class ...Args>
	requires std::is_same_v<Ret, RetType>
	inline bool bind(KeyType evt, Ret(*f)(Proto, Args...)) {
		modules::unqualified_t<Proto> pcg;
		return this->bind_t(evt, handle_msg<Ret, Args...>(f, pcg));
	}
	
    //reference OR point
	template<class Ret, class C, class Proto, class ...Args, class T>
    requires (c_is_same_category<C, T> && std::is_same_v<Ret, RetType>)
	inline bool bind(KeyType evt, Ret(C::* f)(Proto, Args...), T&& c) {
		if constexpr (std::is_pointer_v<std::decay_t<T>>) {
			CHECK_POINT(c);
		}
		modules::unqualified_t<Proto> pcg;
		return this->bind_t(evt, handle_msg<Ret, Args...>(f, pcg, std::forward<T>(c)));
	}

	template<class Ret, class C, class Proto, class ...Args, class T>
    requires (c_is_same_category<C, T> && std::is_same_v<Ret, RetType>)
	inline bool bind(KeyType evt, Ret(C::* f)(Proto, Args...) const, T&& c) {
		if constexpr (std::is_pointer_v<std::decay_t<T>>) {
			CHECK_POINT(c);
		}
		modules::unqualified_t<Proto> pcg;
		return this->bind_t(evt, handle_msg<Ret, Args...>(f, pcg, std::forward<T>(c)));
	}
	
	//std::shared_ptr
	template<class Ret, class C, class Proto, class ...Args>
	inline bool bind(KeyType evt, Ret(C::* f)(Proto, Args...), std::shared_ptr<std::decay_t<C>> c) {
		CHECK_POINT(c);
		modules::unqualified_t<Proto> pcg;
		return this->bind_t(evt, handle_msg<Ret, Args...>(f, pcg, c));
	}

	template<class Ret, class C, class Proto, class ...Args>
	inline bool bind(KeyType evt, Ret(C::* f)(Proto, Args...) const, std::shared_ptr<std::decay_t<C>> c) {
		CHECK_POINT(c);
		modules::unqualified_t<Proto> pcg;
		return this->bind_t(evt, handle_msg<Ret, Args...>(f, pcg, c));
	}

	template<class Callable>
	requires std::is_class_v<Callable>
	inline bool bind(KeyType evt, Callable&& lam) {
		return this->bind(evt, &Callable::operator(), std::forward<Callable>(lam));
	}
protected:
	template<class T>
	inline bool bind_t(KeyType evt, T&& t) {
		if (this->check(evt)) {
			std::cout << " func is exist." << std::endl;
			return false;
		}
		this->route_[evt] = std::make_unique<T>(std::forward<T>(t));
		return true;
	}

	std::unordered_map<modules::unqualified_t<KeyType>, std::unique_ptr<handle_msg_base>> route_;
};

} // namespace agt
} // namespace modules

