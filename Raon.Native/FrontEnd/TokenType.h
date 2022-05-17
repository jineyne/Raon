#ifndef __TOKENTYPE_H__
#define __TOKENTYPE_H__

#include "CoreMinimal.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum TokenType {
    TOKEN_IDENTIFIER,
    TOKEN_BOOL,
    TOKEN_INTEGER,
    TOKEN_REAL,
    TOKEN_STRING,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_ASTERISK,
    TOKEN_SLASH,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,

    TOKEN_IF,
    TOKEN_ELSE,

    TOKEN_ASSIGN,

    TOKEN_LT,
    TOKEN_LTE,
    TOKEN_GT,
    TOKEN_GTE,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_EQ,
    TOKEN_NEQ,

    TOKEN_EOL,
    TOKEN_EOF,

    TOKEN_UNKNOWN,
} ETokenType;

#ifdef __cplusplus
}
#endif

#endif //__TOKENTYPE_H__
