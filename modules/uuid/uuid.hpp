#pragma once

//#include <iostream>
//#include <random>
//#include <chrono>
//#include <iomanip>
//#include <sstream>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <string_view>

#include <cctype>
#include <cstring>
#include <random>

#include "comparable.hpp"
#include "network_order.hpp"
#include "fnv.hpp"
#include "parser_state.hpp"
#include "append_hex.hpp"
#include "util/expected.hpp"

namespace modules {
namespace uuid {
/// Denotes the variant (type) that determines the layout of the UUID. The
/// interpretation of all other bits in a UUID depend on this field.
enum variant_field {
    reserved,
    rfc4122,
    microsoft,
};

/// Denotes the version, i.e., which algorithm was used to create this UUID.
enum version_field {
    /// Time-based algorithm.
    time_based = 1,

    /// DCE security version with embedded POSIX UIDs.
    dce_compatible = 2,

    /// Name-based algorithm using MD5 hashing.
    md5_based = 3,

    /// Random or pseudo-random algorithm.
    randomized = 4,

    /// Name-based algorithm using SHA-1 hashing.
    sha1_based = 5,
};

namespace {

// The following table lists the contents of the variant field, where the
// letter "x" indicates a "don't-care" value.
//
// ```
//   Msb0  Msb1  Msb2  Description
//
//    0     x     x    Reserved, NCS backward compatibility.
//
//    1     0     x    The variant specified in this document.
//
//    1     1     0    Reserved, Microsoft Corporation backward
//                     compatibility
//
//    1     1     1    Reserved for future definition.
// ```
static variant_field variant_table[] = {
    reserved,  // 0 0 0
    reserved,  // 0 0 1
    reserved,  // 0 1 0
    reserved,  // 0 1 1
    rfc4122,   // 1 0 0
    rfc4122,   // 1 0 1
    microsoft, // 1 1 0
    reserved,  // 1 1 1
};

static std::byte nil_bytes[16];

using array_type = std::array<std::byte, 16>;
enum parse_result {
    valid_uuid,
    malformed_uuid,
    invalid_variant,
    invalid_version,
};

static parse_result parse_impl(string_parser_state& ps, array_type& x) noexcept {
    // Create function object for writing into x.
    auto read_byte = [pos{x.data()}](auto& ps) mutable {
        uint8_t value = 0;
        auto c1 = ps.current();
        if (!isxdigit(c1) || !add_ascii<16>(value, c1))
            return false;
        auto c2 = ps.next();
        if (!isxdigit(c2) || !add_ascii<16>(value, c2))
            return false;
        ps.next();
        *pos++ = static_cast<std::byte>(value);
        return true;
    };
    // Parse the formatted string.
    ps.skip_whitespaces();
    for (int i = 0; i < 4; ++i)
        if (!read_byte(ps))
            return malformed_uuid;
    for (int block_size : {2, 2, 2, 6}) {
        if (!ps.consume_strict('-'))
            return malformed_uuid;
        for (int i = 0; i < block_size; ++i)
            if (!read_byte(ps))
                return malformed_uuid;
    }
    ps.skip_whitespaces();
    if (!ps.at_end())
        return malformed_uuid;
        // Check whether the bytes form a valid UUID.
    if (memcmp(x.data(), uuid::nil_bytes, 16) == 0)
        return valid_uuid;
    if (auto subtype = std::to_integer<long>(x[6]) >> 4;
        subtype == 0 || subtype > 5)
        return invalid_version;
    return valid_uuid;
}

} // namespace
} // namespace uuid 

/// A universally unique identifier according to
/// [RFC 4122](https://tools.ietf.org/html/rfc4122). While this implementation
/// can read all UUID versions, it can only create random-generated ones.
class uuid_t : comparable<uuid_t> {
public:
    using array_type = typename uuid::array_type; //std::array<std::byte, 16>;

    /// Creates the nil UUID with all 128 bits set to zero.
    uuid_t() noexcept {
        memset(bytes_.data(), 0, bytes_.size());
    }

    uuid_t(const uuid_t&) noexcept = default;

    uuid_t& operator=(const uuid_t&) noexcept = default;

    explicit uuid_t(const array_type& bytes) noexcept : bytes_(bytes) {
        // nop
    }

    const array_type& bytes() const noexcept {
        return bytes_;
    }

