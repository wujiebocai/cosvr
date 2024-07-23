// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_no_generic_services.proto
// Protobuf C++ Version: 4.26.0-dev

#ifndef GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto_2epb_2eh

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
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto;
namespace protobuf_unittest {
namespace no_generic_services_test {
class TestMessage;
struct TestMessageDefaultTypeInternal;
extern TestMessageDefaultTypeInternal _TestMessage_default_instance_;
}  // namespace no_generic_services_test
}  // namespace protobuf_unittest
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace protobuf_unittest {
namespace no_generic_services_test {
enum TestEnum : int {
  FOO = 1,
};

bool TestEnum_IsValid(int value);
extern const uint32_t TestEnum_internal_data_[];
constexpr TestEnum TestEnum_MIN = static_cast<TestEnum>(1);
constexpr TestEnum TestEnum_MAX = static_cast<TestEnum>(1);
constexpr int TestEnum_ARRAYSIZE = 1 + 1;
const ::google::protobuf::EnumDescriptor*
TestEnum_descriptor();
template <typename T>
const std::string& TestEnum_Name(T value) {
  static_assert(std::is_same<T, TestEnum>::value ||
                    std::is_integral<T>::value,
                "Incorrect type passed to TestEnum_Name().");
  return TestEnum_Name(static_cast<TestEnum>(value));
}
template <>
inline const std::string& TestEnum_Name(TestEnum value) {
  return ::google::protobuf::internal::NameOfDenseEnum<TestEnum_descriptor,
                                                 1, 1>(
      static_cast<int>(value));
}
inline bool TestEnum_Parse(absl::string_view name, TestEnum* value) {
  return ::google::protobuf::internal::ParseNamedEnum<TestEnum>(
      TestEnum_descriptor(), name, value);
}

// ===================================================================


// -------------------------------------------------------------------

class TestMessage final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:protobuf_unittest.no_generic_services_test.TestMessage) */ {
 public:
  inline TestMessage() : TestMessage(nullptr) {}
  ~TestMessage() override;
  template <typename = void>
  explicit PROTOBUF_CONSTEXPR TestMessage(
      ::google::protobuf::internal::ConstantInitialized);

  inline TestMessage(const TestMessage& from) : TestMessage(nullptr, from) {}
  inline TestMessage(TestMessage&& from) noexcept
      : TestMessage(nullptr, std::move(from)) {}
  inline TestMessage& operator=(const TestMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline TestMessage& operator=(TestMessage&& from) noexcept {
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
  static const TestMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const TestMessage* internal_default_instance() {
    return reinterpret_cast<const TestMessage*>(
        &_TestMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(TestMessage& a, TestMessage& b) { a.Swap(&b); }
  inline void Swap(TestMessage* other) {
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
  void UnsafeArenaSwap(TestMessage* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  TestMessage* New(::google::protobuf::Arena* arena = nullptr) const final {
    return ::google::protobuf::Message::DefaultConstruct<TestMessage>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const TestMessage& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const TestMessage& from) { TestMessage::MergeImpl(*this, from); }

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
  void InternalSwap(TestMessage* other);
 private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() { return "protobuf_unittest.no_generic_services_test.TestMessage"; }

 protected:
  explicit TestMessage(::google::protobuf::Arena* arena);
  TestMessage(::google::protobuf::Arena* arena, const TestMessage& from);
  TestMessage(::google::protobuf::Arena* arena, TestMessage&& from) noexcept
      : TestMessage(arena) {
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
  // optional int32 a = 1;
  bool has_a() const;
  void clear_a() ;
  ::int32_t a() const;
  void set_a(::int32_t value);

  private:
  ::int32_t _internal_a() const;
  void _internal_set_a(::int32_t value);

  public:
  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline bool HasExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id) const {
    return _impl_._extensions_.Has(id.number());
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline void ClearExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id) {
    _impl_._extensions_.ClearExtension(id.number());
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline int ExtensionSize(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id) const {
    return _impl_._extensions_.ExtensionSize(id.number());
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed,
            std::enable_if_t<!_proto_TypeTraits::kLifetimeBound, int> = 0>
  inline typename _proto_TypeTraits::Singular::ConstType GetExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id) const {
    return _proto_TypeTraits::Get(id.number(), _impl_._extensions_, id.default_value());
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed,
            std::enable_if_t<_proto_TypeTraits::kLifetimeBound, int> = 0>
  inline typename _proto_TypeTraits::Singular::ConstType GetExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id) const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _proto_TypeTraits::Get(id.number(), _impl_._extensions_, id.default_value());
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Singular::MutableType MutableExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id)
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _proto_TypeTraits::Mutable(id.number(), _field_type, &_impl_._extensions_);
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline void SetExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id,
      typename _proto_TypeTraits::Singular::ConstType value) {
    _proto_TypeTraits::Set(id.number(), _field_type, value, &_impl_._extensions_);
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline void SetAllocatedExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id,
      typename _proto_TypeTraits::Singular::MutableType value) {
    _proto_TypeTraits::SetAllocated(id.number(), _field_type, value,
                                    &_impl_._extensions_);
  }
  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline void UnsafeArenaSetAllocatedExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id,
      typename _proto_TypeTraits::Singular::MutableType value) {
    _proto_TypeTraits::UnsafeArenaSetAllocated(id.number(), _field_type,
                                               value, &_impl_._extensions_);
  }
  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  PROTOBUF_NODISCARD inline
      typename _proto_TypeTraits::Singular::MutableType
      ReleaseExtension(
          const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                           _field_type, _is_packed>& id) {
    return _proto_TypeTraits::Release(id.number(), _field_type, &_impl_._extensions_);
  }
  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Singular::MutableType
  UnsafeArenaReleaseExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id) {
    return _proto_TypeTraits::UnsafeArenaRelease(id.number(), _field_type,
                                                 &_impl_._extensions_);
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed,
            std::enable_if_t<!_proto_TypeTraits::kLifetimeBound, int> = 0>
  inline typename _proto_TypeTraits::Repeated::ConstType GetExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id,
      int index) const {
    return _proto_TypeTraits::Get(id.number(), _impl_._extensions_, index);
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed,
            std::enable_if_t<_proto_TypeTraits::kLifetimeBound, int> = 0>
  inline typename _proto_TypeTraits::Repeated::ConstType GetExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id,
      int index) const ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _proto_TypeTraits::Get(id.number(), _impl_._extensions_, index);
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Repeated::MutableType MutableExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id,
      int index) ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _proto_TypeTraits::Mutable(id.number(), index, &_impl_._extensions_);
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline void SetExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id,
      int index, typename _proto_TypeTraits::Repeated::ConstType value) {
    _proto_TypeTraits::Set(id.number(), index, value, &_impl_._extensions_);
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Repeated::MutableType AddExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id)
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    typename _proto_TypeTraits::Repeated::MutableType to_add =
        _proto_TypeTraits::Add(id.number(), _field_type, &_impl_._extensions_);
    return to_add;
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline void AddExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id,
      typename _proto_TypeTraits::Repeated::ConstType value) {
    _proto_TypeTraits::Add(id.number(), _field_type, _is_packed, value,
                           &_impl_._extensions_);
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline const typename _proto_TypeTraits::Repeated::RepeatedFieldType&
  GetRepeatedExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id) const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _proto_TypeTraits::GetRepeated(id.number(), _impl_._extensions_);
  }

  template <typename _proto_TypeTraits, ::google::protobuf::internal::FieldType _field_type,
            bool _is_packed>
  inline typename _proto_TypeTraits::Repeated::RepeatedFieldType*
  MutableRepeatedExtension(
      const ::google::protobuf::internal::ExtensionIdentifier<TestMessage, _proto_TypeTraits,
                                       _field_type, _is_packed>& id)
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _proto_TypeTraits::MutableRepeated(id.number(), _field_type,
                                              _is_packed, &_impl_._extensions_);
  }
  // @@protoc_insertion_point(class_scope:protobuf_unittest.no_generic_services_test.TestMessage)
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
    ::google::protobuf::internal::ExtensionSet _extensions_;
    ::google::protobuf::internal::HasBits<1> _has_bits_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    ::int32_t a_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto;
};

