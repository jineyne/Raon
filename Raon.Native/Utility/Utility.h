#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "Prerequisites/PrerequisitesUtil.h"

#define EmptyString '\0'

#ifdef __cplusplus
extern "C" {
#endif

DLL_EXPORT size_t CombineHash(size_t hash, size_t hash2);

DLL_EXPORT void InitRaon();

#ifdef __cplusplus
}
#endif

#endif // __UTILITY_H__