    array_type& bytes() noexcept {
        return bytes_;
    }

    /// Returns `true` if this UUID is *not* `nil`, `false` otherwise.
    /// A UUID is `nil` if all bits are 0.
    operator bool() const noexcept {
        return memcmp(bytes_.data(), uuid::nil_bytes, 16) != 0;
    }

    /// Returns `true` if this UUID is `nil`, `false` otherwise.
    bool operator!() const noexcept {
        return memcmp(bytes_.data(), uuid::nil_bytes, 16) == 0;
    }

    /// Returns the variant (type) that determines the layout of the UUID.
    /// @pre `not nil()`
    uuid::variant_field variant() const noexcept {
        return uuid::variant_table[std::to_integer<size_t>(bytes_[8]) >> 5];
    }

    /// Returns the version (sub type) that identifies the algorithm used to
    /// generate this UUID. The algorithms defined in RFC 4122 are:
    ///
    /// 1. Time-based
    /// 2. DCE security with embedded POSIX UIDs
    /// 3. Name-based, using MD5 hashing
    /// 4. Random or pseudo-random
    /// 5. Name-based, using SHA-1 hashing
    /// @pre `not nil()`
    uuid::version_field version() const noexcept {
        return static_cast<uuid::version_field>(std::to_integer<int>(bytes_[6]) >> 4);
    }

    /// The 60-bit timestamp of a time-based UUID. Usually represents a count of
    /// 100- nanosecond intervals since 00:00:00.00, 15 October 1582 in UTC.
    /// @pre `version() == time_based`
    uint64_t timestamp() const noexcept {
        // Assemble octets like this (L = low, M = mid, H = high):
        // 0H HH MM MM LL LL LL LL
        std::byte ts[8];
        memcpy(ts + 4, bytes_.data() + 0, 4);
        memcpy(ts + 2, bytes_.data() + 4, 2);
        memcpy(ts + 0, bytes_.data() + 6, 2);
        ts[0] &= std::byte{0x0F};
        uint64_t result;
        memcpy(&result, ts, 8);
        // UUIDs are stored in network byte order.
        return from_network_order(result);
    }

    /// The 14-bit unsigned integer helps to avoid duplicates that could arise
    /// when the clock is set backwards in time or if the node ID changes.
    /// @pre `version() == time_based`
    uint16_t clock_sequence() const noexcept {
        // Read clk_seq_(hi|low) fields and strip the variant bits.
        std::byte cs[2];
        memcpy(cs, bytes_.data() + 8, 2);
        cs[0] &= std::byte{0x3F};
        uint16_t result;
        memcpy(&result, cs, 2);
        // UUIDs are stored in network byte order.
        return from_network_order(result);
    }

    /// 48-bit value, representing a network address (`time_based` UUIDs), a hash
    /// (`md5_based` and `sha1_based` UUIDs), or a random bit sequence
    /// (`randomized` UUIDs).
    uint64_t node() const noexcept {
        std::byte n[8];
        memset(n, 0, 2);
        memcpy(n + 2, bytes_.data() + 10, 6);
        uint64_t result;
        memcpy(&result, n, 8);
        return from_network_order(result);
    }

    /// Returns a platform-specific hash value for this UUID.
    size_t hash() const noexcept {
        return hash::fnv<size_t>::compute(bytes_);
    }

    /// Creates a random UUID.
    static uuid_t random() noexcept {
        std::random_device rd;
        return random(rd());
    }

    /// Creates a random UUID with a predefined seed.
    static uuid_t random(unsigned seed) noexcept {
        // Algorithm as defined in RFC4122:
        // - Set the two most significant bits (bits 6 and 7) of the
        //    clock_seq_hi_and_reserved to zero and one, respectively.
        // - Set the four most significant bits (bits 12 through 15) of the
        //   time_hi_and_version field to the 4-bit version number from Section 4.1.3.
        // - Set all the other bits to randomly (or pseudo-randomly) chosen values.
        // However, we first fill all bits with random data and then fix the variant
        // and version fields. It's more straightforward that way.
        std::minstd_rand engine{seed};
        std::uniform_int_distribution<> rng{0, 255};
        uuid_t result;
        for (size_t index = 0; index < 16; ++index)
            result.bytes_[index] = static_cast<std::byte>(rng(engine));
        result.bytes_[6] = (result.bytes_[6] & std::byte{0x0F}) | std::byte{0x50};
        result.bytes_[8] = (result.bytes_[8] & std::byte{0x3F}) | std::byte{0x80};
        return result;
    }

