#ifndef BTASM_H
#define BTASM_H
/**********************************
 * btasm.h
 * Header for main compiler source file
 * 4/6/12 - J. MacMillan
 * ********************************/


//Node in the syntax tree 
typedef struct node {
    int nodeType;
    int intVal;
    char *strVal;
    int nops;
    struct node **children;
} node;


#endif
