#ifndef COMPILE_H
#define COMPILE_H

/************************************
 * Compiler - makes the bytecode from
 *  a syntax tree.
 * 4/12/12 - J. MacMillan
 ***********************************/

/**
 * Compile a syntax tree into bytecode
 * /param n The root of the syntax tree to compile
 * /param result Pointer to a string used to return 
 * /returns Length in bytes of all the code compiled by this call to compile
 */
int compile(node *n, char **result);


#endif
