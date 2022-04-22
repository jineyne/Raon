#include "Str.h"

FStr *CreateStr(FString *value) {
    FStr *str = (FStr*) malloc(sizeof(FStr));

    str->type = IL_STRING;
    str->operand = 0;
    str->value = CreateString(value->data);

    return str;
}

void FreeStr(FStr *str) {
    FreeString(str->value);
    free(str);
}
