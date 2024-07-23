// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_import.proto
// Protobuf C++ Version: 4.26.0-dev

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fimport_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fimport_2eproto_2epb_2eh

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
#include "google/protobuf/generated_enum_reflection.h"
#include "google/protobuf/unknown_field_set.h"
#include "google/protobuf/unittest_import_public.pb.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_5fimport_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2funittest_5fimport_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_google_2fprotobuf_2funittest_5fimport_2eproto;
namespace protobuf_unittest_import {
class ImportMessage;
struct ImportMessageDefaultTypeInternal;
extern ImportMessageDefaultTypeInternal _ImportMessage_default_instance_;
}  // namespace protobuf_unittest_import
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace protobuf_unittest_import {
enum ImportEnum : int {
  IMPORT_FOO = 7,
  IMPORT_BAR = 8,
  IMPORT_BAZ = 9,
};

bool ImportEnum_IsValid(int value);
extern const uint32_t ImportEnum_internal_data_[];
constexpr ImportEnum ImportEnum_MIN = static_cast<ImportEnum>(7);
constexpr ImportEnum ImportEnum_MAX = static_cast<ImportEnum>(9);
constexpr int ImportEnum_ARRAYSIZE = 9 + 1;
const ::google::protobuf::EnumDescriptor*
ImportEnum_descriptor();
template <typename T>
const std::string& ImportEnum_Name(T value) {
  static_assert(std::is_same<T, ImportEnum>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to ImportEnum_Name().");
  return ImportEnum_Name(static_cast<ImportEnum>(value));
}
template <>
inline const std::string& ImportEnum_Name(ImportEnum value) {
  return ::google::protobuf::internal::NameOfDenseEnum<ImportEnum_descriptor,
                                                 7, 9>(
      static_cast<int>(value));
}
inline bool ImportEnum_Parse(absl::string_view name, ImportEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ImportEnum>(
      ImportEnum_descriptor(), name, value);
}
enum ImportEnumForMap : int {
  UNKNOWN = 0,
  FOO = 1,
  BAR = 2,
};

bool ImportEnumForMap_IsValid(int value);
extern const uint32_t ImportEnumForMap_internal_data_[];
constexpr ImportEnumForMap ImportEnumForMap_MIN = static_cast<ImportEnumForMap>(0);
constexpr ImportEnumForMap ImportEnumForMap_MAX = static_cast<ImportEnumForMap>(2);
constexpr int ImportEnumForMap_ARRAYSIZE = 2 + 1;
const ::google::protobuf::EnumDescriptor*
ImportEnumForMap_descriptor();
template <typename T>
const std::string& ImportEnumForMap_Name(T value) {
  static_assert(std::is_same<T, ImportEnumForMap>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to ImportEnumForMap_Name().");
  return ImportEnumForMap_Name(static_cast<ImportEnumForMap>(value));
}
template <>
inline const std::string& ImportEnumForMap_Name(ImportEnumForMap value) {
  return ::google::protobuf::internal::NameOfDenseEnum<ImportEnumForMap_descriptor,
                                                 0, 2>(
      static_cast<int>(value));
}
inline bool ImportEnumForMap_Parse(absl::string_view name, ImportEnumForMap* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ImportEnumForMap>(
      ImportEnumForMap_descriptor(), name, value);
}

// ===================================================================


// -------------------------------------------------------------------

class ImportMessage final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:protobuf_unittest_import.ImportMessage) */ {
 public:
  inline ImportMessage() : ImportMessage(nullptr) {}
  ~ImportMessage() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR ImportMessage(
      ::google::protobuf::internal::ConstantInitialized);

  inline ImportMessage(const ImportMessage& from) : ImportMessage(nullptr, from) {}
  inline ImportMessage(ImportMessage&& from) noexcept
      : ImportMessage(nullptr, std::move(from)) {}
  inline ImportMessage& operator=(const ImportMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline ImportMessage& operator=(ImportMessage&& from) noexcept {
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
  static const ImportMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const ImportMessage* internal_default_instance() {
    return reinterpret_cast<const ImportMessage*>(
        &_ImportMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(ImportMessage& a, ImportMessage& b) { a.Swap(&b); }
  inline void Swap(ImportMessage* other) {
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
  void UnsafeArenaSwap(ImportMessage* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ImportMessage* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<ImportMessage>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const ImportMessage& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const ImportMessage& from) { ImportMessage::MergeImpl(*this, from); }

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
  void InternalSwap(ImportMessage* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "protobuf_unittest_import.ImportMessage"; }

 protected:
  explicit ImportMessage(::google::protobuf::Arena* arena);
  ImportMessage(::google::protobuf::Arena* arena, const ImportMessage& from);
  ImportMessage(::google::protobuf::Arena* arena, ImportMessage&& from) noexcept
      : ImportMessage(arena) {
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
  // optional int32 d = 1;
  bool has_d() const;
  void clear_d() ;
  ::int32_t d() const;
  void set_d(::int32_t value);

  private:
  ::int32_t _internal_d() const;
  void _internal_set_d(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:protobuf_unittest_import.ImportMessage)
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
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5fimport_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// ImportMessage

// optional int32 d = 1;
inline bool ImportMessage::has_d() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline void ImportMessage::clear_d() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.d_ = 0;
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline ::int32_t ImportMessage::d() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest_import.ImportMessage.d)
  return _internal_d();
}
inline void ImportMessage::set_d(::int32_t value) {
  _internal_set_d(value);
  _impl_._has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_set:protobuf_unittest_import.ImportMessage.d)
}
inline ::int32_t ImportMessage::_internal_d() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.d_;
}
inline void ImportMessage::_internal_set_d(::int32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.d_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace protobuf_unittest_import


namespace google {
namespace protobuf {

template <>
struct is_proto_enum<::protobuf_unittest_import::ImportEnum> : std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor<::protobuf_unittest_import::ImportEnum>() {
  return ::protobuf_unittest_import::ImportEnum_descriptor();
}
template <>
struct is_proto_enum<::protobuf_unittest_import::ImportEnumForMap> : std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor<::protobuf_unittest_import::ImportEnumForMap>() {
  return ::protobuf_unittest_import::ImportEnumForMap_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fimport_2eproto_2epb_2eh