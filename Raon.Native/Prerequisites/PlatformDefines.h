#ifndef __PLATFORMDEFINES_H__
#define __PLATFORMDEFINES_H__

#define PLATFORM_WIN32 1
#define PLATFORM_LINUX 2

#define COMPILER_MSVC 1
#define COMPILER_GNUC 2
#define COMPILER_CLANG 3

#if defined(_MSC_VER)
#   define COMPILER COMPILER_MSVC
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#elif defined(__GNUC__)
#   define COMPILER COMPILER_GNUC
#elif defined(__clang__)
#   define COMPILER COMPILER_CLANG
#else
#   pragma error "not supported compiler"
#endif

#if defined( __WIN32__  ) || defined( _WIN32  )
#   define PLATFORM PLATFORM_WIN32
#else
#   define PLATFORM PLATFORM_LINUX
#endif


#if PLATFORM == PLATFORM_WIN32
#   if COMPILER == COMPILER_MSVC
#       if defined(STATIC_LIB)
#           define DLL_EXPORT
#       else
#           if defined(EXPORTS)
#               define DLL_EXPORT __declspec(dllexport)
#           else
#               define DLL_EXPORT __declspec(dllimport)
#           endif
#       endif
#   else
#       if defined(STATIC_LIB)
#           define DLL_EXPORT
#       else
#           if defined(EXPORTS)
#               define DLL_EXPORT __attribute__ ((dllexport))
#           else
#               define DLL_EXPORT __attribute__ ((dllimport))
#           endif
#       endif
#   endif
#else
#   define DLL_EXPORT __attribute__ ((visibility("default")))
#endif

#if PLATFORM == PLATFORM_WIN32 // Windows
#   if COMPILER == COMPILER_MSVC
#       define PLUGIN_EXPORT __declspec(dllexport)
#   else
#       define PLUGIN_EXPORT __attribute__ ((dllexport))
#   endif
#else // Linux/Mac settings
#   define PLUGIN_EXPORT __attribute__((visibility("default")))
#endif

#endif // __PLATFORMDEFINES_H__
