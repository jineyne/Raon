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
    HashMap *symbolsIndex; // name -> index

    uint32_t currentSlot;

    FSymbolTable *parent;
} FSymbolTable;

DLL_EXPORT FSymbolTable *CreateSymbolTable(u16 *name, FSymbolTable *parent);
DLL_EXPORT FSymbolTable *CopySymbolTable(u16 *name, FSymbolTable *original);
DLL_EXPORT void FreeSymbolTable(FSymbolTable *table);

DLL_EXPORT int InsertSymbol(FSymbolTable *table, FSymbol *symbol);
DLL_EXPORT int FindSymbol(FSymbolTable *table, FString *name, FSymbol **out);
DLL_EXPORT int FindSymbolDeep(FSymbolTable *table, FString *name, FSymbol **out);

DLL_EXPORT bool ApplyAndFreeSymbolTable(FSymbolTable *dst, FSymbolTable *src);

#ifdef __cplusplus
}
#endif

#endif // __SYMBOLTABLE_H__
