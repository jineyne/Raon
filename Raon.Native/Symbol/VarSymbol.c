#include "VarSymbol.h"

FVarSymbol *CreateVarSymbol(FString *name, FSymbol *type) {
    FVarSymbol *symbol = malloc(sizeof(FVarSymbol));
    symbol->name = CreateString(name->data);
    symbol->symbolType = SYMBOL_VARIABLE;
    symbol->type = type;
    if (type != NULL) {
        symbol->size = type->size;
    } else {
        symbol->size = 0;
    }

    symbol->lineNo = -1;
    symbol->slot = -1;

    return symbol;
}

void FreeVarSymbol(FVarSymbol *symbol) {
    FreeString(symbol->name);
    free(symbol);
}