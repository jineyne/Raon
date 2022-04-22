#include "AssignOpNode.h"

FAssignOpNode *CreateAssignOpNode(FToken *token, FBaseNode *left, FBaseNode *right) {
    FAssignOpNode *node = malloc(sizeof(FAssignOpNode));
    node->type = AST_ASSIGNOP;
    node->hash = CombineHash(HashString(left->token->str), HashString(right->token->str));
    node->token = token;

    node->left = left;
    node->right = right;

    return node;
}

void FreeAssignNode(FAssignOpNode *node) {
    FreeNode(node->left);
    FreeNode(node->right);

    FreeToken(node->token);
    free(node);
}
