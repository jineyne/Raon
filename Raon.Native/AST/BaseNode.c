#include "BaseNode.h"

#include "AssignOpNode.h"
#include "CompoundNode.h"
#include "EmptyNode.h"
#include "BinOpNode.h"
#include "ExprStmtNode.h"
#include "UnaryOpNode.h"
#include "IntegerNode.h"
#include "RealNode.h"
#include "StringNode.h"
#include "VarNode.h"

void FreeNode(FBaseNode *node) {
    switch (node->type) {
    case AST_COMPOUND:
        FreeCompoundNode(node);
        break;
    case AST_EXPRSTMT:
        FreeExprStmtNode(node);
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
    case AST_INTEGER:
        FreeIntegerNode(node);
        break;
    case AST_REAL:
        FreeRealNode(node);
        break;
    case AST_VAR:
        FreeVarNode(node);
        break;

    default: ;
    }
}

#define INDENT_SIZE 2
#define PRINT_INDENT for (int i = 0; i < indent * INDENT_SIZE; i++) { wprintf(U16(" ")); }
#define PRINT(STMT) wprintf(U16(#STMT))
#define LN  wprintf(U16("\n"))
#define PRINTT(STMT) { wprintf(STMT); }
#define PRINTF(STMT, ...) { wprintf(U16(" ")); } wprintf(U16(STMT), __VA_ARGS__)
#define TO(TYPE) ((TYPE *) node)

void printNodeInternal(FBaseNode *node, int indent) {
    u16 buffer[8] = {0,};
    FBaseNode *it;
    switch (node->type) {
    case AST_COMPOUND:
        PRINT_INDENT PRINT(COMPOUND); LN;
        ARRAY_FOREACH(((FCompoundNode *)node)->children, it) {
            printNodeInternal(it, indent + 1);
        }

        break;
    case AST_EXPRSTMT:
        PRINT_INDENT PRINT(EXPRSTMT); LN;
        printNodeInternal(TO(FExprStmtNode)->expr, indent + 1);
        break;
    case AST_EMPTY:
        PRINT_INDENT PRINT(EMPTY); LN;
        break;
    case AST_ASSIGNOP:
        PRINT_INDENT PRINT(ASSIGNOP); LN;

        PRINT_INDENT PRINT(LEFT); LN;
        printNodeInternal(TO(FAssignOpNode)->left, indent + 1);

        PRINT_INDENT PRINT(RIGHT); LN;
        printNodeInternal(TO(FAssignOpNode)->right, indent + 1);
        break;
    case AST_BINOP:
        PRINT_INDENT PRINT(BINOP); LN;

        PRINT_INDENT PRINT(LEFT); LN;
        printNodeInternal(TO(FBinOpNode)->left, indent + 1);

        buffer[0] = TO(FBinOpNode)->op->op;
        PRINT_INDENT PRINTT("OP ") PRINTT(buffer); LN;
        buffer[0] = '\0';

        PRINT_INDENT PRINT(RIGHT); LN;
        printNodeInternal(TO(FBinOpNode)->right, indent + 1);
        break;
    case AST_UNARYOP:
        PRINT_INDENT PRINT(UNARYOP); LN;

        PRINT_INDENT PRINTT(TO(FUnaryOpNode)->token->str->data); LN;
        printNodeInternal(TO(FUnaryOpNode)->expr, indent + 1);
        break;
    case AST_INTEGER:
        PRINT_INDENT PRINT(INTEGER); PRINTF(" %lld", TO(FIntegerNode)->value); LN;
        break;
    case AST_REAL:
        PRINT_INDENT PRINT(REAL); PRINTF(" %llf", TO(FRealNode)->value); LN;
        break;
    case AST_STRING:
        PRINT_INDENT PRINT(STRING); PRINTF(" %s", TO(FStringNode)->value->data); LN;
        break;

    case AST_VAR:
        PRINT_INDENT PRINT(VAR); PRINTT(" ") PRINTT(TO(FVarNode)->token->str->data); LN;
        break;

    default: ;
    }
}

void PrintNode(FBaseNode *node) {
    printNodeInternal(node, 0);
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
