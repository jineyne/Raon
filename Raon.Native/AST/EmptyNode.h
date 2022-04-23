#ifndef __EMPTYNODE_H__
#define __EMPTYNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EmptyNode {
    AST_REQUIRED
} FEmptyNode;

DLL_EXPORT FEmptyNode *CreateEmptyNode(AST_REQUIRE_ARGS);
DLL_EXPORT void FreeEmptyNode(FEmptyNode *node);

#ifdef __cplusplus
}
#endif

#endif // __EMPTYNODE_H__
