#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>



Token* eat(Token*** tokenPointer) {
    Token* currentChar = **tokenPointer;
    (*tokenPointer)++;  // Move the pointer to the next character
    return currentChar;
}


void* literal(Token*** tokenPointer) {
    printf("literal: %d\n", (**tokenPointer)->tokenType);

    Token* token = **tokenPointer;

    // printf("literal: %c\n", **tokenPointer);

    if(token->tokenType == LPAREN) {
        eat(tokenPointer);
        void* node = NULL;
        // printf("Entering parentheses\n");
        node = expr(node, tokenPointer);
        
        if((**tokenPointer)->tokenType == RPAREN) {
            eat(tokenPointer);
        }
        // printf("Leaving parentheses\n");
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
    printf("exponent: %d\n", (**tokenPointer)->tokenType);

    node = literal(tokenPointer);

    while((**tokenPointer)->tokenType == EXPONENT) {
        Token* token = eat(tokenPointer);
        Op* op = (Op*)malloc(sizeof(Op));

        op->left = node;
        op->op = token->tokenType;
        op->right = literal(tokenPointer);

        node = op;
    }

    return node;
}

void* term(void* node, Token*** tokenPointer) {
    printf("term: %d\n", (**tokenPointer)->tokenType);
    
    node = exponent(node, tokenPointer);

    while((**tokenPointer)->tokenType = MULTIPLY || (**tokenPointer)->tokenType == DIVIDE) {
        Token* token = eat(tokenPointer);
        Op* op = (Op*)malloc(sizeof(Op));

        op->optype = TERM;
        op->left = node;
        op->op = token->tokenType;
        op->right = exponent(node, tokenPointer);

        node = op;
    }

    return node;
}

void* expr(void* node, Token*** tokenPointer) {
    printf("expr: %d\n", (**tokenPointer)->tokenType);
    
    node = term(node, tokenPointer);

    while((**tokenPointer)->tokenType == PLUS || (**tokenPointer)->tokenType == MINUS) {
        Token* token = eat(tokenPointer);
        Op* op = (Op*)malloc(sizeof(Op));

        op->optype = EXPR;
        op->left = node;
        op->op = token->tokenType;
        op->right = term(node, tokenPointer);

        node = op;
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
        case '+':
            result = lvalue + rvalue;
            break;
        case '-':
            result = lvalue - rvalue;
            break;
        case '*':
            result = lvalue * rvalue;
            break;
        case '/':
            result = lvalue / rvalue;
            break;
        case '^':
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
    printf("%c ", opNode->op);
    traverse(opNode->right);
}

// int main() {
//     char tokens[] = "1+3^2+1";
//     char *tokenPointer = tokens;

//     void* node = NULL;

//     node = expr(node, &tokenPointer);

//     traverse(node);

//     Literal* solved = (Literal*)solve(node);

//     printf("= %d\n", solved->num);

//     free(solved);

// }