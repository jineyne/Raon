#include "pch.h"

#include "FrontEnd/Parser.h"
#include "Utility/Error.h"

#define TO(TYPE, NODE) ((TYPE *) NODE)

TEST(ParserTest, BinOp) {
    InitRaon();

    FParser *parser = nullptr;
    FBaseNode *node = nullptr;

    u16 *src1 = U16("a = 1 + \"1\" * 2 - 3.0");
    EXPECT_NO_THROW(parser = CreateParserFromMemory(src1));
    EXPECT_NO_THROW(node = Parse(parser));

    EXPECT_EQ(GetErrorCount(), 0);
    EXPECT_EQ(node->type, AST_COMPOUND);

    EXPECT_NO_THROW(FreeNode(node));
    EXPECT_NO_THROW(FreeParser(parser));

    u16 *src2 = U16(R"(
a = 10
b = 1
)");
    EXPECT_NO_THROW(parser = CreateParserFromMemory(src2));
    EXPECT_NO_THROW(node = Parse(parser));

    EXPECT_EQ(GetErrorCount(), 0);
    EXPECT_EQ(node->type, AST_COMPOUND);

    EXPECT_NO_THROW(FreeNode(node));
    EXPECT_NO_THROW(FreeParser(parser));
}

TEST(ParserTest, Assign) {
    InitRaon();

    FParser *parser = nullptr;
    FBaseNode *node = nullptr;

    {
        EXPECT_NO_THROW(parser = CreateParserFromMemory(U16("a = 1")));
        EXPECT_NO_THROW(node = Parse(parser));

        EXPECT_EQ(GetErrorCount(), 0);
        EXPECT_EQ(node->type, AST_COMPOUND);

        FBaseNode **children = TO(FCompoundNode, node)->children;
        EXPECT_EQ(ARRAY_SIZE(children), 1);
        EXPECT_EQ(children[0]->type, AST_EXPRSTMT);

        FBaseNode *expr = TO(FExprStmtNode, children[0])->expr;
        EXPECT_EQ(expr->type, AST_ASSIGNOP);
        EXPECT_EQ(TO(FAssignOpNode, expr)->left->type, AST_VAR);
        EXPECT_EQ(TO(FAssignOpNode, expr)->right->type, AST_INTEGER);

        EXPECT_NO_THROW(FreeNode(node));
        EXPECT_NO_THROW(FreeParser(parser));
    }

    {
        EXPECT_NO_THROW(parser = CreateParserFromMemory(U16("a = 1.0")));
        EXPECT_NO_THROW(node = Parse(parser));

        EXPECT_EQ(GetErrorCount(), 0);
        EXPECT_EQ(node->type, AST_COMPOUND);

        FBaseNode **children = TO(FCompoundNode, node)->children;
        EXPECT_EQ(ARRAY_SIZE(children), 1);
        EXPECT_EQ(children[0]->type, AST_EXPRSTMT);

        FBaseNode *expr = TO(FExprStmtNode, children[0])->expr;
        EXPECT_EQ(expr->type, AST_ASSIGNOP);
        EXPECT_EQ(TO(FAssignOpNode, expr)->left->type, AST_VAR);
        EXPECT_EQ(TO(FAssignOpNode, expr)->right->type, AST_REAL);

        EXPECT_NO_THROW(FreeNode(node));
        EXPECT_NO_THROW(FreeParser(parser));
    }

    {
        EXPECT_NO_THROW(parser = CreateParserFromMemory(U16("a = \"Hello, World!\"")));
        EXPECT_NO_THROW(node = Parse(parser));

        EXPECT_EQ(GetErrorCount(), 0);
        EXPECT_EQ(node->type, AST_COMPOUND);

        FBaseNode **children = TO(FCompoundNode, node)->children;
        EXPECT_EQ(ARRAY_SIZE(children), 1);
        EXPECT_EQ(children[0]->type, AST_EXPRSTMT);

        FBaseNode *expr = TO(FExprStmtNode, children[0])->expr;
        EXPECT_EQ(expr->type, AST_ASSIGNOP);
        EXPECT_EQ(TO(FAssignOpNode, expr)->left->type, AST_VAR);
        EXPECT_EQ(TO(FAssignOpNode, expr)->right->type, AST_STRING);

        EXPECT_NO_THROW(FreeNode(node));
        EXPECT_NO_THROW(FreeParser(parser));
    }

    {
        EXPECT_NO_THROW(parser = CreateParserFromMemory(U16("a = true")));
        EXPECT_NO_THROW(node = Parse(parser));

        EXPECT_EQ(GetErrorCount(), 0);
        EXPECT_EQ(node->type, AST_COMPOUND);

        FBaseNode **children = TO(FCompoundNode, node)->children;
        EXPECT_EQ(ARRAY_SIZE(children), 1);
        EXPECT_EQ(children[0]->type, AST_EXPRSTMT);

        FBaseNode *expr = TO(FExprStmtNode, children[0])->expr;
        EXPECT_EQ(expr->type, AST_ASSIGNOP);
        EXPECT_EQ(TO(FAssignOpNode, expr)->left->type, AST_VAR);
        EXPECT_EQ(TO(FAssignOpNode, expr)->right->type, AST_BOOL);

        EXPECT_NO_THROW(FreeNode(node));
        EXPECT_NO_THROW(FreeParser(parser));
    }

    {
        EXPECT_NO_THROW(parser = CreateParserFromMemory(U16("a = false")));
        EXPECT_NO_THROW(node = Parse(parser));

        EXPECT_EQ(GetErrorCount(), 0);
        EXPECT_EQ(node->type, AST_COMPOUND);

        FBaseNode **children = TO(FCompoundNode, node)->children;
        EXPECT_EQ(ARRAY_SIZE(children), 1);
        EXPECT_EQ(children[0]->type, AST_EXPRSTMT);

        FBaseNode *expr = TO(FExprStmtNode, children[0])->expr;
        EXPECT_EQ(expr->type, AST_ASSIGNOP);
        EXPECT_EQ(TO(FAssignOpNode, expr)->left->type, AST_VAR);
        EXPECT_EQ(TO(FAssignOpNode, expr)->right->type, AST_BOOL);

        EXPECT_NO_THROW(FreeNode(node));
        EXPECT_NO_THROW(FreeParser(parser));
    }
}
