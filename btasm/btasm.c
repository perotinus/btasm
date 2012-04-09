/************************************
 * btasm.c - BTASM main source file *
 * J. MacMillan - 4/6/12            *
 ***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
extern map rmap; //Resources
extern map smap; //States

//Syntax tree
extern node *stree;

//Lexer source file
extern FILE *yyin;


//Return the next item in the argv array
char *nextOpt();

int g_argc;
char **g_argv;


int main(int argc, char ** argv) {
    
    g_argv = argv;
    g_argc = argc;
     
    //Initialize the maps for the parser/compiler
    vmap = create_map();
    fmap = create_map();
    rmap = create_map();
    smap = create_map();
  
    //hack - assume that the last listed file is the source file
    yyin = fopen(argv[argc-1], "r");
    if (argc < 2 || !yyin) {
        die("btasm [-g <fname>] <source file>");
    } 
    
    //Parse the file.  
    if(yyparse())
       die("btasm: Parsing failed"); 


    //Process the "action" arguments
    char *arg = nextOpt();

    //-g <fname>
    if (!strcmp("-g",arg)) {
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
    }

    return 0;
}

char *nextOpt()
{
    static int av_idx = 1;
    return (av_idx < g_argc) ? g_argv[av_idx++] : NULL;
}
