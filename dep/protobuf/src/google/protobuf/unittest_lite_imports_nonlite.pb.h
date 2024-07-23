// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_lite_imports_nonlite.proto
// Protobuf C++ Version: 4.26.0-dev

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION != 4026000
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unittest.pb.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto {
  static const ::uint32_t offsets[];
};
namespace protobuf_unittest {
class TestLiteImportsNonlite;
struct TestLiteImportsNonliteDefaultTypeInternal;
extern TestLiteImportsNonliteDefaultTypeInternal _TestLiteImportsNonlite_default_instance_;
}  // namespace protobuf_unittest
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace protobuf_unittest {

// ===================================================================


// -------------------------------------------------------------------

class TestLiteImportsNonlite final : public ::google::protobuf::MessageLite
/* @@protoc_insertion_point(class_definition:protobuf_unittest.TestLiteImportsNonlite) */ {
 public:
  inline TestLiteImportsNonlite() : TestLiteImportsNonlite(nullptr) {}
  ~TestLiteImportsNonlite() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR TestLiteImportsNonlite(
      ::google::protobuf::internal::ConstantInitialized);

  inline TestLiteImportsNonlite(const TestLiteImportsNonlite& from) : TestLiteImportsNonlite(nullptr, from) {}
  inline TestLiteImportsNonlite(TestLiteImportsNonlite&& from) noexcept
      : TestLiteImportsNonlite(nullptr, std::move(from)) {}
  inline TestLiteImportsNonlite& operator=(const TestLiteImportsNonlite& from) {
    CopyFrom(from);
    return *this;
  }
  inline TestLiteImportsNonlite& operator=(TestLiteImportsNonlite&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
#ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
#endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const std::string& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString);
  }
  inline std::string* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<std::string>();
  }

  static const TestLiteImportsNonlite& default_instance() {
    return *internal_default_instance();
  }
  static inline const TestLiteImportsNonlite* internal_default_instance() {
    return reinterpret_cast<const TestLiteImportsNonlite*>(
        &_TestLiteImportsNonlite_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(TestLiteImportsNonlite& a, TestLiteImportsNonlite& b) { a.Swap(&b); }
  inline void Swap(TestLiteImportsNonlite* other) {
    if (other == this) return;
#ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr && GetArena() == other->GetArena()) {
#else   // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
#endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(TestLiteImportsNonlite* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  TestLiteImportsNonlite* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::MessageLite::DefaultConstruct<TestLiteImportsNonlite>(arena);
  }
  void CheckTypeAndMergeFrom(
      const ::google::protobuf::MessageLite& from) final;
  void CopyFrom(const TestLiteImportsNonlite& from);
  void MergeFrom(const TestLiteImportsNonlite& from);
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(TestLiteImportsNonlite* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "protobuf_unittest.TestLiteImportsNonlite"; }

 protected:
  explicit TestLiteImportsNonlite(::google::protobuf::Arena* arena);
  TestLiteImportsNonlite(::google::protobuf::Arena* arena, const TestLiteImportsNonlite& from);
  TestLiteImportsNonlite(::google::protobuf::Arena* arena, TestLiteImportsNonlite&& from) noexcept
      : TestLiteImportsNonlite(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kMessageFieldNumber = 1,
    kMessageWithRequiredFieldNumber = 2,
  };
  // optional .protobuf_unittest.TestAllTypes message = 1;
  bool has_message() const;
  void clear_message() ;
  const ::protobuf_unittest::TestAllTypes& message() const;
  PROTOBUF_NODISCARD ::protobuf_unittest::TestAllTypes* release_message();
  ::protobuf_unittest::TestAllTypes* mutable_message();
  void set_allocated_message(::protobuf_unittest::TestAllTypes* value);
  void unsafe_arena_set_allocated_message(::protobuf_unittest::TestAllTypes* value);
  ::protobuf_unittest::TestAllTypes* unsafe_arena_release_message();

  private:
  const ::protobuf_unittest::TestAllTypes& _internal_message() const;
  ::protobuf_unittest::TestAllTypes* _internal_mutable_message();

  public:
  // optional .protobuf_unittest.TestRequired message_with_required = 2;
  bool has_message_with_required() const;
  void clear_message_with_required() ;
  const ::protobuf_unittest::TestRequired& message_with_required() const;
  PROTOBUF_NODISCARD ::protobuf_unittest::TestRequired* release_message_with_required();
  ::protobuf_unittest::TestRequired* mutable_message_with_required();
  void set_allocated_message_with_required(::protobuf_unittest::TestRequired* value);
  void unsafe_arena_set_allocated_message_with_required(::protobuf_unittest::TestRequired* value);
  ::protobuf_unittest::TestRequired* unsafe_arena_release_message_with_required();

  private:
  const ::protobuf_unittest::TestRequired& _internal_message_with_required() const;
  ::protobuf_unittest::TestRequired* _internal_mutable_message_with_required();

  public:
  // @@protoc_insertion_point(class_scope:protobuf_unittest.TestLiteImportsNonlite)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      1, 2, 2,
      0, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from);
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    ::protobuf_unittest::TestAllTypes* message_;
    ::protobuf_unittest::TestRequired* message_with_required_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// TestLiteImportsNonlite

// optional .protobuf_unittest.TestAllTypes message = 1;
inline bool TestLiteImportsNonlite::has_message() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || _impl_.message_ != nullptr);
  return value;
}
inline const ::protobuf_unittest::TestAllTypes& TestLiteImportsNonlite::_internal_message() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  const ::protobuf_unittest::TestAllTypes* p = _impl_.message_;
  return p != nullptr ? *p : reinterpret_cast<const ::protobuf_unittest::TestAllTypes&>(::protobuf_unittest::_TestAllTypes_default_instance_);
}
inline const ::protobuf_unittest::TestAllTypes& TestLiteImportsNonlite::message() const ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:protobuf_unittest.TestLiteImportsNonlite.message)
  return _internal_message();
}
inline void TestLiteImportsNonlite::unsafe_arena_set_allocated_message(::protobuf_unittest::TestAllTypes* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::google::protobuf::MessageLite*>(_impl_.message_);
  }
  _impl_.message_ = reinterpret_cast<::protobuf_unittest::TestAllTypes*>(value);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:protobuf_unittest.TestLiteImportsNonlite.message)
}
inline ::protobuf_unittest::TestAllTypes* TestLiteImportsNonlite::release_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);

  _impl_._has_bits_[0] &= ~0x00000001u;
  ::protobuf_unittest::TestAllTypes* released = _impl_.message_;
  _impl_.message_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old = reinterpret_cast<::google::protobuf::MessageLite*>(released);
  released = ::google::protobuf::internal::DuplicateIfNonNull(released);
  if (GetArena() == nullptr) {
    delete old;
  }
