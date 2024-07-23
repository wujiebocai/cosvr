#pragma once

#include <bnet.hpp>
#include "protocol/rds_protocol.hpp"

namespace modules::rds {
// net type
using namespace bnet;
using rds_protocol_type = protocol::rds_protocol;
using rds_net_type = txt_cli<rds_protocol_type>;
using session_type = typename rds_net_type::session_type;
using session_ptr_type = typename rds_net_type::session_ptr_type;
using session_weakptr_type = typename rds_net_type::session_weakptr_type;
using key_type = typename session_type::key_type;
}