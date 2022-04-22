#include "Compound.h"

FCompound *CreateCompound(FStmt **statements) {
    FCompound *compound = malloc(sizeof(FCompound));

    compound->type = IL_COMPOUND;
    compound->operand = 0;

    compound->statements = statements;

    return compound;
}

void FreeCompound(FCompound *statements) {
    FILBase *it;
    ARRAY_FOREACH(statements->statements, it) {
        FreeIL(it);
    }
    free(statements);
}
