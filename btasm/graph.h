#ifndef BTASM_GRAPH_H
#define BTASM_GRAPH H
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

#include "btasm.h"
#include <stdio.h>

/**
 * Create a syntax tree for the graph rooted at n.
 * @param n The root node of the tree
 * @return A unique identifier for the node n.  These are used by \
 *          recursive calls of graph to create the graph.
 */
char *graph(node *n, FILE *f);




#endif
