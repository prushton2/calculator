#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>



Token* parseNextToken(char** inputPointer) {
    if(**inputPointer == '\0') {
        return NULL;
    }

    Token* next = (Token*)malloc(sizeof(Token));
    next->value = 0;
    char token = **inputPointer;
    
    while(isdigit(token) && **inputPointer != '\0') {
        next->tokenType = NUMBER;
        next->value *= 10;
        next->value += atoi(&token);
        (*inputPointer)++;
        token = **inputPointer;
    }

    if(next->tokenType == NUMBER) {
        return next;
    }
    
    switch(token) {
        case '+':
            next->tokenType = PLUS;
            break;

        case '-':
            next->tokenType = MINUS;
            break;

        case '*':
            next->tokenType = MULTIPLY;
            break;
        
        case '/':
            next->tokenType = DIVIDE;
            break;
        
        case '(':
            next->tokenType = LPAREN;
            break;
        
        case ')':
            next->tokenType = RPAREN;
            break;
        
        case '^':
            next->tokenType = EXPONENT;
            break;
        
    }
    (*inputPointer)++;
    return next;
}

// int main() {
//     char input[] = "(32+12)*2^(4/2)\0";
//     char* inputPointer = input;

//     Token tokens[64] = {};

//     for(int i = 0; i < 32; i++) {
//         Token* t = parseNextToken(&inputPointer);

//         if(t == NULL) {
//             break;
//         }

//         switch(t->tokenType) {
//             case 0:
//                 printf("PLUS");
//                 break;
//             case 1:
//                 printf("MINUS");
//                 break;
//             case 2:
//                 printf("MULTIPLY");
//                 break;
//             case 3:
//                 printf("DIVIDE");
//                 break;
//             case 4:
//                 printf("EXPONENT");
//                 break;
//             case 5:
//                 printf("LPAREN");
//                 break;
//             case 6:
//                 printf("RPAREN");
//                 break;
//             case 7:
//                 printf("NUMBER");
//                 break;
//         }

//         printf(":   %d\n", t->value);

//         free(t);
//     }
// }