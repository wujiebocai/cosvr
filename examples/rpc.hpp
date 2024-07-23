#pragma once

#include "rpc/rpc.hpp"
#include "test.pb.h"

std::atomic<std::size_t> rpccount{ 0 };

void
test_func_1(modules::rpc::rpc_context<test::TestDataResponse> ctx, test::TestDataRequest req) { 
    std::cout << "test_func_1 " << req.data() << std::endl;

    test::TestDataResponse rsp;
    rsp.set_data("test_func_1 rsp data");
    ctx.response(rsp);
}

async_simple::coro::Lazy<void> 
co_test_func_1(modules::rpc::rpc_context<test::TestDataResponse> ctx, test::TestDataRequest req) { 
    std::cout << "co_test_func_1 " << req.data() << std::endl;

    test::TestDataResponse rsp;
    rsp.set_data("co_test_func_1 rsp data");
    ctx.response(rsp);
    co_return;
}

test::TestDataResponse
test_func_2(test::TestDataRequest req) { 
    std::cout << "test_func_2 " << req.data() << std::endl;

    test::TestDataResponse rsp;
    rsp.set_data("test_func_2 rsp data");
    return rsp; 
}

async_simple::coro::Lazy<test::TestDataResponse>
co_test_func_2(test::TestDataRequest req) { 
    std::cout << "co_test_func_2 " << req.data() << std::endl;

    test::TestDataResponse rsp;
    rsp.set_data("co_test_func_2 rsp data");
    co_return rsp; 
}

void 
test_func_3() {
    std::cout << "test_func_3 " << std::endl;
}

async_simple::coro::Lazy<void> 
co_test_func_3() {
    std::cout << "co_test_func_3 " << std::endl;
    co_return;
}

async_simple::coro::Lazy<void>
co_test_rpc() {
    modules::rpc_server_config scfg;
    scfg.thread_num = 5;
    
	modules::rpc_client_config ccfg;
    ccfg.thread_num = 3;
    ccfg.pool_size = 10;

    // rpc service
    static modules::rpc::rpc_server server(scfg);
    auto err = co_await server.start();
    if (err) {
        std::cerr << "rpc server start, errmsg: " << err.message() << std::endl;
        co_return;
    }

    server.register_handler<test_func_1, co_test_func_1>();
    server.register_handler<test_func_2, co_test_func_2>();
    server.register_handler<test_func_3, co_test_func_3>();

    // rpc client
    static modules::rpc::rpc_client client(ccfg);
    err = co_await client.start();
    if (err) {
        std::cerr << "rpc client start, errmsg: " << err.message() << std::endl;
        co_return;
    }

    for (size_t i = 0; i < 1; i++) {
        if (0) {
            test::TestDataRequest req;
            req.set_data("req data");
            auto ret = co_await client.call<test_func_1>(req);
            if (ret.has_value())
                std::cout << "test_func_1 rsp: " << ret.value().data() << std::endl;
            else {
                std::cout << "test_func_1 rsp err: " << ret.error().message() << std::endl;
            }
            test::TestDataRequest req1;
            req1.set_data("req data1");
            ret = co_await client.call<test_func_2>(req1);
            if (ret.has_value())
                std::cout << "test_func_2 rsp: " << ret.value().data() << std::endl;
            else {
                std::cout << "test_func_2 rsp err: " << ret.error().message() << std::endl;
            }
            co_await client.call<test_func_3>();
            std::cout << "test_func_3 rsp" << std::endl;
        }
        else {
            test::TestDataRequest req;
            req.set_data("req data");
            client.call<test_func_1>(req).start([i](async_simple::Try<modules::rpc::rpc_result<test::TestDataResponse>> ret) {
                if (!ret.hasError() && ret.value().has_value())
                    std::cout << "test_func_1 rsp: " << ret.value().value().data() << std::endl;
                else {
                    std::cout << "test_func_1 rsp err: " << ret.value().error().message() << std::endl;
                }
            });
            client.call<co_test_func_1>(req).start([i](async_simple::Try<modules::rpc::rpc_result<test::TestDataResponse>> ret) {
                if (!ret.hasError() && ret.value().has_value())
                    std::cout << "co_test_func_1 rsp: " << ret.value().value().data() << std::endl;
                else {
                    std::cout << "co_test_func_1 rsp err: " << ret.value().error().message() << std::endl;
                }
            });

            test::TestDataRequest req1;
            req1.set_data("req data1");
            client.call<test_func_2>(req1).start([i](async_simple::Try<modules::rpc::rpc_result<test::TestDataResponse>> ret) {
                if (!ret.hasError() && ret.value().has_value())
                    std::cout << "test_func_2 rsp: " << ret.value().value().data() << std::endl;
                else {
                    std::cout << "test_func_2 err: " << ret.value().error().message() << std::endl;
                }
            });
            client.call<co_test_func_2>(req1).start([i](async_simple::Try<modules::rpc::rpc_result<test::TestDataResponse>> ret) {
                if (!ret.hasError() && ret.value().has_value())
                    std::cout << "co_test_func_2 rsp: " << ret.value().value().data() << std::endl;
                else {
                    std::cout << "co_test_func_2 err: " << ret.value().error().message() << std::endl;
                }
            });

            client.call<test_func_3>().start([i](auto&& ) {
                std::cout << "test_func_3 rsp" << std::endl;
            });
            client.call<co_test_func_3>().start([i](auto&& ) {
                std::cout << "co_test_func_3 rsp" << std::endl;
            });
        }
    }
}

// test rpc
void test_rpc() {
    co_test_rpc().start([](auto&&){});
}