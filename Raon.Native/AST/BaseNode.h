#ifndef __BASENODE_H__
#define __BASENODE_H__

#include "Prerequisites/PrerequisitesUtil.h"
#include "FrontEnd/Token.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AST_REQUIRED EASTType type; FToken *token; size_t hash;

typedef enum ASTType {
    AST_NONE,

    // STATEMENT

    AST_COMPOUND,
    AST_EXPRSTMT,
    AST_EMPTY,

    // EXPRESSION

    AST_ASSIGNOP,
    AST_BINOP,
    AST_UNARYOP,


    // RVALUE

    AST_INTEGER,
    AST_REAL,
    AST_STRING,

    // LVALUE

    AST_VAR,

    AST_COUNT,
    AST_UNKNOWN,
} EASTType;

typedef struct BaseNode {
    AST_REQUIRED
} FBaseNode;

DLL_EXPORT void FreeNode(FBaseNode *node);
DLL_EXPORT void PrintNode(FBaseNode *node);

DLL_EXPORT bool IsStmtNode(FBaseNode *node);
DLL_EXPORT bool IsExprNode(FBaseNode *node);

#ifdef __cplusplus
}
#endif

#endif // __BASENODE_H__
