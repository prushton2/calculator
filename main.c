#include "ast.h"
#include "tokenizer.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
    Token* tokens[64] = {};
    Token** tokenPointer = tokens;

    char input[] = "(22-12)^(400/200)\0";
    char* inputPointer = input;

    for(int i = 0; i < 64; i++) {
        Token* t = parseNextToken(&inputPointer);
        if(t == NULL) {
            tokens[i] = nullToken();
            break;
        }
        tokens[i] = t;
    }

    void* node = NULL;
    node = expr(NULL, &tokenPointer);

    traverse(node);

    Literal* solved = (Literal*)solve(node); //solve eats the node and frees it up

    printf("\n%d\n", solved->num);

    free(solved);
    for(int i = 0; i < 64; i++) {
        if(tokens[i] != NULL)
            free(tokens[i]);
    }
}