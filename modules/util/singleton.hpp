#pragma once
#include <thread>
#include <mutex>
#include <iostream> 

namespace modules {
template <typename T>
class singleton {
public:
    template<class ... Args>
    inline static T& instance(Args&&... args) {
        static T ins(std::forward<Args>(args)...);
        return ins;
    }
};
}
