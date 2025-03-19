#pragma once
#include "tokenizer.h"

typedef enum {
    EXPR,
    TERM,
    LITERAL
} OPTYPE;

typedef struct {
    OPTYPE optype;
    void* left;
    TokenType op;
    void* right;
} Op;

typedef struct {
    OPTYPE optype;
    int num;
} Literal;

Token* eat(Token*** tokenPointer);
void* literal(Token*** tokenPointer);
void* exponent(void* node, Token*** tokenPointer);
void* term(void* node, Token*** tokenPointer);
void* expr(void* node, Token*** tokenPointer);
void* solve(void* node);
void traverse(void* node);