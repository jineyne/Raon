#include "Token.h"

FToken *CreateToken(ETokenType type, size_t line, size_t pos, u16 *str) {
    FToken *token = malloc(sizeof(FToken));
    token->type = type;

    token->str = CreateString(str);
    token->value.integer = 0;

    token->line = line;
    token->pos = pos;

    return token;
}


FToken *CreateTokenWithString(ETokenType type, size_t line, size_t pos, u16 *cstr) {
    FToken *token = malloc(sizeof(FToken));
    token->type = type;

    token->str = CreateString(cstr);
    token->value.integer = 0;

    token->line = line;
    token->pos = pos;

    return token;
}

FToken *CreateTokenFromInteger(size_t line, size_t pos, FString *str, int64_t value) {
    FToken *token = malloc(sizeof(FToken));
    token->type = TOKEN_INTEGER;

    token->str = str;
    token->value.integer = value;

    token->line = line;
    token->pos = pos;

    return token;
}

FToken *CreateTokenFromReal(size_t line, size_t pos, FString *str, double value) {
    FToken *token = malloc(sizeof(FToken));
    token->type = TOKEN_REAL;

    token->str = str;
    token->value.real = value;

    token->line = line;
    token->pos = pos;

    return token;
}

FToken *CreateTokenFromString(size_t line, size_t pos, FString *string) {
    FToken *token = malloc(sizeof(FToken));
    token->type = TOKEN_STRING;

    token->str = CreateString(string->data);
    token->value.integer = 0;

    token->line = line;
    token->pos = pos;

    return token;
}

void FreeToken(FToken *token) {
    FreeString(token->str);
    free(token);
}

ETokenType GetTokenType(FToken *token) {
    if (token == NULL) {
        return TOKEN_UNKNOWN;
    }

    return token->type;
}

int64_t GetTokenValueAsInteger(FToken *token) {
    if (token == NULL || token->type != TOKEN_INTEGER) {
        // TODO:
        return 0;
    }

    return token->value.integer;
}

double GetTokenValueAsReal(FToken *token) {
    if (token == NULL || token->type != TOKEN_REAL) {
        // TODO:
        return 0;
    }

    return token->value.real;
}

u16 *GetTokenValueAsCString(FToken *token) {
    if (token == NULL || token->str == NULL) {
        // TODO:
        return U16("");
    }

    return token->str->data;
}
