#ifndef __ERROR_H__
#define __ERROR_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    ERROR_NONE,

    ERROR_NOT_IMPLEMENT,
    ERROR_ARGUMENT_NULL,
    ERROR_INTERNAL_ERROR,

    ERROR_INVALID_TOKEN,
    ERROR_INVALID_SYNTAX,
    ERROR_INVALID_EOF,
    ERROR_INVALID_OP_CODE,
    ERROR_INVALID_IDENTIFIER,

    ERROR_SYMBOL_DUPLICATED,
    ERROR_SYMBOL_NOT_FOUND,

    ERROR_RVALUE_NOT_POSITION_AT_LVALUE,

    ERROR_ALLOC_FAIL,
    ERROR_STACK_OVERFLOW,
    ERROR_STACK_UNDERFLOW,

    ERROR_UNKNOWN,
};

DLL_EXPORT int GetErrorCount();
DLL_EXPORT int GetError();
DLL_EXPORT void ClearError();
DLL_EXPORT void PushError(int type);
DLL_EXPORT void Critical(int type);
DLL_EXPORT u16 *GetErrorString(int type);

#ifdef __cplusplus
}
#endif

#endif // __ERROR_H__
