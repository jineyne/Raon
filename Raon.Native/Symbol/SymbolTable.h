#ifndef __SYMBOLTABLE_H__
#define __SYMBOLTABLE_H__

#include "CoreMinimal.h"
#include "Symbol/Symbol.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SymbolTable FSymbolTable;

typedef struct SymbolTable {
    FString *name;
    uint32_t scope;

    FSymbol **symbols;
    HashMap *symbolsIndex;

    uint32_t currentSlot;

    FSymbolTable *parent;
} FSymbolTable;

DLL_EXPORT FSymbolTable *CreateSymbolTable(FString *name, FSymbolTable *parent);
DLL_EXPORT void FreeSymbolTable(FSymbolTable *table);

DLL_EXPORT bool InsertSymbol(FSymbolTable *table, FSymbol *symbol);
DLL_EXPORT FSymbol *FindSymbol(FSymbolTable *table, FString *name);
DLL_EXPORT FSymbol *FindSymbolDeep(FSymbolTable *table, FString *name);

#ifdef __cplusplus
}
#endif

#endif // __SYMBOLTABLE_H__