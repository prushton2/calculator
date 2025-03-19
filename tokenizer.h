#pragma once

typedef enum {
    PLUS,     // 0
    MINUS,    // 1
    MULTIPLY, // 2
    DIVIDE,   // 3
    EXPONENT, // 4
    LPAREN,   // 5
    RPAREN,   // 6
    NUMBER    // 7
} TokenType;

typedef struct {
    TokenType tokenType;
    int value; //i have both dont @ me
} Token;

Token* parseNextToken(char** inputPointer);