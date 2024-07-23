set(MODULE_PATH "${PROJECT_SOURCE_DIR}/dep/yaml-cpp")
find_path( YAML_INCLUDE_DIR NAMES "yaml-cpp/yaml.h" PATHS "${MODULE_PATH}/include" NO_DEFAULT_PATH)
if(UNIX)
  find_library(YAML_LIBRARIES NAMES "yaml-cpp" PATHS "${ROOT_LIB_OUT_DIR}" NO_DEFAULT_PATH)
else()
  find_library(YAML_LIBRARIES NAMES "yaml-cpp" PATHS "${ROOT_ARC_OUT_DIR}" NO_DEFAULT_PATH)
endif()
MARK_AS_ADVANCED(
  YAML_INCLUDE_DIR
  YAML_LIBRARIES
  )
  
# handle the QUIETLY and REQUIRED arguments and set YAML_FOUND to TRUE if
# all listed variables are TRUE
include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( Yaml REQUIRED_VARS YAML_LIBRARIES YAML_INCLUDE_DIR)

option(YAML_CPP_BUILD_TOOLS "Enable parse tools" OFF)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")
add_subdirectory("dep/yaml-cpp")
set(YAML_LIBRARIES yaml-cpp)

if(NOT YAML_FOUND)
message(STATUS "******** Rebuild yaml-cpp ********")
endif()
