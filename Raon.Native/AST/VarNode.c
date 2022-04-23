#include "VarNode.h"

FVarNode *CreateVarNode(AST_REQUIRE_ARGS) {
    FVarNode *node = malloc(sizeof(FVarNode));
    INIT_BASE_NODE(node, AST_VAR);

    return node;
}

void FreeVarNode(FVarNode *node) {
    FinitBaseNode(node);
    free(node);
}
