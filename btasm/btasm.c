/************************************
 * btasm.c - BTASM main source file *
 * J. MacMillan - 4/6/12            *
 ***********************************/

#include "btasm.h"
#include "y.tab.h"
#include "map.h"

//Maps for the compiler.  The bytecode only uses integers to
//reference variables, functions, resources and states.  This
//maps the identifiers into integers which will be used by the
//compiler.
extern map vmap; //Variables
extern map fmap; //Functions
extern map rmap; //Resources
extern map smap; //States

int main(int argc, char * argv) {
    
    //Initialize the maps for the parser/compiler
    vmap = create_map();
    fmap = create_map();
    rmap = create_map();
    smap = create_map();
   
    //Parse and compile 
    yyparse();

    return 0;
}
