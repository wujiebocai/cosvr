#pragma once

#include "policy.hpp"
#include "pubsub.hpp"

namespace modules {
namespace rds {
template<typename ClusterPolicy>
class cluster_imp : public rds_net_type {
public:
    using super_type = rds_net_type;
    using policy_ptr_type = std::unique_ptr<ClusterPolicy>;
    using pubsub_ptr_type = std::unique_ptr<pubsub_mgr>;

    explicit cluster_imp(const redis_config& cfg) 
        : super_type(cfg.net_config())
        , policy_(std::make_unique<ClusterPolicy>(this, cfg)) 
        , pubsub_(std::make_unique<pubsub_mgr>(this, cfg)) {
        this->bind(event::connect, &cluster_imp::connect_cb, this);
        this->bind(event::disconnect, &cluster_imp::disconnect_cb, this);
    }

    inline ClusterPolicy* get_policy() { return policy_.get(); }
    inline pubsub_mgr* get_pubsub_mgr() { return pubsub_.get(); }
private:
    inline void connect_cb([[maybe_unused]]session_ptr_type& ptr) {
		std::cout << "redis client connect success" << std::endl;
	}

    inline void disconnect_cb([[maybe_unused]]session_ptr_type& ptr, error_code ec) {
		std::cout << "redis client disconnect" << ec.message() << std::endl;
	}

private:
    policy_ptr_type policy_;
    pubsub_ptr_type pubsub_;
};

} // namespace rds

} // namespace modules