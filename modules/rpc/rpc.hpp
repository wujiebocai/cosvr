#pragma once

#include "rpc_context.hpp"
#include "rpc_client.hpp"
#include "rpc_server.hpp"

namespace modules {
namespace rpc {
using bnet::svr_cfg;
using bnet::cli_cfg;

template <typename RetType>
using rpc_context = rpc_context_tpl<RetType, typename rpc_server::context_data_type>;

} // namespace rpc
} // namespace modules