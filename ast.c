#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printTokenType(TokenType tokentype) {
    switch(tokentype) {
        case PLUS:
            printf("PLUS");
            break;
        case MINUS:
            printf("MINUS");
            break;
        case MULTIPLY:
            printf("MULTIPLY");
            break;
        case DIVIDE:
            printf("DIVIDE");
            break;
        case EXPONENT:
            printf("EXPONENT");
            break;
        case LPAREN:
            printf("LPAREN");
            break;
        case RPAREN:
            printf("RPAREN");
            break;
        case NUMBER:
            printf("NUMBER");
            break;
        case EXIT:
            printf("EXIT");
            break;
    }

}

Token* eat(Token*** tokenPointer) {
    Token* currentChar = **tokenPointer;
    (*tokenPointer)++;  // Move the pointer to the next character
    return currentChar;
}

Token* getToken(Token*** tokenPointer) {
    return **tokenPointer;
}


void* literal(Token*** tokenPointer) {
    Token* token = getToken(tokenPointer);

    if(token->tokenType == LPAREN) {
        eat(tokenPointer);
        void* node = NULL;
        node = expr(node, tokenPointer);
        
        if((**tokenPointer)->tokenType == RPAREN) {
            eat(tokenPointer);
        }
        return node;
    }

    if(token->tokenType == NUMBER) {
        eat(tokenPointer);

        Literal* a = (Literal*)malloc(sizeof(Literal));
        a->optype = LITERAL;
        a->num = token->value;

        return a;
    }

    return NULL;

}

void* exponent(void* node, Token*** tokenPointer) {
    node = literal(tokenPointer);
    Token* token = getToken(tokenPointer);

    while(token->tokenType == EXPONENT) {
        eat(tokenPointer);
        Op* op = (Op*)malloc(sizeof(Op));

        op->left = node;
        op->op = token->tokenType;
        op->right = literal(tokenPointer);

        node = op;
        token = getToken(tokenPointer);
    }

    return node;
}

void* term(void* node, Token*** tokenPointer) {
    node = exponent(node, tokenPointer);
    Token* token = getToken(tokenPointer);

    while(token->tokenType == MULTIPLY || token->tokenType == DIVIDE) {
        eat(tokenPointer);
        Op* op = (Op*)malloc(sizeof(Op));

        op->optype = TERM;
        op->left = node;
        op->op = token->tokenType;
        op->right = exponent(node, tokenPointer);

        node = op;
        token = getToken(tokenPointer);
    }

    return node;
}

void* expr(void* node, Token*** tokenPointer) {
    node = term(node, tokenPointer);
    Token* token = getToken(tokenPointer);

    while(token->tokenType == PLUS || token->tokenType == MINUS) {
        eat(tokenPointer);
        Op* op = (Op*)malloc(sizeof(Op));

        op->optype = EXPR;
        op->left = node;
        op->op = token->tokenType;
        op->right = term(node, tokenPointer);

        node = op;
        token = getToken(tokenPointer);
    }

    return node;
}

void* solve(void* node) {
    Op* opNode = (Op*)node;

    //Since the node is a literal, its already solved
    if(opNode->optype == LITERAL) {
        return node;
    }

    Op* left = (Op*)(opNode->left);
    Op* right = (Op*)(opNode->right);

    //if either side isnt a literal, we are going to solve both sides to ensure they are literals.
    if(left->optype != LITERAL || right->optype != LITERAL ) { 
        opNode->left = solve(opNode->left);
        opNode->right = solve(opNode->right);
    }

    //now both sides are literal, we are going to evaluate the current node
    int lvalue = ((Literal*)(opNode->left))->num;
    int rvalue = ((Literal*)(opNode->right))->num;
    int result;

    switch (opNode->op) {
        case PLUS:
            result = lvalue + rvalue;
            break;
        case MINUS:
            result = lvalue - rvalue;
            break;
        case MULTIPLY:
            result = lvalue * rvalue;
            break;
        case DIVIDE:
            result = lvalue / rvalue;
            break;
        case EXPONENT:
            result = pow(lvalue, rvalue);
            break;
    }

    free(opNode->left);
    free(opNode->right);
    free(opNode);

    Literal* l = (Literal*)malloc(sizeof(Literal));
    l->optype = LITERAL;
    l->num = result;

    return l;
}

void traverse(void* node) {
    if(((Literal*)node)->optype == LITERAL) {
        printf("%d ", ((Literal*)node)->num);
        return;
    }

    Op* opNode = (Op*)node;

    traverse(opNode->left);
    // printf("%c ", opNode->op);
    printTokenType(opNode->op);
    printf(" ");
    traverse(opNode->right);
}