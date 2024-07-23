#include <spdlog/fmt/fmt.h>

// 临时接口后续直接使用标准库的
namespace std {
using fmt::format;
using fmt::format_to;
using fmt::format_to_n;
using fmt::formatted_size;
using fmt::vformat;
using fmt::vformat_to;
using fmt::vformat_to_n;
using fmt::visit_format_arg;
using fmt::make_format_args;

//using fmt::arg;
//using fmt::format_system_error;
//using fmt::group_digits;
//using fmt::join;
//using fmt::report_system_error;
//using fmt::runtime;
//using fmt::system_error;
//using fmt::to_string;
//using fmt::underlying;
//using fmt::vprint;
//using fmt::vsystem_error;
//using fmt::print;
//using fmt::ptr;
}