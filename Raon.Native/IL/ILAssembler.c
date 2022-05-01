#include "ILAssembler.h"

#include "BackEnd/BackEndDefines.h"
#include "Utility/Converter.h"

#include "AssignOp.h"
#include "BinOp.h"
#include "Bool.h"
#include "Compound.h"
#include "ExprStmt.h"
#include "Int.h"
#include "Real.h"
#include "Str.h"
#include "Stmt.h"
#include "Var.h"

#include "ILMacros.h"
#include "UnaryOp.h"
#include "Utility/Error.h"

typedef enum {
    PHASE_GENERATION,
    PHASE_SEARCH,
} EPhase;

FILAssembler *CreateILAssembler() {
    FILAssembler *assembler = malloc(sizeof(FILAssembler));
    assembler->context = CreateILContext();
    assembler->graph = CreateColorGraph();
    assembler->phase = PHASE_GENERATION;
    assembler->statements = NULL;

    return assembler;
}

void FreeILAssembler(FILAssembler *assembler) {
    if (assembler == NULL) {
        return;
    }

    FreeILContext(assembler->context);
    free(assembler);
}

typedef enum {
    RESULT_INTEGER,
    RESULT_REAL,
    RESULT_REGISTER,
} EILAssemblerVisitResultType;

typedef struct {
    bool success;
    FILBase *il;
} FILAssemblerVisitResult;

DEFINE_VISITER(FILAssemblerVisitResult, FILAssembler *)

FILBase *ILGenerate(FILAssembler *assembler, FBaseNode *node) {
    FILAssemblerVisitResult result = visit(assembler, node);
    if (result.success) {
        return result.il;
    }
    int error;
    while ((error = GetError()) != ERROR_NONE) {
        wprintf(U16("ERROR: %ls"), GetErrorString(error));
    }

    FreeIL(result.il);
    return NULL;
}

IMPL_VISITER(FILAssemblerVisitResult, FILAssembler *)

#define BEGIN FILAssemblerVisitResult __result = { true, NULL }
#define END return __result

#define FAILED __result.success = false
#define IS_FAILED __result.success == false

#define IL __result.il

#define STMT(NAME, NODE) FILAssemblerVisitResult NAME = visit(this, NODE); if (this->phase == PHASE_GENERATION && (!NAME.success || !(NAME.il == NULL || IsStmt(NAME.il)))) { FAILED; }
#define EXPR(NAME, NODE) FILAssemblerVisitResult NAME = visit(this, NODE); if (this->phase == PHASE_GENERATION && (!NAME.success || !(NAME.il != NULL && IsExpr(NAME.il)))) { FAILED; }

#define PUSH_STMT(NODE) { assert(IsStmt(NODE)); ARRAY_PUSH(this->statements, NODE); }

#define GENERATION_PHASE if (this->phase == PHASE_GENERATION) {
#define SEARCH_PHASE if (this->phase == PHASE_SEARCH) {
#define PHASE_END }

#define ENTER_SEARCH_PHASE this->phase = PHASE_SEARCH
#define ENTER_GENERATION_PHASE this->phase = PHASE_GENERATION

EOperation tokenToOp(FToken *str) {
    switch (str->type) {
    case TOKEN_PLUS:
        return OPERATION_ADD;
    case TOKEN_MINUS:
        return OPERATION_SUB;
    case TOKEN_ASTERISK:
        return OPERATION_MUL;
    case TOKEN_SLASH:
        return OPERATION_DIV;

#define CASE(EXPR) case TOKEN_##EXPR: return OPERATION_##EXPR

    CASE(LT);
    CASE(LTE);
    CASE(GT);
    CASE(GTE);
    CASE(EQ);
    CASE(NEQ);

    CASE(AND);
    CASE(OR);
#undef CASE
    }

    return OPERATION_UNKNOWN;
}


FILAssemblerVisitResult visitAssignOpNode(FILAssembler *this, FAssignOpNode *node) {
    BEGIN;

    EXPR(left, node->left)
    EXPR(right, node->right)

    GENERATION_PHASE
        IL = CreateAssignOp(left.il, right.il);
    PHASE_END

    SEARCH_PHASE
        AddEdgeToGraph(this->graph, (FBaseNode*) node, node->left);
        AddEdgeToGraph(this->graph, (FBaseNode*) node, node->right);
        AddEdgeToGraph(this->graph, node->left, node->right);
    PHASE_END

    END;
}

