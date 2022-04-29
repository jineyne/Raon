#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "CoreMinimal.h"
#include "TokenType.h"
#include "TokenValue.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Token {
    ETokenType type;

    FString *str;

    UTokenValue value;

    size_t line;
    size_t pos;
} FToken;

DLL_EXPORT FToken *CreateToken(ETokenType type, size_t line, size_t pos, u16 *str);
DLL_EXPORT FToken *CreateTokenWithString(ETokenType type, size_t line, size_t pos, u16 *cstr);
DLL_EXPORT FToken *CreateTokenFromInteger(size_t line, size_t pos, FString *str, int64_t value);
DLL_EXPORT FToken *CreateTokenFromReal(size_t line, size_t pos, FString *str, double value);
DLL_EXPORT FToken *CreateTokenFromString(size_t line, size_t pos, FString *string);

DLL_EXPORT void FreeToken(FToken *token);

DLL_EXPORT ETokenType GetTokenType(FToken *token);

DLL_EXPORT int64_t GetTokenValueAsInteger(FToken *token);
DLL_EXPORT double GetTokenValueAsReal(FToken *token);
DLL_EXPORT u16 *GetTokenValueAsCString(FToken *token);

#ifdef __cplusplus
}
#endif

#endif //__TOKEN_H__
