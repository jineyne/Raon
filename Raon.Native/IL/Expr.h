#ifndef __EXPR_H__
#define __EXPR_H__

#include "CoreMinimal.h"

#include "ILBase.h"
#include "ILType.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_ILEXPR_MEMBERS DEFAULT_IL_MEMBERS

typedef struct {
    DEFAULT_ILEXPR_MEMBERS
} FExpr;

DLL_EXPORT bool IsValue(FExpr *exp);
DLL_EXPORT bool IsAddress(FExpr *exp);

#ifdef __cplusplus
}
#endif


#endif // __EXPR_H__
