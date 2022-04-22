#include "CompoundNode.h"

FCompoundNode *CreateCompoundNode() {
    FCompoundNode *node = malloc(sizeof(FCompoundNode));
    node->type = AST_COMPOUND;
    node->hash = 0;

    node->token = CreateToken(TOKEN_UNKNOWN, U16('\0'));
    node->children = NULL;
}

void FreeCompoundNode(FCompoundNode *node) {
    FBaseNode *it;
    ARRAY_FOREACH(node->children, it) {
        FreeNode(it);
    }

    FreeToken(node->token);
    free(node);
}

void AppendASTNode(FCompoundNode *node, FBaseNode *ast) {
    ARRAY_PUSH(node->children, ast);
}
