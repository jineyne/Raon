#ifndef __ILCONTEXT_H__
#define __ILCONTEXT_H__

#include "CoreMinimal.h"

#include "AST/AST.h"
#include "Symbol/SymbolTable.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    FSymbolTable *globalSymTab;
    FSymbolTable *localSymTab;
} FILContext;

DLL_EXPORT FILContext *CreateILContext();
DLL_EXPORT void FreeILContext(FILContext *context);

#ifdef __cplusplus
}
#endif

#endif // __ILCONTEXT_H__
