#pragma once

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include "spdlog/sinks/rotating_file_sink.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>

#include "config.hpp"
#include "logsink.hpp"

namespace modules {
namespace log {
class blog {
public:
    blog(const blog_cfg& param) : param_(param) {
	    try  {
		    std::vector<spdlog::sink_ptr> sinks;
            if (param.enable_file_) {
			    //sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/" + name + ".log", 23, 59));
                auto file_sink = std::make_shared<spdlog::sinks::blog_rotating_file_sink_mt>(param.file_path_, param.max_file_size_, param.max_files_);
                sinks.push_back(file_sink);
		    }

            if (param.enable_console_) {
#ifndef WIN32
			    auto colorSink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
#else
			    auto colorSink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
#endif
			    sinks.push_back(colorSink);
		    }

            if (param.async_) {
                //get the global thread pool.
                //spdlog::init_thread_pool(param.qsize_, param.thread_num_);
                //spdlog::thread_pool()
                thread_pool_ = std::make_shared<spdlog::details::thread_pool>(param.qsize_, param.thread_num_);
		    	logger_ = std::make_shared<spdlog::async_logger>(param.name_, sinks.begin(), sinks.end(), thread_pool_, spdlog::async_overflow_policy::block);
            } 
            else {
                logger_ = std::make_shared<spdlog::logger>(param.name_, sinks.begin(), sinks.end());
            }

            auto level = param.lv_;
            if (level < 0 || level > spdlog::level::level_enum::off)
		    	level = 0;
		    logger_->set_level((spdlog::level::level_enum)level);
            logger_->set_pattern(param.pattern_);
		

            // logger_->set_error_handler([](const std::string &msg) { spdlog::get("console")->error("*** LOGGER ERROR ***: {}", msg); });

            logger_->flush_on(spdlog::level::critical);
		    spdlog::flush_every(std::chrono::seconds(3));
		    spdlog::register_logger(logger_);
	    }
	    catch(const spdlog::spdlog_ex& ex) {
            spdlog::throw_spdlog_ex("blog initialization failed, log name: " + param.name_ +
                                        " filepath: " + param.file_path_,
                                    errno);
	    }
    }
 
    ~blog() {
        spdlog::drop(param_.name_);
	    //spdlog::drop_all();
	    //spdlog::shutdown();
    }

    template <typename... Args>
    inline void trace(const spdlog::source_loc& loc, const spdlog::format_string_t<Args...>& fmt, Args&&... args) {
        (logger_)->log(loc, spdlog::level::trace, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void debug(const spdlog::source_loc& loc, const spdlog::format_string_t<Args...>& fmt, Args&&... args) {
        (logger_)->log(loc, spdlog::level::debug, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void info(const spdlog::source_loc& loc, const spdlog::format_string_t<Args...>& fmt, Args&&... args) {
        (logger_)->log(loc, spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void warn(const spdlog::source_loc& loc, const spdlog::format_string_t<Args...>& fmt, Args&&... args) {
        (logger_)->log(loc, spdlog::level::warn, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void err(const spdlog::source_loc& loc, const spdlog::format_string_t<Args...>& fmt, Args&&... args) {
        (logger_)->log(loc, spdlog::level::err, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline void critical(const spdlog::source_loc& loc, const spdlog::format_string_t<Args...>& fmt, Args&&... args) {
        (logger_)->log(loc, spdlog::level::critical, fmt, std::forward<Args>(args)...);
    }

    inline auto& log() { return logger_; }
protected:
    std::shared_ptr<spdlog::logger> logger_;
    std::shared_ptr<spdlog::details::thread_pool> thread_pool_;
    blog_cfg param_;
};

} // namespace log

//static const char* tst_pattern = "[%Y-%m-%d %H:%M:%S.%e] <thread %t> [%n] [%^%l%$]\n[%@,%!]\n%v\n";

} // namespace modules
