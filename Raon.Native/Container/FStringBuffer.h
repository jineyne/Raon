#ifndef __STRING_BUFFER_H__
#define __STRING_BUFFER_H__

#include "CoreMinimal.h"
#include "String/UTF16.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StringBuffer {
    uint32_t size;
    uint32_t length;
    u16 *data;
} FStringBuffer;

DLL_EXPORT FStringBuffer *CreateStringBuffer();
DLL_EXPORT void FreeStringBuffer(FStringBuffer *sb);

DLL_EXPORT void AppendString(FStringBuffer *sb, FString *str);
DLL_EXPORT void AppendCString(FStringBuffer *sb, u16 *str);
DLL_EXPORT void AppendChar(FStringBuffer *sb, u16 ch);
DLL_EXPORT FString *StringBufferToString(FStringBuffer *sb);

#ifdef __cplusplus
}
#endif

#endif // __STRING_BUFFER_H__
