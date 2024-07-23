# build type
if(NOT CMAKE_BUILD_TYPE)
	#set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# cxx flag
set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -Wall -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -g")

# binary path
set(RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/__GEN/linux)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/__GEN/linux)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
set(GENERATE_PATH ${RUNTIME_OUTPUT_DIRECTORY})
set(BIN_PATH ${PROJECT_SOURCE_DIR}/bin/linux)
set(BIN_SUFFIX "")
set(DLL_SUFFIX ".so")

# def
add_definitions(-DASIO_HAS_EPOLL)
# option
set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)

# openssl
# find_package(OpenSSL REQUIRED)
# set(OPENSSL_LIBRARY ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY})
set(OPENSSL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/dep/openssl")
set(OPENSSL_LIBRARY 
    "${PROJECT_SOURCE_DIR}/dep/lib/ubuntu/libssl.a"
    "${PROJECT_SOURCE_DIR}/dep/lib/ubuntu/libcrypto.a")

# zlib
# find_package(ZLIB REQUIRED)
#set(ZLIB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/dep/zlib/${LIBPROTOBUF_PLATFORM}/include")
#set(ZLIB_LIBRARIES "${PROJECT_SOURCE_DIR}/dep/zlib/${LIBPROTOBUF_PLATFORM}/lib/libz.so")

# thread
set(THREAD_LIBRARY pthread)

# filesystem
set(FILE_SYSTEM_LIBRARY stdc++fs)
