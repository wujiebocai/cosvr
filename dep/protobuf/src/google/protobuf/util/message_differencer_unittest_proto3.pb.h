// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/util/message_differencer_unittest_proto3.proto
// Protobuf C++ Version: 4.26.0-dev

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2futil_2fmessage_5fdifferencer_5funittest_5fproto3_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2futil_2fmessage_5fdifferencer_5funittest_5fproto3_2eproto_2epb_2eh

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
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2futil_2fmessage_5fdifferencer_5funittest_5fproto3_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2futil_2fmessage_5fdifferencer_5funittest_5fproto3_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_google_2fprotobuf_2futil_2fmessage_5fdifferencer_5funittest_5fproto3_2eproto;
namespace proto3_unittest {
class TestNoPresenceField;
struct TestNoPresenceFieldDefaultTypeInternal;
extern TestNoPresenceFieldDefaultTypeInternal _TestNoPresenceField_default_instance_;
}  // namespace proto3_unittest
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace proto3_unittest {

// ===================================================================


// -------------------------------------------------------------------

class TestNoPresenceField final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:proto3_unittest.TestNoPresenceField) */ {
 public:
  inline TestNoPresenceField() : TestNoPresenceField(nullptr) {}
  ~TestNoPresenceField() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR TestNoPresenceField(
      ::google::protobuf::internal::ConstantInitialized);

