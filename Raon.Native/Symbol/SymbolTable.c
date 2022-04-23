#include "SymbolTable.h"

#include "Utility/Error.h"

FSymbolTable *CreateSymbolTable(u16 *name, FSymbolTable *parent) {
    FSymbolTable *table = malloc(sizeof(FSymbolTable));
    table->name = CreateString(name);
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

FSymbolTable *CopySymbolTable(u16 *name, FSymbolTable *original) {
    FSymbolTable *table = malloc(sizeof(FSymbolTable));
    table->name = CreateString(name);
    table->symbols = NULL;

    table->symbolsIndex = malloc(sizeof(HashMap));
    if (hashmap_create(pow(2, 10), table->symbolsIndex) != 0) {
        Critical(ERROR_ALLOC_FAIL);
    }

    FSymbol *it;
    ARRAY_FOREACH(original->symbols, it) {
        switch (it->symbolType) {
        case SYMBOL_TYPE:
            // SKIP
            break;

        case SYMBOL_VARIABLE:
            InsertSymbol(table, CreateVarSymbol(it->name, it->type));
            break;

        case SYMBOL_FUNCTION:
            // InsertSymbol(table, CreateFun(it->name, it->type));
            break;
        }
    }

    table->parent = original->parent;
    table->scope = original->scope;
    table->currentSlot = original->currentSlot;

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

int InsertSymbol(FSymbolTable *table, FSymbol *symbol) {
    if (symbol == NULL || table == NULL) {
        return ERROR_ARGUMENT_NULL;
    }

    if (hashmap_get(table->symbolsIndex, symbol->name->data, symbol->name->length * sizeof(u16)) != NULL) {
        return ERROR_SYMBOL_DUPLICATED;
    }

    symbol->slot = table->currentSlot++;

    void *p = (void*) ((ARRAY_SIZE(table->symbols)) + 1);
    hashmap_put(table->symbolsIndex, symbol->name->data, symbol->name->length * sizeof(u16), p);

    ARRAY_PUSH(table->symbols, symbol);

    return ERROR_NONE;
}

int FindSymbol(FSymbolTable *table, FString *name, FSymbol **out) {
    *out = NULL;
    if (name == NULL || table == NULL) {
        return ERROR_ARGUMENT_NULL;
    }

    void *p = hashmap_get(table->symbolsIndex, name->data, name->length * sizeof(u16));
    if (p == NULL) {
        return ERROR_SYMBOL_NOT_FOUND;
    }

    *out = table->symbols[(uint16_t) ((uint64_t) p - 1)];
    return ERROR_NONE;
}

int FindSymbolDeep(FSymbolTable *table, FString *name, FSymbol **out) {
    *out = NULL;
    if (name == NULL || table == NULL) {
        return ERROR_ARGUMENT_NULL;
    }

    FSymbol *symbol = NULL;
    FindSymbol(table, name, &symbol);
    while (symbol == NULL) {
        table = table->parent;
        if (table == NULL) {
            break;
        }

        FindSymbol(table, name, &symbol);
    }

    if (symbol == NULL) {
        return ERROR_SYMBOL_NOT_FOUND;
    }

    *out = symbol;
    return ERROR_NONE;
}

bool ApplyAndFreeSymbolTable(FSymbolTable *dst, FSymbolTable *src) {
    if (dst == NULL || src == NULL) {
        return false;
    }

    FSymbol *it;
    ARRAY_FOREACH(src->symbols, it) {
        FSymbol *found = NULL;
        FindSymbol(dst, it->name, &found);
        if (found == NULL) {
            InsertSymbol(dst, it);
        } else {
            void *p = hashmap_get(dst->symbolsIndex, it->name->data, it->name->length * sizeof(u16));
            if (p == NULL) {
                Critical(ERROR_INVALID_TOKEN, U16("SymbolTable"), it->lineNo, 0);
            }
            dst->symbols[((int64_t) p - 1)] = it;

            FreeSymbol(found);
        }
    }

    ARRAY_CLEAR(src->symbols);

    FreeString(src->name);
    hashmap_destroy(src->symbolsIndex);
    free(src->symbolsIndex);
    free(src);

    return true;
}
