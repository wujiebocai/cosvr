#pragma once

#include "error/error.hpp"

namespace modules {
//constexpr error err_success(0, "success");
//constexpr error err_invalid_param(1, "invalid param");
//constexpr error err_connet_fail(2, "connect fail");

// error code
ERR_ENUM_CATEGORY_BEGIN(com, 
    success = 0,
    invalid_param,
    agent_is_not_exist, 
    msg_is_not_exist, 
    protocol_format_err,
    enqueue_msg_fail,
    transfer_fail,
    io_error,
    logic_error,
    init_error,

    connect_fail,
    connection_is_disconnected,
    connecting_unable_operate,
    reconnect_fail,
    auth_passwd_fail,
    switch_resp_fail,
    init_cluster_slots_fail,
    cluster_is_going_down,
    data_type_error,
    server_rsp_error,
    parse_string_failure,
    asking_failure,
    invalid_data,
    not_reached,
    invalid_address,
    operation_failure,
    config_error,
    switch_protocol_fail,
    auth_fail,
    null_value,
    keys_at_diffrent_slot,
    cluster_is_not_ready,

    other
)

// error code, errmsg
ERR_ENTRY(success, "success")
ERR_ENTRY(invalid_param, "invalid param")
ERR_ENTRY(agent_is_not_exist, "agent is not exist")
ERR_ENTRY(msg_is_not_exist, "messsage is not exist")
ERR_ENTRY(protocol_format_err, "the protocol format is invalid")
ERR_ENTRY(enqueue_msg_fail, "enqueue messsage fail")
ERR_ENTRY(transfer_fail, "transfer messsage fail")
ERR_ENTRY(io_error, "error in read or write")
ERR_ENTRY(logic_error, "logic error")
ERR_ENTRY(init_error, "initialization error")
ERR_ENTRY(connect_fail, "connect fail")
ERR_ENTRY(connection_is_disconnected, "connection is disconnected")
ERR_ENTRY(connecting_unable_operate, "connecting unable operate")
ERR_ENTRY(reconnect_fail, "reconnect fail")
ERR_ENTRY(auth_passwd_fail, "auth passwd fail")
ERR_ENTRY(switch_resp_fail, "switch resp protocol fail")
ERR_ENTRY(init_cluster_slots_fail, "init cluster slots fail")
ERR_ENTRY(cluster_is_going_down, "cluster is going down")
ERR_ENTRY(data_type_error, "data type error")
ERR_ENTRY(server_rsp_error, "the server returns an error message")
ERR_ENTRY(parse_string_failure, "parsing string failure")
ERR_ENTRY(asking_failure, "asking failure")
ERR_ENTRY(invalid_data, "invalid data")
ERR_ENTRY(not_reached, "not reached")
ERR_ENTRY(invalid_address, "invalid address")
ERR_ENTRY(operation_failure, "operation failure")
ERR_ENTRY(config_error, "config error")
ERR_ENTRY(switch_protocol_fail, "switch protocol fail")
ERR_ENTRY(auth_fail, "auth fail")
ERR_ENTRY(null_value, "null value")
ERR_ENTRY(keys_at_diffrent_slot, "crossslot keys in request don't hash to the same slot")
ERR_ENTRY(cluster_is_not_ready, "the cluster is not ready")
ERR_ENTRY(other, "other error")
ERR_ENUM_CATEGORY_END(com)


inline auto get_com_err_message(com_errors err) {
    static com_category instance;
    return instance.message(err);
}

}

ERR_STD_CODE_ENUM(modules, com)