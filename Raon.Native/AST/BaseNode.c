#include "BaseNode.h"

#include "AssignOpNode.h"
#include "CompoundNode.h"
#include "EmptyNode.h"
#include "BinOpNode.h"
#include "BoolNode.h"
#include "BoolOpNode.h"
#include "ExprStmtNode.h"
#include "IfNode.h"
#include "UnaryOpNode.h"
#include "IntegerNode.h"
#include "RealNode.h"
#include "StringNode.h"
#include "VarNode.h"

void InitBaseNode(FBaseNode *node, EASTType type, AST_REQUIRE_ARGS) {
    node->type = type;
    node->location = CreateLocation(source, token);
    if (node->location->token->str != NULL) {
        node->hash = HashString(node->location->token->str);
    } else {
        node->hash = 0;
    }
}

void FinitBaseNode(FBaseNode *node) {
    FreeLocation(node->location);
}

void FreeNode(FBaseNode *node) {
    if (node == NULL) {
        return;
    }

    switch (node->type) {
    case AST_COMPOUND:
        FreeCompoundNode(node);
        break;
    case AST_EXPRSTMT:
        FreeExprStmtNode(node);
        break;
    case AST_IF:
        FreeIfNode(node);
        break;
    case AST_EMPTY:
        FreeEmptyNode(node);
        break;
    case AST_ASSIGNOP:
        FreeAssignNode(node);
        break;
    case AST_BINOP:
        FreeBinOpNode(node);
        break;
    case AST_UNARYOP:
        FreeUnaryOpNode(node);
        break;
    case AST_BOOL:
        FreeBoolNode(node);
        break;
    case AST_BOOLOP:
        FreeBoolOpNode(node);
        break;
    case AST_INTEGER:
        FreeIntegerNode(node);
        break;
    case AST_REAL:
        FreeRealNode(node);
        break;
    case AST_STRING:
        FreeStringNode(node);
        break;
    case AST_VAR:
        FreeVarNode(node);
        break;

    default: ;
    }
}

bool IsStmtNode(FBaseNode *node) {
    if (AST_COMPOUND <= node->type && node->type <= AST_EMPTY) {
        return true;
    }

    return false;
}

bool IsExprNode(FBaseNode *node) {
    if (AST_EMPTY < node->type && node->type < AST_COUNT) {
        return true;
    }

    return false;
}