#else   // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArena() != nullptr) {
    released = ::google::protobuf::internal::DuplicateIfNonNull(released);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return released;
}
inline ::protobuf_unittest::TestAllTypes* TestLiteImportsNonlite::unsafe_arena_release_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:protobuf_unittest.TestLiteImportsNonlite.message)

  _impl_._has_bits_[0] &= ~0x00000001u;
  ::protobuf_unittest::TestAllTypes* temp = _impl_.message_;
  _impl_.message_ = nullptr;
  return temp;
}
inline ::protobuf_unittest::TestAllTypes* TestLiteImportsNonlite::_internal_mutable_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (_impl_.message_ == nullptr) {
    auto* p = ::google::protobuf::MessageLite::DefaultConstruct<::protobuf_unittest::TestAllTypes>(GetArena());
    _impl_.message_ = reinterpret_cast<::protobuf_unittest::TestAllTypes*>(p);
  }
  return _impl_.message_;
}
inline ::protobuf_unittest::TestAllTypes* TestLiteImportsNonlite::mutable_message() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  _impl_._has_bits_[0] |= 0x00000001u;
  ::protobuf_unittest::TestAllTypes* _msg = _internal_mutable_message();
  // @@protoc_insertion_point(field_mutable:protobuf_unittest.TestLiteImportsNonlite.message)
  return _msg;
}
inline void TestLiteImportsNonlite::set_allocated_message(::protobuf_unittest::TestAllTypes* value) {
  ::google::protobuf::Arena* message_arena = GetArena();
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (message_arena == nullptr) {
    delete reinterpret_cast<::google::protobuf::MessageLite*>(_impl_.message_);
  }

  if (value != nullptr) {
    ::google::protobuf::Arena* submessage_arena = reinterpret_cast<::google::protobuf::MessageLite*>(value)->GetArena();
    if (message_arena != submessage_arena) {
      value = ::google::protobuf::internal::GetOwnedMessage(message_arena, value, submessage_arena);
    }
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }

  _impl_.message_ = reinterpret_cast<::protobuf_unittest::TestAllTypes*>(value);
  // @@protoc_insertion_point(field_set_allocated:protobuf_unittest.TestLiteImportsNonlite.message)
}

