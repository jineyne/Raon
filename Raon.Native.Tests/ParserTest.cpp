#include "pch.h"

#include "FrontEnd/Parser.h"
#include "Utility/Error.h"

TEST(ParserTest, GetNextToken) {
    SetLocale(LOCALE_KO);
    ClearError();

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
