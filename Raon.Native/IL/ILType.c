#include "ILType.h"

#define STRCMP(STR, TEXT) strncmp(STR->data, U16(TEXT), STR->length) == 0

EOperation StringToOp(FString *str) {
    if (STRCMP(str, "+")) {
        return OPERATION_ADD;
    } else if (STRCMP(str, "-")) {
        return OPERATION_SUB;
    } else if (STRCMP(str, "*")) {
        return OPERATION_MUL;
    } else if (STRCMP(str, "/")) {
        return OPERATION_DIV;
    }

    return OPERATION_UNKNOWN;
}
