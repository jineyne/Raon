#ifndef __INTEGERNODE_H__
#define __INTEGERNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct IntegerNode {
    AST_REQUIRED

    int64_t value;
} FIntegerNode;

DLL_EXPORT FIntegerNode *CreateIntegerNode(AST_REQUIRE_ARGS, int64_t value);
DLL_EXPORT void FreeIntegerNode(FIntegerNode *node);

#ifdef __cplusplus
}
#endif

#endif // __INTEGERNODE_H__
