#ifndef __EXPRSTMT_H__
#define __EXPRSTMT_H__

#include "CoreMinimal.h"
#include "Expr.h"
#include "ILBase.h"
#include "ILType.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_ILEXPR_MEMBERS DEFAULT_IL_MEMBERS

typedef struct {
    DEFAULT_ILEXPR_MEMBERS

    FExpr *expr;
} FExprStmt;

DLL_EXPORT FExprStmt *CreateExprStmt(FExpr *expr);
DLL_EXPORT void FreeExprStmt(FExprStmt *stmt);

#ifdef __cplusplus
}
#endif


#endif // __EXPRSTMT_H__
