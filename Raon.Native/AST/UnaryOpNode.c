#include "UnaryOpNode.h"

FUnaryOpNode* CreateUnaryOpNode(FToken* token, FBaseNode* expr) {
    FUnaryOpNode* node = malloc(sizeof(FUnaryOpNode));
    node->type = AST_UNARYOP;
    node->type = CombineHash(HashString(token->str), expr->hash);

    node->token = token;
    node->expr = expr;

    return node;
}

void FreeUnaryOpNode(FUnaryOpNode* node) {
    FreeNode(node->expr);

    free(node);
}