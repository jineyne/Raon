#include "Expr.h"

bool IsValue(FExpr *exp) {
    if (IL_INTEGER <= exp->type && exp->type <= IL_STRING) {
        return true;
    }

    return false;
}

bool IsAddress(FExpr *exp) {}
