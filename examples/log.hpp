#pragma once

#include "log/log.hpp"

// rotate log files:
// log.0.txt -> log.1.2024-04-25T20:44:10.txt
// log.1.2024-04-25T20:44:10.txt -> log.2.2024-04-25T20:44:10.txt
// log.2.2024-04-25T20:44:10.txt -> log.3.2024-04-25T20:44:10.txt
// log.3.2024-04-25T20:44:10.txt -> delete

// 日志系统使用(详细看demo或者文档)：G_LOG_TRACE("test log {}", i);
// 下面提供了多种用法

modules::blog_cfg logcfg {
    name_: "logtest",
    file_path_: std::string(PROJECT_PATH) + "/examples/logs/log.log",
    max_file_size_: 1024 * 1024 * 5,
    max_files_: 20
};

void test_log() {
    modules::blog_cfg cfg;
    cfg.file_path_ = std::string(PROJECT_PATH) + "/examples/logs/glog.log";
    modules::set_global_log_config(cfg);

    static std::shared_ptr<modules::log::blog> logptr = modules::make_log(logcfg);

    for (size_t i = 0; i < 100000; i++) {
        // get the global log.
        G_LOG_TRACE("ggggggggggggggggggg {}", i);

        // log handle is indexed by name, which has the lowest efficiency
        LOG_TRACE("logtest", "llllllllllllllllllllll {}", i);

        // 
        logptr->trace(SOURCE_LOC, "aaaaaaaaaaaaaaaaaaa {}", i);
    }
}