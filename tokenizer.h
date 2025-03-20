#pragma once

typedef enum {
    PLUS,     // 0
    MINUS,    // 1
    MULTIPLY, // 2
    DIVIDE,   // 3
    EXPONENT, // 4
    LPAREN,   // 5
    RPAREN,   // 6
    NUMBER,   // 7
    EXIT,     // 8
} TokenType;

typedef struct {
    TokenType tokenType;
    int value; //i have both dont @ me
} Token;

Token* nullToken();
Token* parseNextToken(char** inputPointer);