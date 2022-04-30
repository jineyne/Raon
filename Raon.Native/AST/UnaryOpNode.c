#include "UnaryOpNode.h"

FUnaryOpNode *CreateUnaryOpNode(AST_REQUIRE_ARGS, FBaseNode *expr) {
    FUnaryOpNode *node = malloc(sizeof(FUnaryOpNode));
    INIT_BASE_NODE(node, AST_UNARYOP);

    node->hash = CombineHash(HashString(token->str), expr->hash);
    node->expr = expr;

    return node;
}

void FreeUnaryOpNode(FUnaryOpNode *node) {
    FinitBaseNode(node);

    FreeNode(node->expr);
    free(node);
}
