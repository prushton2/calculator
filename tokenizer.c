#include "tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

Token* nullToken() {
    Token* a = (Token*)malloc(sizeof(Token));
    a->tokenType = EXIT;
    a->value = 0;
    return a;
}


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