#include "Compiler.h"

#include "AST/AST.h"
#include "Utility/Converter.h"
#include "Utility/Error.h"

enum {
    PHASE_LVALUE,
    PHASE_RVALUE,
};

FCompiler *CreateCompiler() {
    FCompiler *compiler = malloc(sizeof(FCompiler));

    compiler->index = 0;

    return compiler;
}

void FreeCompiler(FCompiler *compiler) {
    if (compiler == NULL) {
        return;
    }

    free(compiler);
}

typedef struct CompilerVisitResult {
    bool success;
    EOperand type;
    int64_t result;
} FCompilerVisitResult;

#define FREE_RESULT(NAME) ARRAY_FREE(NAME.codes)


#define BEGIN FCompilerVisitResult __result = { true, 0, NULL }

#define FAILED __result.success = false

#define LITERAL __result.type = L
#define MEMORY __result.type = M
#define REFERENCE __result.type = R

#define END return __result;

#define CODES this->object->codes
#define TYPE __result.type
#define RESULT __result.result

#define LPHASE this->phase = PHASE_LVALUE
#define RPHASE this->phase = PHASE_RVALUE

#define VISIT_ANON(NODE) { FCompilerVisitResult ___result = VISIT(NODE); if (!___result.success) FAILED; }
#define VISIT_GRAP(NAME, NODE) FCompilerVisitResult NAME = VISIT(NODE); if (!NAME.success) FAILED
#define VISIT_GRAP_ND(NAME, NODE) NAME = VISIT(NODE); if (!NAME.success) FAILED
#define VISIT_THROW(NODE) { __result = VISIT(NODE); if (!__result.success) FAILED; }

#define PRINT(EXP) DEBUG_ONLY(wprintf(EXP))

#define MAKE_OPCODE(OP, O1, O2, O3, O4) (OPERAND(O1, O2, O3, O4) << 16 | OP)

DEFINE_ILVISITER(FCompilerVisitResult, FCompiler *);

#define PRINT_OP(OP, VALUE) DEBUG_ONLY(printOp(OP, VALUE))
#define PRINT_RESULT(RESULT) DEBUG_ONLY(printOp(RESULT.type, RESULT.result))
#define PRINT_COMMA() PRINT(U16(", "));
#define PRINT_LN() PRINT(U16("\n"));

void printOp(EOperand op, int64_t value) {
    switch (op) {
    case B:
        (bool) value ? wprintf(U16("true")) : wprintf(U16("false"));
        break;

    case L:
        wprintf(U16("%lld"), value);
        break;

    case C:
        wprintf(U16("c%lld"), value);
        break;

    case R:
        wprintf(U16("r%lld"), value);
        break;

    case M:
        wprintf(U16("&%lld"), value);
        break;

    default:
        wprintf(U16("%lld"), value);
        break;
    }
}

FCompilerObject *CompileIL(FCompiler *this, FILBase *node) {
    this->object = CreateCompilerObject();
    FCompilerVisitResult result = visit(this, node);
    ARRAY_PUSH(CODES, MAKE_OPCODE(OP_HALT, 0, 0, 0, 0));

    return this->object;
}

IMPL_ILVISITER(FCompilerVisitResult, FCompiler *);

FCompilerVisitResult visitAssignOp(FCompiler *this, FAssignOp *il) {
    BEGIN;

    RPHASE;
    VISIT_GRAP(right, il->right);

    LPHASE;
    VISIT_GRAP(left, il->left);

    PRINT(U16("MOVE "));
    PRINT_RESULT(left);
    PRINT_COMMA();
    PRINT_RESULT(right);
    PRINT_LN();

    ARRAY_PUSH(CODES, MAKE_OPCODE(OP_MOVE, left.type, right.type, 0, 0));
    ARRAY_PUSH(CODES, left.result);
    ARRAY_PUSH(CODES, right.result);

    TYPE = left.type;
    RESULT = left.result;

    END;
}

FCompilerVisitResult visitBinOp(FCompiler *this, FBinOp *il) {
    BEGIN;

    FCompilerVisitResult left = {false, 0, NULL};
    FCompilerVisitResult right = {false, 0, NULL};

    bool bLeftIsConstant = IsConstant(il->left);
    bool bRightIsConstant = IsConstant(il->right);

    if (bLeftIsConstant && !bRightIsConstant) {
        RPHASE;
        VISIT_GRAP_ND(right, il->right);

        LPHASE;
        VISIT_GRAP_ND(left, il->left);
    } else if (bRightIsConstant && !bLeftIsConstant) {
        LPHASE;
        VISIT_GRAP_ND(left, il->left);

        RPHASE;
        VISIT_GRAP_ND(right, il->right);
    } else {
        RPHASE;
        VISIT_GRAP_ND(right, il->right);

        LPHASE;
        VISIT_GRAP_ND(left, il->left);
    }

#define CASE(EXPR) case OPERATION_##EXPR: opcode = OP_##EXPR; PRINT(U16(#EXPR) U16(" ")); break
    int opcode = 0;
    switch (il->op) {
    CASE(ADD);
    CASE(SUB);
    CASE(MUL);
    CASE(DIV);
    CASE(AND);
    CASE(OR);
    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        break;
    }
#undef CASE

    ARRAY_PUSH(CODES, MAKE_OPCODE(opcode, R, left.type, right.type, 0));
    ARRAY_PUSH(CODES, il->operand);
    ARRAY_PUSH(CODES, left.result);
    ARRAY_PUSH(CODES, right.result);

    PRINT_OP(R, il->operand);
    PRINT_COMMA();
    PRINT_RESULT(left);
    PRINT_COMMA();
    PRINT_RESULT(right);
    PRINT_LN();

    TYPE = R;
    RESULT = il->operand;

    END;
}

