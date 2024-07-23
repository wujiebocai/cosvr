#pragma once

#include <bnet/tool/bytebuffer.hpp>
#include "google/protobuf/message.h"
#include "coder/coder.hpp"

// net protocol

namespace modules {
namespace protocol {
using namespace bnet;

//struct net_header_bit {
//    uint16_t opcode 	: 8;
//    uint16_t encrypt	: 3;
//	  uint16_t coder_type : 3;
//    uint16_t is_lzo 	: 1;
//	  uint16_t is_error 	: 1;
//};

struct net_header {
    uint8_t version;		// protocol version
	uint8_t opcode;			// operation code
	uint8_t coder_type;		// coder type (protobuf, json, struct)
    uint32_t length;		// length of message body
    uint32_t msg_id;		// message id
	uint64_t to_id;			// target agent id
	uint64_t from_id;		// source agent id
};

// 加密解密处理
struct handle_encrypt {
	inline static bool handle_encode(net_header& head, std::string_view& data) {
		/* code */
		return true;
	}
	inline static bool handle_decode(net_header& head, char* data, int len) {
		/* code */
		return true;
	}
};

// 压缩解压缩处理
struct handle_compressed {
	inline static bool handle_encode(net_header& head, std::string_view& data) {
        /* code */
		return true;
	}
	inline static bool handle_decode(net_header& head, char* data, int len) {
		/* code */
		return true;
	}
};

template<typename... Args>
inline void reverse_handle(Args... args) {}

template<class... Handle>
struct net_proto {
    using route_key_t = uint32_t;
	using header_type = net_header;
    static constexpr auto HEAD_SIZE = sizeof(net_header); 
    static constexpr auto SEND_MAX_LEN = 65535;
    static constexpr auto CODER_TYPE = modules::coder_type::CODERTYPE_PROTOBUF;

	inline static int unpack(const char* data, const std::size_t len, net_header& out_head, std::string& out_data) {
		if (HEAD_SIZE > len) {
			return 0;
		}

        out_head = *(net_header*)data;
		if (out_head.length <= 0) {
			return HEAD_SIZE;
		}

        auto msglen = out_head.length + HEAD_SIZE;
		if (msglen > len) {
			return 0;
		}

		bool ret = true;
		reverse_handle((ret ? ret = Handle::handle_decode(out_head, const_cast<char*>(data + HEAD_SIZE), out_head.length) : false)...);
		if (!ret) {
			return -1;
		}

        out_data.append(data + HEAD_SIZE, out_head.length);

		return msglen;
	}

	inline static bool pack(std::string_view data, net_header& head, std::string& out_data) {
		auto datalen = data.size();
        auto length = datalen + HEAD_SIZE;
		if (length >= SEND_MAX_LEN) {
			return false;
		}

		out_data.reserve(length);
		
        head.length = datalen;
        head.coder_type = CODER_TYPE;
        bool ret = true;
		((ret ? ret = Handle::handle_encode(head, data) : false), ...);
		if (!ret) {
			return false;
		}

		out_data.append((char*)&head, HEAD_SIZE);
		out_data.append(data.data(), data.length());

        return true;
	}

    template <typename T, typename Buffer>
    inline static bool deserialize(T& t, Buffer&& buffer) {
        return coder::deserialize(t, std::forward<Buffer>(buffer));
    }

    template <typename T, typename Buffer>
    inline static bool serialize(const T& t, Buffer& buffer) {
        return coder::serialize(t, buffer);
    }
};

}   // namespace protocol
}   // namespace modules