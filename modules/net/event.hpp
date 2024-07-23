#pragma once

#include "agent/agent.hpp"

// User-defined events

namespace modules {
namespace net {
struct user_event {
    using handle_connect_type = std::function<void(const modules::agent_ptr_type&)>;
    using handle_disconnect_type = std::function<void(const modules::agent_ptr_type&)>;

    inline void set_handle_connect(handle_connect_type&& f) { connect_ = f; }
    inline void set_handle_disconnect(handle_disconnect_type&& f) { disconnect_ = f; }

    handle_connect_type connect_;
    handle_disconnect_type disconnect_;
};

} // namespace net
} // namespace modules