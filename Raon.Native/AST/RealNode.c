#include "RealNode.h"

#include "IntegerNode.h"
#include "Utility/Math.h"

FRealNode* CreateRealNode(FToken* token, double value) {
    FRealNode* node = malloc(sizeof(FRealNode));
    node->type = AST_REAL;
    node->hash = HashDouble(value);

    node->token = token;
    node->value = value;

    return node;
}

void FreeRealNode(FRealNode* node) {
    FreeToken(node->token);
    free(node);
}