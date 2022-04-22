#ifndef __EXPRSTMTNODE_H__
#define __EXPRSTMTNODE_H__

#include "CoreMinimal.h"
#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    AST_REQUIRED

    FBaseNode *expr;
} FExprStmtNode;

DLL_EXPORT FExprStmtNode *CreateExprStmtNode(FExprStmtNode *node);
DLL_EXPORT void FreeExprStmtNode(FExprStmtNode *node);

#ifdef __cplusplus
}
#endif


#endif // __EXPRSTMTNODE_H__