  inline TestNoPresenceField(const TestNoPresenceField& from) : TestNoPresenceField(nullptr, from) {}
  inline TestNoPresenceField(TestNoPresenceField&& from) noexcept
      : TestNoPresenceField(nullptr, std::move(from)) {}
  inline TestNoPresenceField& operator=(const TestNoPresenceField& from) {
    CopyFrom(from);
    return *this;
  }
  inline TestNoPresenceField& operator=(TestNoPresenceField&& from) noexcept {
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

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const TestNoPresenceField& default_instance() {
    return *internal_default_instance();
  }
  static inline const TestNoPresenceField* internal_default_instance() {
    return reinterpret_cast<const TestNoPresenceField*>(
        &_TestNoPresenceField_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(TestNoPresenceField& a, TestNoPresenceField& b) { a.Swap(&b); }
  inline void Swap(TestNoPresenceField* other) {
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
  void UnsafeArenaSwap(TestNoPresenceField* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  TestNoPresenceField* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<TestNoPresenceField>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const TestNoPresenceField& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const TestNoPresenceField& from) { TestNoPresenceField::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
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
  void InternalSwap(TestNoPresenceField* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "proto3_unittest.TestNoPresenceField"; }

 protected:
  explicit TestNoPresenceField(::google::protobuf::Arena* arena);
  TestNoPresenceField(::google::protobuf::Arena* arena, const TestNoPresenceField& from);
  TestNoPresenceField(::google::protobuf::Arena* arena, TestNoPresenceField&& from) noexcept
      : TestNoPresenceField(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kNoPresenceRepeatedNestedFieldNumber = 3,
    kNoPresenceStringFieldNumber = 4,
    kNoPresenceNestedFieldNumber = 2,
    kNoPresenceBoolFieldNumber = 1,
    kNoPresenceBool2FieldNumber = 5,
    kNoPresenceBool3FieldNumber = 6,
  };
  // repeated .proto3_unittest.TestNoPresenceField no_presence_repeated_nested = 3;
  int no_presence_repeated_nested_size() const;
  private:
  int _internal_no_presence_repeated_nested_size() const;

  public:
  void clear_no_presence_repeated_nested() ;
  ::proto3_unittest::TestNoPresenceField* mutable_no_presence_repeated_nested(int index);
  ::google::protobuf::RepeatedPtrField<::proto3_unittest::TestNoPresenceField>* mutable_no_presence_repeated_nested();

  private:
  const ::google::protobuf::RepeatedPtrField<::proto3_unittest::TestNoPresenceField>& _internal_no_presence_repeated_nested() const;
  ::google::protobuf::RepeatedPtrField<::proto3_unittest::TestNoPresenceField>* _internal_mutable_no_presence_repeated_nested();
  public:
  const ::proto3_unittest::TestNoPresenceField& no_presence_repeated_nested(int index) const;
  ::proto3_unittest::TestNoPresenceField* add_no_presence_repeated_nested();
  const ::google::protobuf::RepeatedPtrField<::proto3_unittest::TestNoPresenceField>& no_presence_repeated_nested() const;
  // string no_presence_string = 4;
  void clear_no_presence_string() ;
  const std::string& no_presence_string() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_no_presence_string(Arg_&& arg, Args_... args);
  std::string* mutable_no_presence_string();
  PROTOBUF_NODISCARD std::string* release_no_presence_string();
  void set_allocated_no_presence_string(std::string* value);

  private:
  const std::string& _internal_no_presence_string() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_no_presence_string(
      const std::string& value);
  std::string* _internal_mutable_no_presence_string();

  public:
  // .proto3_unittest.TestNoPresenceField no_presence_nested = 2;
  bool has_no_presence_nested() const;
  void clear_no_presence_nested() ;
  const ::proto3_unittest::TestNoPresenceField& no_presence_nested() const;
  PROTOBUF_NODISCARD ::proto3_unittest::TestNoPresenceField* release_no_presence_nested();
  ::proto3_unittest::TestNoPresenceField* mutable_no_presence_nested();
  void set_allocated_no_presence_nested(::proto3_unittest::TestNoPresenceField* value);
  void unsafe_arena_set_allocated_no_presence_nested(::proto3_unittest::TestNoPresenceField* value);
  ::proto3_unittest::TestNoPresenceField* unsafe_arena_release_no_presence_nested();

  private:
  const ::proto3_unittest::TestNoPresenceField& _internal_no_presence_nested() const;
  ::proto3_unittest::TestNoPresenceField* _internal_mutable_no_presence_nested();

  public:
  // bool no_presence_bool = 1;
  void clear_no_presence_bool() ;
  bool no_presence_bool() const;
  void set_no_presence_bool(bool value);

  private:
  bool _internal_no_presence_bool() const;
  void _internal_set_no_presence_bool(bool value);

  public:
  // bool no_presence_bool2 = 5;
  void clear_no_presence_bool2() ;
  bool no_presence_bool2() const;
  void set_no_presence_bool2(bool value);

  private:
  bool _internal_no_presence_bool2() const;
  void _internal_set_no_presence_bool2(bool value);

  public:
  // bool no_presence_bool3 = 6;
  void clear_no_presence_bool3() ;
  bool no_presence_bool3() const;
  void set_no_presence_bool3(bool value);

  private:
  bool _internal_no_presence_bool3() const;
  void _internal_set_no_presence_bool3(bool value);

  public:
  // @@protoc_insertion_point(class_scope:proto3_unittest.TestNoPresenceField)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      3, 6, 2,
      62, 2>
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
    ::google::protobuf::RepeatedPtrField< ::proto3_unittest::TestNoPresenceField > no_presence_repeated_nested_;
    ::google::protobuf::internal::ArenaStringPtr no_presence_string_;
    ::proto3_unittest::TestNoPresenceField* no_presence_nested_;
    bool no_presence_bool_;
    bool no_presence_bool2_;
    bool no_presence_bool3_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_google_2fprotobuf_2futil_2fmessage_5fdifferencer_5funittest_5fproto3_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// TestNoPresenceField

// bool no_presence_bool = 1;
inline void TestNoPresenceField::clear_no_presence_bool() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_bool_ = false;
}
inline bool TestNoPresenceField::no_presence_bool() const {
  // @@protoc_insertion_point(field_get:proto3_unittest.TestNoPresenceField.no_presence_bool)
  return _internal_no_presence_bool();
}
inline void TestNoPresenceField::set_no_presence_bool(bool value) {
  _internal_set_no_presence_bool(value);
  // @@protoc_insertion_point(field_set:proto3_unittest.TestNoPresenceField.no_presence_bool)
}
inline bool TestNoPresenceField::_internal_no_presence_bool() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.no_presence_bool_;
}
inline void TestNoPresenceField::_internal_set_no_presence_bool(bool value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_bool_ = value;
}

// .proto3_unittest.TestNoPresenceField no_presence_nested = 2;
inline bool TestNoPresenceField::has_no_presence_nested() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  PROTOBUF_ASSUME(!value || _impl_.no_presence_nested_ != nullptr);
  return value;
}
inline void TestNoPresenceField::clear_no_presence_nested() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (_impl_.no_presence_nested_ != nullptr) _impl_.no_presence_nested_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline const ::proto3_unittest::TestNoPresenceField& TestNoPresenceField::_internal_no_presence_nested() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  const ::proto3_unittest::TestNoPresenceField* p = _impl_.no_presence_nested_;
  return p != nullptr ? *p : reinterpret_cast<const ::proto3_unittest::TestNoPresenceField&>(::proto3_unittest::_TestNoPresenceField_default_instance_);
}
inline const ::proto3_unittest::TestNoPresenceField& TestNoPresenceField::no_presence_nested() const ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:proto3_unittest.TestNoPresenceField.no_presence_nested)
  return _internal_no_presence_nested();
}
inline void TestNoPresenceField::unsafe_arena_set_allocated_no_presence_nested(::proto3_unittest::TestNoPresenceField* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (GetArena() == nullptr) {
    delete reinterpret_cast<::google::protobuf::MessageLite*>(_impl_.no_presence_nested_);
  }
  _impl_.no_presence_nested_ = reinterpret_cast<::proto3_unittest::TestNoPresenceField*>(value);
  if (value != nullptr) {
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }
  // @@protoc_insertion_point(field_unsafe_arena_set_allocated:proto3_unittest.TestNoPresenceField.no_presence_nested)
}
inline ::proto3_unittest::TestNoPresenceField* TestNoPresenceField::release_no_presence_nested() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);

  _impl_._has_bits_[0] &= ~0x00000001u;
  ::proto3_unittest::TestNoPresenceField* released = _impl_.no_presence_nested_;
  _impl_.no_presence_nested_ = nullptr;
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
inline ::proto3_unittest::TestNoPresenceField* TestNoPresenceField::unsafe_arena_release_no_presence_nested() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:proto3_unittest.TestNoPresenceField.no_presence_nested)

  _impl_._has_bits_[0] &= ~0x00000001u;
  ::proto3_unittest::TestNoPresenceField* temp = _impl_.no_presence_nested_;
  _impl_.no_presence_nested_ = nullptr;
  return temp;
}
inline ::proto3_unittest::TestNoPresenceField* TestNoPresenceField::_internal_mutable_no_presence_nested() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (_impl_.no_presence_nested_ == nullptr) {
    auto* p = ::google::protobuf::Message::DefaultConstruct<::proto3_unittest::TestNoPresenceField>(GetArena());
    _impl_.no_presence_nested_ = reinterpret_cast<::proto3_unittest::TestNoPresenceField*>(p);
  }
  return _impl_.no_presence_nested_;
}
inline ::proto3_unittest::TestNoPresenceField* TestNoPresenceField::mutable_no_presence_nested() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  _impl_._has_bits_[0] |= 0x00000001u;
  ::proto3_unittest::TestNoPresenceField* _msg = _internal_mutable_no_presence_nested();
  // @@protoc_insertion_point(field_mutable:proto3_unittest.TestNoPresenceField.no_presence_nested)
  return _msg;
}
inline void TestNoPresenceField::set_allocated_no_presence_nested(::proto3_unittest::TestNoPresenceField* value) {
  ::google::protobuf::Arena* message_arena = GetArena();
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (message_arena == nullptr) {
    delete (_impl_.no_presence_nested_);
  }

  if (value != nullptr) {
    ::google::protobuf::Arena* submessage_arena = (value)->GetArena();
    if (message_arena != submessage_arena) {
      value = ::google::protobuf::internal::GetOwnedMessage(message_arena, value, submessage_arena);
    }
    _impl_._has_bits_[0] |= 0x00000001u;
  } else {
    _impl_._has_bits_[0] &= ~0x00000001u;
  }

  _impl_.no_presence_nested_ = reinterpret_cast<::proto3_unittest::TestNoPresenceField*>(value);
  // @@protoc_insertion_point(field_set_allocated:proto3_unittest.TestNoPresenceField.no_presence_nested)
}

