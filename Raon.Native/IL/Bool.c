#include "Bool.h"

FBool *CreateBool(bool value) {
    FBool *boolean = malloc(sizeof(FBool));

    boolean->type = IL_BOOL;
    boolean->operand = 0;
    boolean->value = value;

    return boolean;
}

void FreeBool(FBool *boolean) {
    free(boolean);
}
