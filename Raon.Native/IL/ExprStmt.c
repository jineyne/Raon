#include "ExprStmt.h"

FExprStmt *CreateExprStmt(FExpr *expr) {
    FExprStmt *stmt = (FExprStmt*) malloc(sizeof(FExprStmt));

    stmt->type = IL_EXPR_STATEMENT;
    stmt->operand = 0;
    stmt->expr = expr;

    return stmt;
}

void FreeExprStmt(FExprStmt *stmt) {
    FreeIL(stmt->expr);
    free(stmt);
}
