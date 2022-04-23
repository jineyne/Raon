#ifndef __STRING_H__
#define __STRING_H__

#include "Prerequisites/PrerequisitesUtil.h"
#include "String/UTF16.h"

#define EmptyString '\0'

#ifdef __cplusplus
extern "C" {
#endif

typedef struct String {
    u16 *data;
    size_t length;
} FString;

DLL_EXPORT FString *CreateString(const u16 *str);
DLL_EXPORT FString *CopyString(const FString *str);
DLL_EXPORT FString *CreateStringWithLength(const u16 *str, size_t len);
DLL_EXPORT void FreeString(FString *string);

DLL_EXPORT size_t HashString(FString *string);

#ifdef __cplusplus
}
#endif

#endif // __STRING_H__
