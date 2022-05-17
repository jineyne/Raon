#include "BoolOpNode.h"

#include "Container/FStringBuffer.h"

FBoolOpNode *CreateBoolOpNode(AST_REQUIRE_ARGS, FBaseNode *left, FBaseNode *right) {
    FBoolOpNode *node = malloc(sizeof(FBoolOpNode));
    INIT_BASE_NODE(node, AST_BOOLOP);

    size_t lhash = HashString(left->location->token->str);
    size_t rhash = HashString(right->location->token->str);
    node->hash = CombineHash(lhash, rhash);

    node->left = left;
    node->right = right;

    return node;
}

void FreeBoolOpNode(FBoolOpNode *node) {
    FinitBaseNode(node);

    FreeNode(node->right);
    FreeNode(node->left);
    free(node);
}
