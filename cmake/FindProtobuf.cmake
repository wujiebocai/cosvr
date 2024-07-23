# find protobuf
set(MODULE_PATH "${PROJECT_SOURCE_DIR}/dep/protobuf")
if(UNIX)
  set(PROTOC_EXECUTABLE "protoc")
  set(CMAKE_FIND_LIBRARY_PREFIXES "")
  set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
else()
set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  set(PROTOC_EXECUTABLE "protoc.exe")
endif()
find_path( PROTOBUF_INCLUDE_DIR NAMES "google/protobuf/message.h" PATHS "${MODULE_PATH}/src/" NO_DEFAULT_PATH)
find_library(PROTOBUF_LIBRARIES NAMES "libprotobuf" PATHS "${ROOT_ARC_OUT_DIR}" NO_DEFAULT_PATH)
find_library(PROTOBUF_LITE_LIBRARIES NAMES "libprotobuf_lite" PATHS "${ROOT_ARC_OUT_DIR}" NO_DEFAULT_PATH)
find_path(PROTOBUF_PROTOC_EXECUTABLE NAMES ${PROTOC_EXECUTABLE} PATHS "${ROOT_BIN_OUT_DIR}" NO_DEFAULT_PATH)

MARK_AS_ADVANCED(
  PROTOBUF_INCLUDE_DIR
  PROTOBUF_LIBRARIES
  PROTOBUF_LITE_LIBRARIES
  )

# handle the QUIETLY and REQUIRED arguments and set PROTOBUF_FOUND to TRUE if
# all listed variables are TRUE
include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( Protobuf REQUIRED_VARS PROTOBUF_LIBRARIES PROTOBUF_INCLUDE_DIR PROTOBUF_LITE_LIBRARIES PROTOBUF_PROTOC_EXECUTABLE)

option(COMPILE_PROTOBUF "Compile protobuf libraries" ON)
add_subdirectory("dep/protobuf")
set(PROTOBUF_LIBRARIES libprotobuf)
set(PROTOBUF_LITE_LIBRARIES libprotobuf_lite)

if(NOT PROTOBUF_FOUND)
message(STATUS "******** Rebuild protobuf ********")
endif()
