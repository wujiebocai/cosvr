// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: google/protobuf/unittest_invalid_features.proto
// Protobuf C++ Version: 4.26.0-dev

#include "google/protobuf/unittest_invalid_features.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
#include "google/protobuf/generated_message_tctable_impl.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::google::protobuf;
namespace _pbi = ::google::protobuf::internal;
namespace _fl = ::google::protobuf::internal::field_layout;
namespace pb {

inline constexpr TestInvalidFeatures::Impl_::Impl_(
    ::_pbi::ConstantInitialized) noexcept
      : repeated_feature_{},
        _cached_size_{0} {}

template <typename>
PROTOBUF_CONSTEXPR TestInvalidFeatures::TestInvalidFeatures(::_pbi::ConstantInitialized)
    : _impl_(::_pbi::ConstantInitialized()) {}
struct TestInvalidFeaturesDefaultTypeInternal {
  PROTOBUF_CONSTEXPR TestInvalidFeaturesDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~TestInvalidFeaturesDefaultTypeInternal() {}
  union {
    TestInvalidFeatures _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 TestInvalidFeaturesDefaultTypeInternal _TestInvalidFeatures_default_instance_;
}  // namespace pb
static ::_pb::Metadata file_level_metadata_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto[1];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto = nullptr;
const ::uint32_t
    TableStruct_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto::offsets[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
        protodesc_cold) = {
        ~0u,  // no _has_bits_
        PROTOBUF_FIELD_OFFSET(::pb::TestInvalidFeatures, _internal_metadata_),
        ~0u,  // no _extensions_
        ~0u,  // no _oneof_case_
        ~0u,  // no _weak_field_map_
        ~0u,  // no _inlined_string_donated_
        ~0u,  // no _split_
        ~0u,  // no sizeof(Split)
        PROTOBUF_FIELD_OFFSET(::pb::TestInvalidFeatures, _impl_.repeated_feature_),
};

static const ::_pbi::MigrationSchema
    schemas[] ABSL_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
        {0, -1, -1, sizeof(::pb::TestInvalidFeatures)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::pb::_TestInvalidFeatures_default_instance_._instance,
};
const char descriptor_table_protodef_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto[] ABSL_ATTRIBUTE_SECTION_VARIABLE(
    protodesc_cold) = {
    "\n/google/protobuf/unittest_invalid_featu"
    "res.proto\022\002pb\032 google/protobuf/descripto"
    "r.proto\"@\n\023TestInvalidFeatures\022)\n\020repeat"
    "ed_feature\030\001 \003(\005B\017\210\001\001\230\001\004\242\001\006\022\0013\030\350\007:K\n\014tes"
    "t_invalid\022\033.google.protobuf.FeatureSet\030\214"
    "N \001(\0132\027.pb.TestInvalidFeatures"
};
static const ::_pbi::DescriptorTable* const descriptor_table_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto_deps[1] =
    {
        &::descriptor_table_google_2fprotobuf_2fdescriptor_2eproto,
};
static ::absl::once_flag descriptor_table_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto = {
    false,
    false,
    230,
    descriptor_table_protodef_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto,
    "google/protobuf/unittest_invalid_features.proto",
    &descriptor_table_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto_once,
    descriptor_table_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto_deps,
    1,
    1,
    schemas,
    file_default_instances,
    TableStruct_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto::offsets,
    file_level_metadata_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto,
    file_level_enum_descriptors_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto,
    file_level_service_descriptors_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto_getter() {
  return &descriptor_table_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto;
}
namespace pb {
// ===================================================================

class TestInvalidFeatures::_Internal {
 public:
};

TestInvalidFeatures::TestInvalidFeatures(::google::protobuf::Arena* arena)
    : ::google::protobuf::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:pb.TestInvalidFeatures)
}
inline PROTOBUF_NDEBUG_INLINE TestInvalidFeatures::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility, ::google::protobuf::Arena* arena,
    const Impl_& from)
      : repeated_feature_{visibility, arena, from.repeated_feature_},
        _cached_size_{0} {}

TestInvalidFeatures::TestInvalidFeatures(
    ::google::protobuf::Arena* arena,
    const TestInvalidFeatures& from)
    : ::google::protobuf::Message(arena) {
  TestInvalidFeatures* const _this = this;
  (void)_this;
  _internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(
      from._internal_metadata_);
  new (&_impl_) Impl_(internal_visibility(), arena, from._impl_);

  // @@protoc_insertion_point(copy_constructor:pb.TestInvalidFeatures)
}
inline PROTOBUF_NDEBUG_INLINE TestInvalidFeatures::Impl_::Impl_(
    ::google::protobuf::internal::InternalVisibility visibility,
    ::google::protobuf::Arena* arena)
      : repeated_feature_{visibility, arena},
        _cached_size_{0} {}

inline void TestInvalidFeatures::SharedCtor(::_pb::Arena* arena) {
  new (&_impl_) Impl_(internal_visibility(), arena);
}
TestInvalidFeatures::~TestInvalidFeatures() {
  // @@protoc_insertion_point(destructor:pb.TestInvalidFeatures)
  _internal_metadata_.Delete<::google::protobuf::UnknownFieldSet>();
  SharedDtor();
}
inline void TestInvalidFeatures::SharedDtor() {
  ABSL_DCHECK(GetArena() == nullptr);
  _impl_.~Impl_();
}

const ::google::protobuf::MessageLite::ClassData*
TestInvalidFeatures::GetClassData() const {
  PROTOBUF_CONSTINIT static const ::google::protobuf::MessageLite::
      ClassDataFull _data_ = {
          {
              nullptr,  // OnDemandRegisterArenaDtor
              PROTOBUF_FIELD_OFFSET(TestInvalidFeatures, _impl_._cached_size_),
              false,
          },
          &TestInvalidFeatures::MergeImpl,
          &TestInvalidFeatures::kDescriptorMethods,
      };
  return &_data_;
}
PROTOBUF_NOINLINE void TestInvalidFeatures::Clear() {
// @@protoc_insertion_point(message_clear_start:pb.TestInvalidFeatures)
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.repeated_feature_.Clear();
  _internal_metadata_.Clear<::google::protobuf::UnknownFieldSet>();
}

const char* TestInvalidFeatures::_InternalParse(
    const char* ptr, ::_pbi::ParseContext* ctx) {
  ptr = ::_pbi::TcParser::ParseLoop(this, ptr, ctx, &_table_.header);
  return ptr;
}


PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1
const ::_pbi::TcParseTable<0, 1, 0, 0, 2> TestInvalidFeatures::_table_ = {
  {
    0,  // no _has_bits_
    0, // no _extensions_
    1, 0,  // max_field_number, fast_idx_mask
    offsetof(decltype(_table_), field_lookup_table),
    4294967294,  // skipmap
    offsetof(decltype(_table_), field_entries),
    1,  // num_field_entries
    0,  // num_aux_entries
    offsetof(decltype(_table_), field_names),  // no aux_entries
    &_TestInvalidFeatures_default_instance_._instance,
    ::_pbi::TcParser::GenericFallback,  // fallback
    #ifdef PROTOBUF_PREFETCH_PARSE_TABLE
    ::_pbi::TcParser::GetTable<::pb::TestInvalidFeatures>(),  // to_prefetch
    #endif  // PROTOBUF_PREFETCH_PARSE_TABLE
  }, {{
    // repeated int32 repeated_feature = 1 [retention = RETENTION_RUNTIME, targets = TARGET_TYPE_FIELD, edition_defaults = {
    {::_pbi::TcParser::FastV32R1,
     {8, 63, 0, PROTOBUF_FIELD_OFFSET(TestInvalidFeatures, _impl_.repeated_feature_)}},
  }}, {{
    65535, 65535
  }}, {{
    // repeated int32 repeated_feature = 1 [retention = RETENTION_RUNTIME, targets = TARGET_TYPE_FIELD, edition_defaults = {
    {PROTOBUF_FIELD_OFFSET(TestInvalidFeatures, _impl_.repeated_feature_), 0, 0,
    (0 | ::_fl::kFcRepeated | ::_fl::kInt32)},
  }},
  // no aux_entries
  {{
  }},
};

::uint8_t* TestInvalidFeatures::_InternalSerialize(
    ::uint8_t* target,
    ::google::protobuf::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:pb.TestInvalidFeatures)
  ::uint32_t cached_has_bits = 0;
  (void)cached_has_bits;

