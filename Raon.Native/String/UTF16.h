#ifndef __UTF16_H__
#define __UTF16_H__

#include "Prerequisites/PrerequisitesUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

#define U16(str) u##str
typedef char16_t u16;

DLL_EXPORT size_t u16len(const u16* str);
DLL_EXPORT int u16cmp(const u16* str1, const u16* str2);
DLL_EXPORT void* u16cat(u16* dst, const u16* src);
DLL_EXPORT void* u16ncat(u16* dst, const u16* src, size_t num);
DLL_EXPORT void* u16cpy(u16* dst, const u16* src);
DLL_EXPORT void* u16ncpy(u16* dst, const u16* src, size_t num);
DLL_EXPORT int u16charsize(const u16* peek);
DLL_EXPORT int u16isspace(const u16 ch);
DLL_EXPORT int u16isalpha(const u16 ch);
DLL_EXPORT int u16isdigit(const u16 ch);
DLL_EXPORT int u16isalnum(const u16 ch);
DLL_EXPORT int u16isspecial(const u16 ch);
DLL_EXPORT int u16atoi(const u16* ch);

#ifdef __cplusplus
}
#endif

#endif //__UTF16_H__
