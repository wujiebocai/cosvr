#pragma once

#include "cluster.hpp"
#include "pubsub.hpp"
#include "cluster.hpp"

namespace modules {
namespace rds {
using bnet::cli_cfg;

template<typename ClusterPolicy>
class redis_imp {
public:
    explicit redis_imp(const redis_config& cfg)
        : cluster_(cfg) { }

    inline auto
    init() { 
        return cluster_.get_policy()->init();
    }

    inline auto
    sync_init() {
        return async_simple::coro::syncAwait(init());
    }

    template<class... Args>
    inline async_simple::coro::Lazy<object>
    execute(Args&&... args) { 
        return cluster_.get_policy()->execute(std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline auto
    sync_execute(Args &&...args) {
        return async_simple::coro::syncAwait(execute(std::forward<Args>(args)...));
    }

    /*!
     * Gets a publish subscription object.
     * This object implements a subscription-related interface that can provide subscription operations.
    */
    inline auto
    get_pubsub() {
        return cluster_.get_pubsub_mgr()->get_pubsub();
    }

    inline auto
    sync_get_pubsub() {
        return async_simple::coro::syncAwait(get_pubsub());
    }

    /*!
     * Posts a message to the given channel.
     *
     * In a Redis Cluster clients can publish to every node. 
     * The cluster makes sure that published messages are forwarded as needed, 
     * so clients can subscribe to any channel by connecting to any one of the nodes.
     * @note that in a Redis Cluster, only clients that are connected to the same node as the publishing client are included in the count.
     * @param channel
     * @param data
     * @return Integer reply: the number of clients that received the message. 
    */
    template<typename DataType>
    inline auto
    publish(const std::string& channel, DataType&& data) { 
        return execute("publish", channel, std::forward<DataType>(data));
    }
    
    template<typename DataType>
    inline auto
    sync_publish(const std::string& channel, DataType&& data) { 
        return sync_execute("publish", channel, std::forward<DataType>(data));
    }

    /*!
     * Posts a message to the given shard channel.
     *
     * In Redis Cluster, shard channels are assigned to slots by the same algorithm used to assign keys to slots. 
     * A shard message must be sent to a node that own the slot the shard channel is hashed to. 
     * The cluster makes sure that published shard messages are forwarded to all the node in the shard, 
     * so clients can subscribe to a shard channel by connecting to any one of the nodes in the shard.
     * @note that in a Redis Cluster, only clients that are connected to the same node as the publishing client are included in the count.
     * @param shardchannel
     * @param data
     * @return Integer reply: the number of clients that received the message. 
    */
    template<typename DataType>
    inline auto
    spublish(const std::string& shardchannel, DataType&& data) { 
        return execute("spublish", shardchannel, std::forward<DataType>(data));
    }
    
    template<typename DataType>
    inline auto
    sync_spublish(const std::string& shardchannel, DataType&& data) { 
        return sync_execute("spublish", shardchannel, std::forward<DataType>(data));
    }

    /*!
     * Lists the currently active channels.
     *
     * An active channel is a Pub/Sub channel with one or more subscribers (excluding clients subscribed to patterns).
     * If no pattern is specified, all the channels are listed, otherwise if pattern is specified only 
     * channels matching the specified glob-style pattern are listed.
     * 
     * Cluster note: in a Redis Cluster clients can subscribe to every node, 
     * and can also publish to every other node. The cluster will make sure that published messages are forwarded as needed. 
     * That said, PUBSUB's replies in a cluster only report information from the node's Pub/Sub context, rather than the entire cluster.
     * @param args subscribe pattern ...
     * @return Array reply: a list of active channels, optionally matching the specified pattern.
    */
    template <typename... Args>
    inline auto
    pubsub_channels(Args&&... args) { 
        return execute("pubsub", "channels", std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline auto
    sync_pubsub_channels(Args&&... args) { 
        return sync_execute("pubsub", "channels", std::forward<Args>(args)...);
    }

    /*!
     * Returns the number of unique patterns that are subscribed to by clients (that are performed using the PSUBSCRIBE command).
     * Note that this isn't the count of clients subscribed to patterns, but the total number of unique patterns all the clients are subscribed to.
     * 
     * Cluster note: in a Redis Cluster clients can subscribe to every node, and can also publish to every other node. 
     * The cluster will make sure that published messages are forwarded as needed. 
     * That said, PUBSUB's replies in a cluster only report information from the node's Pub/Sub context, rather than the entire cluster.
     * @return Integer reply: the number of patterns all the clients are subscribed to.
    */
    inline auto
    pubsub_numpat() { 
        return execute("pubsub", "numpat");
    }
    
    inline auto
    sync_pubsub_numpat() { 
        return sync_execute("pubsub", "numpat");
    }

    /*!
     * Returns the number of subscribers (exclusive of clients subscribed to patterns) for the specified channels.
     * Note that it is valid to call this command without channels. In this case it will just return an empty list.
     * 
     * Cluster note: in a Redis Cluster clients can subscribe to every node, and can also publish to every other node. 
     * The cluster will make sure that published messages are forwarded as needed. That said, PUBSUB's replies in a cluster only 
     * report information from the node's Pub/Sub context, rather than the entire cluster.
     * @param args channel ...
     * @return Array reply: the number of subscribers per channel, each even element (including the 0th) is channel name, 
     *         each odd element is the number of subscribers
    */
    template <typename... Args>
    inline auto
    pubsub_numsub(Args&&... args) { 
        return execute("pubsub", "numsub", std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline auto
    sync_pubsub_numsub(Args&&... args) { 
        return sync_execute("pubsub", "numsub", std::forward<Args>(args)...);
    }

    /*!
     * Lists the currently active shard channels.
     *
     * An active shard channel is a Pub/Sub shard channel with one or more subscribers.
     * If no pattern is specified, all the channels are listed, otherwise if pattern is specified 
     * only channels matching the specified glob-style pattern are listed.
     * The information returned about the active shard channels are at the shard level and not at the cluster level.
     * @param args subscribe pattern ...
     * @return Array reply: a list of active channels, optionally matching the specified pattern.
    */
    template <typename... Args>
    inline auto
    pubsub_shardchannels(Args&&... args) { 
        return execute("pubsub", "shardchannels", std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline auto
    sync_pubsub_shardchannels(Args&&... args) { 
        return sync_execute("pubsub", "shardchannels", std::forward<Args>(args)...);
    }

    /*!
     * Returns the number of subscribers for the specified shard channels.
     * Note that it is valid to call this command without channels, in this case it will just return an empty list.
     * Cluster note: in a Redis Cluster, PUBSUB's replies in a cluster only report information from the node's Pub/Sub context, 
     * rather than the entire cluster.
     * @param args channel ...
     * @return Array reply: the number of subscribers per shard channel, each even element (including the 0th) is channel name, 
     *         each odd element is the number of subscribers.
    */
   template <typename... Args>
    inline auto
    pubsub_shardnumsub(Args&&... args) { 
        return execute("pubsub", "shardnumsub", std::forward<Args>(args)...);
    }

    template <typename... Args>
    inline auto
    sync_pubsub_shardnumsub(Args&&... args) { 
        return sync_execute("pubsub", "shardnumsub", std::forward<Args>(args)...);
    }

    // eval script numkeys [key [key ...]] [arg [arg ...]]
    template <typename... Args>
    inline async_simple::coro::Lazy<object>
    eval_exe(const std::string& eval_cmd, const std::string& script, int32_t key_num, Args&&... args) {
        if constexpr (std::is_same_v<ClusterPolicy, rds::cluster_policy_single_node>) {
            return cluster_.get_policy()->execute(eval_cmd, script, key_num, std::forward<Args>(args)...);
        }
        else {
            return cluster_.get_policy()->eval_exe(eval_cmd, script, key_num, std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    inline auto
    sync_eval_exe(const std::string& eval_cmd, const std::string& script, int32_t key_num, Args&&... args) { 
        return async_simple::coro::syncAwait(this->eval_exe(eval_cmd, script, key_num, std::forward<Args>(args)...));
    }
private:
    cluster_imp<ClusterPolicy> cluster_;
};

} // namespace rds

using redis_type = rds::redis_imp<rds::cluster_policy_single_node>;
using redis_cluster_type = rds::redis_imp<rds::cluster_policy_hash_slot>;

} // namespace modules