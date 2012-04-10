#ifndef BTASM_H
#define BTASM_H
/**********************************
 * btasm.h
 * Header for main compiler source file
 * 4/6/12 - J. MacMillan
 * ********************************/

/**
 * Enums for the lexer and the parser
 * The enums are clear as to whether they are for bookkeeping or if
 * they actually represent what goes into the bytecode (k prefix for
 * bytecode constants, kbk for bookkeeping constants.
 */

enum {kSEND=1, kRECEIVE=2, kCONFIG=3};

enum {kSUP=0, kINF=1, kCOMP=2, kDIFF=3};

enum {  kBUTTON_1_JUST_PRESSED  = 0,
        kBUTTON_2_JUST_PRESSED  = 1,
        kBUTTON_3_JUST_PRESSED  = 2,
        kTIMER                  = 9,
        kTICK                   = 10,
        kHIT                    = 11,
        kENTER_STATE            = 12,
        kANIM_FINISHED          = 14,
        kDATA_CHANGE            = 15
};

enum { kLIFE=2, kBULLET=3, kGOAL=4};

enum {  kbkHURT, kbkASSIST_SCANAMMO, kbkSCAN_BAD, kbkSCAN_GOOD, kbkBIP, 
        kbkRELOAD_CLIP, kbkRELOAD, kbkOK, kbkASSIST_BACKINGAME, kbkRESPAWN,
        kbkSTART, kbkASSIST_SCANLIFE, kbkDEAD, kbkSG01, kbkSG02, kbkSG03,
        kbkSG04, kbkSC11, kbkASSIST_BASE1, kbkASSIST_BASE2, kbkASSIST_BASE3,
        kbkASSIST_BASE4, kbkASSIST_UBICONNECT, kbkSHOOT, kbkEMPTY, kbkASHT,
        kbkARAM, kbkAMED, kbkAOUT, kbkAGB1, kbkAGB2, kbkAGB3, kbkAGB4,
        kbkAUBI
};
 
//REMEMBER TO UPDATE THIS AS RESOURCES ARE ADDED
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define RES_COUNT 34


//todo - need the correct numbers!!
enum {
    kRFID_AMMO_PACK = 0x0, 
    kRFID_AMMO1     = 0x1,
    kRFID_LIFE_PACK = 0x2,
    kRFID_BASE_PACK = 0x3,
    kRFID_BASE1     = 0x4
};

//Node in the syntax tree 
typedef struct node {
    int nodeType;
    int intVal;
    char *strVal;
    int nops;
    struct node **children;
} node;

/**
 * Create a node representing the integer i
 * /param i Integer to create node for
 * /return The created node
 */
node *int_node(int i);

/**
 * Create an ID node representing the string s
 * /param s String to create node for
 * /return The created node
 */
node *id_node(char *s);

/**
 * Create an arbitrary syntax tree node.
 * /param type Type of the node
 * /param nops Number of children nodes this node has
 * /param ... Variable list child nodes
 * /return The created node
 */
node *cr_node(int type, int nops, ...);

/**
 * Free the tree rooted at n
 * /param n The root of the tree to be freed.
 */
void free_tree(node *n);

//First parse.  Check and replace IDs.  Die if missing ID.
void parse1(node *n);

void reverse_imap(int *m);
#endif
