#ifndef __STRINGNODE_H__
#define __STRINGNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StringNode {
    AST_REQUIRED

    FString *value;
} FStringNode;

DLL_EXPORT FStringNode *CreateStringNode(FToken *token, FString *value);
DLL_EXPORT void FreeStringNode(FStringNode *node);

#ifdef __cplusplus
}
#endif

#endif // __STRINGNODE_H__