// ===================================================================



static const int kTestExtensionFieldNumber = 1000;
extern ::google::protobuf::internal::ExtensionIdentifier<
    ::protobuf_unittest::no_generic_services_test::TestMessage, ::google::protobuf::internal::PrimitiveTypeTraits< ::int32_t >, 5,
    false>
    test_extension;

// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// TestMessage

// optional int32 a = 1;
inline bool TestMessage::has_a() const {
  bool value = (_impl_._has_bits_[0] & 0x00000001u) != 0;
  return value;
}
inline void TestMessage::clear_a() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.a_ = 0;
  _impl_._has_bits_[0] &= ~0x00000001u;
}
inline ::int32_t TestMessage::a() const {
  // @@protoc_insertion_point(field_get:protobuf_unittest.no_generic_services_test.TestMessage.a)
  return _internal_a();
}
inline void TestMessage::set_a(::int32_t value) {
  _internal_set_a(value);
  _impl_._has_bits_[0] |= 0x00000001u;
  // @@protoc_insertion_point(field_set:protobuf_unittest.no_generic_services_test.TestMessage.a)
}
inline ::int32_t TestMessage::_internal_a() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.a_;
}
inline void TestMessage::_internal_set_a(::int32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.a_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace no_generic_services_test
}  // namespace protobuf_unittest


namespace google {
namespace protobuf {

template <>
struct is_proto_enum<::protobuf_unittest::no_generic_services_test::TestEnum> : std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor<::protobuf_unittest::no_generic_services_test::TestEnum>() {
  return ::protobuf_unittest::no_generic_services_test::TestEnum_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_google_2fprotobuf_2funittest_5fno_5fgeneric_5fservices_2eproto_2epb_2eh