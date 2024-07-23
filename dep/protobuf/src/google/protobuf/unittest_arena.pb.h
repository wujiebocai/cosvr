// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_arena.proto
// Protobuf C++ Version: 4.26.0-dev

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5farena_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5farena_2eproto_2epb_2eh

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

#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_5farena_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2funittest_5farena_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_google_2fprotobuf_2funittest_5farena_2eproto;
namespace proto2_arena_unittest {
class ArenaMessage;
struct ArenaMessageDefaultTypeInternal;
extern ArenaMessageDefaultTypeInternal _ArenaMessage_default_instance_;
class NestedMessage;
struct NestedMessageDefaultTypeInternal;
extern NestedMessageDefaultTypeInternal _NestedMessage_default_instance_;
}  // namespace proto2_arena_unittest
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace proto2_arena_unittest {

// ===================================================================


// -------------------------------------------------------------------

class NestedMessage final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:proto2_arena_unittest.NestedMessage) */ {
 public:
  inline NestedMessage() : NestedMessage(nullptr) {}
  ~NestedMessage() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR NestedMessage(
      ::google::protobuf::internal::ConstantInitialized);

  inline NestedMessage(const NestedMessage& from) : NestedMessage(nullptr, from) {}
  inline NestedMessage(NestedMessage&& from) noexcept
      : NestedMessage(nullptr, std::move(from)) {}
  inline NestedMessage& operator=(const NestedMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline NestedMessage& operator=(NestedMessage&& from) noexcept {
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
  static const NestedMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const NestedMessage* internal_default_instance() {
    return reinterpret_cast<const NestedMessage*>(
        &_NestedMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(NestedMessage& a, NestedMessage& b) { a.Swap(&b); }
  inline void Swap(NestedMessage* other) {
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
  void UnsafeArenaSwap(NestedMessage* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  NestedMessage* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<NestedMessage>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const NestedMessage& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const NestedMessage& from) { NestedMessage::MergeImpl(*this, from); }

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
  void InternalSwap(NestedMessage* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "proto2_arena_unittest.NestedMessage"; }

 protected:
  explicit NestedMessage(::google::protobuf::Arena* arena);
  NestedMessage(::google::protobuf::Arena* arena, const NestedMessage& from);
  NestedMessage(::google::protobuf::Arena* arena, NestedMessage&& from) noexcept
      : NestedMessage(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kDFieldNumber = 1,
  };
  // int32 d = 1;
  bool has_d() const;
  void clear_d() ;
  ::int32_t d() const;
  void set_d(::int32_t value);

  private:
  ::int32_t _internal_d() const;
  void _internal_set_d(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:proto2_arena_unittest.NestedMessage)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
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
    ::int32_t d_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5farena_2eproto;
};
// -------------------------------------------------------------------

class ArenaMessage final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:proto2_arena_unittest.ArenaMessage) */ {
 public:
  inline ArenaMessage() : ArenaMessage(nullptr) {}
  ~ArenaMessage() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR ArenaMessage(
      ::google::protobuf::internal::ConstantInitialized);

  inline ArenaMessage(const ArenaMessage& from) : ArenaMessage(nullptr, from) {}
  inline ArenaMessage(ArenaMessage&& from) noexcept
      : ArenaMessage(nullptr, std::move(from)) {}
  inline ArenaMessage& operator=(const ArenaMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline ArenaMessage& operator=(ArenaMessage&& from) noexcept {
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
  static const ArenaMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const ArenaMessage* internal_default_instance() {
    return reinterpret_cast<const ArenaMessage*>(
        &_ArenaMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(ArenaMessage& a, ArenaMessage& b) { a.Swap(&b); }
  inline void Swap(ArenaMessage* other) {
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
  void UnsafeArenaSwap(ArenaMessage* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ArenaMessage* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<ArenaMessage>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const ArenaMessage& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const ArenaMessage& from) { ArenaMessage::MergeImpl(*this, from); }

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
  void InternalSwap(ArenaMessage* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "proto2_arena_unittest.ArenaMessage"; }

 protected:
  explicit ArenaMessage(::google::protobuf::Arena* arena);
  ArenaMessage(::google::protobuf::Arena* arena, const ArenaMessage& from);
  ArenaMessage(::google::protobuf::Arena* arena, ArenaMessage&& from) noexcept
      : ArenaMessage(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kRepeatedNestedMessageFieldNumber = 1,
  };
  // repeated .proto2_arena_unittest.NestedMessage repeated_nested_message = 1;
  int repeated_nested_message_size() const;
  private:
  int _internal_repeated_nested_message_size() const;

  public:
  void clear_repeated_nested_message() ;
  ::proto2_arena_unittest::NestedMessage* mutable_repeated_nested_message(int index);
  ::google::protobuf::RepeatedPtrField<::proto2_arena_unittest::NestedMessage>* mutable_repeated_nested_message();

  private:
  const ::google::protobuf::RepeatedPtrField<::proto2_arena_unittest::NestedMessage>& _internal_repeated_nested_message() const;
  ::google::protobuf::RepeatedPtrField<::proto2_arena_unittest::NestedMessage>* _internal_mutable_repeated_nested_message();
  public:
  const ::proto2_arena_unittest::NestedMessage& repeated_nested_message(int index) const;
  ::proto2_arena_unittest::NestedMessage* add_repeated_nested_message();
  const ::google::protobuf::RepeatedPtrField<::proto2_arena_unittest::NestedMessage>& repeated_nested_message() const;
  // @@protoc_insertion_point(class_scope:proto2_arena_unittest.ArenaMessage)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 1,
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
    ::google::protobuf::RepeatedPtrField< ::proto2_arena_unittest::NestedMessage > repeated_nested_message_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5farena_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// NestedMessage

// int32 d = 1;
inline bool NestedMessage::has_d() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline void NestedMessage::clear_d() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.d_ = 0;
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline ::int32_t NestedMessage::d() const {
  // @@protoc_insertion_point(field_get:proto2_arena_unittest.NestedMessage.d)
  return _internal_d();
}
inline void NestedMessage::set_d(::int32_t value) {
  _internal_set_d(value);
  _impl_._has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_set:proto2_arena_unittest.NestedMessage.d)
}
inline ::int32_t NestedMessage::_internal_d() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.d_;
}
inline void NestedMessage::_internal_set_d(::int32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.d_ = value;
}

// -------------------------------------------------------------------

// ArenaMessage

// repeated .proto2_arena_unittest.NestedMessage repeated_nested_message = 1;
inline int ArenaMessage::_internal_repeated_nested_message_size() const {
  return _internal_repeated_nested_message().size();
}
inline int ArenaMessage::repeated_nested_message_size() const {
  return _internal_repeated_nested_message_size();
}
inline void ArenaMessage::clear_repeated_nested_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.repeated_nested_message_.Clear();
}
inline ::proto2_arena_unittest::NestedMessage* ArenaMessage::mutable_repeated_nested_message(int index)
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return _internal_mutable_repeated_nested_message()->Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField<::proto2_arena_unittest::NestedMessage>* ArenaMessage::mutable_repeated_nested_message()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  return _internal_mutable_repeated_nested_message();
}
inline const ::proto2_arena_unittest::NestedMessage& ArenaMessage::repeated_nested_message(int index) const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return _internal_repeated_nested_message().Get(index);
}
inline ::proto2_arena_unittest::NestedMessage* ArenaMessage::add_repeated_nested_message() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::proto2_arena_unittest::NestedMessage* _add = _internal_mutable_repeated_nested_message()->Add();
  // @@protoc_insertion_point(field_add:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return _add;
}
inline const ::google::protobuf::RepeatedPtrField<::proto2_arena_unittest::NestedMessage>& ArenaMessage::repeated_nested_message() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:proto2_arena_unittest.ArenaMessage.repeated_nested_message)
  return _internal_repeated_nested_message();
}
inline const ::google::protobuf::RepeatedPtrField<::proto2_arena_unittest::NestedMessage>&
ArenaMessage::_internal_repeated_nested_message() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.repeated_nested_message_;
}
inline ::google::protobuf::RepeatedPtrField<::proto2_arena_unittest::NestedMessage>*
ArenaMessage::_internal_mutable_repeated_nested_message() {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return &_impl_.repeated_nested_message_;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace proto2_arena_unittest


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5farena_2eproto_2epb_2eh