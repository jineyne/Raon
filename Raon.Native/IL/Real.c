#include "Real.h"

FReal *CreateReal(double value) {
    FReal *real = (FReal*) malloc(sizeof(FReal));

    real->type = IL_REAL;
    real->operand = 0;
    real->value = value;

    return real;
}

void FreeReal(FReal *integer) {
    free(integer);
}
