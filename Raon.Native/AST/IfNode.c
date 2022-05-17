#include "IfNode.h"

FIfNode *CreateIfNode(FString *source, FToken *token, FBaseNode *cond, FBaseNode *stmt, FBaseNode *elseExpr) {
    FIfNode *node = malloc(sizeof(FIfNode));

    INIT_BASE_NODE(node, AST_IF);
    node->cond = cond;
    node->stmt = stmt;
    node->elseExpr = elseExpr;

    return node;
}

void FreeIfNode(FIfNode *node) {
    FinitBaseNode(node);

    FreeNode(node->cond);
    FreeNode(node->elseExpr);
    free(node);
}