// repeated .proto3_unittest.TestNoPresenceField no_presence_repeated_nested = 3;
inline int TestNoPresenceField::_internal_no_presence_repeated_nested_size() const {
  return _internal_no_presence_repeated_nested().size();
}
inline int TestNoPresenceField::no_presence_repeated_nested_size() const {
  return _internal_no_presence_repeated_nested_size();
}
inline void TestNoPresenceField::clear_no_presence_repeated_nested() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_repeated_nested_.Clear();
}
inline ::proto3_unittest::TestNoPresenceField* TestNoPresenceField::mutable_no_presence_repeated_nested(int index)
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable:proto3_unittest.TestNoPresenceField.no_presence_repeated_nested)
  return _internal_mutable_no_presence_repeated_nested()->Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField<::proto3_unittest::TestNoPresenceField>* TestNoPresenceField::mutable_no_presence_repeated_nested()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:proto3_unittest.TestNoPresenceField.no_presence_repeated_nested)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _internal_mutable_no_presence_repeated_nested();
}
inline const ::proto3_unittest::TestNoPresenceField& TestNoPresenceField::no_presence_repeated_nested(int index) const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:proto3_unittest.TestNoPresenceField.no_presence_repeated_nested)
  return _internal_no_presence_repeated_nested().Get(index);
}
inline ::proto3_unittest::TestNoPresenceField* TestNoPresenceField::add_no_presence_repeated_nested() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::proto3_unittest::TestNoPresenceField* _add = _internal_mutable_no_presence_repeated_nested()->Add();
  // @@protoc_insertion_point(field_add:proto3_unittest.TestNoPresenceField.no_presence_repeated_nested)
  return _add;
}
inline const ::google::protobuf::RepeatedPtrField<::proto3_unittest::TestNoPresenceField>& TestNoPresenceField::no_presence_repeated_nested() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:proto3_unittest.TestNoPresenceField.no_presence_repeated_nested)
  return _internal_no_presence_repeated_nested();
}
inline const ::google::protobuf::RepeatedPtrField<::proto3_unittest::TestNoPresenceField>&
TestNoPresenceField::_internal_no_presence_repeated_nested() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.no_presence_repeated_nested_;
}
inline ::google::protobuf::RepeatedPtrField<::proto3_unittest::TestNoPresenceField>*
TestNoPresenceField::_internal_mutable_no_presence_repeated_nested() {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return &_impl_.no_presence_repeated_nested_;
}

