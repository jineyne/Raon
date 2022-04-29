#ifndef __ASTCPP_H__
#define __ASTCPP_H__

#ifdef __cplusplus

#define DEFINE_VISITER(RETURN_TYPE, THIS_TYPE) \
    RETURN_TYPE visitAssignOpNode(THIS_TYPE this, FAssignOpNode *node); \
    RETURN_TYPE visitBinOpNode(THIS_TYPE this, FBinOpNode *node); \
    RETURN_TYPE visitCompoundNode(THIS_TYPE this, FCompoundNode *node); \
    RETURN_TYPE visitBoolNode(THIS_TYPE this, FBoolNode *node); \
    RETURN_TYPE visitIntegerNode(THIS_TYPE this, FIntegerNode *node); \
    RETURN_TYPE visitRealNode(THIS_TYPE this, FRealNode *node); \
    RETURN_TYPE visitStringNode(THIS_TYPE this, FStringNode *node); \
    RETURN_TYPE visitUnaryOpNode(THIS_TYPE this, FUnaryOpNode *node); \
    RETURN_TYPE visitVarNode(THIS_TYPE this, FVarNode *node); \
    RETURN_TYPE visitEmptyNode(THIS_TYPE this, FEmptyNode *node); \
    RETURN_TYPE visit(THIS_TYPE this, FBaseNode *node);

#define VISIT_CASE(NODE_TYPE, NODE_NAME) case NODE_TYPE : return visit##NODE_NAME(this, node);
#define IMPL_VISITER(RETURN_TYPE, THIS_TYPE) \
    RETURN_TYPE visit(THIS_TYPE this, FBaseNode *node) { \
        if (node == NULL) return (RETURN_TYPE) {0,}; \
        switch (node->type) { \
            VISIT_CASE(AST_COMPOUND, CompoundNode); \
            VISIT_CASE(AST_EMPTY, EmptyNode); \
            VISIT_CASE(AST_ASSIGNOP, AssignOpNode); \
            VISIT_CASE(AST_BINOP, BinOpNode); \
            VISIT_CASE(AST_UNARYOP, UnaryOpNode); \
            VISIT_CASE(AST_BOOL, BoolNode); \
            VISIT_CASE(AST_INTEGER, IntegerNode); \
            VISIT_CASE(AST_REAL, RealNode); \
            VISIT_CASE(AST_STRING, StringNode); \
            VISIT_CASE(AST_VAR, VarNode); \
            default: break; \
        } \
    }


#define VISIT(node) visit(this, node)

template <typename ReturnType>
class ASTVisiter {
public:
#define VISIT_CASE(NODE_TYPE, NODE_NAME) case NODE_TYPE : return visit##NODE_NAME((F##NODE_NAME *) node);

    ReturnType visit(FBaseNode *node) {
        if (node == nullptr) return ReturnType();
        switch (node->type) {
        VISIT_CASE(AST_COMPOUND, CompoundNode);
        VISIT_CASE(AST_EMPTY, EmptyNode);
        VISIT_CASE(AST_ASSIGNOP, AssignOpNode);
        VISIT_CASE(AST_BINOP, BinOpNode);
        VISIT_CASE(AST_UNARYOP, UnaryOpNode);
        VISIT_CASE(AST_BOOL, BoolNode);
        VISIT_CASE(AST_INTEGER, IntegerNode);
        VISIT_CASE(AST_REAL, RealNode);
        VISIT_CASE(AST_STRING, StringNode);
        VISIT_CASE(AST_VAR, VarNode);
        default: break;
        }
    }
#undef VISIT_CASE


protected:
    virtual ReturnType visitAssignOpNode(FAssignOpNode *node) = 0;
    virtual ReturnType visitBinOpNode(FBinOpNode *node) = 0;
    virtual ReturnType visitCompoundNode(FCompoundNode *node) = 0;
    virtual ReturnType visitBoolNode(FBoolNode *node) = 0;
    virtual ReturnType visitIntegerNode(FIntegerNode *node) = 0;
    virtual ReturnType visitRealNode(FRealNode *node) = 0;
    virtual ReturnType visitStringNode(FStringNode *node) = 0;
    virtual ReturnType visitUnaryOpNode(FUnaryOpNode *node) = 0;
    virtual ReturnType visitVarNode(FVarNode *node) = 0;
    virtual ReturnType visitEmptyNode(FEmptyNode *node) = 0;
};

#endif

#endif //__ASTM__ASTCPP_H__ACROS_H__
