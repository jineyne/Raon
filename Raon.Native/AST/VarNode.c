#include "VarNode.h"

FVarNode* CreateVarNode(FToken* token) {
    FVarNode* node = malloc(sizeof(FVarNode));
    node->type = AST_VAR;
    node->hash = HashString(token->str);

    node->token = token;

    return node;
}

void FreeVarNode(FVarNode* node) {
    FreeToken(node->token);
    free(node);
}