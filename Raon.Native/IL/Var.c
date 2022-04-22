#include "Var.h"

FVar *CreateVar(FString *name, size_t addr) {
    FVar *var = (FVar*) malloc(sizeof(FVar));

    var->type = IL_VAR;
    var->operand = 0;

    var->name = CreateStringWithLength(name->data, name->length);
    var->addr = addr;

    return var;
}

void FreeVar(FVar *var) {
    FreeString(var->name);
    free(var);
}
