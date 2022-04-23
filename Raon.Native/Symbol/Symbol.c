#include "Symbol.h"

void FreeSymbol(FSymbol *symbol) {
    if (symbol == NULL) {
        return;
    }

    switch (symbol->symbolType) {
    case SYMBOL_TYPE:
        FreeTypeSymbol(symbol);
        break;

    case SYMBOL_VARIABLE:
        FreeVarSymbol(symbol);
        break;

    case SYMBOL_FUNCTION:
        break;

    default:
        break;
    }
}
