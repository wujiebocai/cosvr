#pragma once

#include <deque>
#include <async_simple/coro/ConditionVariable.h>
#include <async_simple/coro/Lazy.h>
#include <async_simple/coro/SpinLock.h>

namespace modules {
namespace agt {
template <typename T>
struct mb_queue {
    void push_back(T&& item) {
        {
            std::scoped_lock lock(mutex_);
            qu_.push_back(std::move(item));
        }
        cv_.notifyOne();
    }

    bool try_push_back(const T &item) {
        {
            std::unique_lock lock(mutex_, std::try_to_lock);
            if (!lock)
                return false;
            qu_.push_back(std::move(item));
        }
        cv_.notifyOne();
        return true;
    }

    void push_front(T&& item) {
        {
            std::scoped_lock lock(mutex_);
            qu_.push_front(std::move(item));
        }
        cv_.notifyOne();
    }

    bool try_push_front(const T &item) {
        {
            std::unique_lock lock(mutex_, std::try_to_lock);
            if (!lock)
                return false;
            qu_.push_front(std::move(item));
        }
        cv_.notifyOne();
        return true;
    }

    async_simple::coro::Lazy<bool> pop_front(T& item) {
        std::unique_lock lock(mutex_);
        co_await cv_.wait(mutex_, [&]() { return !qu_.empty() || stop_; });
        if (qu_.empty())
            co_return false;
        item = std::move(qu_.front());
        qu_.pop_front();
        co_return true;
    }

    bool try_pop_front(T &item) {
        std::unique_lock lock(mutex_, std::try_to_lock);
        if (!lock || qu_.empty())
            return false;

        item = std::move(qu_.front());
        qu_.pop_front();
        return true;
    }

    bool try_pop_front_if(T &item, bool (*predict)(T &) = nullptr) {
        std::unique_lock lock(mutex_, std::try_to_lock);
        if (!lock || qu_.empty())
            return false;

        if (predict && !predict(qu_.front())) {
            return false;
        }

        item = std::move(qu_.front());
        qu_.pop_front();
        return true;
    }

    std::size_t size() const {
        std::scoped_lock guard(mutex_);
        return qu_.size();
    }

    bool empty() const {
        std::scoped_lock guard(mutex_);
        return qu_.empty();
    }

    void stop() {
        {
            std::scoped_lock guard(mutex_);
            stop_ = true;
        }
        cv_.notifyAll();
    }

    inline auto is_stop() {
        return stop_;
    }

protected:
    std::deque<T> qu_;
    async_simple::coro::SpinLock mutex_;
    async_simple::coro::ConditionVariable<async_simple::coro::SpinLock> cv_;

    bool stop_ = false;
};
} // namespace agt
} // namespace modules