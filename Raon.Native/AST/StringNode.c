#include "StringNode.h"

FStringNode *CreateStringNode(FToken *token, FString *value) {
    FStringNode *node = malloc(sizeof(FStringNode));
    node->type = AST_STRING;
    node->hash = HashString(value);

    node->token = token;
    node->value = value;

    return node;
}

void FreeStringNode(FStringNode *node) {
    FreeString(node->value);

    free(node);
}
