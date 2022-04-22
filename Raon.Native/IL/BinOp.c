#include "BinOp.h"

FBinOp *CreateBinOp(EOperation op, FExpr *left, FExpr *right) {
    FBinOp *binOp = (FBinOp*) malloc(sizeof(FBinOp));

    binOp->type = IL_BINOP;
    binOp->operand = 0;
    binOp->op = op;
    binOp->left = left;
    binOp->right = right;

    return binOp;
}

void FreeBinOp(FBinOp *binOp) {
    FreeIL(binOp->left);
    FreeIL(binOp->right);
    free(binOp);
}
