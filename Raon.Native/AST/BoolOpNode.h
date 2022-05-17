#ifndef __BOOLOPNODE_H__
#define __BOOLOPNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    AST_REQUIRED

    FBaseNode *left;
    FBaseNode *right;
} FBoolOpNode;

DLL_EXPORT FBoolOpNode *CreateBoolOpNode(AST_REQUIRE_ARGS, FBaseNode *left, FBaseNode *right);
DLL_EXPORT void FreeBoolOpNode(FBoolOpNode *node);

#ifdef __cplusplus
}
#endif

#endif // __BOOLOPNODE_H__
