#pragma once

#include <cstdint>

namespace modules {
// agent type
enum e_agent_type : uint8_t {
    AGENT_TYPE_DEFUALT = 0,
    AGENT_TYPE_PROXY = 1,

    // 1-127 Reserved for use by the architecture itself for subsequent expansion; 
    AGENT_TYPE_SYS_MAX = 128, 
};

}