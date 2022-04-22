#ifndef __PARSER_H__
#define __PARSER_H__

#include "CoreMinimal.h"
#include "Lexer.h"
#include "AST/AST.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Parser {
    FLexer *lexer;
    FToken *token;
} FParser;

DLL_EXPORT FParser *CreateParser(FLexer *lexer);
DLL_EXPORT void FreeParser(FParser *parser);

DLL_EXPORT FBaseNode *Parse(FParser* parser);

#ifdef __cplusplus
}
#endif

#endif //__PARSER_H__