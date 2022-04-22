#ifndef __ILBASE_H__
#define __ILBASE_H__

#include "CoreMinimal.h"
#include "ILType.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEFAULT_IL_MEMBERS uint16_t type; int operand;

typedef struct {
    DEFAULT_IL_MEMBERS
} FILBase;

DLL_EXPORT bool IsStmt(FILBase *il);
DLL_EXPORT bool IsExpr(FILBase *il);

DLL_EXPORT void FreeIL(FILBase *il);

#ifdef __cplusplus
}
#endif


#endif // __ILBASE_H__