  // repeated int32 repeated_feature = 1 [retention = RETENTION_RUNTIME, targets = TARGET_TYPE_FIELD, edition_defaults = {
  for (int i = 0, n = this->_internal_repeated_feature_size(); i < n; ++i) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(
        1, this->_internal_repeated_feature().Get(i), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target =
        ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
            _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pb.TestInvalidFeatures)
  return target;
}

::size_t TestInvalidFeatures::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pb.TestInvalidFeatures)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated int32 repeated_feature = 1 [retention = RETENTION_RUNTIME, targets = TARGET_TYPE_FIELD, edition_defaults = {
  {
    std::size_t data_size = ::_pbi::WireFormatLite::Int32Size(
        this->_internal_repeated_feature())
    ;
    std::size_t tag_size = std::size_t{1} *
        ::_pbi::FromIntSize(this->_internal_repeated_feature_size());
    ;
    total_size += tag_size + data_size;
  }
  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}


void TestInvalidFeatures::MergeImpl(::google::protobuf::MessageLite& to_msg, const ::google::protobuf::MessageLite& from_msg) {
  auto* const _this = static_cast<TestInvalidFeatures*>(&to_msg);
  auto& from = static_cast<const TestInvalidFeatures&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:pb.TestInvalidFeatures)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_internal_mutable_repeated_feature()->MergeFrom(from._internal_repeated_feature());
  _this->_internal_metadata_.MergeFrom<::google::protobuf::UnknownFieldSet>(from._internal_metadata_);
}

