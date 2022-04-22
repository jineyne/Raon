#ifndef __VARSYMBOL_H__
#define __VARSYMBOL_H__

#include "CoreMinimal.h"
#include "Symbol/Symbol.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VarSymbol {
    SYMBOL_BASE_DECLARE
} FVarSymbol;

DLL_EXPORT FVarSymbol *CreateVarSymbol(FString *name, FSymbol *type);
DLL_EXPORT void FreeVarSymbol(FVarSymbol *symbol);

#ifdef __cplusplus
}
#endif

#endif // __VARSYMBOL_H__