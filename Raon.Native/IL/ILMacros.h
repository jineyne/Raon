#ifndef __ILMACROS_H__
#define __ILMACROS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define DEFINE_ILVISITER(RETURN_TYPE, THIS_TYPE) \
    static RETURN_TYPE visitAssignOp(THIS_TYPE this, FAssignOp *il); \
    static RETURN_TYPE visitBinOp(THIS_TYPE this, FBinOp *il); \
    static RETURN_TYPE visitVar(THIS_TYPE this, FVar *il); \
    static RETURN_TYPE visitInt(THIS_TYPE this, FInt *il); \
    static RETURN_TYPE visitReal(THIS_TYPE this, FReal *il); \
    static RETURN_TYPE visitStr(THIS_TYPE this, FString *il); \
    static RETURN_TYPE visitCompound(THIS_TYPE this, FCompound *il); \
    static RETURN_TYPE visitExprStmt(THIS_TYPE this, FExprStmt *il); \
    static RETURN_TYPE visit(THIS_TYPE this, FILBase *il); \

#define VISIT_ILCASE(NODE_TYPE, NODE_NAME) case NODE_TYPE : return visit##NODE_NAME(this, il);
#define IMPL_ILVISITER(RETURN_TYPE, THIS_TYPE) \
    RETURN_TYPE visit(THIS_TYPE this, FILBase *il) { \
        if (il == NULL) return (RETURN_TYPE) {0,}; \
        switch (il->type) { \
            VISIT_ILCASE(IL_ASSIGNOP, AssignOp); \
            VISIT_ILCASE(IL_BINOP, BinOp); \
            VISIT_ILCASE(IL_VAR, Var); \
            VISIT_ILCASE(IL_INTEGER, Int); \
            VISIT_ILCASE(IL_REAL, Real); \
            VISIT_ILCASE(IL_STRING, Str); \
            VISIT_ILCASE(IL_COMPOUND, Compound); \
            VISIT_ILCASE(IL_EXPR_STATEMENT, ExprStmt); \
            default: break; \
        } \
    }


#define VISIT(node) visit(this, node)

#ifdef __cplusplus
}
#endif

#endif