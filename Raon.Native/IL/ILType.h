#ifndef __ILTYPE_H__
#define __ILTYPE_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    IL_UNKNOWN,

    IL_EXPRESSION = 0x100,

    IL_ASSIGNOP,
    IL_BINOP,

    IL_VAR,

    IL_INTEGER,
    IL_REAL,
    IL_STRING,

    IL_EXPRESSION_END,
    IL_EXPRESSION_COUNT = IL_EXPRESSION_END - IL_EXPRESSION,

    IL_STATEMENT = 0x200,

    IL_COMPOUND,
    IL_EXPR_STATEMENT,

    IL_STATEMENT_END,
    IL_STATEMENT_COUNT = IL_STATEMENT_END - IL_STATEMENT,
} EILType;

typedef enum {
    OPERATION_ADD,
    OPERATION_SUB,
    OPERATION_MUL,
    OPERATION_DIV,

    OPERATION_UNKNOWN,
} EOperation;

#ifdef __cplusplus
}
#endif


#endif // __ILTYPE_H__
