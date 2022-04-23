﻿#include "Parser.h"

#include "Utility/Error.h"

#define CHECK(x, t) if(!x) { FreeNode((FBaseNode*) node); node = NULL; if (t != NULL) { FreeToken(t); t = NULL; } return NULL; }
#define NULL_CHECK(x, t) if (x == NULL) { FreeNode(node); node = NULL; FreeToken(t); t = NULL; return NULL; }

#define ERROR(ERRNO, ...) CompileError(ERRNO, parser->source->data, parser->token->line, parser->token->pos, __VA_ARGS__)

static bool eat(FParser *parser, char type);
static FBaseNode *program(FParser *parser);
static FBaseNode *compound(FParser *parser);
static FBaseNode *statement(FParser *parser);
static FBaseNode *assignStatement(FParser *parser);
static FBaseNode *variable(FParser *parser);
static FBaseNode *factor(FParser *parser);
static FBaseNode *term(FParser *parser);
static FBaseNode *expr(FParser *parser);

//FParser *CreateParser(FLexer *lexer) {
//    FParser *parser = malloc(sizeof(FParser));
//
//    parser->lexer = lexer;
//    parser->token = GetNextToken(parser->lexer);
//
//    return parser;
//}

FParser *CreateParserFromMemory(u16 *source) {
    FParser *parser = malloc(sizeof(FParser));

    parser->source = CreateString(U16("__inline_source"));
    parser->lexer = CreateLexer(source);
    parser->token = GetNextToken(parser->lexer);

    return parser;
}

FParser *CreateParserFromFile(u16 *source) {
    FParser *parser = malloc(sizeof(FParser));

    parser->source = CreateString(source);
    parser->lexer = CreateLexer(source);
    parser->token = GetNextToken(parser->lexer);

    return parser;
}

void FreeParser(FParser *parser) {
    if (parser == NULL) {
        return;
    }

    FreeLexer(parser->lexer);

    free(parser);
}

FBaseNode *Parse(FParser *parser) {
    return program(parser);
}

static bool eat(FParser *parser, char type) {
    if (parser->token->type == type) {
        parser->token = GetNextToken(parser->lexer);
        return (parser->token != NULL);
    }
    ERROR(ERROR_INVALID_SYNTAX, parser->token->str->data);
    return false;
}

static bool eatAndFree(FParser *parser, char type) {
    if (parser->token->type == type) {
        FreeToken(parser->token);
        parser->token = GetNextToken(parser->lexer);
        return (parser->token != NULL);
    }
    FreeToken(parser->token);
    parser->token = NULL;

    ERROR(ERROR_INVALID_SYNTAX, parser->token->str->data);
    return false;
}

static FBaseNode *program(FParser *parser) {
    FBaseNode *result = compound(parser);

    // TODO?

    return result;
}

static FBaseNode *compound(FParser *parser) {
    FToken *token = CreateToken(TOKEN_UNKNOWN, parser->token->line, parser->token->pos, U16(""));
    FCompoundNode *compound = CreateCompoundNode(parser->source, token);

    // eat begin
    FBaseNode *node = statement(parser);
    if (node == NULL) {
        goto failed;
    }

    AppendASTNode(compound, node);

    while (parser->token->type == TOKEN_EOL) {
        if (!eat(parser, TOKEN_EOL)) {
            break;
        }

        node = statement(parser);
        if (node == NULL) {
            goto failed;
        }

        AppendASTNode(compound, node);
    }

    if (parser->token->type == TOKEN_IDENTIFIER) {
        ERROR(ERROR_INVALID_TOKEN, parser->token->str->data);
        goto failed;
    }

    goto success;

failed:
    FreeCompoundNode(compound);
    compound = NULL;

success:
    return (FBaseNode*) compound;
}

static FBaseNode *statement(FParser *parser) {
    FBaseNode *node = NULL;

    if (parser->token->type == TOKEN_LPAREN) {
        eat(parser, TOKEN_LPAREN);
        node = expr(parser);
        if (!eat(parser, TOKEN_LPAREN)) {
            return NULL;
        }

        CHECK(eat(parser, TOKEN_RPAREN), parser->token)
        return node;
    }
    if (parser->token->type == TOKEN_IDENTIFIER) {
        return assignStatement(parser);
    }

    return (FBaseNode*) CreateEmptyNode(parser->source, parser->token);
}

