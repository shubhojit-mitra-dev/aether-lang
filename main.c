#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef enum {
  INT,
  KEYWORD,
  SEPARATOR,
  NULL_TOKEN,
} TokenType;

typedef struct {
  TokenType type;
  char* value;
} Token;

void print_token(Token* token) {
  printf("TOKEN VALUE: %s\n", token->value);
  if (token->type == INT) {
    printf("TOKEN TYPE: INT\n");
  }
  if (token->type == KEYWORD) {
    printf("TOKEN TYPE: KEYWORD\n");
  }
  if (token->type == SEPARATOR) {
    printf("TOKEN TYPE: SEPARATOR\n");
  }
}

Token* generate_keyword(char curr, FILE *file) {
  Token *token = malloc(sizeof(Token));
  char *keyword = malloc(sizeof(char)*4);
  int keyword_idx = 0;
  while (isalpha(curr) && curr != EOF) {
    keyword[keyword_idx++] = curr;
    curr = fgetc(file);
  }
  
  keyword[keyword_idx] = '\0';
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
  
  value[value_idx] = '\0';
  if (curr != EOF) ungetc(curr, file);
  token->value = value;
  return (token);
}

Token* generate_separator(char curr) {
  Token* token = malloc(sizeof(Token));
  token->type = SEPARATOR;
  char* value = malloc(2);
  value[0] = curr;
  value[1] = '\0';
  token->value = value;
  return (token);
}

Token* lexer(FILE *file) {
  Token* tokens = malloc(sizeof(Token)*1024);
  size_t token_idx = 0;
  char curr;
  while ((curr = fgetc(file)) != EOF) {
    if (isalpha(curr)) {
      tokens[token_idx++] = *generate_keyword(curr, file);
    } else if (isdigit(curr)) {
      tokens[token_idx++] = *generate_number(curr, file);
    } else if (curr == ';' || curr == '(' || curr == ')') {
      tokens[token_idx++] = *generate_separator(curr);
    }
  }
  tokens[token_idx].type = NULL_TOKEN;
  fclose(file);
  return tokens;
}

int main() {
  FILE *file;
  file = fopen("test.ae", "r");
  Token* tokens = lexer(file);
  for (size_t i = 0; tokens[i].type != NULL_TOKEN; i++) {
    print_token(&tokens[i]);
  }
  return 0;
}
