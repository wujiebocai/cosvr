// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_lite_imports_nonlite.proto
// Protobuf C++ Version: 4.26.0-dev

#include "google/protobuf/unittest_lite_imports_nonlite.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/io/zero_copy_stream_impl_lite.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace protobuf_unittest {

inline constexpr TestLiteImportsNonlite::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : _cached_size_{0},
        message_{nullptr},
        message_with_required_{nullptr} {}

template <typename>
PROTOBUF_CONSTEXPR TestLiteImportsNonlite::TestLiteImportsNonlite(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct TestLiteImportsNonliteDefaultTypeInternal {
  PROTOBUF_CONSTEXPR TestLiteImportsNonliteDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~TestLiteImportsNonliteDefaultTypeInternal() {}
  union {
    TestLiteImportsNonlite _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 TestLiteImportsNonliteDefaultTypeInternal _TestLiteImportsNonlite_default_instance_;
}  // namespace protobuf_unittest
namespace protobuf_unittest {
// ===================================================================

class TestLiteImportsNonlite::_Internal {
 public:
  using HasBits = decltype(std::declval<TestLiteImportsNonlite>()._impl_._has_bits_);
  static constexpr ::int32_t kHasBitsOffset =
    8 * PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, _impl_._has_bits_);
};

void TestLiteImportsNonlite::clear_message() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (_impl_.message_ != nullptr) _impl_.message_->Clear();
  _impl_._has_bits_[0] &= ~0x00000001u;
}
void TestLiteImportsNonlite::clear_message_with_required() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  if (_impl_.message_with_required_ != nullptr) _impl_.message_with_required_->Clear();
  _impl_._has_bits_[0] &= ~0x00000002u;
}
TestLiteImportsNonlite::TestLiteImportsNonlite(::google::protobuf::Arena* arena)
    : ::google::protobuf::MessageLite(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:protobuf_unittest.TestLiteImportsNonlite)
}
inline PROTOBUF_NDEBUG_INLINE TestLiteImportsNonlite::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : _has_bits_{from._has_bits_},
        _cached_size_{0} {}

TestLiteImportsNonlite::TestLiteImportsNonlite(
    ::google::protobuf::Arena* arena,
    const TestLiteImportsNonlite& from)
    : ::google::protobuf::MessageLite(arena) {
  TestLiteImportsNonlite* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<std::string>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);
  ::uint32_t cached_has_bits = _impl_._has_bits_[0];
  _impl_.message_ = (cached_has_bits & 0x00000001u) ? ::google::protobuf::MessageLite::CopyConstruct<::protobuf_unittest::TestAllTypes>(
                              arena, *from._impl_.message_)
                        : nullptr;
  _impl_.message_with_required_ = (cached_has_bits & 0x00000002u) ? ::google::protobuf::MessageLite::CopyConstruct<::protobuf_unittest::TestRequired>(
                              arena, *from._impl_.message_with_required_)
                        : nullptr;

  // @@protoc_insertion_point(copy_constructor:protobuf_unittest.TestLiteImportsNonlite)
}
inline PROTOBUF_NDEBUG_INLINE TestLiteImportsNonlite::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : _cached_size_{0} {}

inline void TestLiteImportsNonlite::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
  ::memset(reinterpret_cast<char *>(&_impl_) +
               offsetof(Impl_, message_),
           0,
           offsetof(Impl_, message_with_required_) -
               offsetof(Impl_, message_) +
               sizeof(Impl_::message_with_required_));
}
TestLiteImportsNonlite::~TestLiteImportsNonlite() {
  // @@protoc_insertion_point(destructor:protobuf_unittest.TestLiteImportsNonlite)
  _internal_metadata_.Delete<std::string>();
  SharedDtor();
}
inline void TestLiteImportsNonlite::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  delete _impl_.message_;
  delete _impl_.message_with_required_;
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
TestLiteImportsNonlite::GetClassData() const {
  struct ClassData_ {
    ::google::protobuf::MessageLite::ClassData header;
    char type_name[41];
  };

  PROTOBUF_CONSTINIT static const ClassData_ _data_ = {
      {
          nullptr,  // OnDemandRegisterArenaDtor
          PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, _impl_._cached_size_),
          true,
      },
      "protobuf_unittest.TestLiteImportsNonlite",
  };

  return &_data_.header;
}
PROTOBUF_NOINLINE void TestLiteImportsNonlite::Clear() {
// @@protoc_insertion_point(message_clear_start:protobuf_unittest.TestLiteImportsNonlite)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      ABSL_DCHECK(_impl_.message_ != nullptr);
      _impl_.message_->Clear();
    }
    if (cached_has_bits & 0x00000002u) {
      ABSL_DCHECK(_impl_.message_with_required_ != nullptr);
      _impl_.message_with_required_->Clear();
    }
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<std::string>();
}