FCompilerVisitResult visitBoolOp(FCompiler *this, FBoolOp *il) {
    BEGIN;

    FCompilerVisitResult left = {false, 0, NULL};
    FCompilerVisitResult right = {false, 0, NULL};

    bool bLeftIsConstant = IsConstant(il->left);
    bool bRightIsConstant = IsConstant(il->right);

    if (bLeftIsConstant && !bRightIsConstant) {
        RPHASE;
        VISIT_GRAP_ND(right, il->right);

        LPHASE;
        VISIT_GRAP_ND(left, il->left);
    } else if (bRightIsConstant && !bLeftIsConstant) {
        LPHASE;
        VISIT_GRAP_ND(left, il->left);

        RPHASE;
        VISIT_GRAP_ND(right, il->right);
    } else {
        RPHASE;
        VISIT_GRAP_ND(right, il->right);

        LPHASE;
        VISIT_GRAP_ND(left, il->left);
    }


#define CASE(EXPR) case OPERATION_##EXPR: opcode = OP_##EXPR; PRINT(U16(#EXPR) U16(" ")); break
    int opcode = 0;
    switch (il->op) {
    CASE(ADD);
    CASE(SUB);
    CASE(MUL);
    CASE(DIV);
    CASE(AND);
    CASE(OR);
    default:
        Critical(ERROR_OPERAND_NOT_SUPPORT);
        break;
    }
#undef CASE

    ARRAY_PUSH(CODES, MAKE_OPCODE(OP_CMP, left.type, right.type, 0, 0));
    ARRAY_PUSH(CODES, left.result);
    ARRAY_PUSH(CODES, right.result);

    PRINT_OP(R, il->operand);
    PRINT_COMMA();
    PRINT_RESULT(left);
    PRINT_COMMA();
    PRINT_RESULT(right);
    PRINT_LN();

    TYPE = R;
    RESULT = REG_ZF;

    END;
}

FCompilerVisitResult visitUnaryOp(FCompiler *this, FUnaryOp *il) {
    BEGIN;

    FCompilerVisitResult expr = {false, 0, NULL};

    RPHASE;
    VISIT_GRAP_ND(expr, il->expr);

    if (il->op == OPERATION_SUB) {
        ARRAY_PUSH(CODES, MAKE_OPCODE(OP_SUB, R, L, expr.type, 0));
        ARRAY_PUSH(CODES, il->operand);
        ARRAY_PUSH(CODES, 0);
        ARRAY_PUSH(CODES, expr.result);

        PRINT(U16("SUB "));
        PRINT_OP(R, il->operand);
        PRINT_COMMA();
        PRINT(U16("0"));
        PRINT_COMMA();
        PRINT_RESULT(expr);
        PRINT_LN();
    }

    TYPE = R;
    RESULT = il->operand;

    END;
}

FCompilerVisitResult visitVar(FCompiler *this, FVar *il) {
    BEGIN;

    if (this->phase == PHASE_RVALUE) {
        ARRAY_PUSH(CODES, MAKE_OPCODE(OP_MOVE, R, M, 0, 0));
        ARRAY_PUSH(CODES, il->operand);
        ARRAY_PUSH(CODES, il->addr);

        PRINT(U16("MOVE "));
        PRINT_OP(R, il->operand);
        PRINT_COMMA()
        PRINT_OP(M, il->addr);
        PRINT_LN();

        TYPE = R;
        RESULT = il->operand;
    } else {
        TYPE = M;
        RESULT = il->addr;
    }

    END;
}

FCompilerVisitResult visitBool(FCompiler *this, FBool *il) {
    BEGIN;

    TYPE = B;
    RESULT = il->value;

    END;
}

FCompilerVisitResult visitInt(FCompiler *this, FInt *il) {
    BEGIN;

    TYPE = L;
    RESULT = il->value;

    END;
}

FCompilerVisitResult visitReal(FCompiler *this, FReal *il) {
    BEGIN;

    ARRAY_PUSH(CODES, MAKE_OPCODE(OP_MOVE, R, C, 0, 0));
    int64_t addr = AppendDoubleConstant(this->object, il->value);
    ARRAY_PUSH(CODES, il->operand);
    ARRAY_PUSH(CODES, addr);

    PRINT(U16("MOVE "));
    PRINT_OP(R, il->operand);
    PRINT_COMMA()
    PRINT_OP(C, addr);
    PRINT_LN();

    TYPE = R;
    RESULT = il->operand;

    END;
}

FCompilerVisitResult visitStr(FCompiler *this, FStr *il) {
    BEGIN;

    ARRAY_PUSH(CODES, MAKE_OPCODE(OP_MOVE, R, C, 0, 0));
    uint64_t addr = AppendStringConstant(this->object, il->value);
    ARRAY_PUSH(CODES, addr);

    PRINT(U16("MOVE "));
    PRINT_OP(R, il->operand);
    PRINT_COMMA()
    PRINT_OP(C, addr);
    PRINT_LN();

    TYPE = R;
    RESULT = il->operand;

    END;
}

FCompilerVisitResult visitCompound(FCompiler *this, FCompound *il) {
    BEGIN;

    FILBase *it;
    ARRAY_FOREACH(il->statements, it) {
        VISIT_ANON(it);
    }

    END;
}

FCompilerVisitResult visitExprStmt(FCompiler *this, FExprStmt *il) {
    BEGIN;

    VISIT_THROW(il->expr);

    END;
}

FCompilerVisitResult visitIf(FCompiler *this, FIf *il) {
    BEGIN;

    // size_t beginOffset = ARRAY_SIZE(CODES);

    END;
}
