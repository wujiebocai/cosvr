#pragma once

#include "config/yaml_cfg.hpp"

// yaml配置测试(test_config.yaml), 结构体字段与yaml配置中字段名对应, yaml的层级结构和struct的层级结构一样的, 没有配置的字段直接使用默认值.
// 注：这里仅仅是提供读取yaml配置的demo，不代表具体生成环境中的使用，生产环境下可以像helm工具一样，提供yaml配置模板及相关工具链提供更加强大的配置能力.

struct redis_config {
	std::vector<std::string> addrs;
	std::string password;
    bool readOnly;

    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(addrs, password, readOnly);
        return true;
    }
};

struct redismap_config {
    std::string addr;
    std::string password;

    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(addr, password);
        return true;
    }
};

struct net_config {
    std::string url;
    int tcpKeepAlive;
    int disconnectTimeout;

    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(url, tcpKeepAlive, disconnectTimeout);
        return true;
    }
};

struct common_config {
    bool errWithStack;
    std::string logLevel;

    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(errWithStack, logLevel);
        return true;
    }
};

struct gatewaysvr_config {
    net_config net;

    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(net);
        return true;
    }
};

struct gamesvr_config {
    net_config net;

    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(net);
        return true;
    }
};

struct redisproxysvr_config {
    net_config net;
    std::vector<redis_config> redises;
    std::unordered_map<std::string, redismap_config> redisesmap;

    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(net, redises, redisesmap);
        return true;
    }
};

struct servers_congfig {
    common_config common;
    gatewaysvr_config gatewaysvr;
    gamesvr_config gamesvr;
    redisproxysvr_config redisproxysvr;

    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(common, gatewaysvr, gamesvr, redisproxysvr);
        return true;
    }
};
struct game_config {
    std::string gameName;
    std::string datasDir;
    int instStr;
    servers_congfig servers;
    bool dumpmsg;

    // 下面没有配置字段直接使用默认值
    std::vector<std::string> test_arr { "sss", "ccc", "aaa"};
    std::unordered_map<std::string, std::string> test_map { {"111", "222"}, {"333", "555"}, {"acs", "sss"} };
    std::string test_val;

    inline bool load(const YAML::Node& node) {
        YAML_ALL_PARAM(gameName, datasDir, instStr, servers, dumpmsg, test_arr, test_map, test_val);
        return true;
    }
};

// test yaml config
void test_yaml() {
    game_config cfg;
    modules::cfg::load_config(std::string(PROJECT_PATH) + "/examples/test_config.yaml", cfg);
}