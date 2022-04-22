#include "SyntaxAnalyzer.h"

#include "Utility/Error.h"

typedef enum {
    NotValue,

    RValue,
    LValue,
} EValueType;

FSyntaxAnalyzer *CreateSyntaxAnalyzer() {
    FSyntaxAnalyzer *analyzer = malloc(sizeof(FSyntaxAnalyzer));

    analyzer->symtab = CreateSymbolTable(CreateString(U16("SyntaxAnalyzer")), NULL);
    analyzer->limit = NotValue;

    return analyzer;
}

void FreeSyntaxAnalyzer(FSyntaxAnalyzer *analyzer) {
    FSymbolTable *parent = NULL;
    while (analyzer->symtab != NULL) {
        parent = analyzer->symtab->parent;

        FreeSymbolTable(analyzer->symtab);
        analyzer->symtab = NULL;

        if (parent != NULL) {
            analyzer->symtab = parent->parent;
        }
    };

    free(analyzer);
}

typedef struct SyntaxAnalyzerResult {
    bool success;
    EValueType valueType;
} FSyntaxAnalyzerResult;

DEFINE_VISITER(FSyntaxAnalyzerResult, FSyntaxAnalyzer *);

bool RunSyntaxAnalyzer(FSyntaxAnalyzer *analyzer, FBaseNode *node) {
    return visit(analyzer, node).success;
}

bool ClearSyntaxAnalyzer(FSyntaxAnalyzer *analyzer) {
    FSymbolTable *parent = analyzer->symtab->parent;
    do {
        FreeSymbolTable(analyzer->symtab);

        if (parent != NULL) {
            parent = parent->parent;
        }
    } while (parent != NULL);

    analyzer->symtab = CreateSymbolTable(CreateString(U16("SyntaxAnalyzer")), NULL);
    analyzer->limit = NotValue;

    return true;
}

IMPL_VISITER(FSyntaxAnalyzerResult, FSyntaxAnalyzer *);

#define BEGIN FSyntaxAnalyzerResult result = { true, NotValue }
#define END return result

#define FAILED result.success = false

#define RVALUE result.valueType = RValue
#define LVALUE result.valueType = LValue

#define VISIT_ANON(NODE) { FSyntaxAnalyzerResult __result = VISIT(NODE); if (!__result.success) FAILED; }
#define VISIT_GRAP(NAME, NODE) FSyntaxAnalyzerResult NAME = VISIT(NODE); if (!NAME.success) FAILED;

FSyntaxAnalyzerResult visitAssignOpNode(FSyntaxAnalyzer *this, FAssignOpNode *node) {
    BEGIN;

    this->limit = LValue;
    VISIT_GRAP(left, node->left);

    this->limit = RValue;
    VISIT_GRAP(right, node->right);

    if (left.valueType < LValue) {
        PushError(ERROR_RVALUE_NOT_POSITION_AT_LVALUE);
        FAILED;
    }

    END;
}

FSyntaxAnalyzerResult visitBinOpNode(FSyntaxAnalyzer *this, FBinOpNode *node) {
    BEGIN;

    this->limit = LValue;
    VISIT_GRAP(left, node->left);

    this->limit = RValue;
    VISIT_GRAP(right, node->right);

    END;
}

FSyntaxAnalyzerResult visitCompoundNode(FSyntaxAnalyzer *this, FCompoundNode *node) {
    BEGIN;

    FBaseNode *it;
    ARRAY_FOREACH(node->children, it) {
        VISIT_ANON(it);
    }

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

    END;
}

FSyntaxAnalyzerResult visitVarNode(FSyntaxAnalyzer *this, FVarNode *node) {
    BEGIN;

    RVALUE;

    FSymbol *symbol = FindSymbol(this->symtab, node->token->str);
    if (symbol == NULL) {
        // this is not declare case!
        // foo = [Unknown Var Name]
        if (this->limit == RValue) {
            PushError(ERROR_SYMBOL_NOT_FOUND);
            FAILED;
        }
    }

    if (this->limit == LValue) {
        // this is declare case!
        FSymbol *symbol = CreateVarSymbol(node->token->str, NULL);
        if (!InsertSymbol(this->symtab, symbol)) {
            PushError(ERROR_INTERNAL_ERROR);
            FAILED;
        }

        LVALUE;
    }

    END;
}

FSyntaxAnalyzerResult visitExprStmtNode(FSyntaxAnalyzer *this, FExprStmtNode *node) {
    BEGIN;

    VISIT_ANON(node->expr);

    END;
}

FSyntaxAnalyzerResult visitEmptyNode(FSyntaxAnalyzer *this, FEmptyNode *node) {
    BEGIN;

    END;
}
