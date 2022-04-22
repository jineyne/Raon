#include "BinOpNode.h"

#include "Container/FStringBuffer.h"

FBinOpNode* CreateBinOpNode(FToken* token, FBaseNode* left, FBaseNode* right) {
    FBinOpNode* node = malloc(sizeof(FBinOpNode));
    node->type = AST_BINOP;
    node->hash = CombineHash(HashString(left->token->str), HashString(right->token->str));

    FStringBuffer *sb = CreateStringBuffer();
    AppendString(sb, left->token->str);
    AppendChar(sb, token->op);
    AppendString(sb, right->token->str);

    node->token = CreateTokenFromString(StringBufferToString(sb));
    node->op = token;
    node->left = left;
    node->right = right;

    FreeStringBuffer(sb);

    return node;
}

void FreeBinOpNode(FBinOpNode* node) {
    FreeNode(node->right);
    FreeNode(node->left);

    FreeToken(node->token);
    FreeToken(node->op);
    free(node);
}