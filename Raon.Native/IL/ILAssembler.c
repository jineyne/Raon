#include "ILAssembler.h"

#include "BackEnd/BackEndDefines.h"
#include "Utility/Converter.h"

#include "AssignOp.h"
#include "BinOp.h"
#include "Compound.h"
#include "ExprStmt.h"
#include "Int.h"
#include "Real.h"
#include "Str.h"
#include "Stmt.h"
#include "Var.h"

#include "ILMacros.h"
#include "Utility/Error.h"

typedef enum {
    PHASE_GENERATION,
    PHASE_SEARCH,
};

ILAssembler *CreateILAssembler() {
    ILAssembler *assembler = malloc(sizeof(ILAssembler));
    assembler->context = CreateILContext();
    assembler->graph = CreateColorGraph();
    assembler->phase = PHASE_GENERATION;
    assembler->statements = NULL;

    return assembler;
}

void FreeILAssembler(ILAssembler *assembler) {
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

DEFINE_VISITER(FILAssemblerVisitResult, ILAssembler *);

FILBase *ILGenerate(ILAssembler *assembler, FBaseNode *node) {
    FILAssemblerVisitResult result = visit(assembler, node);
    if (result.success) {
        return result.il;
    } else {
        int error;
        while ((error = GetError()) != ERROR_NONE) {
            wprintf(U16("ERROR: %ls"), GetErrorString(error));
        }

        FreeIL(result.il);
        return NULL;
    }
}

IMPL_VISITER(FILAssemblerVisitResult, ILAssembler *);

#define BEGIN FILAssemblerVisitResult __result = { true, NULL };
#define END return __result;

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

FILAssemblerVisitResult visitAssignOpNode(ILAssembler *this, FAssignOpNode *node) {
    BEGIN;

    EXPR(left, node->left);
    EXPR(right, node->right);

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

FILAssemblerVisitResult visitBinOpNode(ILAssembler *this, FBinOpNode *node) {
    BEGIN;

    EXPR(left, node->left);
    EXPR(right, node->right);

    GENERATION_PHASE
        EOperation op = StringToOp(node->op->op);
        if (op == OPERATION_UNKNOWN) {
            FAILED;
        } else {
            IL = CreateBinOp(op, left.il, right.il);
            IL->operand = GetColorFromGraph(this->graph, node);
        }
    PHASE_END

    SEARCH_PHASE
        AddEdgeToGraph(this->graph, (FBaseNode*) node, node->left);
        AddEdgeToGraph(this->graph, (FBaseNode*) node, node->right);
        AddEdgeToGraph(this->graph, node->left, node->right);
    PHASE_END

    END;
}

FILAssemblerVisitResult visitCompoundNode(ILAssembler *this, FCompoundNode *node) {
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

FILAssemblerVisitResult visitIntegerNode(ILAssembler *this, FIntegerNode *node) {
    BEGIN;

    GENERATION_PHASE
        IL = CreateInt(node->value);
        IL->operand = GetColorFromGraph(this->graph, node);
    PHASE_END

    SEARCH_PHASE
    PHASE_END

    END;
}

FILAssemblerVisitResult visitRealNode(ILAssembler *this, FRealNode *node) {
    BEGIN;

    GENERATION_PHASE
        IL = CreateReal(node->value);
        IL->operand = GetColorFromGraph(this->graph, node);
    PHASE_END

    SEARCH_PHASE

    PHASE_END

    END;
}

FILAssemblerVisitResult visitStringNode(ILAssembler *this, FStringNode *node) {
    BEGIN;

    GENERATION_PHASE
        IL = CreateStr(node->value);
    PHASE_END

    SEARCH_PHASE

    PHASE_END

    END;
}

FILAssemblerVisitResult visitUnaryOpNode(ILAssembler *this, FUnaryOpNode *node) {
    BEGIN;

    EXPR(expr, node->expr);

    GENERATION_PHASE
        /*EOperation op = StringToOp(node->op->op);
        if (op == OPERATION_UNKNOWN) {
            FAILED;
        } else {
            IL = CreateBinOp(op, left.il, right.il);
        }*/
    PHASE_END

    SEARCH_PHASE
        AddEdgeToGraph(this->graph, (FBaseNode*) node, node->expr);
    PHASE_END

    END;
}

FILAssemblerVisitResult visitVarNode(ILAssembler *this, FVarNode *node) {
    BEGIN;

    GENERATION_PHASE
        size_t addr = -1;
        FSymbol *symbol = FindSymbol(this->local, node->token->str);
        if (symbol != NULL) {
            addr = symbol->slot;
        }

        IL = CreateVar(node->token->str, addr);
        IL->operand = GetColorFromGraph(this->graph, node);
    PHASE_END

    SEARCH_PHASE

    PHASE_END

    END;
}

FILAssemblerVisitResult visitExprStmtNode(ILAssembler *this, FExprStmtNode *node) {
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

FILAssemblerVisitResult visitEmptyNode(ILAssembler *this, FEmptyNode *node) {
    BEGIN;

    END;
}
