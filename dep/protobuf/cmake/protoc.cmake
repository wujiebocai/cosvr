#set(protoc_files ${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/main.cc)
#add_executable(protoc ${protoc_files})
#target_link_libraries(protoc libprotoc libprotobuf ${protobuf_ABSL_USED_TARGETS})
#set_target_properties(protoc PROPERTIES PREFIX "" FOLDER "dep")

#add_executable(protobuf::protoc ALIAS protoc)

set(protoc_files
  ${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/compiler/main.cc
)

add_executable(protoc ${protoc_files} ${protobuf_version_rc_file})
target_link_libraries(protoc
  libprotoc
)
add_executable(protobuf::protoc ALIAS protoc)

#set_target_properties(protoc PROPERTIES
#    VERSION ${protobuf_VERSION})