// optional .protobuf_unittest.TestRequired message_with_required = 2;
inline bool TestLiteImportsNonlite::has_message_with_required() const {
  bool value = (_impl_._has_bits_[0] & 0x00000002u) != 0;
  PROTOBUF_ASSUME(!value || _impl_.message_with_required_ != nullptr);
  return value;
}
inline const ::protobuf_unittest::TestRequired& TestLiteImportsNonlite::_internal_message_with_required() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  const ::protobuf_unittest::TestRequired* p = _impl_.message_with_required_;
  return p != nullptr ? *p : reinterpret_cast<const ::protobuf_unittest::TestRequired&>(::protobuf_unittest::_TestRequired_default_instance_);
}
inline const ::protobuf_unittest::TestRequired& TestLiteImportsNonlite::message_with_required() const ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:protobuf_unittest.TestLiteImportsNonlite.message_with_required)
  return _internal_message_with_required();
}
inline void TestLiteImportsNonlite::unsafe_arena_set_allocated_message_with_required(::protobuf_unittest::TestRequired* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::google::protobuf::MessageLite*>(_impl_.message_with_required_);
  }
  _impl_.message_with_required_ = reinterpret_cast<::protobuf_unittest::TestRequired*>(value);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000002u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000002u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:protobuf_unittest.TestLiteImportsNonlite.message_with_required)
}
inline ::protobuf_unittest::TestRequired* TestLiteImportsNonlite::release_message_with_required() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);

  _impl_._has_bits_[0] &= ~0x00000002u;
  ::protobuf_unittest::TestRequired* released = _impl_.message_with_required_;
  _impl_.message_with_required_ = nullptr;
#ifdef PROTOBUF_FORCE_COPY_IN_RELEASE
  auto* old = reinterpret_cast<::google::protobuf::MessageLite*>(released);
  released = ::google::protobuf::internal::DuplicateIfNonNull(released);
  if (GetArena() == nullptr) {
    delete old;
  }
#else   // PROTOBUF_FORCE_COPY_IN_RELEASE
  if (GetArena() != nullptr) {
    released = ::google::protobuf::internal::DuplicateIfNonNull(released);
  }
#endif  // !PROTOBUF_FORCE_COPY_IN_RELEASE
  return released;
}
inline ::protobuf_unittest::TestRequired* TestLiteImportsNonlite::unsafe_arena_release_message_with_required() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:protobuf_unittest.TestLiteImportsNonlite.message_with_required)

  _impl_._has_bits_[0] &= ~0x00000002u;
  ::protobuf_unittest::TestRequired* temp = _impl_.message_with_required_;
  _impl_.message_with_required_ = nullptr;
  return temp;
}
inline ::protobuf_unittest::TestRequired* TestLiteImportsNonlite::_internal_mutable_message_with_required() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (_impl_.message_with_required_ == nullptr) {
    auto* p = ::google::protobuf::MessageLite::DefaultConstruct<::protobuf_unittest::TestRequired>(GetArena());
    _impl_.message_with_required_ = reinterpret_cast<::protobuf_unittest::TestRequired*>(p);
  }
  return _impl_.message_with_required_;
}
inline ::protobuf_unittest::TestRequired* TestLiteImportsNonlite::mutable_message_with_required() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  _impl_._has_bits_[0] |= 0x00000002u;
  ::protobuf_unittest::TestRequired* _msg = _internal_mutable_message_with_required();
  // @@protoc_insertion_point(field_mutable:protobuf_unittest.TestLiteImportsNonlite.message_with_required)
  return _msg;
}
inline void TestLiteImportsNonlite::set_allocated_message_with_required(::protobuf_unittest::TestRequired* value) {
  ::google::protobuf::Arena* message_arena = GetArena();
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (message_arena == nullptr) {
    delete reinterpret_cast<::google::protobuf::MessageLite*>(_impl_.message_with_required_);
  }

  if (value != nullptr) {
    ::google::protobuf::Arena* submessage_arena = reinterpret_cast<::google::protobuf::MessageLite*>(value)->GetArena();
    if (message_arena != submessage_arena) {
      value = ::google::protobuf::internal::GetOwnedMessage(message_arena, value, submessage_arena);
    }
    _impl_._has_bits_[0] |= 0x00000002u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000002u;
  }

  _impl_.message_with_required_ = reinterpret_cast<::protobuf_unittest::TestRequired*>(value);
  // @@protoc_insertion_point(field_set_allocated:protobuf_unittest.TestLiteImportsNonlite.message_with_required)
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace protobuf_unittest


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5flite_5fimports_5fnonlite_2eproto_2epb_2eh
