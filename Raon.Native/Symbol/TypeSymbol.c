#include "TypeSymbol.h"

FTypeSymbol *CreateTypeSymbol(FString *name, size_t size) {
    FTypeSymbol *symbol = malloc(sizeof(FTypeSymbol));
    symbol->name = CreateString(name->data);
    symbol->symbolType = SYMBOL_TYPE;
    symbol->type = NULL;
    symbol->size = size;

    symbol->lineNo = -1;
    symbol->slot = -1;

    return symbol;
}

void FreeTypeSymbol(FTypeSymbol *symbol) {
    FreeString(symbol->name);
    free(symbol);
}