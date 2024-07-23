#pragma once

#include <bnet.hpp>

namespace modules {
namespace net {
using namespace bnet;

template<typename NetType, typename ProtoType, typename CfgType>
class stream : public NetType {
public:
    using super = NetType;
    using session_type = typename NetType::session_type;
	using session_ptr_type = typename NetType::session_ptr_type;
	using session_weakptr_type = typename NetType::session_weakptr_type;
	using msgid_type = typename ProtoType::route_key_t;
	using header_type = typename ProtoType::header_type;
	using handle_message_type = std::function<void(header_type&, const session_ptr_type&, const std::string&)>;
public:
    explicit stream(CfgType cfg)
	: super(cfg) {
        this->bind(event::recv, &stream::recv_cb, this);
    }

    inline void start() {
        super::start();
    }

    inline void stop() {
        super::stop();
    }

	inline bool send(std::size_t sid, header_type& head, const std::string& data) {
		auto sptr = this->globalctx().sessions_.get_by_key(sid);
		if (!sptr) {
			return false;
		}

		return this->send(sptr, head, data);
	}

	inline bool broadcast(const std::vector<std::size_t>& sids, header_type& head, const std::string& data) {
		std::string packdata;
		auto ret = ProtoType::pack(data, head, packdata);
		if (!ret) {
			return false;
		}

		for (auto& sid : sids) {
			auto ptr = this->globalctx().sessions_.get_by_key(sid);
		    if (ptr) ptr->send(packdata);
		}

		return true;
	}

    template<is_coder T>
    inline bool send(std::size_t sid, header_type& head, T&& msg) {
        auto sptr = this->globalctx().sessions_.get_by_key(sid);
		if (!sptr) {
			return false;
		}

        return this->send(sptr, head, std::forward<T>(msg));
    }

    template<is_coder T>
    inline bool broadcast(const std::vector<std::size_t>& sids, header_type& head, T&& msg) {
        std::string data;
        if (!ProtoType::serialize(std::forward<T>(msg), data)) {
            return false;
        }

        return this->broadcast(sids, head, data);
    }

// ------------------ static imp ---------------------------------
	inline bool send(const session_ptr_type& ptr, header_type& head, const std::string& data) {
		if (!ptr) {
			return false;
		}

		std::string packdata;
		auto ret = ProtoType::pack(data, head, packdata);
		if (!ret) {
			return false;
		}

		ptr->send(std::move(packdata));
		return true;
	}

	inline bool broadcast(const std::vector<session_ptr_type>& ptrs, header_type& head, const std::string& data) {
		std::string packdata;
		auto ret = ProtoType::pack(data, head, packdata);
		if (!ret) {
			return false;
		}

		for (auto& ptr : ptrs) {
			ptr->send(packdata);
		}
		return true;
	}

	template<is_coder T>
    inline bool send(const session_weakptr_type& wptr, header_type& head, T&& msg) {
        auto ptr = wptr.lock();
		if (!ptr) {
			return false;
		}

        return this->send(ptr, head, msg);
    }

	template<is_coder T>
    inline bool send(const session_ptr_type& ptr, header_type& head, T&& msg) {
		if (!ptr) {
			return false;
		}
		
        std::string data;
        if (!ProtoType::serialize(std::forward<T>(msg), data)) {
            return false;
        }

        return this->send(ptr, head, data);
    }

    template<is_coder T>
    inline bool broadcast(const std::vector<session_ptr_type>& ptrs, header_type& head, T&& msg) {
        std::string data;
        if (!ProtoType::serialize(std::forward<T>(msg), data)) {
            return false;
        }

        return this->broadcast(ptrs, head, data);
    }

	void set_handle_message(const handle_message_type& f) { handle_msg_ = f; }
private:
    inline void recv_cb(const session_ptr_type& ptr, std::string_view&& s) {
		if (s.size() <= 0) {
			return;
		}
		auto& rbuf = ptr->rbuffer();
		rbuf.put(s.data(), s.size());

		const char* buffstart = rbuf.rd_buf();
		const auto bufflen = rbuf.rd_size();
		int totallen = 0, len = 0;
		do {
			std::string data;
			header_type head;
			len = ProtoType::unpack(buffstart + totallen, bufflen - totallen, head, data);
			if (len > 0) {
				totallen += len;
				if (handle_msg_) AS_LIKELY handle_msg_(head, ptr, data);
			}
			if (len < 0) {
				rbuf.reset();
				totallen = 0;
			}
		} while (len > 0);

		if (totallen > 0) {
			rbuf.rd_flip(totallen);
		}
	}

private:
	handle_message_type handle_msg_;
};

} // namespace net
} // namespace modules