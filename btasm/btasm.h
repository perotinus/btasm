//Node 
typedef struct node {
    int nodeType;
    int intVal;
    char *strVal;
    int nops;
    struct node **children;
} node;


enum {EQ, NEQ, GT};
