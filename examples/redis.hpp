#pragma once

#include "redis/redis.hpp"

static std::atomic<std::size_t> rediscount{ 0 };

// redis 命令
template<typename RedisType>
async_simple::coro::Lazy<void>
co_test_redis_cmd(RedisType& redis) {
    auto obj = co_await redis.execute("set", "key", 123.321);
    if (obj.is_valide()) {
        std::cout << "reids cmd(set) result: " << std::string(obj) << std::endl;
    }
    else {
        std::cout << "reids cmd(set) fail, errmsg: " << obj.errmsg() << std::endl;
    }

    obj = co_await redis.execute("get", "key");
    if (obj.is_valide()) {
        std::cout << "reids cmd(get) result: " << obj.template value<double>() << std::endl;
    }
    else {
        std::cout << "reids cmd(get) fail, errmsg: " << obj.errmsg() << std::endl;
    }

    obj = co_await redis.execute("hset", "role", "10001", "role info data");
    if (obj.is_valide()) {
        std::cout << "reids cmd(hset) result: " << int64_t(obj) << std::endl;
    }
    else {
        std::cout << "reids cmd(hset) fail, errmsg: " << obj.errmsg() << std::endl;
    }

    obj = co_await redis.execute("hget", "role", "10001");
    if (obj.is_valide()) {
        std::cout << "reids cmd(hget) result: " << std::string(obj) << std::endl;
    }
    else {
        std::cout << "reids cmd(hget) fail, errmsg: " << obj.errmsg() << std::endl;
    }
}

// eval脚本相关命令(eval, eval_ro, evalsha, evalsha_ro)
template<typename RedisType>
async_simple::coro::Lazy<void>
co_test_redis_eval_script(RedisType& redis) {
    std::string script = R"(
        redis.pcall('hset', KEYS[1], KEYS[2], ARGV[1])
        local num = redis.pcall('hget', KEYS[1], KEYS[2])
        return num
    )";

    auto obj = co_await redis.eval_exe("eval", script, 2, "{sss}", "{sss}1", 123.321);
    if (obj.is_valide()) {
        std::cout << "reids cmd(eval script) result: " << obj.template value<double>() << std::endl;
    }
    else {
        std::cout << "reids cmd(eval script) fail, errmsg: " << obj.errmsg() << std::endl;
    }

    std::string script1 = R"(
        local ret = redis.pcall('hset', KEYS[1], ARGV[1], ARGV[2])
        local num = redis.pcall('hget', KEYS[1], ARGV[1])
        return {ret, num, KEYS[1], ARGV[1], ARGV[2]}
    )";

    obj = co_await redis.eval_exe("eval_ro", script1, 1, "sss", "sss123", "xxxyyysss");
    if (obj.is_valide()) {
        //std::cout << "reids cmd(get test1) result " << obj.template value<const char*>() << std::endl;
        modules::rds::print_object(obj);
    }
    else {
        std::cout << "reids cmd(eval_ro script) fail, errmsg: " << obj.errmsg() << std::endl;
    }

    obj = co_await redis.execute("script", "load", script);
    std::string sha1 = "";
    if (obj.is_valide()) {
        sha1 = std::string(obj);
        std::cout << "reids cmd(script load) result: " << sha1 << std::endl;
    }
    else {
        std::cout << "reids cmd(script load) fail, errmsg: " << obj.errmsg() << std::endl;
        co_return;
    }

    obj = co_await redis.execute("SCRIPT", "EXISTS", sha1);
    if (obj.is_valide()) {
        //std::cout << "reids cmd(script exists) result " << obj.template value<double>() << std::endl;
        modules::rds::print_object(obj);
    }
    else {
        std::cout << "reids cmd(script exists) fail, errmsg: " << obj.errmsg() << std::endl;
    }

    obj = co_await redis.eval_exe("evalsha", sha1, 2, "{sss}", "{sss}123", "sssaaasss");
    if (obj.is_valide()) {
        std::cout << "reids cmd(evalsha sha1) result: " << obj.template value<std::string>() << std::endl;
    }
    else {
        std::cout << "reids cmd(evalsha sha1) fail, errmsg: " << obj.errmsg() << std::endl;
    }

    obj = co_await redis.eval_exe("evalsha_ro", sha1, 2, "{sss}", "{sss}123", "sssaaasss");
    if (obj.is_valide()) {
        std::cout << "reids cmd(evalsha_ro sha1) result: " << obj.template value<std::string>() << std::endl;
    }
    else {
        std::cout << "reids cmd(evalsha_ro sha1) fail, errmsg: " << obj.errmsg() << std::endl;
    }
}

// redis发布订阅相关命令
template<typename RedisType>
async_simple::coro::Lazy<void>
co_test_redis_pubsub() {
    modules::redis_config cfg;
    static RedisType redis(cfg);

    auto ret = co_await redis.init();
    if (ret != modules::com_errors::success) {
        std::cerr << "redis init fail, errmsg: " << modules::get_com_err_message(ret) << std::endl;
        co_return;
    }

    static auto psptr = co_await redis.get_pubsub();
    if (!psptr) {
        std::cerr << "get redis pubsub fail." << std::endl;
        co_return;
    }

    auto handle = [](const std::string& channel, const modules::rds::object& obj) {
        std::cout << "channel: " << channel << ", val: " << (std::string&)obj << std::endl;
    };

    ret = co_await psptr.value()->subscribe(handle, "aaa", "ggg", "jjj");
    ret = co_await psptr.value()->subscribe(handle, "aaa", "ggg", "jjj");

    static auto psptr1 = co_await redis.get_pubsub();
    if (!psptr1) {
        std::cerr << "get redis pubsub fail." << std::endl;
        co_return;
    }

    ret = co_await psptr1.value()->ssubscribe(handle, "asa");
    ret = co_await psptr1.value()->psubscribe(handle, "a?a");
    ret = co_await psptr1.value()->unsubscribe("aaa", "ggg", "jjj");

    auto obj = co_await redis.publish("aaa", "test redis pubsub");
    if (obj.is_valide()) std::cout << "publish success, the number of clients that received the message: " << int64_t(obj) << std::endl;
    else std::cerr << "publish fail, errmsg: " << obj.errmsg() << std::endl;
    
    obj = co_await redis.pubsub_numsub("aaa", "ggg");
    modules::rds::print_object(obj);

    ret = co_await psptr.value()->unsubscribe("aaa", "ggg", "jjj");

    std::ignore = ret;
    std::ignore = obj;
}

template<typename RedisType>
async_simple::coro::Lazy<void>
co_test_redis() {
    modules::redis_config cfg;
    static RedisType redis(cfg);

    auto ret = co_await redis.init();
    if (ret != modules::com_errors::success) {
        std::cerr << "redis init fail, errmsg: " << modules::get_com_err_message(ret) << std::endl;
        co_return;
    }

    //auto exe = modules::get_global_executor();
    for (size_t i = 0; i < 1; i++) {
        co_test_redis_cmd(redis).start([](auto&&){});
        co_test_redis_eval_script(redis).start([](auto&&){});
    }
}

// test redis
void test_redis() {
    co_test_redis<modules::redis_type>().start([](auto&&){});
}

// test redis cluster
void test_redis_cluster() {
    co_test_redis<modules::redis_cluster_type>().start([](auto&&){});
}

// test reids publish/subscribe
void test_redis_pubsub() {
    co_test_redis_pubsub<modules::redis_type>().start([](auto&&){});
    // co_test_redis_pubsub<modules::redis_cluster_type>().start([](auto&&){});
}
