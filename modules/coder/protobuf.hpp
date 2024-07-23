#pragma once

#include <string_view>
#include "google/protobuf/message.h"

namespace modules {
struct protobuf_coder {
    static bool deserialize(::google::protobuf::Message& msg, std::string_view buffer) {
        return msg.ParseFromString(buffer);
    }

    static bool serialize(const ::google::protobuf::Message& msg, std::string& buffer) {
        return msg.SerializeToString(&buffer);
    }
};

}