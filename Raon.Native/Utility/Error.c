#include "Error.h"

static int *gErrorList = ERROR_NONE;

int GetErrorCount() {
    return STACK_SIZE(gErrorList);
}

int GetError() {
    if (STACK_SIZE(gErrorList) <= 0) {
        return ERROR_NONE;
    }

    return STACK_POP(gErrorList);
}

void ClearError() {
    STACK_CLEAR(gErrorList);
}

void PushError(int type) {
    STACK_PUSH(gErrorList, type);
}

void Critical(int type) {
    wprintf(U16("CRITICAL ERROR!: %s"), GetErrorString(type));
    exit(type);
}

#define CASE(t) case t : return U16(#t);

u16 *GetErrorString(int type) {
    switch (type) {
    CASE(ERROR_NONE);

    CASE(ERROR_NOT_IMPLEMENT);
    CASE(ERROR_ARGUMENT_NULL);
    CASE(ERROR_INTERNAL_ERROR);

    CASE(ERROR_INVALID_TOKEN);
    CASE(ERROR_INVALID_SYNTAX);
    CASE(ERROR_INVALID_EOF);
    CASE(ERROR_INVALID_OP_CODE);
    CASE(ERROR_INVALID_IDENTIFIER);

    CASE(ERROR_ALLOC_FAIL);
    CASE(ERROR_STACK_OVERFLOW);
    CASE(ERROR_STACK_UNDERFLOW);

    CASE(ERROR_UNKNOWN);

    default:
        return U16("");
    }
}
