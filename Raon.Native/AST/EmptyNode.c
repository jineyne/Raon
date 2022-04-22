#include "EmptyNode.h"

FEmptyNode* CreateEmptyNode() {
    FEmptyNode* node = malloc(sizeof(FEmptyNode));
    node->type = AST_EMPTY;
    node->hash = 0;

    node->token = CreateToken(TOKEN_UNKNOWN, U16('\0'));

    return node;
}

void FreeEmptyNode(FEmptyNode* node) {
    FreeToken(node->token);
    free(node);
}