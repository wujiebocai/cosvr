// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_lazy_dependencies_custom_option.proto
// Protobuf C++ Version: 4.26.0-dev

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5flazy_5fdependencies_5fcustom_5foption_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5flazy_5fdependencies_5fcustom_5foption_2eproto_2epb_2eh

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
#include "google/protobuf/descriptor.pb.h"
#include "google/protobuf/unittest_lazy_dependencies_enum.pb.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_5flazy_5fdependencies_5fcustom_5foption_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2funittest_5flazy_5fdependencies_5fcustom_5foption_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_google_2fprotobuf_2funittest_5flazy_5fdependencies_5fcustom_5foption_2eproto;
namespace protobuf_unittest {
namespace lazy_imports {
class LazyMessage;
struct LazyMessageDefaultTypeInternal;
extern LazyMessageDefaultTypeInternal _LazyMessage_default_instance_;
}  // namespace lazy_imports
}  // namespace protobuf_unittest
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace protobuf_unittest {
namespace lazy_imports {

// ===================================================================


// -------------------------------------------------------------------

class LazyMessage final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:protobuf_unittest.lazy_imports.LazyMessage) */ {
 public:
  inline LazyMessage() : LazyMessage(nullptr) {}
  ~LazyMessage() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR LazyMessage(
      ::google::protobuf::internal::ConstantInitialized);

  inline LazyMessage(const LazyMessage& from) : LazyMessage(nullptr, from) {}
  inline LazyMessage(LazyMessage&& from) noexcept
      : LazyMessage(nullptr, std::move(from)) {}
  inline LazyMessage& operator=(const LazyMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline LazyMessage& operator=(LazyMessage&& from) noexcept {
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
  static const LazyMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const LazyMessage* internal_default_instance() {
    return reinterpret_cast<const LazyMessage*>(
        &_LazyMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(LazyMessage& a, LazyMessage& b) { a.Swap(&b); }
  inline void Swap(LazyMessage* other) {
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
  void UnsafeArenaSwap(LazyMessage* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  LazyMessage* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<LazyMessage>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const LazyMessage& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const LazyMessage& from) { LazyMessage::MergeImpl(*this, from); }

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
  void InternalSwap(LazyMessage* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "protobuf_unittest.lazy_imports.LazyMessage"; }

 protected:
  explicit LazyMessage(::google::protobuf::Arena* arena);
  LazyMessage(::google::protobuf::Arena* arena, const LazyMessage& from);
  LazyMessage(::google::protobuf::Arena* arena, LazyMessage&& from) noexcept
      : LazyMessage(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::MessageLite::ClassData* GetClassData()
      const final;

 public:
  ::google::protobuf::Metadata GetMetadata() const final;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kAFieldNumber = 1,
  };
  // int32 a = 1;
  bool has_a() const;
  void clear_a() ;
  ::int32_t a() const;
  void set_a(::int32_t value);

  private:
  ::int32_t _internal_a() const;
  void _internal_set_a(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:protobuf_unittest.lazy_imports.LazyMessage)
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
    ::int32_t a_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5flazy_5fdependencies_5fcustom_5foption_2eproto;
};

// ===================================================================



static const int kLazyEnumOptionFieldNumber = 138596335;
extern ::google::protobuf::internal::ExtensionIdentifier<
    ::google::protobuf::MessageOptions, ::google::protobuf::internal::EnumTypeTraits< ::protobuf_unittest::lazy_imports::LazyEnum, ::protobuf_unittest::lazy_imports::LazyEnum_IsValid>, 14,
    false>
    lazy_enum_option;

// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// LazyMessage

// int32 a = 1;
inline bool LazyMessage::has_a() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline void LazyMessage::clear_a() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.a_ = 0;
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline ::int32_t LazyMessage::a() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest.lazy_imports.LazyMessage.a)
  return _internal_a();
}
inline void LazyMessage::set_a(::int32_t value) {
  _internal_set_a(value);
  _impl_._has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_set:protobuf_unittest.lazy_imports.LazyMessage.a)
}
inline ::int32_t LazyMessage::_internal_a() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.a_;
}
inline void LazyMessage::_internal_set_a(::int32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.a_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace lazy_imports
}  // namespace protobuf_unittest


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5flazy_5fdependencies_5fcustom_5foption_2eproto_2epb_2eh