#pragma once

#include <functional>
#include "queue.hpp"

namespace modules {
namespace agt {
template <typename T>
class mailbox {
public:
    mailbox() {}
    mailbox(const mailbox&) = delete;
    mailbox& operator=(const mailbox&) = delete;

    inline auto push_back(T&& t) {
        return qu_.push_back(std::move(t));
    }

    inline auto push_front(T&& t) {
        return qu_.push_front(std::move(t));
    }

    inline auto pop_front(T& t) {
        return qu_.pop_front(t);
    }

    inline auto size() {
        return qu_.size();
    }

    inline void stop() {
        qu_.stop();
    }

    inline auto is_stop() {
        return qu_.is_stop();
    }

protected:
    mb_queue<T> qu_;
};

} // namespace agt
} // namespace modules