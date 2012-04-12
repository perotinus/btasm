/*****************************************************************
 * BTASM syntax-tree graph creator
 *
 * Used by the parser to create a GraphViz-format syntax tree
 * For debugging purposes.
 *
 * 4/7/12 - J. MacMillan
 *
 *
 *****************************************************************/

#include "graph.h"
#include "y.tab.h"
#include "toktab.h"
#include <stdlib.h>

/**
 * Generate a unique identifier for the graph.
 * @return Unique identifier string
 * @todo Will fail catastrophically when called to create \
 *      more than 100,000 nodes
 */
char *gen_node();


//Make the syntax tree graph
char *graph(node *n, FILE *fp)
{
    
    char *dotName = gen_node();
    
    filltoktab(); 


    switch (n->nodeType) {
        
        case INT:   
                    fprintf(fp, "%s [label=\"INT_%d\", shape=box]\n", \
                            dotName, n->intVal);
                    break; 
        case LONG_INT:   
                    fprintf(fp, "%s [label=\"LONGINT_%d\", shape=box]\n", \
                            dotName, n->intVal);
                    break; 
        case ID:    
                    fprintf(fp, "%s [label=\"ID_%s\", shape=diamond]\n", \
                            dotName, n->strVal);
                    break;
        default:    0; 
                    int i=0;
                    for (i=0; i<n->nops; i++) {
                        char *cn = graph(n->children[i], fp);
                        fprintf(fp, "%s -> %s\n", dotName, cn);
                    }
                    fprintf(fp, "%s [label=\"%s\"]\n", dotName, 
                                                toktab[n->nodeType]); 
                    break;
    
    }

    free(dotName);

    return dotName;

}

char *gen_node() 
{
    static int curr=0;
    
    //BAD - can only support 100,000 nodes!
    char *buf = malloc(5*sizeof(char));
    sprintf(buf, "%d", curr++);
    return buf;
}
