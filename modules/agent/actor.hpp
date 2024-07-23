#pragma once

#include <memory>
#include <any>
#include <async_simple/coro/Lazy.h>
#include "mailbox.hpp"

namespace modules {
namespace agt {
class actor {
public:
    using mailbox_element_type =  std::function<async_simple::coro::Lazy<>()>;
public:
    actor(const actor&) = delete;
    actor& operator=(const actor&) = delete;

    inline uint64_t id() { return id_; }
    inline uint32_t type() { return type_; }

    inline auto& executor() { return *exe_; }

    // Concurrent processing message
    bool enqueue(mailbox_element_type&& elm) {
        if (!exe_ || !elm) {
            return false;
        }

        return exe_->schedule([this, elm = std::move(elm)](){
            elm().start([](auto&&){});
        });
    }
    
    // Serial processing message
    bool enqueue_strand(mailbox_element_type&& elm) {
        if (!exe_ || !elm) {
            return false;
        }

        mailbox_.push_back(std::move(elm));
        
        return true;
    }
    
    inline auto& get_mailbox() { return mailbox_; }

    template<class DataT>
	inline void user_data(DataT&& data) {
		this->user_data_ = std::forward<DataT>(data);
	}
	template<class DataT>
    requires (!std::is_pointer_v<DataT>)
	inline DataT* user_data() {
		return std::any_cast<DataT>(&this->user_data_);
	}
    template<class DataT>
    requires (std::is_pointer_v<DataT>)
	inline DataT user_data() {
		return std::any_cast<DataT>(this->user_data_);
	}

protected:
    template <typename ExecutorType>
    explicit actor(uint64_t id, uint32_t type, ExecutorType&& exe) 
        : id_(id)
        , type_(type)
        , exe_(exe) {
        handle().via(exe).start([](auto&&){});
    }

private:
    async_simple::coro::Lazy<> handle() {
        mailbox_element_type t;
        while (!mailbox_.is_stop()) {
            if (auto ret = co_await mailbox_.pop_front(t); ret) {
                co_await t();
            }
        }
    }
    
protected:
    const uint64_t id_;
    uint32_t type_;
    async_simple::Executor *exe_;
    mailbox<mailbox_element_type> mailbox_;
    std::any user_data_;
};

} // namespace agt
} // namespace modules