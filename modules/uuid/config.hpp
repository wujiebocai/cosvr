#pragma once

/// Denotes version of svr in the format {MAJOR}{MINOR}{PATCH},
/// whereas each number is a two-digit decimal number without
/// leading zeros (e.g. 900 is version 0.9.0).
#define SVR_VERSION 1905

/// Defined to the major version number of SVR.
#define SVR_MAJOR_VERSION (SVR_VERSION / 10000)

/// Defined to the minor version number of SVR.
#define SVR_MINOR_VERSION ((SVR_VERSION / 100) % 100)

/// Defined to the patch version number of SVR.
#define SVR_PATCH_VERSION (SVR_VERSION % 100)

// This compiler-specific block defines:
// - SVR_PUSH_WARNINGS/SVR_POP_WARNINGS to surround "noisy" header includes
// - SVR_COMPILER_VERSION to retrieve the compiler version in SVR_VERSION format
// - One of the following:
//   + SVR_CLANG
//   + SVR_GCC
//   + SVR_MSVC

// sets SVR_PUSH_WARNINGS and SVR_POP_WARNINGS
// clang-format off
#if defined(__clang__)
#  define SVR_CLANG
#  define SVR_PUSH_WARNINGS                                                    \
    _Pragma("clang diagnostic push")                                           \
    _Pragma("clang diagnostic ignored \"-Wall\"")                              \
    _Pragma("clang diagnostic ignored \"-Wextra\"")                            \
    _Pragma("clang diagnostic ignored \"-Wundef\"")                            \
    _Pragma("clang diagnostic ignored \"-Wshadow\"")                           \
    _Pragma("clang diagnostic ignored \"-Wdeprecated\"")                       \
    _Pragma("clang diagnostic ignored \"-Wextra-semi\"")                       \
    _Pragma("clang diagnostic ignored \"-Wconversion\"")                       \
    _Pragma("clang diagnostic ignored \"-Wcast-align\"")                       \
    _Pragma("clang diagnostic ignored \"-Wfloat-equal\"")                      \
    _Pragma("clang diagnostic ignored \"-Wswitch-enum\"")                      \
    _Pragma("clang diagnostic ignored \"-Wweak-vtables\"")                     \
    _Pragma("clang diagnostic ignored \"-Wdocumentation\"")                    \
    _Pragma("clang diagnostic ignored \"-Wold-style-cast\"")                   \
    _Pragma("clang diagnostic ignored \"-Wsign-conversion\"")                  \
    _Pragma("clang diagnostic ignored \"-Wunused-template\"")                  \
    _Pragma("clang diagnostic ignored \"-Wshorten-64-to-32\"")                 \
    _Pragma("clang diagnostic ignored \"-Wunreachable-code\"")                 \
    _Pragma("clang diagnostic ignored \"-Wdouble-promotion\"")                 \
    _Pragma("clang diagnostic ignored \"-Wc++14-extensions\"")                 \
    _Pragma("clang diagnostic ignored \"-Wunused-parameter\"")                 \
    _Pragma("clang diagnostic ignored \"-Wnested-anon-types\"")                \
    _Pragma("clang diagnostic ignored \"-Wreserved-id-macro\"")                \
    _Pragma("clang diagnostic ignored \"-Wconstant-conversion\"")              \
    _Pragma("clang diagnostic ignored \"-Wimplicit-fallthrough\"")             \
    _Pragma("clang diagnostic ignored \"-Wused-but-marked-unused\"")           \
    _Pragma("clang diagnostic ignored \"-Wdisabled-macro-expansion\"")
#  define SVR_PUSH_UNUSED_LABEL_WARNING                                        \
    _Pragma("clang diagnostic push")                                           \
    _Pragma("clang diagnostic ignored \"-Wunused-label\"")
#  define SVR_PUSH_DEPRECATED_WARNING                                          \
    _Pragma("clang diagnostic push")                                           \
    _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#  define SVR_POP_WARNINGS                                                     \
    _Pragma("clang diagnostic pop")
