#pragma once

#include <iostream>
#include <asio.hpp>
#include "redis/resp.hpp"

// redis protocol

namespace modules {
namespace protocol {
class rds_protocol {
public:
    template<class ... FArgs>
	explicit rds_protocol([[maybe_unused]] FArgs&&... args) {}

    using result_type = rds::object;
    using iterator = asio::buffers_iterator<asio::streambuf::const_buffers_type>;
	using diff_type = typename iterator::difference_type;
    static std::pair<iterator, bool> match_func(iterator begin, iterator end, rds::object& obj) {
        auto size = static_cast<std::size_t>(end - begin);
        if (size <= 0) {
            return std::pair(begin, false);
        }
        rds::resp_parse rparse((char*)begin.operator->(), size);
        auto ret = rparse.decode(obj);
        if (ret == REDIS_OK) {
			//std::cout << "========================================" << std::endl;
            return std::pair(begin + static_cast<diff_type>(rparse.offset()), true);
		}
		else if (ret == EOS) {
			//std::cout << "resp data parse finish." << std::endl;
			return std::pair(end, false);
		}
		else if (ret == REDIS_ERR) {
			//std::cout << "data is not received completely; resp protocol data parse fail." << std::endl;
		}

        return std::pair(begin, false);
    }
};   

}   // namespace protocol
}   // namespace modules