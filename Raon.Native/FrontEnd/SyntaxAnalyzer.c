#include "SyntaxAnalyzer.h"

#include "Utility/Error.h"

typedef enum {
    NotValue,

    RValue,
    LValue,
} EValueType;

FSyntaxAnalyzer *CreateSyntaxAnalyzer(FSymbolTable *table) {
    FSyntaxAnalyzer *analyzer = malloc(sizeof(FSyntaxAnalyzer));

    analyzer->symtab = table == NULL ? CreateSymbolTable(U16("SyntaxAnalyzer"), NULL) : table;
    analyzer->limit = NotValue;
    analyzer->freeSymTab = table == NULL;

    return analyzer;
}

void FreeSyntaxAnalyzer(FSyntaxAnalyzer *analyzer) {
    if (analyzer == NULL) {
        return;
    }

    if (analyzer->freeSymTab) {
        while (analyzer->symtab != NULL) {
            FSymbolTable *parent = analyzer->symtab->parent;

            FreeSymbolTable(analyzer->symtab);
            analyzer->symtab = NULL;

            if (parent != NULL) {
                analyzer->symtab = parent->parent;
            }
        }
    }

    free(analyzer);
}

typedef struct SyntaxAnalyzerResult {
    bool success;
    EValueType valueType;
} FSyntaxAnalyzerResult;

DEFINE_VISITER(FSyntaxAnalyzerResult, FSyntaxAnalyzer *)

bool RunSyntaxAnalyzer(FSyntaxAnalyzer *analyzer, FBaseNode *node) {
    return visit(analyzer, node).success;
}

bool ClearSyntaxAnalyzer(FSyntaxAnalyzer *analyzer) {
    FSymbolTable *parent = analyzer->symtab->parent;
    do {
        if (analyzer->freeSymTab) {
            FreeSymbolTable(analyzer->symtab);
            analyzer->symtab = NULL;
        }

        if (parent != NULL) {
            parent = parent->parent;
        }
    } while (parent != NULL);

    analyzer->symtab = CreateSymbolTable(U16("SyntaxAnalyzer"), NULL);
    analyzer->limit = NotValue;

    return true;
}

IMPL_VISITER(FSyntaxAnalyzerResult, FSyntaxAnalyzer *)

#define BEGIN FSyntaxAnalyzerResult result = { true, NotValue }
#define END return result

#define FAILED result.success = false

#define RVALUE result.valueType = RValue
#define LVALUE result.valueType = LValue

#define VISIT_ANON(NODE) { FSyntaxAnalyzerResult __result = VISIT(NODE); if (!__result.success) FAILED; }
#define VISIT_GRAP(NAME, NODE) FSyntaxAnalyzerResult NAME = VISIT(NODE); if (!NAME.success) FAILED;

#define ERROR(ENUM, ...) CompileError(ENUM, node->location->source->data, node->location->token->line, node->location->token->pos, __VA_ARGS__)

FSyntaxAnalyzerResult visitAssignOpNode(FSyntaxAnalyzer *this, FAssignOpNode *node) {
    BEGIN;

    this->limit = LValue;
    VISIT_GRAP(left, node->left)

    this->limit = RValue;
    VISIT_GRAP(right, node->right)

    if (left.valueType < LValue) {
        ERROR(ERROR_RVALUE_NOT_POSITION_AT_LVALUE, node->left->location->token->str->data);
        FAILED;
    }

    END;
}

FSyntaxAnalyzerResult visitBinOpNode(FSyntaxAnalyzer *this, FBinOpNode *node) {
    BEGIN;

    this->limit = LValue;
    VISIT_GRAP(left, node->left)

    this->limit = RValue;
    VISIT_GRAP(right, node->right)

    END;
}

FSyntaxAnalyzerResult visitBoolOpNode(FSyntaxAnalyzer *this, FBoolOpNode *node) {
    BEGIN;

    this->limit = LValue;
    VISIT_GRAP(left, node->left)

    this->limit = RValue;
    VISIT_GRAP(right, node->right)

    END;
}

FSyntaxAnalyzerResult visitCompoundNode(FSyntaxAnalyzer *this, FCompoundNode *node) {
    BEGIN;

    FBaseNode *it;
    ARRAY_FOREACH(node->children, it) {
        VISIT_ANON(it)
    }

    END;
}

FSyntaxAnalyzerResult visitBoolNode(FSyntaxAnalyzer *this, FBoolNode *node) {
    BEGIN;

    RVALUE;

    END;
}

FSyntaxAnalyzerResult visitIntegerNode(FSyntaxAnalyzer *this, FIntegerNode *node) {
    BEGIN;

    RVALUE;

    END;
}

FSyntaxAnalyzerResult visitRealNode(FSyntaxAnalyzer *this, FRealNode *node) {
    BEGIN;

    RVALUE;

    END;
}

FSyntaxAnalyzerResult visitStringNode(FSyntaxAnalyzer *this, FStringNode *node) {
    BEGIN;

    RVALUE;

    END;
}

FSyntaxAnalyzerResult visitUnaryOpNode(FSyntaxAnalyzer *this, FUnaryOpNode *node) {
    BEGIN;

    this->limit = RValue;
    VISIT_GRAP(right, node->expr)

    END;
}

FSyntaxAnalyzerResult visitVarNode(FSyntaxAnalyzer *this, FVarNode *node) {
    BEGIN;

    RVALUE;

    FSymbol *symbol = NULL;
    int error = FindSymbol(this->symtab, node->location->token->str, &symbol);
    if (error != ERROR_NONE) {
        // this is not declare case!
        // foo = [Unknown Var Name]
        if (this->limit == RValue) {
            ERROR(ERROR_SYMBOL_NOT_FOUND, node->location->token->str->data);
            FAILED;
        } else if (this->limit == LValue) {
            // this is declare case!
            symbol = (FSymbol*) CreateVarSymbol(node->location->token->str, NULL);
            error = InsertSymbol(this->symtab, symbol);
            if (error != ERROR_NONE) {
                ERROR(error, node->location->token->str->data);
                FAILED;
            }

            LVALUE;
        }
    } else {
        LVALUE;
    }

    END;
}

FSyntaxAnalyzerResult visitExprStmtNode(FSyntaxAnalyzer *this, FExprStmtNode *node) {
    BEGIN;

    VISIT_ANON(node->expr);

    END;
}

FSyntaxAnalyzerResult visitIfNode(FSyntaxAnalyzer *this, FIfNode *node) {
    BEGIN;

    VISIT_ANON(node->cond);
    VISIT_ANON(node->stmt);
    VISIT_ANON(node->elseExpr);

    END;
}

FSyntaxAnalyzerResult visitEmptyNode(FSyntaxAnalyzer *this, FEmptyNode *node) {
    BEGIN;

    END;
}
