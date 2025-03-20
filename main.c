#include "ast.h"
#include "tokenizer.h"

#include <stdlib.h>
#include <stdio.h>

// void printTokenType(TokenType tokentype) {
//     switch(tokentype) {
//         case 0:
//             printf("PLUS");
//             break;
//         case 1:
//             printf("MINUS");
//             break;
//         case 2:
//             printf("MULTIPLY");
//             break;
//         case 3:
//             printf("DIVIDE");
//             break;
//         case 4:
//             printf("EXPONENT");
//             break;
//         case 5:
//             printf("LPAREN");
//             break;
//         case 6:
//             printf("RPAREN");
//             break;
//         case 7:
//             printf("NUMBER");
//             break;
//     }

// }


int main() {
    Token* tokens[64] = {};
    Token** tokenPointer = tokens;

    char input[] = "(22-12)^(400/200)\0";
    char* inputPointer = input;

    // Token tokens[64] = {};

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

    Literal* solved = (Literal*)solve(node);

    printf("\n%d\n", solved->num);

    for(int i = 0; i < 64; i++) {
        if(tokens[i] != NULL)
            free(tokens[i]);
    }
}