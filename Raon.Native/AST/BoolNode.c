#include "BoolNode.h"

FBoolNode *CreateBoolNode(FString *source, FToken *token, bool value) {
    FBoolNode *node = malloc(sizeof(FBoolNode));
    INIT_BASE_NODE(node, AST_BOOL);
    node->value = value;

    return node;
}

void FreeBoolNode(FBoolNode *node) {
    free(node);
}
