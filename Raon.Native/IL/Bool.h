#ifndef __BOOL_H__
#define __BOOL_H__

#include "CoreMinimal.h"
#include "Expr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DEFAULT_ILEXPR_MEMBERS

    bool value;
} FBool;

DLL_EXPORT FBool *CreateBool(bool value);
DLL_EXPORT void FreeBool(FBool *boolean);

#ifdef __cplusplus
}
#endif


#endif // __BOOL_H__
