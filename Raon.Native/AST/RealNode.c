#include "RealNode.h"

#include "IntegerNode.h"
#include "Utility/Math.h"

FRealNode *CreateRealNode(AST_REQUIRE_ARGS, double value) {
    FRealNode *node = malloc(sizeof(FRealNode));
    INIT_BASE_NODE(node, AST_REAL);
    node->value = value;

    return node;
}

void FreeRealNode(FRealNode *node) {
    FinitBaseNode(node);
    free(node);
}
