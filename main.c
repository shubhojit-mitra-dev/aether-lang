#include <stdio.h>
#include "lexer.h"

int main() {
    FILE *file = fopen("test.ae", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    Token* tokens = lexer(file);

    for (size_t i = 0; tokens[i].type != NULL_TOKEN; i++) {
        print_token(&tokens[i]);
    }

    return 0;
}
