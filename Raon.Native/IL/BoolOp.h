#ifndef __BOOLOP_H__
#define __BOOLOP_H__

#include "CoreMinimal.h"
#include "Expr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DEFAULT_ILEXPR_MEMBERS

    EOperation op;
    FExpr *left;
    FExpr *right;
} FBoolOp;

DLL_EXPORT FBoolOp *CreateBoolOp(EOperation op, FExpr *left, FExpr *right);
DLL_EXPORT void FreeBoolOp(FBoolOp *boolOp);

#ifdef __cplusplus
}
#endif


#endif // __BOOLOP_H__
