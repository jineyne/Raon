#include "Int.h"

FInt *CreateInt(int64_t value) {
    FInt *integer = (FInt *) malloc(sizeof(FInt));

    integer->type = IL_INTEGER;
    integer->operand = 0;
    integer->value = value;

    return integer;
}

void FreeInt(FInt *integer) {
    free(integer);
}
