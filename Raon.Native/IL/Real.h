#ifndef __REAL_H__
#define __REAL_H__

#include "CoreMinimal.h"
#include "Expr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DEFAULT_ILEXPR_MEMBERS

    double value;
} FReal;

DLL_EXPORT FReal *CreateReal(double value);
DLL_EXPORT void FreeReal(FReal *integer);

#ifdef __cplusplus
}
#endif


#endif // __REAL_H__
