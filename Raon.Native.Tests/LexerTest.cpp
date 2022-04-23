#include "pch.h"

#include "FrontEnd/Lexer.h"
#include "Utility/Error.h"

TEST(LexerTest, GetNextToken) {
    SetLocale(LOCALE_KO);
    ClearError();

    FLexer *lexer = nullptr;
    EXPECT_NO_THROW(lexer = CreateLexer(U16("1 + \"1\" * 2 - 3.0")));

    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_INTEGER);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_PLUS);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_STRING);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_ASTERISK);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_INTEGER);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_MINUS);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_REAL);

    EXPECT_NO_THROW(FreeLexer(lexer));

    lexer = CreateLexer(U16(R"(a = 1 + "1\" * 2 - 3.0
b = a / 10)"));

    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_IDENTIFIER);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_ASSIGN);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_INTEGER);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_PLUS);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_STRING);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_ASTERISK);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_INTEGER);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_MINUS);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_REAL);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_EOL);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_IDENTIFIER);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_ASSIGN);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_IDENTIFIER);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_SLASH);
    EXPECT_EQ(GetNextToken(lexer)->type, TOKEN_INTEGER);

    EXPECT_NO_THROW(FreeLexer(lexer));
}
