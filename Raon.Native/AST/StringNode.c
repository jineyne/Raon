#include "StringNode.h"

FStringNode *CreateStringNode(AST_REQUIRE_ARGS, FString *value) {
    FStringNode *node = malloc(sizeof(FStringNode));
    INIT_BASE_NODE(node, AST_STRING);
    node->value = value;

    return node;
}

void FreeStringNode(FStringNode *node) {
    FreeString(node->value);

    free(node);
}
