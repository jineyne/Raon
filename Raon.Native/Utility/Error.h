#ifndef __ERROR_H__
#define __ERROR_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u16 *notImplement;
    u16 *argumentNull;
    u16 *internalError;

    u16 *invalidToken;
    u16 *invalidSyntax;
    u16 *invalidEof;
    u16 *invalidIdentifier;

    u16 *symbolDuplicated;
    u16 *symbolNotFound;
    u16 *rvalueNotPositionAtLValue;

    u16 *allocFailed;

    u16 *stackOverflow;
    u16 *stackUnderflow;

    u16 *operandNotSupport;
    u16 *castingFailed;
} FErrorStringDesc;

enum {
    ERROR_NONE,

    ERROR_NOT_IMPLEMENT,
    ERROR_ARGUMENT_NULL,
    ERROR_INTERNAL_ERROR,

    ERROR_INVALID_TOKEN,
    ERROR_INVALID_SYNTAX,
    ERROR_INVALID_EOF,
    ERROR_INVALID_IDENTIFIER,

    ERROR_SYMBOL_DUPLICATED,
    ERROR_SYMBOL_NOT_FOUND,

    ERROR_RVALUE_NOT_POSITION_AT_LVALUE,

    ERROR_ALLOC_FAIL,
    ERROR_STACK_OVERFLOW,
    ERROR_STACK_UNDERFLOW,


    ERROR_OPERAND_NOT_SUPPORT,
    ERROR_CASTING_FAIL,

    ERROR_UNKNOWN,
};

DLL_EXPORT int GetErrorCount();
DLL_EXPORT int GetError();
DLL_EXPORT void ClearError();

DLL_EXPORT void CompileInfo(int type, u16 *file, size_t line, size_t pos, ...);
DLL_EXPORT void CompileWarning(int type, u16 *file, size_t line, size_t pos, ...);
DLL_EXPORT void CompileError(int type, u16 *file, size_t line, size_t pos, ...);

DLL_EXPORT void Info(int type, ...);
DLL_EXPORT void Warning(int type, ...);
DLL_EXPORT void Error(int type, ...);
DLL_EXPORT void Critical(int type, ...);

DLL_EXPORT u16 *GetErrorString(int type);

typedef void (*LoggerDelegate)(u16 *buffer);
DLL_EXPORT void AddLogger(LoggerDelegate fn);

#ifdef __cplusplus
}
#endif

#endif // __ERROR_H__
