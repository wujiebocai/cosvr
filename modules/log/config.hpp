#pragma once

#include <spdlog/spdlog.h>
#include "config/yaml_cfg.hpp"

namespace modules {
struct blog_cfg {
    std::string name_ = "glog";
    std::string file_path_ = "../../logs/log.log";
    int lv_ = spdlog::level::trace;
    bool enable_file_ = true;
    bool enable_console_ = false;
    bool async_ = true;
    size_t max_file_size_ = 1024 * 1024 * 5;
    size_t max_files_ = 20;
    size_t qsize_ = 65535;
    size_t thread_num_ = 1;
    std::string pattern_ = "%Y-%m-%dT%H:%M:%S.%e%z %^%l%$ %t %@ %v";

    // 加载yaml配置
    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(name_, file_path_, lv_, enable_file_, enable_console_, async_, max_file_size_, max_files_, qsize_, thread_num_, pattern_);
        return true;
    }
};

} // namespace modules