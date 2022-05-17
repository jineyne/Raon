#ifndef __IFNODE_H__
#define __IFNODE_H__

#include "BaseNode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    AST_REQUIRED

    FBaseNode *cond;
    FBaseNode *stmt;
    FBaseNode *elseExpr;
} FIfNode;

DLL_EXPORT FIfNode *CreateIfNode(AST_REQUIRE_ARGS, FBaseNode *cond, FBaseNode *stmt, FBaseNode *elseExpr);
DLL_EXPORT void FreeIfNode(FIfNode *node);

#ifdef __cplusplus
}
#endif

#endif // __IFNODE_H__