#  define SVR_COMPILER_VERSION                                                 \
    (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(__GNUC__)
#  define SVR_GCC
#  define SVR_PUSH_WARNINGS                                                    \
    _Pragma("GCC diagnostic push")                                             \
    _Pragma("GCC diagnostic ignored \"-Wshadow\"")                             \
    _Pragma("GCC diagnostic ignored \"-Wpragmas\"")                            \
    _Pragma("GCC diagnostic ignored \"-Wpedantic\"")                           \
    _Pragma("GCC diagnostic ignored \"-Wcast-qual\"")                          \
    _Pragma("GCC diagnostic ignored \"-Wconversion\"")                         \
    _Pragma("GCC diagnostic ignored \"-Wfloat-equal\"")                        \
    _Pragma("GCC diagnostic ignored \"-Wc++14-extensions\"")
#  define SVR_PUSH_UNUSED_LABEL_WARNING                                        \
    _Pragma("GCC diagnostic push")                                             \
    _Pragma("GCC diagnostic ignored \"-Wunused-label\"")
#  define SVR_PUSH_DEPRECATED_WARNING                                          \
    _Pragma("GCC diagnostic push")                                             \
    _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#  define SVR_POP_WARNINGS                                                     \
    _Pragma("GCC diagnostic pop")
#  define SVR_COMPILER_VERSION                                                 \
     (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
    // disable thread_local on GCC/macOS due to heap-use-after-free bug:
    // https://gcc.gnu.org/bugzilla/show_bug.cgi?id=67135
#elif defined(_MSC_VER)
#  define SVR_MSVC
#  define SVR_PUSH_WARNINGS                                                    \
    __pragma(warning(push))
#  define SVR_PUSH_UNUSED_LABEL_WARNING                                        \
    __pragma(warning(push))                                                    \
    __pragma(warning(disable: 4102))
#  define SVR_PUSH_DEPRECATED_WARNING                                          \
    __pragma(warning(push))
#  define SVR_POP_WARNINGS __pragma(warning(pop))
#  define SVR_COMPILER_VERSION _MSC_FULL_VER
#  pragma warning( disable : 4624 )
#  pragma warning( disable : 4800 )
#  pragma warning( disable : 4503 )
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif // NOMINMAX
#else
#  define SVR_PUSH_DEPRECATED_WARNING
#  define SVR_POP_WARNINGS
#endif
// clang-format on

// This OS-specific block defines one of the following:
// - SVR_MACOS
// - SVR_LINUX
// - SVR_BSD
// - SVR_WINDOWS
// It also defines SVR_POSIX for POSIX-compatible systems
#if defined(__APPLE__)
#  include "TargetConditionals.h"
#  if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#    define SVR_IOS
#  else
#    define SVR_MACOS
#    if defined(SVR_GCC) && !defined(_GLIBCXX_HAS_GTHREADS)
#      define _GLIBCXX_HAS_GTHREADS
#    endif
#  endif
#elif defined(__ANDROID__)
#  define SVR_ANDROID
#elif defined(__linux__)
#  define SVR_LINUX
#  include <linux/version.h>
#  if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 16)
#    define SVR_POLL_IMPL
#  endif
#elif defined(__FreeBSD__)
#  define SVR_BSD
#  define SVR_FREE_BSD
#elif defined(__NetBSD__)
#  define SVR_BSD
#  define SVR_NET_BSD
#elif defined(__OpenBSD__)
#  define SVR_BSD
#  define SVR_OPEN_BSD
#elif defined(__CYGWIN__)
#  define SVR_CYGWIN
#elif defined(WIN32) || defined(_WIN32)
#  define SVR_WINDOWS
#else
#  error Platform and/or compiler not supported
#endif
#if defined(SVR_MACOS) || defined(SVR_LINUX) || defined(SVR_BSD)               \
  || defined(SVR_CYGWIN) || defined(SVR_NET_BSD)
#  define SVR_POSIX
#endif
