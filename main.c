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

void print_separator(Token* separator_token, char curr) {
  separator_token->type = SEPARATOR;
  char* value = malloc(2);
  value[0] = curr;
  value[1] = '\0';
  separator_token->value = value;
  print_token(separator_token);
}

void lexer(FILE *file) {
  char curr;
  while ((curr = fgetc(file)) != EOF) {
    if (isalpha(curr)) {
      Token *token = generate_keyword(curr, file);
      print_token(token);
    } else if (isdigit(curr)) {
      Token *token = generate_number(curr, file);
      print_token(token); 
    } else if (curr == ';') {
      Token *semicolon_token = malloc(sizeof(Token));
      print_separator(semicolon_token, curr);
    } else if (curr == '(') {
      Token *open_paren_token = malloc(sizeof(Token));
      print_separator(open_paren_token, curr);
    } else if (curr == ')') {
      Token *close_paren_token = malloc(sizeof(Token));
      print_separator(close_paren_token, curr);
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
