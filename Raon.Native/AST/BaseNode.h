#ifndef __BASENODE_H__
#define __BASENODE_H__

#include "Prerequisites/PrerequisitesUtil.h"
#include "Location.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AST_REQUIRED EASTType type; FLocation *location; size_t hash;

#define AST_REQUIRE_ARGS FString *source, FToken *token
#define INIT_BASE_NODE(NODE, OP) InitBaseNode(NODE, OP, source, token)

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

    AST_BOOL,
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


DLL_EXPORT void InitBaseNode(FBaseNode *node, EASTType type, AST_REQUIRE_ARGS);
DLL_EXPORT void FinitBaseNode(FBaseNode *node);

DLL_EXPORT void FreeNode(FBaseNode *node);

DLL_EXPORT bool IsStmtNode(FBaseNode *node);
DLL_EXPORT bool IsExprNode(FBaseNode *node);

#ifdef __cplusplus
}
#endif

#endif // __BASENODE_H__
