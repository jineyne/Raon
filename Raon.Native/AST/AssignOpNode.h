#ifndef __ASSIGNNODE_H__
#define __ASSIGNNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    AST_REQUIRED

    FBaseNode *left;
    FBaseNode *right;
} FAssignOpNode;

DLL_EXPORT FAssignOpNode *CreateAssignOpNode(AST_REQUIRE_ARGS, FBaseNode *left, FBaseNode *right);
DLL_EXPORT void FreeAssignNode(FAssignOpNode *node);

#ifdef __cplusplus
}
#endif

#endif // __ASSIGNNODE_H__
