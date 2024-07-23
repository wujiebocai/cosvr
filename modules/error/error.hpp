#pragma once

#include <system_error>
#include "util/format.hpp"
#include "error/call_stack.hpp"

#define ERR_ENUM_CATEGORY_BEGIN(MOD, ...) \
	enum MOD##_errors {  \
        __VA_ARGS__ \
    }; \
	struct MOD##_category : public std::error_category { \
        const char* name() const noexcept(true) { \
    	    return #MOD" error"; \
  	    } \
        std::string message(int value) const { \
            switch (value) { \
			default: return "defult err";

#define ERR_ENTRY(err, msg) \
    case err : return msg;

#define ERR_ENUM_CATEGORY_END(MOD) }}}; \
	inline std::error_code make_error_code(MOD##_errors e) { \
        static MOD##_category instance; \
        return std::error_code(static_cast<int>(e), instance); \
    } 

#define DEFUALT_NAMESPACE
#define ERR_STD_CODE_ENUM(NAMESPACE, MOD) \
	template<> struct std::is_error_code_enum<NAMESPACE ::MOD##_errors> { \
  	    static const bool value = true; \
    }; 

#ifdef BSVR_NO_EXCEPTIONS
    #define BSVR_TRY
    #define BSVR_THROW(ex)                               \
        do {                                               \
            printf("BSVR fatal error: %s\n", ex.what()); \
            std::abort();                                  \
        } while (0)
    #define BSVR_CATCH_STD
#else
    #define BSVR_TRY try
    #define BSVR_THROW(ex) throw(ex)
    #define BSVR_CATCH_STD             \
        catch (const std::exception &) { \
        }
#endif

#ifdef BSVR_ASSERT
	static_assert(false, "Unknown BSVR_ASSERT definition will affect the relevant functions of this program.");
#else
	#if defined(_DEBUG) || defined(DEBUG)
		#define BSVR_ASSERT(x) assert(x);
	#else
		#define BSVR_ASSERT(x) (void)0;
	#endif
#endif

#define PRINT_STACK_INFO_DEPTH 8

namespace modules {
namespace err {
class svr_ex : public std::exception {
public:
    explicit inline svr_ex(std::string msg) : msg_(msg) {}
    inline svr_ex(const std::string &msg, int last_errno) {
		msg_ = std::system_error(std::error_code(last_errno, std::generic_category()), msg).what();
	}

    inline const char *what() const noexcept override {
		return msg_.c_str();
	}

private:
    std::string msg_;
};
} // namespace err

inline void throw_svr_ex(const std::string &msg, int last_errno) {
    BSVR_THROW(err::svr_ex(msg, last_errno));
}
inline void throw_svr_ex(std::string msg) { BSVR_THROW(err::svr_ex(std::move(msg))); }

// ---------------------- define error ---------------------------------------
class error {
public:
    error() noexcept
    : code_(0), msg_("") { }

    constexpr error(int c, const std::string& msg) noexcept
    : code_(c), msg_(std::move(msg)) { }

    error(const std::error_code& ec) noexcept
    : code_(ec.value()), msg_(ec.message()) { }

    void assign(int c, const std::string& msg) noexcept {
        code_ = c;
        msg_ = std::move(msg);
    }

    void clear() noexcept { code_ = 0; msg_ = ""; }

    int value() const noexcept { return code_; }
    void value(int c) { code_ = c; }
    std::string message() const { return msg_; }
    void message(const std::string& msg) { msg_ = msg; }

    explicit operator bool() const noexcept { return code_ != 0; }
private:
    int code_;
    std::string msg_;
};

// ------------------------ define wrap error imp -----------------------------------------
template <typename... T>
auto wrap_error(int err_code, const fmt::format_string<T...>& fmt, T&&... args)
    -> error {
    auto wrap_msg = std::format(fmt, std::forward<T>(args)...);
    return error(err_code, wrap_msg);
}

template <typename... T>
auto wrap_error(const error& ec, const fmt::format_string<T...>& fmt, T&&... args)
    -> error {
    auto code = ec.value();
    auto wrap_msg = ec.message() + ", " + std::format(fmt, std::forward<T>(args)...);
    return error(code, wrap_msg);
}

template <typename... T>
auto wrap_error(const std::error_code& ec, const fmt::format_string<T...>& fmt, T&&... args)
    -> error {
    auto code = ec.value();
    auto wrap_msg = ec.message() + ", " + std::format(fmt, std::forward<T>(args)...);
    return error(code, wrap_msg);
}

template <typename... T>
auto wrap_error_with_stack(int err_code, const fmt::format_string<T...>& fmt, T&&... args)
    -> error {
    auto wrap_msg = std::format(fmt, std::forward<T>(args)...) + "; " + err::get_stack_info(PRINT_STACK_INFO_DEPTH);
    return error(err_code, wrap_msg);
}

template <typename... T>
auto wrap_error_with_stack(const error& ec, const fmt::format_string<T...>& fmt, T&&... args)
    -> error {
    auto code = ec.value();
    auto wrap_msg = ec.message() + ", " + std::format(fmt, std::forward<T>(args)...) + "; " + err::get_stack_info(PRINT_STACK_INFO_DEPTH);
    return error(code, wrap_msg);
}

template <typename... T>
auto wrap_error_with_stack(const std::error_code& ec, const fmt::format_string<T...>& fmt, T&&... args)
    -> error {
    auto code = ec.value();
    auto wrap_msg = ec.message() + ", " + std::format(fmt, std::forward<T>(args)...) + "; " + err::get_stack_info(PRINT_STACK_INFO_DEPTH);
    return error(code, wrap_msg);
}

thread_local static error no_error;

} // namespace modules