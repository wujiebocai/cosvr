#pragma once

#include <bnet/config.hpp>
#include "config/yaml_cfg.hpp"

using namespace bnet;

namespace modules {
struct rpc_server_config : svr_cfg {
    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(
            host, 
            port, 
            thread_num
        );

        return true;
    }
};

struct rpc_client_config : cli_cfg {
    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(
            host, 
            port, 
            thread_num, 
            pool_size, 
            conn_timeout, 
            is_reconn, 
            retry_num, 
            request_timout
        );

        return true;
    }
};

}