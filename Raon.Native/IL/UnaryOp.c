#include "UnaryOp.h"

FUnaryOp *CreateUnaryOp(EOperation op, FExpr *expr) {
    FUnaryOp *unaryOp = malloc(sizeof(FUnaryOp));

    unaryOp->type = IL_UNARYOP;
    unaryOp->operand = 0;
    unaryOp->op = op;
    unaryOp->expr = expr;

    return unaryOp;
}

void FreeUnaryOp(FUnaryOp *unaryOp) {
    FreeIL(unaryOp->expr);
    free(unaryOp);
}
