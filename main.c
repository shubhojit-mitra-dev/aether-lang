#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
  SEMI,
  OPEN_PAREN,
  CLOSE_PAREN,
} TypeSeparator;

typedef enum {
  EXIT,
} TypeKeyword;

typedef enum {
  INT,
} TypeLiteral;

typedef struct {
  TypeKeyword type;
} TokenKeyword;

typedef struct {
  TypeSeparator type;
} TokenSeparator;

typedef struct {
  TypeLiteral type;
  int value;
} TokenLiteral;

TokenLiteral* generate_number(char curr, FILE *file) {
  TokenLiteral *token = malloc(sizeof(TokenLiteral));
  token->type = INT;
  char *value = malloc(sizeof(char)*8);
  int value_idx = 0;
  while (isdigit(curr) && curr != EOF) {
    value[value_idx++] = curr;
    curr = fgetc(file);
  }
  
  token->value = atoi(value);
  return (token);
}

void lexer(FILE *file) {
  char curr;
  while ((curr = fgetc(file)) != EOF) {
    if (isalpha(curr)) {
      printf("FOUND CHARACTER: %c\n", curr);
    } else if (isdigit(curr)) {
      TokenLiteral *token = generate_number(curr, file);
      printf("FOUND TOKEN VALUE: %d\n", token->value);
    } else if (curr == ';') {
      printf("FOUND SEMICOLON\n");
    } else if (curr == '(') {
      printf("FOUND OPEN PAREN\n");
    } else if (curr == ')') {
      printf("FOUND CLOSE_PAREN\n");
    }
  }
  fclose(file);
}

int main() {
  FILE *file;
  file = fopen("test.ae", "r");
  lexer(file);
  return 0;
}
