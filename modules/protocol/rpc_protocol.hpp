#pragma once

#include "google/protobuf/message.h"
#include "bnet/tool/bytebuffer.hpp"

// rpc protocol

namespace modules {
namespace protocol {
class rpc_proto {
public:
    template<class ... FArgs>
	explicit rpc_proto([[maybe_unused]] FArgs&&... args) {}

    struct req_header {
        uint8_t version;
        uint8_t coder_type;
        uint8_t msg_type;
        uint32_t seq_num;
        uint32_t function_id;
        uint32_t length;
        uint32_t reserved;
    };

    struct rsp_header {
        uint8_t version;
        uint8_t err_code;
        uint8_t msg_type;
        uint32_t seq_num;
        uint32_t length;
        uint32_t reserved;
    };

    static constexpr auto REQ_HEAD_SIZE = sizeof(req_header);
    static constexpr auto RSP_HEAD_SIZE = sizeof(rsp_header);

    using route_key_t = uint32_t;

    template<typename... Args>
    static void pack_req(bnet::dynamic_buffer<>& buffer, uint32_t funcid, Args&&... args) {
        auto &header = *(req_header *)buffer.wr_buf();
        header = {};
        header.function_id = funcid;

        buffer.wr_flip(REQ_HEAD_SIZE);
        if constexpr (sizeof...(Args) == 1) {
            rpc_proto::serialize(buffer, std::forward<Args>(args)...);
        }
        header.length = buffer.rd_size() - REQ_HEAD_SIZE;
    }

    static void pack_rsp(bnet::dynamic_buffer<>& buffer, std::errc rpc_err_code = {}, std::string_view msg_data = {}) {
        auto& header = *(rsp_header*)buffer.wr_buf();
        header = {};
        header.err_code = static_cast<uint8_t>(rpc_err_code);

        buffer.wr_flip(RSP_HEAD_SIZE);
        buffer.put(msg_data.data(), msg_data.length());
        header.length = buffer.rd_size() - RSP_HEAD_SIZE;
    }

    static void pack_rsp(bnet::dynamic_buffer<>& buffer, const ::google::protobuf::Message& msg) {
        auto& header = *(rsp_header*)buffer.wr_buf();
        header = {};
        buffer.wr_flip(RSP_HEAD_SIZE);
        rpc_proto::serialize(buffer, msg);
        header.length = buffer.rd_size() - RSP_HEAD_SIZE;
    }

    static bool serialize(bnet::dynamic_buffer<>& buffer, const ::google::protobuf::Message& msg) {
        auto len = msg.ByteSizeLong();
        buffer.wr_reserve(len);
        auto ret = msg.SerializeToArray(buffer.wr_buf(), buffer.wr_size());
        if (ret) {
            buffer.wr_flip(len);
        }
        return ret;
    }
    //static bool serialize(bnet::dynamic_buffer<>& buffer) { return true; }

    static bool deserialize(std::string_view buffer, ::google::protobuf::Message& msg) {
        return msg.ParseFromArray(buffer.data(), buffer.size());
    }
    //static bool deserialize(std::string_view buffer) { return true; }
};

}   // namespace protocol
}   // namespace modules