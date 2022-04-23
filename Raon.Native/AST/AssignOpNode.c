#include "AssignOpNode.h"

FAssignOpNode *CreateAssignOpNode(AST_REQUIRE_ARGS, FBaseNode *left, FBaseNode *right) {
    FAssignOpNode *node = malloc(sizeof(FAssignOpNode));
    INIT_BASE_NODE(node, AST_ASSIGNOP);

    node->left = left;
    node->right = right;

    return node;
}

void FreeAssignNode(FAssignOpNode *node) {
    FinitBaseNode(node);

    FreeNode(node->left);
    FreeNode(node->right);

    free(node);
}
