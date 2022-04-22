#ifndef __UNARYOPNODE_H__
#define __UNARYOPNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct UnaryOpNode {
    AST_REQUIRED

    FBaseNode* expr;
} FUnaryOpNode;

DLL_EXPORT FUnaryOpNode *CreateUnaryOpNode(FToken *token, FBaseNode *expr);
DLL_EXPORT void FreeUnaryOpNode(FUnaryOpNode *node);

#ifdef __cplusplus
}
#endif

#endif // __UNARYOPNODE_H__
