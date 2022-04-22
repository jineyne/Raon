#ifndef __PREREQUISITES_UTIL_H__
#define __PREREQUISITES_UTIL_H__

#include <assert.h>

#include "PlatformDefines.h"

#if defined(DEBUG) || defined(_DEBUG)
#   define DEBUG_MODE 1
#else
#   define DEBUG_MODE 0
#endif

#if DEBUG_MODE
#   define DEBUG_ONLY(exp) exp
#   define ASSERT(exp) exp
#else
#   define DEBUG_ONLY(exp)
#   define ASSERT(exp)
#endif

#include "StdHeaders.h"

#if PLATFORM == PLATFORM_APPLE
#ifndef __cplusplus
typedef uint16_t char16_t;
typedef uint32_t char32_t;
#endif
#else
#   include <uchar.h>
#endif

#pragma warning( disable : 4133 )

#endif // __PREREQUISITES_UTIL_H__