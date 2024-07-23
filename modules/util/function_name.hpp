#pragma once

#include <string_view>
#include "magic_names.hpp"

namespace modules {
template <auto func>
constexpr std::string_view get_func_name() {
  return std::string_view{refvalue::qualified_name_of_v<func>};
};
}  // namespace modules
