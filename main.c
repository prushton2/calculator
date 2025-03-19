#include "ast.h"
#include "tokenizer.h"

#include <stdlib.h>
#include <stdio.h>

int main() {
    Token* tokens[64] = {};
    Token** tokenPointer = tokens;

    char input[] = "3+12*2\0";   
    char* inputPointer = input;

    // Token tokens[64] = {};

    for(int i = 0; i < 64; i++) {
        Token* t = parseNextToken(&inputPointer);
        if(t == NULL) {
            break;
        }
        tokens[i] = t;
    }

    for(int i = 0; i < 64; i++) {
        if(tokens[i] == NULL) {
            break;
        }
        switch(tokens[i]->tokenType) {
            case 0:
                printf("PLUS");
                break;
            case 1:
                printf("MINUS");
                break;
            case 2:
                printf("MULTIPLY");
                break;
            case 3:
                printf("DIVIDE");
                break;
            case 4:
                printf("EXPONENT");
                break;
            case 5:
                printf("LPAREN");
                break;
            case 6:
                printf("RPAREN");
                break;
            case 7:
                printf("NUMBER");
                break;
        }

        printf(":   %d\n", tokens[i]->value);
    }

    void* node = NULL;
    node = expr(NULL, &tokenPointer);
    // traverse(node);
    // Literal* solved = (Literal*)solve(node);

    // printf("= %d\n", solved->num);


    for(int i = 0; i < 64; i++) {
        if(tokens[i] != NULL)
            free(tokens[i]);
    }
}