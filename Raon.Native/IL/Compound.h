#ifndef __COMPOUND_H__
#define __COMPOUND_H__

#include "CoreMinimal.h"
#include "Stmt.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    DEFAULT_ILSTMT_MEMBERS

    FStmt **statements;
} FCompound;

DLL_EXPORT FCompound *CreateCompound(FStmt **statements);
DLL_EXPORT void FreeCompound(FCompound *binOp);

#ifdef __cplusplus
}
#endif


#endif // __COMPOUND_H__
