set(libprotoc_files
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/allowlists/empty_package.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/allowlists/open_enum.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/code_generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/command_line_interface.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/enum.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/extension.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/field_generators/cord_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/field_generators/enum_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/field_generators/map_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/field_generators/message_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/field_generators/primitive_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/field_generators/string_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/file.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/helpers.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/message.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/padding_optimizer.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/parse_function_generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/service.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/tracker.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_doc_comment.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_enum.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_enum_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_field_base.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_helpers.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_map_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_message.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_message_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_primitive_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_reflection_class.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_repeated_enum_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_repeated_message_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_repeated_primitive_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_source_generator_base.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_wrapper_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/names.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/context.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/doc_comment.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/enum.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/enum_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/enum_field_lite.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/enum_lite.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/extension.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/extension_lite.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/file.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/generator_factory.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/helpers.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/java_features.pb.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/kotlin_generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/map_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/map_field_lite.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_builder.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_builder_lite.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_field_lite.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_lite.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_serialization.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/name_resolver.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/names.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/primitive_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/primitive_field_lite.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/service.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/shared_code_generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/string_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/string_field_lite.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/enum.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/enum_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/extension.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/file.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/helpers.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/import_writer.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/line_consumer.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/map_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/message.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/message_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/names.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/oneof.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/primitive_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/text_format_decode_data.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/php/names.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/php/php_generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/plugin.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/plugin.pb.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/python/generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/python/helpers.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/python/pyi_generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/retention.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/ruby/ruby_generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/accessors.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/helpers.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/map.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/repeated_scalar.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/singular_message.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/singular_scalar.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/singular_string.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/unsupported_field.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/context.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/generator.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/message.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/naming.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/oneof.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/relative_path.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/subprocess.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/versions.cc
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/zip_writer.cc
)

set(libprotoc_headers
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/allowlists/allowlist.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/allowlists/allowlists.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/code_generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/command_line_interface.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/enum.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/extension.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/field_generators/generators.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/file.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/helpers.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/message.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/message_layout_helper.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/names.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/options.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/padding_optimizer.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/parse_function_generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/service.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/cpp/tracker.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_doc_comment.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_enum.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_enum_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_field_base.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_helpers.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_map_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_message.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_message_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_options.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_primitive_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_reflection_class.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_repeated_enum_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_repeated_message_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_repeated_primitive_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_source_generator_base.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/csharp_wrapper_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/csharp/names.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/context.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/doc_comment.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/enum.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/enum_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/enum_field_lite.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/enum_lite.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/extension.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/extension_lite.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/file.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/generator_factory.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/helpers.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/java_features.pb.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/kotlin_generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/map_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/map_field_lite.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_builder.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_builder_lite.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_field_lite.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_lite.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/message_serialization.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/name_resolver.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/names.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/options.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/primitive_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/primitive_field_lite.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/service.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/shared_code_generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/string_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/java/string_field_lite.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/enum.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/enum_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/extension.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/file.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/helpers.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/import_writer.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/line_consumer.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/map_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/message.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/message_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/names.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/nsobject_methods.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/oneof.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/options.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/primitive_field.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/objectivec/text_format_decode_data.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/php/names.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/php/php_generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/plugin.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/plugin.pb.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/python/generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/python/helpers.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/python/pyi_generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/retention.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/ruby/ruby_generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/accessor_generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/accessors.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/accessors/helpers.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/context.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/generator.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/message.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/naming.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/oneof.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/rust/relative_path.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/scc.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/subprocess.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/versions.h
${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/zip_writer.h
)
#add_library(libprotoc ${libprotoc_files} ${libprotoc_headers})
#target_link_libraries(libprotoc libprotobuf libprotobuf_lite )
#set_target_properties(libprotoc PROPERTIES PREFIX "" FOLDER "opt")

add_library(PROTOC_LIB OBJECT ${libprotoc_files} ${libprotoc_headers})
add_dependencies(PROTOC_LIB PROTOBUF_LIB PROTOBUF_LITE_LIB ABSL_LIB)

add_library(libprotoc STATIC $<TARGET_OBJECTS:PROTOC_LIB>
                             $<TARGET_OBJECTS:PROTOBUF_LIB>
                             $<TARGET_OBJECTS:PROTOBUF_LITE_LIB>
                             $<TARGET_OBJECTS:ABSL_LIB>)

#基于ABSL_LIB 就不在需要${protobuf_ABSL_USED_TARGETS}
target_link_libraries(libprotoc ${THREAD_LIBRARY} utf8_validity)
set_target_properties(libprotoc PROPERTIES PREFIX "" FOLDER "opt")
