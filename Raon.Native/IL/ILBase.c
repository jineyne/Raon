#include "ILBase.h"

#include "AssignOp.h"
#include "BinOp.h"
#include "Bool.h"
#include "Compound.h"
#include "ExprStmt.h"
#include "ILType.h"
#include "Int.h"
#include "Real.h"
#include "Str.h"
#include "Var.h"

bool IsStmt(FILBase *il) {
    // EMPTY OP
    if (il == NULL) {
        return true;
    }

    if (IL_STATEMENT <= il->type && il->type < IL_STATEMENT_END) {
        return true;
    }

    return false;
}

bool IsExpr(FILBase *il) {
    if (IL_EXPRESSION <= il->type && il->type < IL_EXPRESSION_END) {
        return true;
    }

    return false;
}

bool IsConstant(FILBase *il) {
    if (il == NULL) {
        return true;
    }

    if (IL_BOOL <= il->type && il->type < IL_STRING) {
        return true;
    }

    return false;
}

void FreeIL(FILBase *il) {
    if (il == NULL) {
        return;
    }

    switch (il->type) {
    case IL_ASSIGNOP:
        FreeAssignOp(il);
        break;

    case IL_BINOP:
        FreeBinOp(il);
        break;

    case IL_VAR:
        FreeVar(il);
        break;

    case IL_BOOL:
        FreeBool(il);
        break;

    case IL_INTEGER:
        FreeInt(il);
        break;

    case IL_REAL:
        FreeReal(il);
        break;

    case IL_STRING:
        FreeStr(il);
        break;

    case IL_COMPOUND:
        FreeCompound(il);
        break;

    case IL_EXPR_STATEMENT:
        FreeExprStmt(il);
        break;

    default: ;
    }
}
