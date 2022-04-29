#include "pch.h"

#include "FrontEnd/Lexer.h"
#include "Utility/Error.h"

TEST(LexerTest, GetNextToken) {
    InitRaon();

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

TEST(LexerTest, Boolean) {
    FLexer *lexer = nullptr;
    FToken *token = nullptr;

    lexer = CreateLexer(U16("a = true"));
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_IDENTIFIER);
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_ASSIGN);
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_BOOL);
    EXPECT_EQ(token->value.boolean, true);
    EXPECT_NO_THROW(FreeLexer(lexer));

    lexer = CreateLexer(U16("a = false"));
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_IDENTIFIER);
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_ASSIGN);
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_BOOL);
    EXPECT_EQ(token->value.boolean, false);
    EXPECT_NO_THROW(FreeLexer(lexer));
}

TEST(LexerTest, Integer) {
    FLexer *lexer = nullptr;
    FToken *token = nullptr;

    lexer = CreateLexer(U16("a = 1"));
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_IDENTIFIER);
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_ASSIGN);
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_INTEGER);
    EXPECT_EQ(token->value.integer, 1);
    EXPECT_NO_THROW(FreeLexer(lexer));

    lexer = CreateLexer(U16("a = -2"));
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_IDENTIFIER);
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_ASSIGN);
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_MINUS);
    EXPECT_EQ((token = GetNextToken(lexer))->type, TOKEN_INTEGER);
    EXPECT_EQ(token->value.integer, 2);
    EXPECT_NO_THROW(FreeLexer(lexer));
}
