#pragma once

#include <string_view>

namespace modules {
struct stream_coder {
    template<typename T>
    static bool deserialize(T& t, std::string_view buffer) {
        auto size = buffer.size();
        auto tsize = sizeof(T);
        if (tsize != size) {
            return false;
        }

        t = *(T*)buffer.data();
        return true;
    }

    template<typename T>
    static bool serialize(const T& t, std::string& buffer) {
        auto size = sizeof(T);
        buffer.reserve(size);
        buffer.assign((char*)&t, size);
        return true;
    }
};
}