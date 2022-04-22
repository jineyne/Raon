#ifndef __STR_H__
#define __STR_H__

#include "CoreMinimal.h"
#include "Expr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DEFAULT_ILEXPR_MEMBERS

    FString *value;
} FStr;

DLL_EXPORT FStr *CreateStr(FString *value);
DLL_EXPORT void FreeStr(FStr *str);

#ifdef __cplusplus
}
#endif


#endif // __STR_H__
