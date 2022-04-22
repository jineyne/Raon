#ifndef __BASESYMBOL_H__
#define __BASESYMBOL_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Symbol FSymbol;

typedef enum SymbolType {
    SYMBOL_VARIABLE,
    SYMBOL_TYPE,
    SYMBOL_FUNCTION,
} ESymbolType;

#define SYMBOL_BASE_DECLARE FString *name; ESymbolType symbolType; uint32_t slot; size_t size; FSymbol *type; uint32_t lineNo;

struct Symbol {
    SYMBOL_BASE_DECLARE
};

#ifdef __cplusplus
}
#endif

#endif // __BASESYMBOL_H__
