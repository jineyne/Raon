#include "IntegerNode.h"

FIntegerNode *CreateIntegerNode(FToken *token, int64_t value) {
    FIntegerNode *node = malloc(sizeof(FIntegerNode));
    node->type = AST_INTEGER;
    node->hash = value;

    node->token = token;
    node->value = value;

    return node;
}

void FreeIntegerNode(FIntegerNode *node) {
    FreeToken(node->token);
    free(node);
}
