#include "Token.h"

FToken *CreateToken(ETokenType type, u16 *op) {
    FToken *token = malloc(sizeof(FToken));
    token->type = type;
    if (op != NULL) {
        token->op = CreateString(op);
    } else {
        token->op = NULL;
    }

    token->str = NULL;
    token->value.integer = 0;

    return token;
}


FToken* CreateTokenWithString(ETokenType type, u16 *cstr) {
    FToken *token = malloc(sizeof(FToken));
    token->type = type;
    token->op = U16('\0');

    token->str = CreateString(cstr);
    token->value.integer = 0;

    return token;
}

FToken *CreateTokenFromInteger(FString *str, int64_t value) {
    FToken *token = malloc(sizeof(FToken));
    token->type = TOKEN_INTEGER;
    token->op = U16('\0');

    token->str = str;
    token->value.integer = value;

    return token;
}

FToken *CreateTokenFromReal(FString *str, double value) {
    FToken *token = malloc(sizeof(FToken));
    token->type = TOKEN_REAL;
    token->op = U16('\0');

    token->str = str;
    token->value.real = value;

    return token;
}

FToken *CreateTokenFromString(FString *string) {
    FToken *token = malloc(sizeof(FToken));
    token->type = TOKEN_STRING;
    token->op = U16('\0');

    token->str = CreateString(string->data);
    token->value.integer = 0;

    return token;
}

void FreeToken(FToken *token) {
    FreeString(token->op);
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
        return "";
    }

    return token->str->data;
}
