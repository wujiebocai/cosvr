#pragma once

#include <cstdint>
#include <string_view>
#include "util/type_traits.hpp"
#include "protobuf.hpp"
#include "json.hpp"
#include "stream.hpp"

namespace modules {
enum coder_type : uint8_t {
    CODERTYPE_PROTOBUF  = 1,
    CODERTYPE_JSON      = 2,
    CODERTYPE_STREAM    = 3,
};

template<typename T>
concept is_protobuf = std::is_base_of_v<::google::protobuf::Message, modules::unqualified_t<T>>;
template<typename T>
concept is_js = std::is_same_v<nlohmann::json, modules::unqualified_t<T>>;
template<typename T>
concept is_stream = std::is_trivial_v<modules::unqualified_t<T>> && std::is_standard_layout_v<modules::unqualified_t<T>>;
template<typename T>
concept is_coder = is_protobuf<T> || is_js<T> || is_stream<T>;

struct coder {
    template <typename T, typename Buffer>
    inline static bool deserialize(T& t, Buffer&& buffer) {
        if constexpr (is_protobuf<T>) {
            return protobuf_coder::deserialize(t, std::forward<Buffer>(buffer));
        }
        else if constexpr (is_js<T>) {
            return json_coder::deserialize(t, std::forward<Buffer>(buffer));
        }
        else if constexpr (is_stream<T>) {
            return stream_coder::deserialize(t, std::forward<Buffer>(buffer));
        }
        
        return false;
    }

    template <typename T, typename Buffer>
    inline static bool serialize(const T& t, Buffer& buffer) {
        if constexpr (is_protobuf<T>) {
            return protobuf_coder::serialize(t, buffer);
        }
        else if constexpr (is_js<T>) {
            return json_coder::serialize(t, buffer);
        }
        else if constexpr (is_stream<T>) {
            return stream_coder::serialize(t, buffer);
        }

        return false;
    }

    template<typename T, coder_type ct>
    inline static constexpr bool check_valid() {
        if constexpr (ct == CODERTYPE_PROTOBUF && is_protobuf<T>) {
            return true;
        }
        if constexpr (ct == CODERTYPE_JSON && is_js<T>) {
            return true;
        }
        if constexpr (ct == CODERTYPE_STREAM && is_stream<T>) {
            return true;
        }

        return false;
    }
};

}