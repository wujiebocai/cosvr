#pragma once

#include "app/app.hpp"
#include "timer/time_util.hpp"
#include "common/define.hpp"
#include "test.pb.h"

// robot->gate->game, 一个简单的基于actor模型的机器人登陆demo

static std::string game_type = "game";
static std::string gate_type = "gate";

enum e_agent_type : uint32_t {
    AGENT_TYPE_USER = modules::e_agent_type::AGENT_TYPE_SYS_MAX,
    AGENT_TYPE_ROBOT,
};

modules::app_cfg get_gate_config() {
    modules::app_cfg cfg;
    cfg.host = "127.0.0.1";
    cfg.port = "11001";
    return cfg;
}

modules::app_cfg get_game_config() {
    modules::app_cfg cfg;
    cfg.host = "127.0.0.1";
    cfg.port = "11002";
    return cfg;
}

class gate_server : public modules::app {
    // user data
    struct user_t {
        uint32_t userid;
        uint64_t game_agent_id;  // It is mainly used to forward protocols to game service
        std::string openid;
        std::string user_type;
    };
public:
    using super = modules::app;
    gate_server(std::string_view svr_type, const modules::app_cfg& cfg)
    : super(svr_type, cfg) {
        // register protocol handlers
        this->register_handle(test::TEST_MSG::REQ_AUTH, &gate_server::auth_handler, this);
        this->register_handle(test::TEST_MSG::REQ_LOGIN, &gate_server::login_handler, this);
    }

    async_simple::coro::Lazy<> auth_handler(test::AuthReq* msg, const modules::agent_ptr_type& to, uint64_t from_id) {
        if (!msg) {
            std::cerr << "auth invalid message param" << std::endl;
            co_return;
        }
        
        // todo
        auto* uptr = to->user_data<user_t>();
        if (uptr) {
            std::cerr << "user is already online, openid " << msg->openid() << std::endl;
            co_return;
        }

        // authentication

        // you may need to load user data from a database

        // create user
        auto userid = modules::hash32(msg->openid());
        user_t user;
        user.userid = userid;
        user.openid = msg->openid();
        user.user_type = msg->usertype();
        to->user_data(user);

        test::AuthRsp rsp;
        rsp.set_userid(userid);
        auto role = rsp.add_roles();
        role->set_roleid(gen_id_++);
        role->set_leve(1);
        role->set_name("robot");
        
        this->send(from_id, to, test::TEST_MSG::RSP_AUTH, rsp);

        // std::cout << "gatesvr auth success, openid: " << msg->openid() << std::endl;

        co_return;
    }

    async_simple::coro::Lazy<> login_handler(test::LoginReq* msg, const modules::agent_ptr_type& to, uint64_t from_id) {
        if (!msg) {
            std::cerr << "login invalid message param" << std::endl;
            co_return;
        }

        auto* uptr = to->user_data<user_t>();
        if (!uptr) {
            std::cerr << "user does not exist, login failed. userid: " << msg->userid() << ", roleid: " << msg->roleid() << std::endl;
            co_return;
        }

        // select a game server at random
        this->send_by_rand(game_type, test::TEST_MSG::REQ_LOGIN, *msg, 0, to->id());

        // std::cout << "gatesvr login success, to_id: " << to->id() << ", from_id: " << from_id << std::endl;

        co_return;
    }

private:
    uint32_t gen_id_ = 0;
};

class game_svr : public modules::app {
    // role data
    struct user_agent : modules::agent_type {
        using super = modules::agent_type;
        using super::super;

        uint32_t userid;
        uint32_t roleid;
        uint32_t level;
        std::string name;
        uint64_t gate_agent_id;  // It is mainly used to forward protocols to gate service
    };
public:
    using super = modules::app;
    game_svr(std::string_view svr_type, const modules::app_cfg& cfg)
    : super(svr_type, cfg) {
        // register protocol handlers
        this->register_handle(test::TEST_MSG::REQ_LOGIN, &game_svr::login_hanler, this);
    }

    async_simple::coro::Lazy<> login_hanler(test::LoginReq* msg, const modules::agent_ptr_type& to, uint64_t from_id) {
        if (!msg) {
            std::cerr << "invalid message param" << std::endl;
            co_return;
        }

        auto* user = this->create_agent<user_agent>(msg->userid(), e_agent_type::AGENT_TYPE_USER, nullptr);
        if (!user) {
            std::cerr << "get user data fail, userid " << msg->userid() << ", roleid " << msg->roleid() << std::endl;
            co_return;
        }

        // you may need to load role data from a database

        user->userid = msg->userid();
        user->roleid = msg->roleid();
        user->gate_agent_id = from_id;

        test::LoginRsp rsp; 
        test::rolebase role;
        rsp.mutable_role()->set_roleid(msg->roleid());
        rsp.mutable_role()->set_name("robot");
        this->send(from_id, user->id(), test::TEST_MSG::RSP_LOGIN, rsp);

        //std::cout << "gamesvr login success, to_id: " << to->id() << ", from_id: " << from_id << ", game_agent_id: " << user->id() << std::endl;

        co_return;
    }

private:
    inline static uint32_t gen_id_ = 0;
};

