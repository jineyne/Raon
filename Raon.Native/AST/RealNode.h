#ifndef __REALNODE_H__
#define __REALNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct RealNode {
    AST_REQUIRED

    double value;
} FRealNode;

DLL_EXPORT FRealNode *CreateRealNode(FToken *token, double value);
DLL_EXPORT void FreeRealNode(FRealNode*node);

#ifdef __cplusplus
}
#endif

#endif // __REALNODE_H__