static FBaseNode *assignStatement(FParser *parser) {
    FBaseNode *lvalue = variable(parser);
    FToken *token = parser->token;

    if (!eat(parser, TOKEN_ASSIGN)) {
        ERROR(ERROR_INVALID_TOKEN);
        FreeNode(lvalue);

        return NULL;
    }

    FBaseNode *rvalue = expr(parser);
    FBaseNode *assignOp = (FBaseNode*) CreateAssignOpNode(parser->source, token, lvalue, rvalue);
    return (FBaseNode*) CreateExprStmtNode(parser->source, parser->token, assignOp);
}

static FBaseNode *variable(FParser *parser) {
    FVarNode *var = CreateVarNode(parser->source, parser->token);
    eat(parser, TOKEN_IDENTIFIER);
    return (FBaseNode*) var;
}

static FBaseNode *factor(FParser *parser) {
    FToken *token = parser->token;
    FBaseNode *node = NULL;
    if (token->type == TOKEN_INTEGER) {
        CHECK(eat(parser, TOKEN_INTEGER), token)
        return (FBaseNode*) CreateIntegerNode(parser->source, token, token->value.integer);
    }
    if (token->type == TOKEN_REAL) {
        CHECK(eat(parser, TOKEN_REAL), token)
        return (FBaseNode*) CreateRealNode(parser->source, token, token->value.real);
    }
    if (token->type == TOKEN_STRING) {
        CHECK(eat(parser, TOKEN_STRING), token)
        return (FBaseNode*) CreateStringNode(parser->source, token, token->str);
    }
    if (token->type == TOKEN_LPAREN) {
        CHECK(eat(parser, TOKEN_LPAREN), token)
        FreeToken(token);
        token = NULL;

        node = expr(parser);
        NULL_CHECK(node, token)
        CHECK(eatAndFree(parser, TOKEN_RPAREN), token)
        return node;
    }
    if (token->type == TOKEN_MINUS) {
        CHECK(eat(parser, TOKEN_MINUS), token)
        node = (FBaseNode*) CreateUnaryOpNode(parser->source, token, factor(parser));
        NULL_CHECK(node, token)
        return node;
    }
    if (token->type == TOKEN_IDENTIFIER) {
        CHECK(eat(parser, TOKEN_IDENTIFIER), token)
        node = (FBaseNode*) CreateVarNode(parser->source, token);
        NULL_CHECK(node, token)
        return node;
    }

    return NULL;
}

static FBaseNode *term(FParser *parser) {
    FBaseNode *node = factor(parser);
    NULL_CHECK(node, parser->token)

    while (parser->token->type == TOKEN_ASTERISK || parser->token->type == TOKEN_SLASH) {
        FToken *token = parser->token;
        if (token->type == TOKEN_ASTERISK) {
            CHECK(eat(parser, TOKEN_ASTERISK), token)
        } else {
            CHECK(eat(parser, TOKEN_SLASH), token)
        }
        FBaseNode *temp = factor(parser);
        NULL_CHECK(temp, token)

        node = (FBaseNode*) CreateBinOpNode(parser->source, token, node, temp);
    }

    return node;
}

static FBaseNode *expr(FParser *parser) {
    FBaseNode *node = term(parser);
    NULL_CHECK(node, parser->token)

    while (parser->token->type == TOKEN_PLUS || parser->token->type == TOKEN_MINUS) {
        FToken *token = parser->token;
        if (token->type == TOKEN_PLUS) {
            CHECK(eat(parser, TOKEN_PLUS), token)
        } else {
            CHECK(eat(parser, TOKEN_MINUS), token)
        }
        FBaseNode *temp = term(parser);
        NULL_CHECK(temp, token)

        node = (FBaseNode*) CreateBinOpNode(parser->source, token, node, temp);
    }

    return node;
}