void TestInvalidFeatures::CopyFrom(const TestInvalidFeatures& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pb.TestInvalidFeatures)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

PROTOBUF_NOINLINE bool TestInvalidFeatures::IsInitialized() const {
  return true;
}

void TestInvalidFeatures::InternalSwap(TestInvalidFeatures* PROTOBUF_RESTRICT other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.repeated_feature_.InternalSwap(&other->_impl_.repeated_feature_);
}

::google::protobuf::Metadata TestInvalidFeatures::GetMetadata() const {
  return ::_pbi::AssignDescriptors(&descriptor_table_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto_getter,
                                   &descriptor_table_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto_once,
                                   file_level_metadata_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto[0]);
}
PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 ::_pbi::
        ExtensionIdentifier<::google::protobuf::FeatureSet, ::_pbi::MessageTypeTraits< ::pb::TestInvalidFeatures >,
                            11, false>
            test_invalid(kTestInvalidFieldNumber, &::pb::_TestInvalidFeatures_default_instance_);
// @@protoc_insertion_point(namespace_scope)
}  // namespace pb
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google
// @@protoc_insertion_point(global_scope)
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::std::false_type _static_init_ PROTOBUF_UNUSED =
    (::_pbi::AddDescriptors(&descriptor_table_google_2fprotobuf_2funittest_5finvalid_5ffeatures_2eproto),
    ::_pbi::ExtensionSet::RegisterMessageExtension(
        &::google::protobuf::FeatureSet::default_instance(), 9996, 11,
        false, false, &::pb::TestInvalidFeatures::default_instance(),
        nullptr, ::_pbi::LazyAnnotation::kUndefined),
     ::std::false_type{});
#include "google/protobuf/port_undef.inc"
