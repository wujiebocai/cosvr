#pragma once

#include <spdlog/spdlog.h>
#include "util/singleton.hpp"
#include "detail.hpp"

namespace modules {
auto make_log(const blog_cfg& cfg) {
    return std::make_shared<log::blog>(cfg);
}

auto close_all_log() {
    spdlog::shutdown();
}

static blog_cfg g_blog_cfg;
inline void set_global_log_config(const blog_cfg& cfg) { g_blog_cfg = cfg; }
class global_log : public singleton<global_log> {
public:
    global_log() : log_(make_log(g_blog_cfg)) {}

    inline auto& log() {
        return log_->log(); 
    }
private:
    std::shared_ptr<log::blog> log_;
};

} // namespace modules

#define SOURCE_LOC spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}
#define LOG_TRACE(LOGNAME, ...) SPDLOG_LOGGER_CALL(spdlog::get(LOGNAME), spdlog::level::trace, __VA_ARGS__)
#define LOG_DEBUG(LOGNAME, ...) SPDLOG_LOGGER_CALL(spdlog::get(LOGNAME), spdlog::level::debug, __VA_ARGS__)
#define LOG_INFO(LOGNAME, ...) SPDLOG_LOGGER_CALL(spdlog::get(LOGNAME), spdlog::level::info, __VA_ARGS__)
#define LOG_WARN(LOGNAME, ...) SPDLOG_LOGGER_CALL(spdlog::get(LOGNAME), spdlog::level::warn, __VA_ARGS__)
#define LOG_ERROR(LOGNAME, ...) SPDLOG_LOGGER_CALL(spdlog::get(LOGNAME), spdlog::level::err, __VA_ARGS__)
#define LOG_CRITI(LOGNAME, ...) SPDLOG_LOGGER_CALL(spdlog::get(LOGNAME), spdlog::level::critical, __VA_ARGS__)

#define G_LOG_TRACE(...) SPDLOG_LOGGER_CALL(modules::global_log::instance().log(), spdlog::level::trace, __VA_ARGS__)
#define G_LOG_DEBUG(...) SPDLOG_LOGGER_CALL(modules::global_log::instance().log(), spdlog::level::debug, __VA_ARGS__)
#define G_LOG_INFO(...) SPDLOG_LOGGER_CALL(modules::global_log::instance().log(), spdlog::level::info, __VA_ARGS__)
#define G_LOG_WARN(...) SPDLOG_LOGGER_CALL(modules::global_log::instance().log(), spdlog::level::warn, __VA_ARGS__)
#define G_LOG_ERROR(...) SPDLOG_LOGGER_CALL(modules::global_log::instance().log(), spdlog::level::err, __VA_ARGS__)
#define G_LOG_CRITI(...) SPDLOG_LOGGER_CALL(modules::global_log::instance().log(), spdlog::level::critical, __VA_ARGS__)
