#ifndef __COMPOUNDNODE_H__
#define __COMPOUNDNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CompoundNode {
    AST_REQUIRED
    FBaseNode **children;
} FCompoundNode;

DLL_EXPORT FCompoundNode *CreateCompoundNode(AST_REQUIRE_ARGS);
DLL_EXPORT void FreeCompoundNode(FCompoundNode *node);

DLL_EXPORT void AppendASTNode(FCompoundNode *node, FBaseNode *ast);

#ifdef __cplusplus
}
#endif

#endif // __COMPOUNDNODE_H__
