#include "IntegerNode.h"

FIntegerNode *CreateIntegerNode(AST_REQUIRE_ARGS, int64_t value) {
    FIntegerNode *node = malloc(sizeof(FIntegerNode));
    INIT_BASE_NODE(node, AST_INTEGER);
    node->value = value;

    return node;
}

void FreeIntegerNode(FIntegerNode *node) {
    FinitBaseNode(node);
    free(node);
}
