#pragma once

#include <bnet/config.hpp>
#include "config/yaml_cfg.hpp"

namespace modules {
struct redis_config {
	// you need to configure more than two cluster node addresses for a cluster.
	// only one address for a single node.
	// try to configure only the address of the primary node in the redis cluster 
	// to reduce the number of connections to the slave node, and of course 
	// the address of the slave node can be configured.
	std::vector<std::string> addrs {"127.0.0.1:8001", "127.0.0.1:8002"};
	std::string username;
	std::string password = "ray";
	// resp protocol type: 1 resp, 2 resp2, 3 resp3
	int protocol_version = 3; 

	size_t pool_size = 10;
	std::size_t thread_num = 0;
	// connection timeout(ms)
	std::size_t conn_timeout = 3000;
	// retry times
	int retry_num = 3;
	// request timeout(s)
    std::size_t request_timout = 3;

	inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(addrs, username, password, protocol_version, pool_size, thread_num, conn_timeout, retry_num, request_timout);
        return true;
    }

	inline bnet::cli_cfg net_config() const {
		return bnet::cli_cfg {
			thread_num: thread_num,
			conn_timeout: conn_timeout,
			retry_num: retry_num,
			request_timout: request_timout,
		};
	}
};

}