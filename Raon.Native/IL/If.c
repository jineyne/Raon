#include "If.h"

FIf *CreateIf(FExpr *cond, FExpr *stmt, FExpr *elseExpr) {
    FIf *_if = malloc(sizeof(FIf));

    _if->type = IL_IF;
    _if->operand = 0;

    _if->cond = cond;
    _if->stmt = stmt;
    _if->elseExpr = elseExpr;

    return _if;
}

void FreeIf(FIf *_if) {
    FreeIL(_if->elseExpr);
    FreeIL(_if->stmt);
    FreeIL(_if->cond);
    free(_if);
}
