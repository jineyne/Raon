#ifndef __ASSIGNOP_H__
#define __ASSIGNOP_H__

#include "CoreMinimal.h"
#include "Stmt.h"
#include "Expr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DEFAULT_ILSTMT_MEMBERS
    FExpr *left;
    FExpr *right;
} FAssignOp;

DLL_EXPORT FAssignOp *CreateAssignOp(FExpr *left, FExpr *right);
DLL_EXPORT void FreeAssignOp(FAssignOp *assign);

#ifdef __cplusplus
}
#endif


#endif // __ASSIGNOP_H__
