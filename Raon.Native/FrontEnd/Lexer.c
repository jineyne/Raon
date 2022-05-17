#include "Lexer.h"

#include "Container/FStringBuffer.h"
#include "String/UTF16.h"

#include "Keyword.h"

FLexer *CreateLexer(const u16 *source) {
    if (source == NULL) {
        return NULL;
    }

    FLexer *lexer = malloc(sizeof(FLexer));
    lexer->source = CreateString(source);
    lexer->cursor = 0;
    lexer->currentChar = lexer->source->data[lexer->cursor];

    lexer->line = 0;
    lexer->pos = 0;

    return lexer;
}

void FreeLexer(FLexer *lexer) {
    if (lexer == NULL) {
        return;
    }

    FreeString(lexer->source);
    free(lexer);
}

static void advance(FLexer *lexer) {
    if (lexer->currentChar == '\n') {
        lexer->line += 1;
        lexer->pos = 0;
    }

    lexer->pos += 1;
    lexer->cursor += 1;
    if (lexer->cursor >= lexer->source->length) {
        lexer->currentChar = EmptyString;
    } else {
        lexer->currentChar = lexer->source->data[lexer->cursor];
    }
}


static u16 peek(FLexer *lexer) {
    size_t peekPos = lexer->cursor + 1;
    if (peekPos >= lexer->source->length) {
        return EmptyString;
    }
    return lexer->source->data[peekPos];
}

static void skipWhitespace(FLexer *lexer) {
    while (lexer->currentChar != EmptyString && lexer->currentChar != U16('\n') && u16isspace(lexer->currentChar)) {
        advance(lexer);
    }
}

static FToken *number(FLexer *lexer) {
    FStringBuffer *sb = CreateStringBuffer();
    int integer = 0;

    while (lexer->currentChar != EmptyString && u16isdigit(lexer->currentChar)) {
        AppendChar(sb, lexer->currentChar);
        integer = integer * 10 + (lexer->currentChar - U16('0'));
        advance(lexer);
    }

    skipWhitespace(lexer);

    if (lexer->currentChar == EmptyString || lexer->currentChar != U16('.')) {
        return CreateTokenFromInteger(lexer->line, lexer->pos, StringBufferToString(sb), integer);
    }

    // REAL!
    double decimal = 1;
    advance(lexer);
    AppendCString(sb, U16("."));
    while (lexer->currentChar != EmptyString && u16isdigit(lexer->currentChar)) {
        AppendChar(sb, lexer->currentChar);

        decimal /= 10.f;

        integer = integer * 10 + (lexer->currentChar - U16('0'));
        advance(lexer);
    }

    FString *str = StringBufferToString(sb);
    FreeStringBuffer(sb);
    return CreateTokenFromReal(lexer->line, lexer->pos, str, (double) integer * decimal);
}

static FToken *string(FLexer *lexer) {
    FStringBuffer *sb = CreateStringBuffer();
    u16 temp[2] = {0,};
    if (lexer->currentChar == U16('"')) {
        advance(lexer);
    }

    while (lexer->currentChar != EmptyString && lexer->currentChar != U16('"')) {
        temp[0] = lexer->currentChar;
        AppendCString(sb, temp);
        advance(lexer);
    }

    // skip "
    advance(lexer);
    return CreateTokenFromString(lexer->line, lexer->pos, StringBufferToString(sb));

}

FKeyword keywords[] = {
    {U16("true"), TOKEN_BOOL, true},
    {U16("false"), TOKEN_BOOL, false},
    {U16("if"), TOKEN_IF, 0},
    {U16("else"), TOKEN_ELSE, 0},
};

static FToken *identifier(FLexer *lexer) {
    FStringBuffer *sb = CreateStringBuffer();
    u16 temp[2] = {0,};
    while (lexer->currentChar != EmptyString && !u16isspace(lexer->currentChar) &&
        !u16isdigit(lexer->currentChar) && !u16isspecial(lexer->currentChar)) {
        temp[0] = lexer->currentChar;
        AppendCString(sb, temp);
        advance(lexer);
    }

    FString *str = StringBufferToString(sb);

    for (uint32_t i = 0; i < sizeof(keywords) / sizeof(FKeyword); i++) {
        FKeyword keyword = keywords[i];
        if (u16cmp(keyword.name, str->data) == 0) {
            FreeString(str);
            FreeStringBuffer(sb);

            FToken *token = CreateToken(keyword.type, lexer->line, lexer->pos, keyword.name);
            token->value = keyword.value;

            return token;
        }
    }

    FToken *FToken = CreateToken(TOKEN_IDENTIFIER, lexer->line, lexer->pos, U16('\0'));
    FToken->str = str;
    FreeStringBuffer(sb);

    return FToken;
}