FILAssemblerVisitResult visitBinOpNode(FILAssembler *this, FBinOpNode *node) {
    BEGIN;

    EXPR(left, node->left)
    EXPR(right, node->right)

    GENERATION_PHASE
        EOperation op = tokenToOp(node->location->token);
        if (op == OPERATION_UNKNOWN) {
            FAILED;
        } else {
            IL = CreateBinOp(op, left.il, right.il);
            IL->operand = GetColorFromGraph(this->graph, node);
        }
    PHASE_END

    SEARCH_PHASE
        AddEdgeToGraph(this->graph, node->left, node->right);
        AddEdgeToGraph(this->graph, (FBaseNode*) node, node->left);
        AddEdgeToGraph(this->graph, (FBaseNode*) node, node->right);
    PHASE_END

    END;
}

FILAssemblerVisitResult visitCompoundNode(FILAssembler *this, FCompoundNode *node) {
    BEGIN;

    FStmt **temp = this->statements;
    this->statements = NULL;

    FBaseNode *it = NULL;
    ARRAY_FOREACH(node->children, it) {
        ClearColorGraph(this->graph);

        ENTER_SEARCH_PHASE;
        VISIT(it);

        GreedyGraph(this->graph);

        ENTER_GENERATION_PHASE;
        STMT(__ano, it);
    }

    IL = CreateCompound(this->statements);
    this->statements = temp;

    END;
}

FILAssemblerVisitResult visitBoolNode(FILAssembler *this, FBoolNode *node) {
    BEGIN;

    GENERATION_PHASE
        IL = CreateBool(node->value);
        IL->operand = GetColorFromGraph(this->graph, node);
    PHASE_END

    SEARCH_PHASE
    PHASE_END

    END;
}

FILAssemblerVisitResult visitIntegerNode(FILAssembler *this, FIntegerNode *node) {
    BEGIN;

    GENERATION_PHASE
        IL = CreateInt(node->value);
        IL->operand = GetColorFromGraph(this->graph, node);
    PHASE_END

    SEARCH_PHASE
    PHASE_END

    END;
}

FILAssemblerVisitResult visitRealNode(FILAssembler *this, FRealNode *node) {
    BEGIN;

    GENERATION_PHASE
        IL = CreateReal(node->value);
        IL->operand = GetColorFromGraph(this->graph, node);
    PHASE_END

    SEARCH_PHASE

    PHASE_END

    END;
}

FILAssemblerVisitResult visitStringNode(FILAssembler *this, FStringNode *node) {
    BEGIN;

    GENERATION_PHASE
        IL = CreateStr(node->value);
    PHASE_END

    SEARCH_PHASE

    PHASE_END

    END;
}

FILAssemblerVisitResult visitUnaryOpNode(FILAssembler *this, FUnaryOpNode *node) {
    BEGIN;

    EXPR(expr, node->expr);

    GENERATION_PHASE
        EOperation op = tokenToOp(node->location->token);
        if (op == OPERATION_UNKNOWN) {
            FAILED;
        } else {
            IL = CreateUnaryOp(op, expr.il);
        }
    PHASE_END

    SEARCH_PHASE
        AddEdgeToGraph(this->graph, (FBaseNode*) node, node->expr);
    PHASE_END

    END;
}

FILAssemblerVisitResult visitVarNode(FILAssembler *this, FVarNode *node) {
    BEGIN;

    GENERATION_PHASE
        size_t addr = -1;
        FSymbol *symbol = NULL;
        if (FindSymbol(this->local, node->location->token->str, &symbol) == ERROR_NONE) {
            addr = symbol->slot;

            IL = CreateVar(node->location->token->str, addr);
            IL->operand = GetColorFromGraph(this->graph, node);
        } else {
            Critical(ERROR_INVALID_IDENTIFIER, node->location->token->str);
        }
    PHASE_END

    SEARCH_PHASE

    PHASE_END

    END;
}

FILAssemblerVisitResult visitExprStmtNode(FILAssembler *this, FExprStmtNode *node) {
    BEGIN;

    EXPR(expr, node->expr);

    GENERATION_PHASE
        IL = CreateExprStmt(expr.il);
        PUSH_STMT(IL);
    PHASE_END

    SEARCH_PHASE

    PHASE_END

    END;
}

FILAssemblerVisitResult visitEmptyNode(FILAssembler *this, FEmptyNode *node) {
    BEGIN;

    END;
}
