%{

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "btasm.h"
#include "map.h"

#include "toktab.h"

node *cr_node(int type, int nops, ...);
node *int_node(int i);
node *id_node(char *s);
char *graph(node *n);
char *gen_node();
void yyerror(char *s);

map vmap; 
map fmap; 
map rmap; 
map smap;

%}




%union {
    int iVal;
    char *sVal;
    node *nPtr;
};

%token  GOTO SET SET_HARNESS INC DEC HUD_DIGIT HUD_DIGIT_BLINK
        HUD_DIGIT_OFF HUD_JAUGE HUD_ICON_ON HUD_ICON_OFF ITYPE ANIM
        SND LED_ON FLASH_ORANGE FLASH_RED FLASH_GREEN IR
        MOTOR STATE FIRST_STATE END_STATE EVENT END_EVENT
        FUN END_FUNCTION IF ELSE END_IF VAR SEQ 
        HUD_JAUGE_BLINK CONFIG SEND RECEIVE LED_OFF
        LED_INFINITE ANIM_OFF SND_PRIO HARNESS RFID_SCAN RFID_TYPE_MAJOR
        RFID_TYPE_MINOR

%token <iVal> INT RTYPE COMP VARATTR ETYPE;
%token <sVal> ID;
%type <nPtr> program stmt stmt_list event_list branch exp id;

%nonassoc ELSE





%%

program: 
    stmt_list           {   printf("digraph syntax_tree {\n"); 
                            graph($$); printf("}"); exit(0); 
                        }

stmt_list:  
      stmt              {$$ = $1;}
    | stmt stmt_list    {$$ = cr_node(SEQ, 2, $1, $2); }

stmt:
    //Declarations
      FUN id stmt_list END_FUNCTION 
        {
            if (insert_map(fmap, $2->strVal)==-1)
                yyerror("error:function redefined\n");  
            $$ = cr_node(FUN, 2, $2, $3); 
        }

    | VAR id                        { if (insert_map(vmap, $2->strVal)==-1)
                                        yyerror("variable redefined\n");
                                      node *attr = int_node(0);
                                      $$ = cr_node(VAR, 2, $2, attr); }
    
    | VAR id VARATTR                { if (insert_map(vmap, $2->strVal)==-1)
                                        yyerror("variable redefined\n");
                                      node *attr = int_node($3);
                                      $$ = cr_node(VAR, 2, $2, attr); }


    //Flow
    | branch            {}
    | GOTO ID           {}
    //Mutation
    | SET ID INT        {}
    | SET ID ID         {}
    | SET_HARNESS INT   {}
    | INC ID            {}
    | DEC ID            {}
    //HUD/sound/motor/etc
    | HUD_DIGIT INT         { $$ = cr_node(HUD_DIGIT, 1, int_node($2));} 
    | HUD_DIGIT ID          { $$ = cr_node(HUD_DIGIT, 1, id_node($2));} 
    | HUD_DIGIT_BLINK INT   { $$ = cr_node(HUD_DIGIT_BLINK,1,int_node($2));}
    | HUD_DIGIT_BLINK ID    { $$ = cr_node(HUD_DIGIT_BLINK,1,id_node($2));} 
    | HUD_DIGIT_OFF         { $$ = cr_node(HUD_DIGIT_OFF, 0);}
    | HUD_JAUGE INT         { $$ = cr_node(HUD_JAUGE, 1, int_node($2)); } 
    | HUD_JAUGE ID          { $$ = cr_node(HUD_JAUGE, 1, id_node($2));  } 
    | HUD_JAUGE_BLINK exp   {} 
    | HUD_JAUGE_BLINK ID    {} 
    | HUD_ICON_ON ITYPE {}
    | HUD_ICON_OFF ITYPE{}
    | ANIM RTYPE        {}
    | SND RTYPE         {}
    | LED_ON exp exp    {}
    | FLASH_ORANGE      {}
    | FLASH_RED         {}
    | FLASH_GREEN       {}
    | IR                {}
    | MOTOR exp         {}
    | ID                {}
    //State/event code
    | STATE ID FIRST_STATE event_list END_STATE {}
    | STATE ID event_list END_STATE {}

id:
      ID                  { $$ = id_node($1);}
exp:
      INT                 { $$ = cr_node(INT, 1, $1);}
event_list: 
      EVENT ETYPE stmt_list END_EVENT             {} 
    | EVENT ETYPE stmt_list END_EVENT event_list {}

branch:
      IF id COMP exp stmt_list END_IF   {$$ = cr_node(IF,4,
                                        $2,int_node($3),$4,$5);}

    | IF id COMP exp stmt_list ELSE stmt_list END_IF {}

%%

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
 
void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s); 
}       

char *graph(node *n)
{
    
    char *dotName = gen_node();
    
    filltoktab(); 


    switch (n->nodeType) {
        
        case INT:   
                    printf("%s [label=\"INT_%d\"]\n", dotName, n->intVal);
                    break; 
        case ID:    
                    printf("%s [label=\"ID_%s\"]\n", dotName, n->strVal);
                    break;
        default:    0; 
                    int i=0;
                    for (i=0; i<n->nops; i++) {
                        char *cn = graph(n->children[i]);
                        printf("%s -> %s\n", dotName, cn);
                    }
                    printf("%s [label=\"%s\"]\n", dotName, 
                                                toktab[n->nodeType]); 
                    break;
    
    }

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
