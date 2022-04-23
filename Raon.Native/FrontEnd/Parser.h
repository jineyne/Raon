#ifndef __PARSER_H__
#define __PARSER_H__

#include "CoreMinimal.h"
#include "Lexer.h"
#include "AST/AST.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Parser {
    FString *source;
    FLexer *lexer;
    FToken *token;
} FParser;

DLL_EXPORT FParser *CreateParserFromMemory(u16 *source);

// TODO:
// DLL_EXPORT FParser *CreateParserFromFile(u16 *source);
DLL_EXPORT void FreeParser(FParser *parser);

DLL_EXPORT FBaseNode *Parse(FParser *parser);

#ifdef __cplusplus
}
#endif

#endif //__PARSER_H__
