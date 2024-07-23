#pragma once

#include "util/utils.hpp"
#include "config/yaml_cfg.hpp"

namespace modules {
struct app_cfg {
    std::string host;
    std::string port;
    std::size_t thread_num = 0;

    // redis cfg

    // net cfg

    // rpc cfg

	inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(host, port, thread_num);
        return true;
    }

};

}