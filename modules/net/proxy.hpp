#pragma once

#include "agent/agent.hpp"

namespace modules {
namespace net {
// During the remote agent communication, a proxy is created on the local device. 
// The proxy id is the same as that of the remote agent
class proxy : public agt::agent {
public:
    using super = agt::agent;
    using super::super;
    using transfer_fun_type = std::function<bool(uint64_t, uint64_t, uint32_t, const std::string&)>;
    using cancel_fun_type = std::function<bool()>;

    com_errors enqueue(router_key_type msgid, const std::string& data, const agent_ptr_type& from, bool is_strand = false) override {
        auto ret = super::enqueue(msgid, data, from, is_strand);
        if (ret == com_errors::success) {
            return ret;
        }

        if (ret != com_errors::msg_is_not_exist) {
            std::cerr << "handle message fail" << ", to_id " << this->id() << ", from_id " << from->id() << ", msgid " << msgid 
                << ", ret " << ret << std::endl;
            return ret;
        }

        // The protocol processing failure is directly forwarded
        if (transfer_fun_) {
            auto ret = transfer_fun_(this->id(), from->id(), msgid, data);
            if (!ret) {
                return com_errors::transfer_fail;
            }
        }

        return com_errors::success;
    }

    com_errors enqueue(uint32_t msgid, const std::string& data, uint64_t from_id, bool is_strand = false) override {
        auto ret = super::enqueue(msgid, data, from_id, is_strand);
        if (ret == com_errors::success) {
            return ret;
        }

        if (ret != com_errors::msg_is_not_exist) {
            std::cerr << "handle message fail" << ", to_id " << this->id() << ", from_id " << from_id << ", msgid " << msgid << std::endl;
            return ret;
        }

        // The protocol processing failure is directly forwarded
        if (transfer_fun_) {
            auto ret = transfer_fun_(this->id(), from_id, msgid, data);
            if (!ret) {
                return com_errors::transfer_fail;
            }
        }

        return com_errors::success;
    }

    inline bool cancel() override { 
        if (cancel_fun_) return cancel_fun_(); 
        else return true;
    }

    inline void set_exe(std::unique_ptr<executor_wrapper<>>& exe) { exe_.swap(exe); }
    
    inline void set_transfer(transfer_fun_type&& f) { transfer_fun_ = f; }
    inline transfer_fun_type& get_transfer() { return transfer_fun_; }

    inline void set_cancel(cancel_fun_type&& f) { cancel_fun_ = f; }
private:
    std::unique_ptr<executor_wrapper<>> exe_;
    transfer_fun_type transfer_fun_;
    cancel_fun_type cancel_fun_;
};

} // namespace net

} // namespace modules