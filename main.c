#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
  INT,
  KEYWORD,
  SEPARATOR,
} TokenType;

typedef struct {
  TokenType type;
  char* value;
} Token;

Token* generate_keyword(char curr, FILE *file) {
  Token *token = malloc(sizeof(Token));
  char *keyword = malloc(sizeof(char)*4);
  int keyword_idx = 0;
  while (isalpha(curr) && curr != EOF) {
    keyword[keyword_idx++] = curr;
    curr = fgetc(file);
  }

  if (curr != EOF) ungetc(curr, file);
  if (strcmp(keyword, "exit") == 0) {
    token->type = KEYWORD;
    token->value = "EXIT";
  }
  return (token);
}

Token* generate_number(char curr, FILE *file) {
  Token *token = malloc(sizeof(Token));
  token->type = INT;
  char *value = malloc(sizeof(char)*8);
  int value_idx = 0;
  while (isdigit(curr) && curr != EOF) {
    value[value_idx++] = curr;
    curr = fgetc(file);
  }

  if (curr != EOF) ungetc(curr, file);
  token->value = value;
  return (token);
}

void lexer(FILE *file) {
  char curr;
  while ((curr = fgetc(file)) != EOF) {
    if (isalpha(curr)) {
      Token *token = generate_keyword(curr, file);
     printf("FOUND KEYWORD: %s\n", token->value); 
    } else if (isdigit(curr)) {
      Token *token = generate_number(curr, file);
      printf("FOUND TOKEN VALUE: %s\n", token->value);
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
