#include "Parser.h"

#include "Utility/Error.h"

#define CHECK(x, t) if(!x) { FreeNode(node); node = NULL; if (t != NULL) { FreeToken(t); t = NULL; } return NULL; }
#define NULL_CHECK(x, t) if (x == NULL) { FreeNode(node); node = NULL; FreeToken(t); t = NULL; return NULL; }

static bool eat(FParser *machine, char type);
static FBaseNode *program(FParser *machine);
static FBaseNode *compound(FParser *machine);
static FBaseNode *statement(FParser *machine);
static FBaseNode *assignStatement(FParser *machine);
static FBaseNode *variable(FParser *machine);
static FBaseNode *factor(FParser *machine);
static FBaseNode *term(FParser *machine);
static FBaseNode *expr(FParser *machine);

FParser *CreateParser(FLexer *lexer) {
    FParser *parser = malloc(sizeof(FParser));

    parser->lexer = lexer;
    parser->token = GetNextToken(parser->lexer);

    return parser;
}

void FreeParser(FParser *parser) {
    free(parser);
}

FBaseNode *Parse(FParser *parser) {
    FBaseNode *result = compound(parser);

    if (parser->token->type != TOKEN_EOF) {
        PushError(ERROR_INVALID_EOF);
    }

    return result;
}

static bool eat(FParser *machine, char type) {
    if (machine->token->type == type) {
        machine->token = GetNextToken(machine->lexer);
        return (machine->token != NULL);
    } else {
        PushError(ERROR_INVALID_SYNTAX);
        return false;
    }
}

static bool eatAndFree(FParser *machine, char type) {
    if (machine->token->type == type) {
        FreeToken(machine->token);
        machine->token = GetNextToken(machine->lexer);
        return (machine->token != NULL);
    } else {
        FreeToken(machine->token);
        machine->token = NULL;

        PushError(ERROR_INVALID_SYNTAX);
        return false;
    }
}

static FBaseNode *program(FParser *machine) {
    FBaseNode *result = compound(machine);

    if (machine->token != NULL && machine->token->type != TOKEN_EOF) {
        PushError(ERROR_INVALID_EOF);
    }

    FreeToken(machine->token);
    return result;
}

static FBaseNode *compound(FParser *machine) {
    FCompoundNode *compound = CreateCompoundNode();
    // eat begin
    FBaseNode *node = statement(machine);
    if (node == NULL) {
        goto failed;
    }

    AppendASTNode(compound, node);

    while (machine->token->type == TOKEN_EOL) {
        if (!eat(machine, TOKEN_EOL)) {
            break;
        }

        FBaseNode *node = statement(machine);
        if (node == NULL) {
            goto failed;
        }

        AppendASTNode(compound, node);
    }

    if (machine->token->type == TOKEN_IDENTIFIER) {
        // TODO: set error;
        // AddError();
        goto failed;
    }

    goto success;

failed:
    FreeCompoundNode(compound);
    compound = NULL;

success:
    return compound;
}

static FBaseNode *statement(FParser *machine) {
    bool isExistParam = false;
    FBaseNode *node = NULL;

    if (machine->token->type == TOKEN_LPAREN) {
        eat(machine, TOKEN_LPAREN);
        node = expr(machine);
        if (!eat(machine, TOKEN_LPAREN)) {
            return NULL;
        }


        CHECK(eat(machine, TOKEN_RPAREN), node);
    } else if (machine->token->type == TOKEN_IDENTIFIER) {
        return assignStatement(machine);
    } else {
        return CreateEmptyNode();
    }
}

static FBaseNode *assignStatement(FParser *machine) {
    FBaseNode *lvalue = variable(machine);
    FToken *token = machine->token;

    if (!eat(machine, TOKEN_ASSIGN)) {
        PushError(ERROR_INVALID_TOKEN);
        FreeToken(lvalue);

        return NULL;
    }

    FBaseNode *rvalue = expr(machine);
    FBaseNode *assignOp = CreateAssignOpNode(token, lvalue, rvalue);
    return CreateExprStmtNode(assignOp);
}

static FBaseNode *variable(FParser *machine) {
    FVarNode *var = CreateVarNode(machine->token);
    eat(machine, TOKEN_IDENTIFIER);
    return var;
}

static FBaseNode *factor(FParser *machine) {
    FToken *token = machine->token;
    FBaseNode *node = NULL;
    if (token->type == TOKEN_INTEGER) {
        CHECK(eat(machine, TOKEN_INTEGER), token);
        return CreateIntegerNode(token, token->value.integer);
    } else if (token->type == TOKEN_REAL) {
        CHECK(eat(machine, TOKEN_REAL), token);
        return CreateRealNode(token, token->value.real);
    } else if (token->type == TOKEN_STRING) {
        CHECK(eat(machine, TOKEN_STRING), token);
        return CreateStringNode(token, token->str);
    } else if (token->type == TOKEN_LPAREN) {
        CHECK(eat(machine, TOKEN_LPAREN), token);
        FreeToken(token);
        token = NULL;

        node = expr(machine);
        NULL_CHECK(node, token);
        CHECK(eatAndFree(machine, TOKEN_RPAREN), token);
        return node;
    } else if (token->type == TOKEN_MINUS) {
        CHECK(eat(machine, TOKEN_MINUS), token);
        node = CreateUnaryOpNode(token, factor(machine));
        NULL_CHECK(node, token);
        return node;
    } else if (token->type == TOKEN_IDENTIFIER) {
        CHECK(eat(machine, TOKEN_IDENTIFIER), token);
        node = CreateVarNode(token);
        NULL_CHECK(node, token);
        return node;
    }

    return NULL;
}

static FBaseNode *term(FParser *machine) {
    FBaseNode *node = factor(machine);
    NULL_CHECK(node, machine->token);

    while (machine->token->type == TOKEN_ASTERISK || machine->token->type == TOKEN_SLASH) {
        FToken *token = machine->token;
        if (token->type == TOKEN_ASTERISK) {
            CHECK(eat(machine, TOKEN_ASTERISK), token);
        } else {
            CHECK(eat(machine, TOKEN_SLASH), token);
        }
        FBaseNode *temp = factor(machine);
        NULL_CHECK(temp, token);

        node = CreateBinOpNode(token, node, temp);
    }

    return node;
}

static FBaseNode *expr(FParser *machine) {
    FBaseNode *node = term(machine);
    NULL_CHECK(node, machine->token);

    while (machine->token->type == TOKEN_PLUS || machine->token->type == TOKEN_MINUS) {
        FToken *token = machine->token;
        if (token->type == TOKEN_PLUS) {
            CHECK(eat(machine, TOKEN_PLUS), token);
        } else {
            CHECK(eat(machine, TOKEN_MINUS), token);
        }
        FBaseNode *temp = term(machine);
        NULL_CHECK(temp, token);

        node = CreateBinOpNode(token, node, temp);
    }

    return node;
}
