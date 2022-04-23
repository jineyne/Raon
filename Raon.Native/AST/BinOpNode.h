#ifndef __BINOPNODE_H__
#define __BINOPNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BinOpNode {
    AST_REQUIRED

    FBaseNode *left;
    FBaseNode *right;
} FBinOpNode;

DLL_EXPORT FBinOpNode *CreateBinOpNode(AST_REQUIRE_ARGS, FBaseNode *left, FBaseNode *right);
DLL_EXPORT void FreeBinOpNode(FBinOpNode *node);

#ifdef __cplusplus
}
#endif

#endif // __BINOPNODE_H__
