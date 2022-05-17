#ifndef __IF_H__
#define __IF_H__

#include "CoreMinimal.h"
#include "Expr.h"
#include "ILBase.h"
#include "ILType.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DEFAULT_IL_MEMBERS

    FExpr *cond;
    FExpr *stmt;
    FExpr *elseExpr;
} FIf;

DLL_EXPORT FIf *CreateIf(FExpr *cond, FExpr *stmt, FExpr *elseExpr);
DLL_EXPORT void FreeIf(FIf *_if);

#ifdef __cplusplus
}
#endif


#endif // __IF_H__
