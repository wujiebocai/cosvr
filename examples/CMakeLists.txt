set(DEP_PATH "${PROJECT_SOURCE_DIR}/dep")

file(GLOB SRC "*.cpp" "*.hpp" "*.h" "*.c")
set(EXE_NAME examples)
source_group("" FILES ${SRC})
ADD_EXECUTABLE(${EXE_NAME} ${SRC})

#if(GENPROTO)
include(../cmake/CompileProto.cmake)
set(PROTO_FILES test.proto)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output/include)
set(PROTOC_FLAGS ${PROTOC_FLAGS} -I${PROTOBUF_INCLUDE_DIR})
compile_proto(PROTO_HDRS PROTO_SRCS ${PROJECT_BINARY_DIR}
                                    ${PROJECT_BINARY_DIR}/output/include
                                    ${PROJECT_SOURCE_DIR}/examples
                                    "${PROTO_FILES}")
add_library(PROTO_LIB OBJECT ${PROTO_SRCS} ${PROTO_HDRS})
include_directories("${PROJECT_BINARY_DIR}/output/include")

add_dependencies(PROTO_LIB protoc ${YAML_LIBRARIES} )

add_library(gsvr-static STATIC $<TARGET_OBJECTS:PROTO_LIB>
                               #$<TARGET_OBJECTS:SOURCES_LIB>
            )
#endif()

target_link_libraries(gsvr-static libprotoc)

if(UNIX)
target_link_libraries(${EXE_NAME} ${OPENSSL_LIBRARY} ${THREAD_LIBRARY} gsvr-static ${YAML_LIBRARIES}  m dl dw)
else()
target_link_libraries(${EXE_NAME} ${OPENSSL_LIBRARY} ${THREAD_LIBRARY})
endif()


#add_custom_command(
 #   TARGET ${EXE_NAME} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#    ${MOD_SOURCE_PATH}/${EXE_NAME}
#    ${MOD_OUTPUT_PATH}/${EXE_NAME}
#)
#set_target_properties(${EXE_NAME} PROPERTIES 
#	PREFIX ""
#	FOLDER "luamod"
#)