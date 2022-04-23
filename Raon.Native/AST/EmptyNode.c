#include "EmptyNode.h"

FEmptyNode *CreateEmptyNode(AST_REQUIRE_ARGS) {
    FEmptyNode *node = malloc(sizeof(FEmptyNode));
    INIT_BASE_NODE(node, AST_EMPTY);

    return node;
}

void FreeEmptyNode(FEmptyNode *node) {
    FinitBaseNode(node);
    free(node);
}