// string no_presence_string = 4;
inline void TestNoPresenceField::clear_no_presence_string() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_string_.ClearToEmpty();
}
inline const std::string& TestNoPresenceField::no_presence_string() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:proto3_unittest.TestNoPresenceField.no_presence_string)
  return _internal_no_presence_string();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void TestNoPresenceField::set_no_presence_string(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_string_.Set(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:proto3_unittest.TestNoPresenceField.no_presence_string)
}
inline std::string* TestNoPresenceField::mutable_no_presence_string() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_no_presence_string();
  // @@protoc_insertion_point(field_mutable:proto3_unittest.TestNoPresenceField.no_presence_string)
  return _s;
}
inline const std::string& TestNoPresenceField::_internal_no_presence_string() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.no_presence_string_.Get();
}
inline void TestNoPresenceField::_internal_set_no_presence_string(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_string_.Set(value, GetArena());
}
inline std::string* TestNoPresenceField::_internal_mutable_no_presence_string() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _impl_.no_presence_string_.Mutable( GetArena());
}
inline std::string* TestNoPresenceField::release_no_presence_string() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:proto3_unittest.TestNoPresenceField.no_presence_string)
  return _impl_.no_presence_string_.Release();
}
inline void TestNoPresenceField::set_allocated_no_presence_string(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_string_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.no_presence_string_.IsDefault()) {
          _impl_.no_presence_string_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:proto3_unittest.TestNoPresenceField.no_presence_string)
}

// bool no_presence_bool2 = 5;
inline void TestNoPresenceField::clear_no_presence_bool2() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_bool2_ = false;
}
inline bool TestNoPresenceField::no_presence_bool2() const {
  // @@protoc_insertion_point(field_get:proto3_unittest.TestNoPresenceField.no_presence_bool2)
  return _internal_no_presence_bool2();
}
inline void TestNoPresenceField::set_no_presence_bool2(bool value) {
  _internal_set_no_presence_bool2(value);
  // @@protoc_insertion_point(field_set:proto3_unittest.TestNoPresenceField.no_presence_bool2)
}
inline bool TestNoPresenceField::_internal_no_presence_bool2() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.no_presence_bool2_;
}
inline void TestNoPresenceField::_internal_set_no_presence_bool2(bool value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_bool2_ = value;
}

// bool no_presence_bool3 = 6;
inline void TestNoPresenceField::clear_no_presence_bool3() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_bool3_ = false;
}
inline bool TestNoPresenceField::no_presence_bool3() const {
  // @@protoc_insertion_point(field_get:proto3_unittest.TestNoPresenceField.no_presence_bool3)
  return _internal_no_presence_bool3();
}
inline void TestNoPresenceField::set_no_presence_bool3(bool value) {
  _internal_set_no_presence_bool3(value);
  // @@protoc_insertion_point(field_set:proto3_unittest.TestNoPresenceField.no_presence_bool3)
}
inline bool TestNoPresenceField::_internal_no_presence_bool3() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.no_presence_bool3_;
}
inline void TestNoPresenceField::_internal_set_no_presence_bool3(bool value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.no_presence_bool3_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto3_unittest


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2futil_2fmessage_5fdifferencer_5funittest_5fproto3_2eproto_2epb_2eh