#ifndef __BINOP_H__
#define __BINOP_H__

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
} FBinOp;

DLL_EXPORT FBinOp *CreateBinOp(EOperation op, FExpr *left, FExpr *right);
DLL_EXPORT void FreeBinOp(FBinOp *binOp);

#ifdef __cplusplus
}
#endif


#endif // __BINOP_H__
