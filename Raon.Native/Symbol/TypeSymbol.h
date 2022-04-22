#ifndef __TYPESYMBOL_H__
#define __TYPESYMBOL_H__

#include "CoreMinimal.h"
#include "Symbol/Symbol.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TypeSymbol {
    SYMBOL_BASE_DECLARE
} FTypeSymbol;

DLL_EXPORT FTypeSymbol *CreateTypeSymbol(FString *name, size_t size);
DLL_EXPORT void FreeTypeSymbol(FTypeSymbol *symbol);

#ifdef __cplusplus
}
#endif

#endif // __TYPESYMBOL_H__