#ifndef __VARNODE_H__
#define __VARNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct VarNode {
    AST_REQUIRED
} FVarNode;

DLL_EXPORT FVarNode *CreateVarNode(AST_REQUIRE_ARGS);
DLL_EXPORT void FreeVarNode(FVarNode *node);

#ifdef __cplusplus
}
#endif

#endif // __VARNODE_H__
