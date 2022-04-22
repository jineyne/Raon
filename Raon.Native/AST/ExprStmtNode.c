#include "ExprStmtNode.h"

FExprStmtNode *CreateExprStmtNode(FBaseNode *expr) {
    FExprStmtNode *node = (FExprStmtNode *)malloc(sizeof(FExprStmtNode));

    node->type = AST_EXPRSTMT;
    node->hash = CombineHash(expr->hash, expr->hash);
    node->token = expr->token;
    node->expr = expr;

    return node;
}

void FreeExprStmtNode(FExprStmtNode *node) {
    FreeNode(node->expr);
    free(node);
}
