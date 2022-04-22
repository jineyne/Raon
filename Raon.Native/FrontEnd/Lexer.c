#include "Lexer.h"

#include "Container/FStringBuffer.h"
#include "String/UTF16.h"

FLexer *CreateLexer(const u16 *source) {
    if (source == NULL) {
        return NULL;
    }

    FLexer *lexer = malloc(sizeof(FLexer));
    lexer->source = CreateString(source);
    lexer->pos = 0;
    lexer->currentChar = lexer->source->data[lexer->pos];

    return lexer;
}

void FreeLexer(FLexer *lexer) {
    free(lexer);
}

static void advance(FLexer *lexer) {
    lexer->pos += 1;
    if (lexer->pos >= lexer->source->length) {
        lexer->currentChar = EmptyString;
    }
    else {
        lexer->currentChar = lexer->source->data[lexer->pos];
    }
}


static u16 peek(FLexer *lexer) {
    size_t peekPos = lexer->pos + 1;
    if (peekPos >= lexer->source->length) {
        return EmptyString;
    }
    else {
        return lexer->source->data[peekPos];
    }
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
        return CreateTokenFromInteger(StringBufferToString(sb), integer);
    }

    // REAL!
    double decimal = 0;
    advance(lexer);
    while (lexer->currentChar != EmptyString && u16isdigit(lexer->currentChar)) {
        decimal = decimal * 0.1 + (lexer->currentChar - U16('0'));
        advance(lexer);
    }

    FString *str =  StringBufferToString(sb);
    FreeStringBuffer(sb);
    return CreateTokenFromReal(str, (double)integer + decimal);
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
    return CreateTokenFromString(StringBufferToString(sb));

}

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

    /*for (uint32_t i = 0; i < sizeof(keywords) / sizeof(Keyword); i++) {
        Keyword keyword = keywords[i];
        if (u16cmp(keyword.str, str->data) == 0) {
            FreeString(str);
            FreeStringBuffer(sb);

            return CreateFTokenWithoutValue(keyword.FToken.type);
        }
    }*/

    FToken *FToken = CreateToken(TOKEN_IDENTIFIER, U16('\0'));
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
            return CreateToken(TOKEN_EOL, U16('\0'));
        }

        if (u16isspace(lexer->currentChar)) {
            skipWhitespace(lexer);
            continue;
        }

        if (u16isdigit(lexer->currentChar)) {
            return number(lexer);
        }

        if (lexer->currentChar == U16('+')) {
            advance(lexer);
            return CreateToken(TOKEN_PLUS, U16("+"));
        }

        if (lexer->currentChar == U16('-')) {
            advance(lexer);
            return CreateToken(TOKEN_MINUS, U16("-"));
        }

        if (lexer->currentChar == U16('*')) {
            advance(lexer);
            return CreateToken(TOKEN_ASTERISK, U16("*"));
        }

        if (lexer->currentChar == U16('/')) {
            advance(lexer);
            return CreateToken(TOKEN_SLASH, U16("/"));
        }

        if (lexer->currentChar == U16('(')) {
            advance(lexer);
            return CreateToken(TOKEN_LPAREN, U16("("));
        }

        if (lexer->currentChar == U16(')')) {
            advance(lexer);
            return CreateToken(TOKEN_RPAREN, U16(")"));
        }

        if (lexer->currentChar == U16('=')) {
            advance(lexer);
            return CreateToken(TOKEN_ASSIGN, U16("="));
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

    return CreateToken(TOKEN_EOF, U16('\0'));
}

FToken *GetIdentifier(FLexer *lexer) {
    FToken* token = GetNextToken(lexer);

    if (token == NULL || token->type != TOKEN_IDENTIFIER) {
        FreeToken(token);
        return NULL;
    }

    return token;
}

FToken *GetSymbol(FLexer *lexer) {
    FToken* token = GetNextToken(lexer);

    if (token == NULL || !(token->type == TOKEN_IDENTIFIER || token->type == TOKEN_INTEGER || token->type == TOKEN_REAL || token->type == TOKEN_STRING || token->type > TOKEN_EOL)) {
        FreeToken(token);
        return NULL;
    }

    return token;
}
