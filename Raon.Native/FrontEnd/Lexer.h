#ifndef __LEXER_H__
#define __LEXER_H__

#include "CoreMinimal.h"
#include "Token.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Lexer {
    FString *source;

    size_t line;
    size_t pos;

    size_t cursor;

    u16 currentChar;
} FLexer;

DLL_EXPORT FLexer *CreateLexer(const u16 *source);
DLL_EXPORT void FreeLexer(FLexer *lexer);

DLL_EXPORT FToken *GetNextToken(FLexer *lexer);
DLL_EXPORT FToken *GetIdentifier(FLexer *lexer);
DLL_EXPORT FToken *GetSymbol(FLexer *lexer);

#ifdef __cplusplus
}
#endif

#endif //__LEXER_H__
