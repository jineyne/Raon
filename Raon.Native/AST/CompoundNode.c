#include "CompoundNode.h"

FCompoundNode *CreateCompoundNode(AST_REQUIRE_ARGS) {
    FCompoundNode *node = malloc(sizeof(FCompoundNode));
    INIT_BASE_NODE(node, AST_COMPOUND);

    node->children = NULL;
}

void FreeCompoundNode(FCompoundNode *node) {
    FinitBaseNode(node);

    FBaseNode *it;
    ARRAY_FOREACH(node->children, it) {
        FreeNode(it);
    }

    free(node);
}

void AppendASTNode(FCompoundNode *node, FBaseNode *ast) {
    ARRAY_PUSH(node->children, ast);
}
