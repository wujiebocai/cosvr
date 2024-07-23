#pragma once

#include <any>
#include <string>
#include <vector>
#include <unordered_map>
#include <bnet/base/traits.hpp>
#include "common/error.hpp"

namespace modules::rds {

using namespace bnet::base;

struct val_data : public std::any {
	using super = std::any;
    using super::super;

	template <typename T>
    val_data(T&& item) {
		this->set(std::forward<T>(item));
	}

	template <typename T>
	inline val_data& set(T&& item) & {
		static_assert(std::is_constructible_v<std::any, T>, "type not supported by std::any.");
		using valtype = unqualified_t<T>;
        if constexpr (std::is_integral_v<valtype>) {
            super::template emplace<std::int64_t>(std::forward<T>(item));
        }
        else if constexpr (std::is_floating_point_v<valtype>) {
            super::template emplace<double>(std::forward<T>(item));
        }
        else if constexpr (is_string_like_or_constructible_c<valtype>) {
            super::template emplace<std::string>(std::forward<T>(item));
        }
		else {
			//super::template operator=(std::forward<T>(item));
			super::template emplace<valtype>(std::forward<T>(item));
		}

		return *this;
	}

	template <typename T>
	inline val_data&& set(T&& item) && {
		return std::move(this->set<T>(std::move(item)));
	}

	template <typename T>
	inline decltype(auto) get() & {
        using valtype = std::decay_t<std::remove_pointer_t<T>>;
		if constexpr (std::is_integral_v<valtype>) {
			return reinterpret_cast<valtype*>(std::any_cast<int64_t>(this));
		}
		else return std::any_cast<valtype>(this);
	}

    template <typename T>
	inline decltype(auto) get() const& {
        return const_cast<val_data&>(*this).get<T>();
	}

	template <typename T>
	inline decltype(auto) get() && {
		return std::move(const_cast<val_data&>(*this).get<T>());
	}

	std::int8_t type_ = -1;
	com_errors err_code_ = com_errors::success;
	std::string vstr_ = ""; // used for verb or errmsg
};

struct object : public val_data {
    using super = val_data;
    using super::super;

    template <typename T>
    operator T* () {
		return this->get<T>();
	}
    template <typename T>
	operator T* () const {
		return this->get<T>();
	}

    template <typename T>
	requires (!std::is_same_v<T, std::string>)
	operator T& () {
		using valtype = std::decay_t<T>;
		static valtype v;
		if (auto* vp = this->get<T>()) {
			return *vp;
		}
		else {
			//throw std::runtime_error("cannot dereference null object.");
			std::cerr << "typeId " << typeid(T).name() << ", obj typeId " << this->type().name() << std::endl;
			return v;
		}
	}
    template <typename T>
	operator T& () const {
		using valtype = std::decay_t<T>;
		static valtype v;
        if (auto* vp = this->get<T>()) {
			return *vp;
		}
		else {
			std::cerr << "typeId " << typeid(T).name() << ", obj typeId " << this->type().name() << std::endl;
			return v;
		}
	}

	operator std::string() const {
		if (auto* vp = this->get<std::string>()) {
			return *vp;
		}
		else {
			std::cerr << "typeId " << typeid(std::string).name() << ", obj typeId " << this->type().name() << std::endl;
			return "";
		}
	}
	
	//explicit operator bool() const noexcept {
	//	return this->is_valide();
	//}

	inline bool is_valide() const {
		if (has_err()) {
			return false;
		}

		return this->has_value();
	}

	template <typename T>
	requires (!std::is_same_v<bnet::base::unqualified_t<T>, object>)
	auto& operator=(T&& other) & {
		this->set(std::forward<T>(other));
		return *this;
	}

	template <typename T>
	requires (!std::is_same_v<bnet::base::unqualified_t<T>, object>)
	auto&& operator=(T&& other) && {
		std::move(*this).set(std::forward<T>(other));
		return std::move(*this);
	}

	template<typename T> 
	inline T value() const {
		using valtype = std::decay_t<T>;
		static valtype v;
		if (this->type() == typeid(std::string)) {
			std::string& data = *this;
			if constexpr (std::is_integral_v<valtype>) {
				return static_cast<valtype>(std::stoll(data));
			}
			else if constexpr (std::is_floating_point_v<valtype>) {
				return static_cast<valtype>(std::stod(data));
			}
			else if constexpr (is_c_str_c<valtype>) {
				return static_cast<T>(data.data());
			}
			else if constexpr (is_string_like_or_constructible_c<valtype>) {
				return data;
			}
		}
		else {
			if constexpr (std::is_integral_v<valtype>) {
				return static_cast<T>(*this);
			}
			else if constexpr (std::is_floating_point_v<valtype>) {
				return static_cast<T>((double)(*this));
			}
			else if constexpr (is_c_str_c<valtype>) {
				std::string& data = *this;
				return static_cast<T>(data.data()); 
			}
			else if constexpr (is_string_like_or_constructible_c<valtype>) {
				return (std::string&)*this;
			}
			else if (auto* vp = this->get<T>()) {
				return static_cast<T>(*vp);
			}
		}

		return v;
	}

	// use for map or vector
	template<typename T> 
	object& operator[](T&& key) const {
		using valtype = unqualified_t<T>;
		using keytype = std::conditional_t<is_string_like_v<valtype>, std::string, valtype>;
		static object obj;
		if (this->has_value() && this->type() == typeid(std::unordered_map<keytype, object>)) {
			std::unordered_map<keytype, object>& map = *this;
			auto item = map.find(key);
			if (item != map.end()) {
				return item->second;
			}
		}
		else if (this->has_value() && this->type() == typeid(std::vector<object>)) {
			if constexpr (std::is_integral_v<valtype>) {
				std::vector<object>& vec = *this;
				auto idx = size_t(key);
				if (idx < vec.size()) {
					return vec[idx];
				}
			}
		}

