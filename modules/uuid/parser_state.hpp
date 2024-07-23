#pragma once

#include <cctype>
#include <cstdint>
#include <string_view>
#include "error/error.hpp"

namespace modules {
/// PEC stands for "Parser Error Code". This enum contains error codes used by
/// various CAF parsers.
enum class pec : uint8_t {
  /// Not-an-error.
  success = 0,
  /// Parser succeeded but found trailing character(s).
  trailing_character = 1,
  /// Parser stopped after reaching the end while still expecting input.
  unexpected_eof,
  /// Parser stopped after reading an unexpected character.
  unexpected_character,
  /// Parsed integer exceeds the number of available bits of a `timespan`.
  timespan_overflow,
  /// Tried constructing a `timespan` with from a floating point number.
  fractional_timespan = 5,
  /// Too many characters for an atom.
  too_many_characters,
  /// Unrecognized character after escaping `\`.
  invalid_escape_sequence,
  /// Misplaced newline, e.g., inside a string.
  unexpected_newline,
  /// Parsed positive integer exceeds the number of available bits.
  integer_overflow,
  /// Parsed negative integer exceeds the number of available bits.
  integer_underflow = 10,
  /// Exponent of parsed double is less than the minimum supported exponent.
  exponent_underflow,
  /// Exponent of parsed double is greater than the maximum supported exponent.
  exponent_overflow,
  /// Parsed type does not match the expected type.
  type_mismatch,
  /// Stopped at an unrecognized option name.
  not_an_option,
  /// Stopped at an unparsable argument.
  invalid_argument = 15,
  /// Stopped because an argument was omitted.
  missing_argument,
  /// Stopped because the key of a category was taken.
  invalid_category,
  /// Stopped at an unexpected field name while reading a user-defined type.
  invalid_field_name,
  /// Stopped at a repeated field name while reading a user-defined type.
  repeated_field_name,
  /// Stopped while reading a user-defined type with one or more missing
  /// mandatory fields.
  missing_field = 20,
  /// Parsing a range statement ('n..m' or 'n..m..step') failed.
  invalid_range_expression,
  /// Stopped after running into an invalid parser state. Should never happen
  /// and most likely indicates a bug in the implementation.
  invalid_state,
  /// Parser stopped after exceeding its maximum supported level of nesting.
  nested_too_deeply,
};

/// Converts the code and the current position of a parser to an error.
error parser_state_to_error(pec code, int32_t line, int32_t column) {
  return wrap_error(static_cast<uint8_t>(code), "error in line {} column {}: {}", line, column, static_cast<uint8_t>(code));
}

/// Stores all information necessary for implementing an FSM-based parser.
template <class Iterator, class Sentinel = Iterator>
struct parser_state {
  using iterator_type = Iterator;

  /// Current position of the parser.
  Iterator i;

  /// End-of-input marker.
  Sentinel e;

  /// Current state of the parser.
  pec code;

  /// Current line in the input.
  int32_t line;

  /// Position in the current line.
  int32_t column;

  parser_state() noexcept : i(), e(), code(pec::success), line(1), column(1) {
    // nop
  }

  explicit parser_state(Iterator first) noexcept : parser_state() {
    i = first;
  }

  parser_state(Iterator first, Sentinel last) noexcept : parser_state() {
    i = first;
    e = last;
  }

  parser_state(const parser_state&) noexcept = default;

  parser_state& operator=(const parser_state&) noexcept = default;

  /// Returns the null terminator when reaching the end of the string,
  /// otherwise the next character.
  char next() noexcept {
    ++i;
    ++column;
    if (i != e) {
      auto c = *i;
      if (c == '\n') {
        ++line;
        column = 1;
      }
      return c;
    }
    return '\0';
  }

  /// Returns the null terminator if `i == e`, otherwise the current character.
  char current() const noexcept {
    return i != e ? *i : '\0';
  }

  /// Checks whether `i == e`.
  bool at_end() const noexcept {
    return i == e;
  }

  /// Skips any whitespaces characters in the input.
  void skip_whitespaces() noexcept {
    auto c = current();
    while (isspace(c))
      c = next();
  }

  /// Tries to read `x` as the next character, automatically skipping leading
  /// whitespaces.
  bool consume(char x) noexcept {
    skip_whitespaces();
    if (current() == x) {
      next();
      return true;
    }
    return false;
  }

  /// Consumes the next character if it satisfies given predicate, automatically
  /// skipping leading whitespaces.
  template <class Predicate>
  bool consume_if(Predicate predicate) noexcept {
    skip_whitespaces();
    if (predicate(current())) {
      next();
      return true;
    }
    return false;
  }

  /// Tries to read `x` as the next character without automatically skipping
  /// leading whitespaces.
  bool consume_strict(char x) noexcept {
    if (current() == x) {
      next();
      return true;
    }
    return false;
  }

  /// Consumes the next character if it satisfies given predicate without
  /// automatically skipping leading whitespaces.
  template <class Predicate>
  bool consume_strict_if(Predicate predicate) noexcept {
    if (predicate(current())) {
      next();
      return true;
    }
    return false;
  }

  /// Returns an error from the current state.
  auto error() {
      return parser_state_to_error(code, line, column);
  }
};

/// Specialization for parsers operating on string views.
using string_parser_state = parser_state<std::string_view::iterator>;

template <int Base, class T>
struct ascii_to_int {
  // @pre `c` is a valid ASCII digit, i.e., matches [0-9].
  constexpr T operator()(char c) const {
    // Result is guaranteed to have a value between 0 and 10 and can be safely
    // cast to any integer type.
    return static_cast<T>(c - '0');
  }
};

template <class T>
struct ascii_to_int<16, T> {
  // @pre `c` is a valid ASCII hex digit, i.e., matches [0-9A-Fa-f].
  constexpr T operator()(char c) const {
    // Numbers start at position 48 in the ASCII table.
    // Uppercase characters start at position 65 in the ASCII table.
    // Lowercase characters start at position 97 in the ASCII table.
    // Result is guaranteed to have a value between 0 and 16 and can be safely
    // cast to any integer type.
    return static_cast<T>(
      c <= '9' ? c - '0' : (c <= 'F' ? 10 + (c - 'A') : 10 + (c - 'a')));
  }
};

// Sum up integers when parsing positive integers.
// @returns `false` on an overflow, otherwise `true`.
// @pre `isdigit(c) || (Base == 16 && isxdigit(c))`
// @warning can leave `x` in an intermediate state when retuning `false`
template <int Base, class T>
bool add_ascii(T& x, char c, std::enable_if_t<std::is_integral_v<T>, int> = 0) {
  if (x > (std::numeric_limits<T>::max() / Base))
    return false;
  x *= static_cast<T>(Base);
  ascii_to_int<Base, T> f;
  auto y = f(c);
  if (x > (std::numeric_limits<T>::max() - y))
    return false;
  x += static_cast<T>(y);
  return true;
}

template <int Base, class T>
bool add_ascii(T& x, char c,
               std::enable_if_t<std::is_floating_point_v<T>, int> = 0) {
  ascii_to_int<Base, T> f;
  x = (x * Base) + f(c);
  return true;
}

} // namespace modules
