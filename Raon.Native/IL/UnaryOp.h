#ifndef __UNARYOP_H__
#define __UNARYOP_H__

#include "CoreMinimal.h"
#include "Expr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DEFAULT_ILEXPR_MEMBERS

    EOperation op;
    FExpr *expr;
} FUnaryOp;

DLL_EXPORT FUnaryOp *CreateUnaryOp(EOperation op, FExpr *expr);
DLL_EXPORT void FreeUnaryOp(FUnaryOp *unaryOp);

#ifdef __cplusplus
}
#endif


#endif // __UNARYOP_H__