		return obj;
	}

	inline void reset() {
		super::reset();
		this->type_ = -1;
		this->err_code_ = com_errors::success;
		this->vstr_.clear();
	}

	inline auto set_err(com_errors errcode) { 
		this->err_code_ = errcode; 
		return *this;
	}
	
	inline bool has_err() const {
		return (this->err_code_ != com_errors::success);
	}

	inline const auto errcode() const { return this->err_code_; }
	inline const auto errmsg() const {
		if (err_code_ == com_errors::server_rsp_error) {
			return this->vstr_;
		} else {
			return get_com_err_message(err_code_);
		}
	}
};

/////////////////////////// test obj //////////////////////////////////////////////
void test_redis_object() {
    try { 
		object objtst("123.321");
		[[maybe_unused]]auto retst1 = objtst.value<int>();
		[[maybe_unused]]auto retst2 = objtst.value<double>();
		[[maybe_unused]]auto retst3 = objtst.value<char*>();
		[[maybe_unused]]auto retst4 = objtst.value<const char*>();
		[[maybe_unused]]auto retst5 = objtst.value<std::string_view>();
		[[maybe_unused]]auto retst6 = objtst.value<std::string&>();
		[[maybe_unused]]auto retst7 = objtst.value<bool>();
		[[maybe_unused]]auto tmp6 = (std::string&)objtst;
		[[maybe_unused]]size_t len = sizeof(object);
		//double fd = 1.23;
		//[[maybe_unused]]float& af = static_cast<float&>(*reinterpret_cast<float*>(&fd));
		[[maybe_unused]]object objaa("sss");
		//[[maybe_unused]]rds_object objss(123, 1.23);
		[[maybe_unused]]object objss1(123);
		[[maybe_unused]]object objss2(12.3);
		
		std::vector<object> vec1 {"123", 123, 1.23};
		object obj = vec1;
		obj = 1;

		[[maybe_unused]]int64_t i = obj;
		[[maybe_unused]]int64_t* iptr = obj;
		*iptr = 3;
		[[maybe_unused]]int64_t& ir = obj;
		ir = 2;
		[[maybe_unused]]const int ci = obj;
		[[maybe_unused]]const int* ciptr = obj;
		[[maybe_unused]]const int& cir = obj;

		obj = 1.23;
		[[maybe_unused]]double f = obj;
		[[maybe_unused]]double* fptr = obj;
		*fptr = 12.3;
		[[maybe_unused]]double& fr = obj;
		fr = 123.01;
		[[maybe_unused]]const float cf = (double)obj;

		obj = "sss";
		[[maybe_unused]]std::string s = obj;
		[[maybe_unused]]std::string* sp = obj;
		*sp = "123";
		[[maybe_unused]]std::string& sr = obj;
		sr = "321";
		[[maybe_unused]]const std::string cs = obj;
		[[maybe_unused]]const std::string* csp = obj;
		[[maybe_unused]]const std::string& csr = obj;

		std::vector<object> vec2 {"123", 123, 1.23};
		obj = vec2;
		[[maybe_unused]]std::vector<object> v = std::move(obj);
		[[maybe_unused]]std::vector<object>* vp = obj;
		[[maybe_unused]]std::vector<object>& vr = obj;
		[[maybe_unused]]const std::vector<object> cv = obj;
		[[maybe_unused]]const std::vector<object>* cvp = obj;
		[[maybe_unused]]const std::vector<object>& cvr = obj;
		auto& objtmp = obj[1];
		objtmp = 321;

		std::unordered_map<std::string, object> map {{"sss", 123}, {"aaa", 1.23}, {"asa", "ooo"}};
		obj = map;
		[[maybe_unused]]std::unordered_map<std::string, object> m = obj;
		[[maybe_unused]]std::unordered_map<std::string, object>* mp = obj;
		[[maybe_unused]]std::unordered_map<std::string, object>& mr = obj;
		[[maybe_unused]]const std::unordered_map<std::string, object> cm = obj;
		[[maybe_unused]]const std::unordered_map<std::string, object>* cmp = obj;
		[[maybe_unused]]const std::unordered_map<std::string, object>& cmr = obj;
		auto& objtmp1 = obj["sss"];
		objtmp1 = 3.21;

		[[maybe_unused]]object o = std::move(obj);
		[[maybe_unused]]object* op = &obj;
		*op = "123";
		[[maybe_unused]]object& objref = obj;
		objref = 123;
		[[maybe_unused]]const object co = obj;
		[[maybe_unused]]const object* cop = &obj;
		[[maybe_unused]]const object& cor = obj;

		obj = true;
		[[maybe_unused]]bool ret1 = obj;
		obj = false;
		[[maybe_unused]]bool ret2 = obj;

		object bobj = false;
		[[maybe_unused]]bool bret = bobj;
		[[maybe_unused]]bool* bret1 = bobj;
		[[maybe_unused]]bool& bret2 = bobj;
		bret2 = true;
		[[maybe_unused]]const bool bcret = bobj;
		[[maybe_unused]]const bool* bcret1 = bobj;
		[[maybe_unused]]const bool& bcret2 = bobj;

		std::cout << "======================" << std::endl;
		
        //int i1 = objjj;
       // int64_t& i2 = objjj;
        //int* i3 = objjj;
        //const int i4 = objjj;
        //const int& i5 = objjj;
        //const int* i6 = objjj;
        //double d = objjj;
        //objjj = "abc";
        //std::string s = objjj;

	}
	catch (std::bad_any_cast& e) {
		std::cout << "err:" << e.what() << std::endl;
	}
}
}