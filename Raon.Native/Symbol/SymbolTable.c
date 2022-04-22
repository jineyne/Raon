#include "SymbolTable.h"

#include "Utility/Error.h"

FSymbolTable *CreateSymbolTable(FString *name, FSymbolTable *parent) {
    FSymbolTable *table = malloc(sizeof(FSymbolTable));
    table->name = name;
    table->symbols = NULL;
    table->symbolsIndex = malloc(sizeof(HashMap));

    if (hashmap_create(pow(2, 10), table->symbolsIndex) != 0) {
        Critical(ERROR_ALLOC_FAIL);
    }

    table->parent = parent;
    if (parent == NULL) {
        table->scope = 0;
        table->currentSlot = 0;
    } else {
        table->scope = parent->scope + 1;
        table->currentSlot = parent->currentSlot + 1;
    }

    return table;
}

void FreeSymbolTable(FSymbolTable *table) {
    if (table == NULL) {
        return;
    }

    FSymbol *it;
    ARRAY_FOREACH(table->symbols, it) {
        FreeSymbol(it);
    }
    ARRAY_CLEAR(table->symbols);

    FreeString(table->name);
    hashmap_destroy(table->symbolsIndex);
    free(table->symbolsIndex);
    free(table);
}

bool InsertSymbol(FSymbolTable *table, FSymbol *symbol) {
    if (symbol == NULL || table == NULL) {
        PushError(ERROR_ARGUMENT_NULL);
        return false;
    }

    if (hashmap_get(table->symbolsIndex, symbol->name->data, symbol->name->length) != NULL) {
        PushError(ERROR_SYMBOL_DUPLICATED);
        return false;
    }

    symbol->slot = table->currentSlot++;

    void *p = (void*)((uint64_t)ARRAY_SIZE(table->symbols) + 1);
    hashmap_put(table->symbolsIndex, symbol->name->data, symbol->name->length, p);

    ARRAY_PUSH(table->symbols, symbol);

    return true;
}

FSymbol *FindSymbol(FSymbolTable *table, FString *name) {
    if (name == NULL || table == NULL) {
        PushError(ERROR_ARGUMENT_NULL);
        return NULL;
    }

    void *p = hashmap_get(table->symbolsIndex, name->data, name->length);
    if (p == NULL) {
        return NULL;
    }

    return table->symbols[(uint16_t)((uint64_t)p - 1)];
}

FSymbol *FindSymbolDeep(FSymbolTable *table, FString *name) {
    if (name == NULL || table == NULL) {
        PushError(ERROR_ARGUMENT_NULL);
        return NULL;
    }

    FSymbol *symbol = FindSymbol(table, name);
    while (symbol == NULL) {
        table = table->parent;
        if (table == NULL) {
            break;
        }

        symbol = FindSymbol(table, name);
    }

    return symbol;
}