#define CHECK_CHAR(c, type) \
if (lexer->currentChar == U16('c')) {advance(lexer); return CreateFTokenWithoutValue(type); }

FToken *GetNextToken(FLexer *lexer) {
    if (lexer == NULL) {
        // AddError(ERROR_ARGUMENT_NULL);
        return NULL;
    }

    while (lexer->currentChar != EmptyString) {
        if (lexer->currentChar == U16('\n')) {
            advance(lexer);
            return CreateToken(TOKEN_EOL, lexer->line, lexer->pos, U16('\0'));
        }

        if (u16isspace(lexer->currentChar)) {
            skipWhitespace(lexer);
            continue;
        }

        if (u16isdigit(lexer->currentChar)) {
            return number(lexer);
        }

        if (lexer->currentChar == U16('(')) {
            advance(lexer);
            return CreateToken(TOKEN_LPAREN, lexer->line, lexer->pos, U16("("));
        }

        if (lexer->currentChar == U16(')')) {
            advance(lexer);
            return CreateToken(TOKEN_RPAREN, lexer->line, lexer->pos, U16(")"));
        }

        if (lexer->currentChar == U16('{')) {
            advance(lexer);
            return CreateToken(TOKEN_LBRACE, lexer->line, lexer->pos, U16("{"));
        }

        if (lexer->currentChar == U16('}')) {
            advance(lexer);
            return CreateToken(TOKEN_RBRACE, lexer->line, lexer->pos, U16("}"));
        }

        if (lexer->currentChar == U16('+')) {
            advance(lexer);
            return CreateToken(TOKEN_PLUS, lexer->line, lexer->pos, U16("+"));
        }

        if (lexer->currentChar == U16('-')) {
            advance(lexer);
            return CreateToken(TOKEN_MINUS, lexer->line, lexer->pos, U16("-"));
        }

        if (lexer->currentChar == U16('*')) {
            advance(lexer);
            return CreateToken(TOKEN_ASTERISK, lexer->line, lexer->pos, U16("*"));
        }

        if (lexer->currentChar == U16('/')) {
            advance(lexer);
            return CreateToken(TOKEN_SLASH, lexer->line, lexer->pos, U16("/"));
        }

        if (lexer->currentChar == U16('<')) {
            if (peek(lexer) == U16('=')) {
                advance(lexer);
                advance(lexer);
                return CreateToken(TOKEN_LTE, lexer->line, lexer->pos, U16("<="));
            }

            advance(lexer);
            return CreateToken(TOKEN_LT, lexer->line, lexer->pos, U16("<"));
        }

        if (lexer->currentChar == U16('>')) {
            if (peek(lexer) == U16('=')) {
                advance(lexer);
                advance(lexer);
                return CreateToken(TOKEN_GTE, lexer->line, lexer->pos, U16(">="));
            }

            advance(lexer);
            return CreateToken(TOKEN_GT, lexer->line, lexer->pos, U16(">"));
        }

        if (lexer->currentChar == U16('&')) {
            if (peek(lexer) == U16('&')) {
                advance(lexer);
                advance(lexer);
                return CreateToken(TOKEN_AND, lexer->line, lexer->pos, U16("&&"));
            }
        }

        if (lexer->currentChar == U16('|')) {
            if (peek(lexer) == U16('|')) {
                advance(lexer);
                advance(lexer);
                return CreateToken(TOKEN_OR, lexer->line, lexer->pos, U16("||"));
            }
        }

        if (lexer->currentChar == U16('=')) {
            advance(lexer);
            return CreateToken(TOKEN_ASSIGN, lexer->line, lexer->pos, U16("="));
        }

        if (lexer->currentChar == U16('"')) {
            return string(lexer);
        }

        if (!u16isspecial(lexer->currentChar)) {
            return identifier(lexer);
        }

        // AddError(ERROR_INVALID_TOKEN);
        return NULL;
    }

    return CreateToken(TOKEN_EOF, lexer->line, lexer->pos, U16('\0'));
}

FToken *GetIdentifier(FLexer *lexer) {
    FToken *token = GetNextToken(lexer);

    if (token == NULL || token->type != TOKEN_IDENTIFIER) {
        FreeToken(token);
        return NULL;
    }

    return token;
}

FToken *GetSymbol(FLexer *lexer) {
    FToken *token = GetNextToken(lexer);

    if (token == NULL || !(token->type == TOKEN_IDENTIFIER || token->type == TOKEN_INTEGER || token->type == TOKEN_REAL
        || token->type == TOKEN_STRING || token->type > TOKEN_EOL)) {
        FreeToken(token);
        return NULL;
    }

    return token;
}
