#include "BinOpNode.h"

#include "Container/FStringBuffer.h"

FBinOpNode *CreateBinOpNode(AST_REQUIRE_ARGS, FBaseNode *left, FBaseNode *right) {
    FBinOpNode *node = malloc(sizeof(FBinOpNode));
    INIT_BASE_NODE(node, AST_BINOP);

    size_t lhash = HashString(left->location->token->str);
    size_t rhash = HashString(right->location->token->str);
    node->hash = CombineHash(lhash, rhash);

    node->left = left;
    node->right = right;

    return node;
}

void FreeBinOpNode(FBinOpNode *node) {
    FinitBaseNode(node);

    FreeNode(node->right);
    FreeNode(node->left);
    free(node);
}
