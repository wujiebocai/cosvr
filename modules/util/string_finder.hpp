#pragma once

#include <cstddef>
#include <string_view>

namespace refvalue {
enum class find_mode_type {
  any_of = 0,
  full_match,
  any_of_reverse,
  full_match_reverse
};

template <find_mode_type Mode>
struct string_finder_traits {};

template <>
struct string_finder_traits<find_mode_type::any_of> {
  static constexpr std::size_t default_index{};
  static constexpr bool forward_direction = true;
  static constexpr auto find = [](std::string_view source,
                                  std::string_view keyword,
                                  std::size_t index = default_index) {
    return source.find_first_of(keyword, index);
  };

  static constexpr auto keyword_size =
      [](std::string_view keyword) -> std::size_t {
    return 1;
  };
};

template <>
struct string_finder_traits<find_mode_type::full_match> {
  static constexpr std::size_t default_index{};
  static constexpr bool forward_direction = true;
  static constexpr auto find = [](std::string_view source,
                                  std::string_view keyword,
                                  std::size_t index = default_index) {
    return source.find(keyword, index);
  };

  static constexpr auto keyword_size = [](std::string_view keyword) {
    return keyword.size();
  };
};

template <>
struct string_finder_traits<find_mode_type::any_of_reverse> {
  static constexpr auto default_index = std::string_view::npos;
  static constexpr bool forward_direction{};
  static constexpr auto find = [](std::string_view source,
                                  std::string_view keyword,
                                  std::size_t index = default_index) {
    return source.find_last_of(keyword, index);
  };

  static constexpr auto keyword_size =
      [](std::string_view keyword) -> std::size_t {
    return 1;
  };
};

template <>
struct string_finder_traits<find_mode_type::full_match_reverse> {
  static constexpr auto default_index = std::string_view::npos;
  static constexpr bool forward_direction{};
  static constexpr auto find = [](std::string_view source,
                                  std::string_view keyword,
                                  std::size_t index = default_index) {
    return source.rfind(keyword, index);
  };

  static constexpr auto keyword_size = [](std::string_view keyword) {
    return keyword.size();
  };
};

template <find_mode_type Mode>
constexpr auto uniform_find_string(
    std::string_view source, std::string_view keyword,
    std::size_t index = string_finder_traits<
        Mode>::default_index) noexcept(noexcept(string_finder_traits<Mode>::
                                                    find(source, keyword,
                                                         index))) {
  return string_finder_traits<Mode>::find(source, keyword, index);
}

template <find_mode_type Mode>
constexpr auto skip_keyword(std::size_t index,
                            std::string_view keyword) noexcept {
  if constexpr (string_finder_traits<Mode>::forward_direction) {
    return index + string_finder_traits<Mode>::keyword_size(keyword);
  }
  else {
    return index - string_finder_traits<Mode>::keyword_size(keyword);
  }
}
}  // namespace refvalue
