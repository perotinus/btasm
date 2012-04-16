/************************************
 * Compiler - makes the bytecode from
 *  a syntax tree.
 * 4/12/12 - J. MacMillan
 ***********************************/

#include "btasm.h"
#include "tables/instrtab.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>




int compile(node *n, char **result)
{
    fillinstrtab();
    return _compile(n, result);
}
    
// Compile a syntax tree into bytecode
int _compile(node *n, char **result) 
{

    //Length of the children of this node
    int child_lengths[10];
    memset(child_lengths,0,10*sizeof(int));

    //Code returned by the children
    char *child_code[10];
    memset(child_code,0,10*sizeof(char *));
    
    int ntype = n->nodeType;
    int nops = n->nops;
    
    //-----------------------
    //Determine the number of bytes used by this command
    //-----------------------

    int cmd_length=0; 

    //Is is not a SEQ node?
    if (ntype != SEQ && ntype != EVENT)
        cmd_length++;

    //Does it have a length argument?
    if (has_len_arg(ntype))
        cmd_length++;

    //Is it an IF command with two length arguments?
    if (ntype == IF)
        cmd_length++;

    //Is it a SET command with an immediate value?
    //if (ntype == SET && n->children[1]->intVal == 1)
    //    cmd_length++;

    //Is if an IF command with an immediate value?
    //if (ntype == IF && n->children[1]->intVal == 1)
    //    cmd_length++;

    //Is it a STATE command with a LONG_INT length?
    if (ntype == STATE)
        cmd_length++;

    //Each INT child is another byte
    int i;
    for (i=0; i<nops; i++) {
        if (n->children[i]->nodeType == INT)
            cmd_length++;
        if (n->children[i]->nodeType == LONG_INT)
            cmd_length += 2;
    }



    //-------------------------
    //Compile the subtree code (for non-INT nodes)
    //-------------------------

    for (i=0; i<nops; i++) {
        int cntype = n->children[i]->nodeType;
        if (cntype != INT && cntype != LONG_INT) {
            child_lengths[i] = _compile(n->children[i], &child_code[i]);
        }
    }

    int tot_child_length = 0;
    for (i=0; i<nops; i++) {
        tot_child_length += child_lengths[i];
    }
            
    char *code = (char *) malloc( sizeof(char) *
                                  cmd_length+tot_child_length);

    if (!code)
        exit(fprintf(stderr, "Out of memory\n"));
    //----------------------------
    //Compile the code!!
    //---------------------------
    
    int code_loc = 0;
    if (ntype != SEQ && ntype != EVENT) {
        code[code_loc++] = instrtab[ntype];
    }

    int if_else = 0; //Set to 1 when an if block is found
    int empty_event = 1; //Set to 0 when an event has commands

    for (i=0; i<nops; i++) {
        node *c = n->children[i];
        int ctype = c->nodeType;
        //Integer nodes
        if (c->nodeType == INT) {
            code[code_loc++] = c->intVal;
            continue;
        } else if (c->nodeType == LONG_INT) {
            code[code_loc++] = (c->intVal & 0xff00) >> 8;
            code[code_loc++] = (c->intVal & 0xff);
            continue;
        //The actual bytecode for events is the first child
        } else if (ntype == EVENT && ctype == INT) {
            code[code_loc++] = c->intVal;
        //Add lengths
        } else if ( (n->nodeType == STATE && ctype != INT) ||
                    (n->nodeType == FIRST_STATE && ctype != INT)    ) {

            code[code_loc++] = (child_lengths[i] & 0xff00) >> 8;
            code[code_loc++] = (child_lengths[i] & 0xff);

        } else if ( (ntype == IF && ctype != INT && ctype != LONG_INT) ||
                    (ntype == FUN && ctype != INT) ||
                    (n->nodeType == EVENT && ctype != INT)) {
            
            if (ntype == IF)
                if_else++;
            if (ntype == EVENT)
                empty_event = 0; 

            code[code_loc++] = child_lengths[i];
        }
    
        memcpy(&code[code_loc], child_code[i], child_lengths[i]);
        free(child_code[i]);
        code_loc += child_lengths[i];
    }

    if (if_else==1)
        code[code_loc++] = 0x00;

    if (ntype == EVENT && empty_event)
        code[code_loc++] = 0x00;

    //code[tot_child_length+cmd_length] = 0xfd;
    
    *result = code;

    //printf("%d:", ntype);
    //for (i=0; i<(cmd_length+tot_child_length); i++)
    //    printf("0x%x, ",code[i]);
    //printf("\n");

    return code_loc;

}     



