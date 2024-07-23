#pragma once

#include "util/expected.hpp"

namespace modules::rds {
// val type
#define REDIS_TYPE_INVALID -1
#define REDIS_TYPE_NIL 0
#define REDIS_TYPE_STRING 1 	// cpp type std::string
#define REDIS_TYPE_ARRAY 2		// cpp type std::vector
#define REDIS_TYPE_INTEGER 3 	// cpp type int64_t
#define REDIS_TYPE_STATUS 4		// cpp type std::string
#define REDIS_TYPE_ERROR 5		// cpp type std::string
#define REDIS_TYPE_DOUBLE 6 	// cpp type double
#define REDIS_TYPE_BOOL 7 		// cpp type bool
#define REDIS_TYPE_MAP 8 		// cpp type std::unordered_map
#define REDIS_TYPE_SET 9		// cpp type std::vector
#define REDIS_TYPE_PUSH 10		// cpp type std::vector
#define REDIS_TYPE_BIGNUM 11	// cpp type std::string
#define REDIS_TYPE_VERB 12		// cpp type std::string
static const char rds_types[] = { '_', '$', '*', ':', '+', '-', ',', '#', '%', '~', '>', '(', '=' };

enum e_cluster_err_type {
    CLUSTER_NOT_ERR = 0,
    CLUSTER_ERR_MOVED,
    CLUSTER_ERR_ASK,
    CLUSTER_ERR_TRYAGAIN,
    CLUSTER_ERR_CLUSTERDOWN,
    CLUSTER_ERR_SENTINEL
};

#define REDIS_ERROR_MOVED "MOVED"
#define REDIS_ERROR_ASK "ASK"
#define REDIS_ERROR_TRYAGAIN "TRYAGAIN"
#define REDIS_ERROR_CLUSTERDOWN "CLUSTERDOWN"

enum e_cluster_node_type {
    CLUSTER_NODE_NULL = 0,
    CLUSTER_NODE_MASTER,
    CLUSTER_NODE_SLAVE
};

/* Configuration flags */
#define HIRCLUSTER_FLAG_NULL 0x0
/* Flag to enable parsing of slave nodes. Currently not used, but the
   information is added to its master node structure. */
#define HIRCLUSTER_FLAG_ADD_SLAVE 0x1000
/* Flag to enable parsing of importing/migrating slots for master nodes.
 * Only applicable when 'cluster nodes' command is used for route updates. */
#define HIRCLUSTER_FLAG_ADD_OPENSLOT 0x2000
/* Flag to enable routing table updates using the command 'cluster slots'.
 * Default is the 'cluster nodes' command. */
#define HIRCLUSTER_FLAG_ROUTE_USE_SLOTS 0x4000

#define REDIS_CLUSTER_SLOTS 16384

}