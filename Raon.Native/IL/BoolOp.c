#include "BoolOp.h"

FBoolOp *CreateBoolOp(EOperation op, FExpr *left, FExpr *right) {
    FBoolOp *boolOp = malloc(sizeof(FBoolOp));

    boolOp->type = IL_BOOLOP;
    boolOp->operand = 0;
    boolOp->op = op;
    boolOp->left = left;
    boolOp->right = right;

    return boolOp;
}

void FreeBoolOp(FBoolOp *boolOp) {
    FreeIL(boolOp->left);
    FreeIL(boolOp->right);
    free(boolOp);
}
