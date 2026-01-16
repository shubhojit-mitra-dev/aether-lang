#include <stdio.h>
#include <stdlib.h>

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

int main() {
  FILE *file;
  file = fopen("test.ae", "r");
  char curr;

  while ((curr = fgetc(file)) != EOF) {
    printf("%c", curr);
  }

  fclose(file);
  return 0;
}
