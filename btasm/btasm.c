/************************************
 * btasm.c - BTASM main source file *
 * J. MacMillan - 4/6/12            *
 ***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


#include "btasm.h"
#include "y.tab.h"
#include "map.h"
#include "graph.h"


#define die(x)  exit(fprintf(stderr, "%s", x));

//Maps for the compiler.  The bytecode only uses integers to
//reference variables, functions, resources and states.  This
//maps the identifiers into integers which will be used by the
//compiler.
extern map vmap; //Variables
extern map fmap; //Functions
extern int *rmap; //Resources
extern map smap; //States

//Syntax tree
extern node *stree;

//Lexer source file
extern FILE *yyin;

//Global copies of the arguments -- used for argument processing.
int g_argc;
char **g_argv;

//Return the next item in the argv array
char *nextOpt();


int main(int argc, char ** argv) {
    
    g_argv = argv;
    g_argc = argc;
     
    int i; 

    //Initialize the maps for the parser/compiler
    vmap = create_map();    //Variables
    fmap = create_map();    //Functions
    rmap = (int *) malloc(sizeof(int)*RES_COUNT);    //Resources
    for (i=0; i<RES_COUNT;i++)
        rmap[i] = -1;
    smap = create_map();
  
    //hack - assume that the last listed file is the source file
    yyin = fopen(argv[argc-1], "r");
    if (argc < 2 || !yyin) {
        die("btasm [-g <fname>] [-td] <source file>\n");
    } 
    
    //Parse the file.  
    if(yyparse())
       die("btasm: Parsing failed"); 


    //Fix the maps
    reverse_map(vmap);
    reverse_map(fmap);
    reverse_map(smap);
    reverse_imap(rmap);

    //Process the "action" arguments
    char *arg;

    while (arg = nextOpt()) {

        //-g <fname> (Output dot graph to <fname>)
        if (!strcmp("-g", arg)) {
            char *fname = nextOpt();
            FILE *f = fopen(fname,"w");
            if (!f) {
                fprintf(stderr, "btasm: cannot open file");
                die(fname);
            }

            fprintf(f, "digraph syntax_tree {\n");
            graph(stree, f);
            fprintf(f, "}");

            fclose(f);
        //-td (Dump tables)
        } else if (!strcmp("-td", arg)) {
            printf("Variable table:\n-----------------------------\n");
            dump_map(vmap);
            printf("\n\nFunction table:\n-----------------------------\n");
            dump_map(fmap);
            printf("\nResource table:\n-----------------------------\nRes. | Location\n");
            int i;
            for (i=0; i<RES_COUNT; i++) {
                printf("%5d|%5d\n", i, rmap[i]);
            }
        //-1 (run parse stage 1)
        } else if (!strcmp("-1", arg)) {
            parse1(stree);
        }

    }

    return 0;
}

char *nextOpt()
{
    static int av_idx = 1;
    return (av_idx < g_argc) ? g_argv[av_idx++] : NULL;
}

void free_tree(node *n)
{
    int i;
    for (i=0; i < n->nops; i++) {
        free_tree(n);
    }
    
    if (n->strVal)
        free(n->strVal);
    
    free(n);
    return;
}

//Convert all IDs to the associated numbers.  Die if an ID that does
//not exist is found.
void parse1(node *n) 
{
    int i;
    
    map m = vmap;

    if (n->nodeType == STATE || n->nodeType == GOTO)
        m = smap;
    else if (n->nodeType == FUN || n->nodeType == CALL)
        m = fmap;

    for (i=0; i < n->nops; i++) {
        if (n->children[i]->nodeType == ID) {
            int vn = lookup_map(m, n->children[i]->strVal);
            
            //No ID by that name in the namespace table
            if (vn == -1) {
                char *namespace;
                switch (n->nodeType) {
                    case FUN:
                    case CALL:   namespace = "function"; break;
                    case STATE:
                    case GOTO:  namespace = "state";    break;
                    default:    namespace = "variable"; break;
                }
                exit(fprintf(stderr, 
                    "Parse error: %s does not exist in %s namespace",
                    n->children[i]->strVal, namespace));
            }

            node *new = int_node(vn);
            free_tree(n->children[i]);
            n->children[i] = new;
        } else if (n->children[i]->nodeType != INT) {
            parse1(n->children[i]);
        }
    }
}
            
node *int_node(int i)
{
    return cr_node(INT, 1, i);
}

node *id_node(char *s)
{
    return cr_node(ID, 1, strdup(s));
}

node *cr_node(int type, int nops, ...) {
    
    va_list vl;
    
    node *n;

    if ((n=malloc(sizeof(node))) == NULL)
        yyerror("Out of memory");


    n->nops = 0;
    n->children = NULL;
    n->nodeType = type;
    
    va_start(vl, nops);

    //Integer
    if (type == INT) {
        n->intVal = va_arg(vl, int);
        return n;
    }
   
    //Identifier 
    n->strVal = NULL;
    if (type == ID) {
        n->strVal = strdup(va_arg(vl, char *));
        return n;
    }
    

    n->nops = nops;
    if ( (n->children = malloc(nops * sizeof(node *))) == NULL )
        yyerror("Out of memory");

    //Add the proper number of children
    int i=0;
    for (i=0;i<nops;i++) {
        n->children[i] = va_arg(vl, node *);
    }

    va_end(vl);
    return n; 

}

void reverse_imap(int *m)
{
    int temp[RES_COUNT];
    int max = 0;
    int i;

    for (i=0; i<RES_COUNT; i++) {
        if (m[i] >= 0)
            temp[m[i]] = i;
        if (m[i] > max) 
            max = m[i];
    }

    for (i=0; i<=max; i++) {
        m[temp[max-i]] = i;
    }
}
