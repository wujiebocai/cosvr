#pragma once

#include "protocol/net_protocol.hpp"
#include "agent/router.hpp"
#include "test.pb.h"

class test_member_func {
public:
    void test_memfunc(const test::TestDataResponse& msg) const {
        std::cout << "sss" << std::endl;
    }

    async_simple::coro::Lazy<std::string> co_test_memfunc(test::TestDataResponse msg, std::string& i, int& v) const {
        std::cout << "co_func_tst, msgdata: " << msg.data() << ", i: " << i << ", v: " << v << std::endl;
        i = "123.321";
        v = 132;

        co_return "asdf123zxcsss";
    }
};

void test_func(test::TestDataResponse& msg, test_member_func& t) {
    std::cout << "testfunc, msgdata: " << msg.data() << std::endl;
    t.test_memfunc(msg);
}

void test_func1(test::TestDataResponse msg, test_member_func t) {
    std::cout << "testfunc1, msgdata: " << msg.data() << std::endl;
    t.test_memfunc(msg);
}

void test_func2(const test::TestDataResponse& msg, const std::shared_ptr<test_member_func>& t) {
    std::cout << "testfunc2, msgdata: " << msg.data() << std::endl;
    t->test_memfunc(msg);
}

void test_func3(test::TestDataResponse* msg, test_member_func* t) {
    std::cout << "testfunc3, msgdata: " << msg->data() << std::endl;
    t->test_memfunc(*msg);
}

void test_func5(const test::TestDataResponse* msg, const test_member_func* t) {
    std::cout << "testfunc5, msgdata: " << msg->data() << std::endl;
    t->test_memfunc(*msg);
}

async_simple::coro::Lazy<std::string> 
co_test_func6(test::TestDataResponse* msg, const test_member_func& t) {
    std::cout << "testfunc6, msgdata: " << msg->data() << std::endl;

    std::string val("123");
    int i = 666;
    co_return co_await t.co_test_memfunc(*msg, val, i);
}

struct str_msg {
    int id;
    double pos;
    char name[32];
};

void test_func7(const str_msg* msg) {
    std::cout << "test_func7, msgdata: " << msg->name << std::endl;
}

async_simple::coro::Lazy<std::string> 
co_test_func7(str_msg* msg) {
    std::cout << "co_test_func7, msgdata: " << msg->name << std::endl;
    co_return "aaasss";
}

async_simple::coro::Lazy<> 
co_test_router() {
    test::TestDataResponse msg;
    msg.set_data("sca");
    std::string buffer;
    modules::coder::serialize(msg, buffer);
    std::string buffer1;
    str_msg strmsg {
        id: 0,
        pos: 123.321,
        name: "sss",
    };
    modules::coder::serialize(strmsg, buffer1);

    test_member_func t;
    auto stptr = std::make_shared<test_member_func>();

    modules::agt::msg_router_imp<modules::protocol::net_proto<>, uint32_t, async_simple::coro::Lazy<std::string>> co_router;
    co_router.bind(1, &test_member_func::co_test_memfunc, t);
    co_router.bind(2, &test_member_func::co_test_memfunc, &t);
    co_router.bind(3, &test_member_func::co_test_memfunc, stptr);
    co_router.bind(4, co_test_func6);
    co_router.bind(5, co_test_func7);
    
    std::string val("1");
    int i = 1;
    //co_router.call(1, buffer, val).start([](auto&&){});
    //co_router.call(2, buffer, val).start([](auto&&){});
    //co_router.call(3, buffer, val).start([](auto&&){});
    //co_router.call(4, buffer).start([](auto&&){});
    //co_router.call(5, buffer1).start([](auto&&){});

    co_await co_router.call(1, buffer, val, i);
    //val = "2";
    //i = 2;
    co_await co_router.call(2, buffer, val, i);
    //val = "3";
    //i = 3;
    co_await co_router.call(3, buffer, val, i);
    co_await co_router.call(4, buffer);
    co_await co_router.call(5, buffer1);
}

// test msg router
void test_router() {
    modules::agt::msg_router_imp<modules::protocol::net_proto<>, uint32_t, void> router;
    router.bind(0, test_func);
    router.bind(1, test_func1);
    router.bind(2, test_func2);
    router.bind(3, test_func3);
    router.bind(5, test_func5);

    test::TestDataResponse msg;
    msg.set_data("sca");
    std::string buffer;
    modules::coder::serialize(msg, buffer);
    std::string buffer1;
    str_msg strmsg {
        id: 0,
        pos: 123.321,
        name: "sss",
    };
    modules::coder::serialize(strmsg, buffer1);

    test_member_func t;
    router.bind(6, &test_member_func::test_memfunc, &t);
    router.bind(7, test_func7);

    router.call(0, buffer, t);
    router.call(1, buffer, t);
    auto stptr = std::make_shared<test_member_func>();
    router.call(2, buffer, stptr);
    router.call(3, buffer, &t);
    router.call(5, buffer, &t);
    router.call(6, buffer);
    router.call(7, buffer1);

    co_test_router().start([](auto&&){});
}

//------------------------------------------------
// 测试agent之间通信
struct pod_str_msg {
    uint64_t roleId;
    char name[32];
    double pos;
    uint32_t lv;
    char openid[32];
};

static modules::agent_mgr_type agent_mgr_;
class message_test {
public:
    message_test() {
        agent_mgr_.register_handle(1, &message_test::test_struct_message, this);
        agent_mgr_.register_handle(2, &message_test::test_pb_message, this);
    }

    // 测试struct协议
    async_simple::coro::Lazy<> test_struct_message(pod_str_msg msg, const modules::agent_ptr_type& to, const modules::agent_ptr_type& from) const {
        std::cout << "test_struct_message " << msg.name << std::endl;
        test::TestDataResponse rsp;
        rsp.set_data("sss");
        agent_mgr_.enqueue(from, to, 2, rsp);
        co_return;
    }

    // 测试protobuf协议
    async_simple::coro::Lazy<> test_pb_message(test::TestDataResponse msg, const modules::agent_ptr_type& to, const modules::agent_ptr_type& from) const {
        std::cout << "func_tst sss 111 " << msg.data() << std::endl;
        pod_str_msg rsp {
            roleId: 10001,
            name: "sss123",
        };
        agent_mgr_.enqueue(from, to, 1, rsp);
        co_return;
    }
};

void test_agent() {
    static auto agent1 = agent_mgr_.add_agent<modules::agent_type>(1, modules::AGENT_TYPE_DEFUALT, modules::get_global_executor());
    static auto agent2 = agent_mgr_.add_agent<modules::agent_type>(2, modules::AGENT_TYPE_DEFUALT, modules::get_global_executor());

    static message_test t;

    test::TestDataResponse rsp;
    rsp.set_data("aaa");

    agent_mgr_.enqueue(agent2, agent1, 2, rsp);
}