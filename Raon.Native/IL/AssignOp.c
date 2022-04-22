#include "AssignOp.h"

FAssignOp *CreateAssignOp(FExpr *left, FExpr *right) {
    FAssignOp *assign = (FAssignOp*) malloc(sizeof(FAssignOp));

    assign->type = IL_ASSIGNOP;
    assign->operand = 0;
    assign->left = left;
    assign->right = right;

    return assign;
}

void FreeAssignOp(FAssignOp *assign) {
    FreeIL(assign->left);
    FreeIL(assign->right);
    free(assign);
}
