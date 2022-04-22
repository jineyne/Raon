#ifndef __INT_H__
#define __INT_H__

#include "CoreMinimal.h"
#include "Expr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DEFAULT_ILEXPR_MEMBERS

    int64_t value;
} FInt;

DLL_EXPORT FInt *CreateInt(int64_t value);
DLL_EXPORT void FreeInt(FInt *integer);

#ifdef __cplusplus
}
#endif


#endif // __INT_H__
