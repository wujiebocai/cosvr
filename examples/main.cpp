#include <iostream> 
#include <thread>
#include <asio.hpp>

// #include <execinfo.h>

//#include "test.pb.h"
#include "error.hpp"
#include "log.hpp"
#include "net.hpp"
#include "redis.hpp"
#include "router.hpp"
#include "rpc.hpp"
#include "timer.hpp"

#include "uuid.hpp"



#include "yaml.hpp"


asio::io_context g_context_(1);
asio::io_context::strand g_context_s_(g_context_);

// 下面是各个模块的demo, 各模块都提供了协程接口, 可以去掉callback逻辑, 让逻辑更加清晰
// 后续会提供一套api标准, 方便各模块的替换
enum e_test_type : uint8_t {
    TEST_ERR = 1,           // 错误
    TEST_LOG,               // 日志
    TEST_NET,               // 网络
    TEST_REDIS,             // redis
    TEST_REDIS_CLUSTER,     // redis集群
    TEST_REDIS_PUBSUB,      // redis发布订阅
    TEST_ROUTER,            // 协议路由
    TEST_AGENT,             // agent
    TEST_RPC,               // rpc
    TEST_TIMER,             // 计时器
    TEST_UUID,              // uuid
    TEST_YAML,              // yaml配置
};

int main(int argc, char * argv[]) {
    e_test_type test_type = TEST_ERR;
    if (argc >= 2) {
        test_type = static_cast<e_test_type>(std::stoi(argv[1]));
    }

    switch (test_type) {
    case TEST_ERR:
        test_err();
        break;
    case TEST_LOG:
        test_log();
        break;
    case TEST_NET:
        test_net();
        break;
    case TEST_REDIS:
        test_redis();
        break;
    case TEST_REDIS_CLUSTER:
        test_redis_cluster();
        break;
    case TEST_REDIS_PUBSUB:
        test_redis_pubsub();
        break;
    case TEST_ROUTER:
        test_router();
        break;
    case TEST_AGENT:
        test_agent();
        break;
    case TEST_RPC:
        test_rpc();
        break;
    case TEST_TIMER:
        test_timer();
        break;
    case TEST_UUID:
        test_uuid();
        break;
    case TEST_YAML:
        test_yaml();
        break;
    default:
        break;
    }

    std::cout << "=============================" << std::endl;
///
	asio::signal_set signals(g_context_, SIGINT, SIGTERM);
	signals.async_wait([&](auto, auto){ g_context_.stop(); });

	auto io_worker = asio::make_work_guard(g_context_);
	g_context_.run();

	return 0;
}