class robot : public modules::client_app {
    bnet::cli_cfg cfg_;
    std::atomic<int> count_ = 0;
    int64_t start_time = 0;
    bool async = true;

    // robot data
    struct robot_t {
        std::string openid;
        uint32_t roleid;
        uint32_t lv;
        std::string name;
        std::string data;
    };
public:
    using super = modules::client_app;
    robot(const bnet::cli_cfg& cfg) 
    : super(cfg)
    , cfg_(cfg) {
        // register protocol handlers
        this->register_handle(test::TEST_MSG::RSP_AUTH, &robot::auth_handler, this);
        this->register_handle(test::TEST_MSG::RSP_LOGIN, &robot::login_handler, this);
    }

    inline void start() {
        start_time = modules::timer::get_time_seconds();
        for (size_t i = 0; i < 20000; i++) {
            if (async) {
                //init(i).via(modules::get_global_executor()).detach();
                init(i).start([](auto&&){});
            }
            else {
                modules::cli_net_stream_type::conn_params p {
                    host: cfg_.host,
                    port: cfg_.port,
                };
                if (auto ec = sync_connect(p); ec ) {
                    continue;
                }
                test::AuthReq req;
                req.set_openid("1-10023132"+std::to_string(i));
                this->send(p.sptr, test::TEST_MSG::REQ_AUTH, req);
            }
        }
        // std::cout << "start passtime " << modules::timer::get_time_seconds() - start_time << std::endl;
    }

    inline async_simple::coro::Lazy<void>
    init(int i) {
        modules::cli_net_stream_type::conn_params p {
            host: cfg_.host,
            port: cfg_.port,
        };

        if (auto ec = co_await connect(p); ec) {
            std::cerr << "connection fail, err msg: " << ec.message() << std::endl;
            co_return;
        }
        if (!p.sptr) {
            std::cerr << "invalid session ptr" << std::endl;
            co_return;
        }

        test::AuthReq req;
        req.set_openid("1-10023132"+std::to_string(i));
        this->send(p.sptr, test::TEST_MSG::REQ_AUTH, req);
        co_return;
    }

    async_simple::coro::Lazy<> auth_handler(test::AuthRsp* msg, const modules::agent_ptr_type& to, uint64_t from_id) {
        if (!msg) {
            std::cerr << "invalid message param" << std::endl;
            co_return;
        }
        
        if (msg->roles_size() > 0) {
            // select role
            auto role = msg->roles().at(0);
            // login
            test::LoginReq req;
            req.set_userid(msg->userid());
            req.set_roleid(role.roleid());
            this->send(from_id, to, test::TEST_MSG::REQ_LOGIN, req);
        }
        else {
            // create role

        }
        
        // std::cout << "robot auth success" << std::endl;

        co_return;
    }

    async_simple::coro::Lazy<> login_handler(test::LoginRsp* msg, const modules::agent_ptr_type& to, uint64_t from_id, const modules::s_session_ptr_type& from_session) {
        if (!msg) {
            std::cerr << "invalid message param" << std::endl;
            co_return;
        }

        count_++;
        if (count_ == 19999) {
            std::cout << "robot login success " << count_ << ", passtimer " << modules::timer::get_time_seconds() - start_time << std::endl;
        }

        // std::cout << "robot login success. roleid: " << msg->role().roleid() << " name: " << msg->role().name() << std::endl;

        co_return;
    }

};

void test_net() {
    // gate service
    static gate_server gate(gate_type, get_gate_config());
    // game service
    static game_svr game(game_type, get_game_config());

    // This logic then depends on the cluster's service discovery, This writing is for testing purposes only
    // You can use etcd, for example, as a cluster for service discovery
    gate.get_net()->sync_add_server(game.get_server_cluster_info());
    game.get_net()->sync_add_server(gate.get_server_cluster_info());
    
    bnet::cli_cfg cfg {
        host: "127.0.0.1",
        port: "11001",
        conn_timeout: 10000,
    };
    // test robot
    static robot robot(cfg);
    robot.start();
}