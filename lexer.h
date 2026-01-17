#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef enum {
    INT,
    KEYWORD,
    SEPARATOR,
    NULL_TOKEN
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

Token* lexer(FILE *file);
void print_token(Token* token);

#endif