const char* TestLiteImportsNonlite::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<1, 2, 2, 0, 2> TestLiteImportsNonlite::_table_ = {
  {
    PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, _impl_._has_bits_),
    0, // no _extensions_
    2, 8,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967292,  // skipmap
    offsetof(decltype(_table_), field_entries),
    2,  // num_field_entries
    2,  // num_aux_entries
    offsetof(decltype(_table_), aux_entries),
    &_TestLiteImportsNonlite_default_instance_._instance,
    ::_pbi::TcParser::GenericFallbackLite,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::protobuf_unittest::TestLiteImportsNonlite>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // optional .protobuf_unittest.TestRequired message_with_required = 2;
    {::_pbi::TcParser::FastMtS1,
     {18, 1, 1, PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, _impl_.message_with_required_)}},
    // optional .protobuf_unittest.TestAllTypes message = 1;
    {::_pbi::TcParser::FastMtS1,
     {10, 0, 0, PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, _impl_.message_)}},
  }}, {{
    65535, 65535
  }}, {{
    // optional .protobuf_unittest.TestAllTypes message = 1;
    {PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, _impl_.message_), _Internal::kHasBitsOffset + 0, 0,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
    // optional .protobuf_unittest.TestRequired message_with_required = 2;
    {PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, _impl_.message_with_required_), _Internal::kHasBitsOffset + 1, 1,
    (0 | ::_fl::kFcOptional | ::_fl::kMessage | ::_fl::kTvTable)},
  }}, {{
    {::_pbi::TcParser::GetTable<::protobuf_unittest::TestAllTypes>()},
    {::_pbi::TcParser::GetTable<::protobuf_unittest::TestRequired>()},
  }}, {{
  }},
};

::uint8_t* TestLiteImportsNonlite::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:protobuf_unittest.TestLiteImportsNonlite)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  // optional .protobuf_unittest.TestAllTypes message = 1;
  if (cached_has_bits & 0x00000001u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        1, *_impl_.message_, _impl_.message_->GetCachedSize(), target, stream);
  }

  // optional .protobuf_unittest.TestRequired message_with_required = 2;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::InternalWriteMessage(
        2, *_impl_.message_with_required_, _impl_.message_with_required_->GetCachedSize(), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = stream->WriteRaw(
        _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).data(),
        static_cast<int>(_internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).size()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:protobuf_unittest.TestLiteImportsNonlite)
  return target;
}

::size_t TestLiteImportsNonlite::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:protobuf_unittest.TestLiteImportsNonlite)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional .protobuf_unittest.TestAllTypes message = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size +=
          1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.message_);
    }

    // optional .protobuf_unittest.TestRequired message_with_required = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size +=
          1 + ::google::protobuf::internal::WireFormatLite::MessageSize(*_impl_.message_with_required_);
    }

  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    total_size += _internal_metadata_.unknown_fields<std::string>(::google::protobuf::internal::GetEmptyString).size();
  }
  _impl_._cached_size_.Set(::_pbi::ToCachedSize(total_size));
  return total_size;
}

void TestLiteImportsNonlite::CheckTypeAndMergeFrom(
    const ::google::protobuf::MessageLite& from) {
  MergeFrom(*::_pbi::DownCast<const TestLiteImportsNonlite*>(
      &from));
}

void TestLiteImportsNonlite::MergeFrom(const TestLiteImportsNonlite& from) {
  TestLiteImportsNonlite* const _this = this;
  ::google::protobuf::Arena* arena = _this->GetArena();
  // @@protoc_insertion_point(class_specific_merge_from_start:protobuf_unittest.TestLiteImportsNonlite)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      ABSL_DCHECK(from._impl_.message_ != nullptr);
      if (_this->_impl_.message_ == nullptr) {
        _this->_impl_.message_ =
            ::google::protobuf::MessageLite::CopyConstruct<::protobuf_unittest::TestAllTypes>(arena, *from._impl_.message_);
      } else {
        _this->_impl_.message_->MergeFrom(*from._impl_.message_);
      }
    }
    if (cached_has_bits & 0x00000002u) {
      ABSL_DCHECK(from._impl_.message_with_required_ != nullptr);
      if (_this->_impl_.message_with_required_ == nullptr) {
        _this->_impl_.message_with_required_ =
            ::google::protobuf::MessageLite::CopyConstruct<::protobuf_unittest::TestRequired>(arena, *from._impl_.message_with_required_);
      } else {
        _this->_impl_.message_with_required_->MergeFrom(*from._impl_.message_with_required_);
      }
    }
  }
  _this->_impl_._has_bits_[0] |= cached_has_bits;
  _this->_internal_metadata_.MergeFrom<std::string>(from._internal_metadata_);
}

void TestLiteImportsNonlite::CopyFrom(const TestLiteImportsNonlite& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:protobuf_unittest.TestLiteImportsNonlite)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool TestLiteImportsNonlite::IsInitialized() const {
  if ((_impl_._has_bits_[0] & 0x00000002u) != 0) {
    if (!_impl_.message_with_required_->IsInitialized()) return false;
  }
  return true;
}

void TestLiteImportsNonlite::InternalSwap(TestLiteImportsNonlite* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::google::protobuf::internal::memswap<
      PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, _impl_.message_with_required_)
      + sizeof(TestLiteImportsNonlite::_impl_.message_with_required_)
      - PROTOBUF_FIELD_OFFSET(TestLiteImportsNonlite, _impl_.message_)>(
          reinterpret_cast<char*>(&_impl_.message_),
          reinterpret_cast<char*>(&other->_impl_.message_));
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace protobuf_unittest
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
