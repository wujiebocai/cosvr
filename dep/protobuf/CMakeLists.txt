if(COMPILE_PROTOBUF)
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
  if(UNIX)
    add_definitions(-DHAVE_PTHREAD)
    add_compile_options(-fPIC)
    add_compile_options(-Wno-sign-compare)
    add_compile_options(-Wno-unused-function)
  else()
  endif()
    
  set(PROTOBUF_LIBRARIES libprotobuf)
  set(PROTOBUF_LITE_LIBRARIES libprotobuf_lite)
  set(PROTOBUF_PROTOC_EXECUTABLE protoc)

  set(protobuf_ABSL_PROVIDER "module" CACHE STRING "Provider of absl library")
  set_property(CACHE protobuf_ABSL_PROVIDER PROPERTY STRINGS "module" "package")

  set(protobuf_ABSL_PROVIDER "module" CACHE STRING "Provider of absl library")
  set_property(CACHE protobuf_ABSL_PROVIDER PROPERTY STRINGS "module" "package")

  #include(cmake/abseil-cpp.cmake)
  include(cmake/libabsl.cmake)
  include(cmake/utf8_range.cmake)
  include(cmake/libprotobuf.cmake)
  include(cmake/libprotoc.cmake)
  include(cmake/protoc.cmake)

else()
  if(UNIX)
    set(PROTOBUF_PROTOC_EXECUTABLE "${ROOT_BIN_OUT_PATH}/protoc")
    set(PROTOBUF_LIBRARIES "${ROOT_LIB_OUT_PATH}/libprotobuf.a")
    set(PROTOBUF_LITE_LIBRARIES "${ROOT_LIB_OUT_PATH}/libprotobuf_lite.a")
  else()
    set(PROTOBUF_PROTOC_EXECUTABLE "${ROOT_BIN_OUT_PATH}/protoc.exe")
    set(PROTOBUF_LIBRARIES "${ROOT_LIB_OUT_PATH}/libprotobuf.lib")
    set(PROTOBUF_LITE_LIBRARIES "${ROOT_LIB_OUT_PATH}/libprotobuf_lite.lib")

  endif()
endif()

# file(GLOB PROTOS "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
# set(INPUT_DIR   ${CMAKE_CURRENT_SOURCE_DIR})
# set(PROTOC_C_OUT_FLAG --cpp_out)
# set(PROTO_GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/out)
# foreach(PROTO ${PROTOS})
#   get_filename_component(PROTO_NAME ${PROTO} NAME_WE)
#   set(CUR_PROTO_GEN
#     ${PROTO_GEN_DIR}/${PROTO_NAME}.pb.h
#     ${PROTO_GEN_DIR}/${PROTO_NAME}.pb.cc)
#   set(PROTO_GEN
#     ${PROTO_GEN}
#     ${CUR_PROTO_GEN})
#   add_custom_command(
#     OUTPUT ${CUR_PROTO_GEN}
#     COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO} ${PROTOC_C_OUT_FLAG} ${PROTO_GEN_DIR} -I${INPUT_DIR}
#     DEPENDS ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO}
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# endforeach()

# add_library(pblib ${PROTO_GEN} ${PROTOS})
# target_link_libraries(pblib ${PROTOBUF_LIBRARIES})
# set_target_properties(pblib PROPERTIES PREFIX "")