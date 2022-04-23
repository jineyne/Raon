#include "ExprStmtNode.h"

FExprStmtNode *CreateExprStmtNode(AST_REQUIRE_ARGS, FBaseNode *expr) {
    FExprStmtNode *node = malloc(sizeof(FExprStmtNode));
    INIT_BASE_NODE(node, AST_EXPRSTMT);

    node->expr = expr;

    return node;
}

void FreeExprStmtNode(FExprStmtNode *node) {
    FinitBaseNode(node);

    FreeNode(node->expr);
    free(node);
}
