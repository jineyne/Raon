#include "pch.h"

#include "FrontEnd/Parser.h"
#include "FrontEnd/SyntaxAnalyzer.h"
#include "Utility/Error.h"

TEST(SyntaxAnalyzerTest, RunSyntaxAnalyzer) {
    FLexer *lexer = NULL;
    FParser *parser = NULL;
    FSyntaxAnalyzer *analyzer = NULL;
    FBaseNode *node = NULL;

    EXPECT_NO_THROW(analyzer = CreateSyntaxAnalyzer());

    {
        u16 *src = U16(R"(
a = 10
b = 1
)");
        EXPECT_NO_THROW(lexer = CreateLexer(src));
        EXPECT_NO_THROW(parser = CreateParser(lexer));
        EXPECT_NO_THROW(node = Parse(parser));

        EXPECT_EQ(GetErrorCount(), 0);
        EXPECT_EQ(node->type, AST_COMPOUND);

        EXPECT_TRUE(RunSyntaxAnalyzer(analyzer, node));
        EXPECT_EQ(GetErrorCount(), 0);

        EXPECT_NO_THROW(FreeParser(parser));
        EXPECT_NO_THROW(FreeLexer(lexer));
    }

    EXPECT_NO_THROW(ClearSyntaxAnalyzer(analyzer));

    {
        u16 *src = U16(R"(
a = b
b = 1
)");
        EXPECT_NO_THROW(lexer = CreateLexer(src));
        EXPECT_NO_THROW(parser = CreateParser(lexer));
        EXPECT_NO_THROW(node = Parse(parser));

        EXPECT_EQ(GetErrorCount(), 0);
        EXPECT_EQ(node->type, AST_COMPOUND);

        EXPECT_FALSE(RunSyntaxAnalyzer(analyzer, node));
        EXPECT_EQ(GetErrorCount(), 1);

        EXPECT_NO_THROW(FreeParser(parser));
        EXPECT_NO_THROW(FreeLexer(lexer));
    }

    EXPECT_NO_THROW(FreeSyntaxAnalyzer(analyzer));
}
