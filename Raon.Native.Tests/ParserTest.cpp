#include "pch.h"

#include "FrontEnd/Parser.h"
#include "Utility/Error.h"

TEST(ParserTest, GetNextToken) {
    FLexer *lexer = NULL;
    FParser *parser = NULL;
    FBaseNode *node = NULL;


    u16 *src1 = U16("a = 1 + \"1\" * 2 - 3.0");
    EXPECT_NO_THROW(lexer = CreateLexer(src1));
    EXPECT_NO_THROW(parser = CreateParser(lexer));
    EXPECT_NO_THROW(node = Parse(parser));

    EXPECT_EQ(GetErrorCount(), 0);
    EXPECT_EQ(node->type, AST_COMPOUND);

    EXPECT_NO_THROW(FreeNode(node));
    EXPECT_NO_THROW(FreeParser(parser));
    EXPECT_NO_THROW(FreeLexer(lexer));

    u16 *src2 = U16(R"(
a = 10
b = 1
)");
    EXPECT_NO_THROW(lexer = CreateLexer(src2));
    EXPECT_NO_THROW(parser = CreateParser(lexer));
    EXPECT_NO_THROW(node = Parse(parser));

    EXPECT_EQ(GetErrorCount(), 0);
    EXPECT_EQ(node->type, AST_COMPOUND);

    EXPECT_NO_THROW(FreeNode(node));
    EXPECT_NO_THROW(FreeParser(parser));
    EXPECT_NO_THROW(FreeLexer(lexer));
}