    /// Convenience function for creating an UUID with all 128 bits set to zero.
    static uuid_t nil() noexcept {
        return uuid_t{};
    }

    /// Returns whether `parse` would produce a valid UUID.
    static bool can_parse(std::string_view str) noexcept {
        array_type bytes;
        string_parser_state ps{str.begin(), str.end()};
        return uuid::parse_impl(ps, bytes) == uuid::valid_uuid;
    }

    /// Lexicographically compares `this` and `other`.
    /// @returns a negative value if `*this < other`, zero if `*this == other`
    ///          and a positive number if `*this > other`.
    int compare(const uuid_t& other) const noexcept {
        return memcmp(bytes_.data(), other.bytes_.data(), 16u);
    }

private:
  /// Stores the fields, encoded as 16 octets:
  ///
  /// ```
  /// 0                   1                   2                   3
  ///  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
  /// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  /// |                          time_low                             |
  /// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  /// |       time_mid                |         time_hi_and_version   |
  /// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  /// |clk_seq_hi_res |  clk_seq_low  |         node (0-1)            |
  /// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  /// |                         node (2-5)                            |
  /// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  /// ```
  array_type bytes_;
};

/// @relates uuid
error parse(std::string_view str, uuid_t& dest) {
  string_parser_state ps{str.begin(), str.end()};
  switch (uuid::parse_impl(ps, dest.bytes())) {
    case uuid::valid_uuid:
      return no_error;
    default:
      return wrap_error(static_cast<uint8_t>(ps.code), "");
    case uuid::invalid_version:
      return wrap_error(static_cast<uint8_t>(pec::invalid_argument),
                        "invalid version in variant field");
  }
}

/// @relates uuid
std::string to_string(const uuid_t& x) {
    static constexpr auto lowercase = hex_format::lowercase;
    std::string result;
    append_hex<lowercase>(result, x.bytes().data() + 0, 4);
    result += '-';
    append_hex<lowercase>(result, x.bytes().data() + 4, 2);
    result += '-';
    append_hex<lowercase>(result, x.bytes().data() + 6, 2);
    result += '-';
    append_hex<lowercase>(result, x.bytes().data() + 8, 2);
    result += '-';
    append_hex<lowercase>(result, x.bytes().data() + 10, 6);
    return result;
}

/// @relates uuid
expected<uuid_t, error> make_uuid(std::string_view str) {
    uuid_t result;
    if (auto err = parse(str, result))
        return expected<uuid_t, error> {
            unexpect_t{}, 
            err
        };
    return result;
}

/*
// 函数用于生成版本4的UUID
std::string generateUUID() {
    // 使用当前时间作为随机数生成器的种子
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 generator(seed); // Mersenne Twister 64-bit engine

    // UUID由16字节组成，分为几个部分处理
    // 版本号和变体固定位设置
    uint8_t data[16] = {0};
    
    // 版本4的UUID，第7字节的高四位设为0100（即版本号4）
    data[6] = (generator() & 0x0F) | 0x40;
    // 变体，第9字节的高四位设为10xx（RFC4122要求的变体2）
    data[8] = (generator() & 0x3F) | 0x80;

    // 填充剩余的14字节为随机数
    std::uniform_int_distribution<uint8_t> distribution(0, 255);
    for(size_t i = 0; i < 16; ++i) {
        if(i != 6 && i != 8) { // 跳过已设置的字节
            data[i] = distribution(generator);
        }
    }

    // 将二进制数据转换为UUID字符串格式
    std::stringstream ss;
    for(size_t i = 0; i < 16; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }
    
    // UUID标准格式为8-4-4-4-12的组合，添加分隔符
    std::string uuid = ss.str();
    uuid.insert(8, "-");
    uuid.insert(13, "-");
    uuid.insert(18, "-");
    uuid.insert(23, "-");

    return uuid;
}
*/
} // namespace modules

namespace std {

template <>
struct hash<modules::uuid_t> {
    size_t operator()(const modules::uuid_t& x) const noexcept {
        return x.hash();
    }
};

} // namespace std