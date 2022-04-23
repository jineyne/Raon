#ifndef __SYNTAXANALYZER_H__
#define __SYNTAXANALYZER_H__

#include "CoreMinimal.h"
#include "AST/AST.h"
#include "Symbol/SymbolTable.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SyntaxAnalyzer {
    FSymbolTable *symtab;
    unsigned char limit;
    bool freeSymTab;
} FSyntaxAnalyzer;

DLL_EXPORT FSyntaxAnalyzer *CreateSyntaxAnalyzer(FSymbolTable *table);
DLL_EXPORT void FreeSyntaxAnalyzer(FSyntaxAnalyzer *analyzer);

DLL_EXPORT bool RunSyntaxAnalyzer(FSyntaxAnalyzer *analyzer, FBaseNode *node);
DLL_EXPORT bool ClearSyntaxAnalyzer(FSyntaxAnalyzer *analyzer);

#ifdef __cplusplus
}
#endif

#endif //__SYNTAXANALYZER_H__
