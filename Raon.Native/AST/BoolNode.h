#ifndef __BOOLNODE_H__
#define __BOOLNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    AST_REQUIRED

    bool value;
} FBoolNode;

DLL_EXPORT FBoolNode *CreateBoolNode(AST_REQUIRE_ARGS, bool value);
DLL_EXPORT void FreeBoolNode(FBoolNode *node);

#ifdef __cplusplus
}
#endif

#endif // __BOOLNODE_H__
