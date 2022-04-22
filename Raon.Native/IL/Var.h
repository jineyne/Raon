#ifndef __VAR_H__
#define __VAR_H__

#include "CoreMinimal.h"
#include "Expr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DEFAULT_ILEXPR_MEMBERS

    FString *name;
    size_t addr;
} FVar;

DLL_EXPORT FVar *CreateVar(FString *name, size_t addr);
DLL_EXPORT void FreeVar(FVar *var);

#ifdef __cplusplus
}
#endif


#endif // __VAR_H__
