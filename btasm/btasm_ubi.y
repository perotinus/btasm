%{

#include <stdio.h>

#include "btasm.h"
#include "map.h"

node *cr_node(int type, int nops, ...);
node *int_node(int i);
node *id_node(char *s);
void yyerror(char *s);

map vmap;   //Variables 
map fmap;   //Functions
int *rmap;  //Resources
map smap;   //S...

//Number of distinct resources already found.  This is increased
//each time a resource is added to the resource map, up to 
//RES_COUNT (which is declared in btasm.h)
int res_loc = 0;

node *stree;

%}




%union {
    int iVal;
    char *sVal;
    node *nPtr;
};

%token  GOTO SET SET_HARNESS INC DEC HUD_DIGIT HUD_DIGIT_BLINK
        HUD_DIGIT_OFF HUD_JAUGE HUD_ICON_ON HUD_ICON_OFF ANIM
        SND LED_ON FLASH_ORANGE FLASH_RED FLASH_GREEN IR
        MOTOR STATE FIRST_STATE END_STATE EVENT END_EVENT
        FUN END_FUNCTION IF ELSE END_IF VAR SEQ 
        HUD_JAUGE_BLINK CONFIG SEND RECEIVE LED_OFF
        LED_INFINITE ANIM_OFF SND_PRIO RFID_SCAN RFID_TYPE_MAJOR
        RFID_TYPE_MINOR CALL ANIM_LOOP SET_TEAM

%token <iVal> INT RTYPE COMP VARATTR ETYPE ITYPE TIMER;
%token <sVal> ID;
%type <nPtr> program stmt stmt_list event_list branch id var_fn_st_list
             var_list fn_list state_list;

%nonassoc ELSE





%%

program: 
    var_fn_st_list     {stree = $$;}

var_fn_st_list:
      var_list fn_list state_list   { node *n = cr_node(SEQ, 2, $2, $3);
                                      $$ = cr_node(SEQ, 2, $1, n); }
    | var_list state_list           { $$ = cr_node(SEQ, 2, $1, $2); }
    | fn_list state_list            { $$ = cr_node(SEQ, 2, $1, $2); }
    | state_list                    { $$ = $1;}

var_list:

      VAR id var_list           { if (insert_map(vmap, $2->strVal)==-1)
                                    yyerror("variable redefined\n");
                                  node *attr = int_node(0);
                                  node *v = cr_node(VAR, 2, $2, attr); 
                                  $$ = cr_node(SEQ, 2, v, $3); }

    | VAR id VARATTR var_list   { if (insert_map(vmap, $2->strVal)==-1)
                                    yyerror("variable redefined\n");
                                  node *attr = int_node($3);
                                  node *v = cr_node(VAR, 2, $2, attr); 
                                  $$ = cr_node(SEQ, 2, v, $4); }

    | VAR id                    { if (insert_map(vmap, $2->strVal)==-1)
                                    yyerror("variable redefined\n");
                                  node *attr = int_node(0);
                                  $$ = cr_node(VAR, 2, $2, attr); }

    | VAR id VARATTR            { if (insert_map(vmap, $2->strVal)==-1)
                                    yyerror("variable redefined\n");
                                  node *attr = int_node($3);
                                  $$ = cr_node(VAR, 2, $2, attr); }

fn_list:
      FUN id stmt_list END_FUNCTION 
        {
            if (insert_map(fmap, $2->strVal)==-1)
                yyerror("error:function redefined\n");  
            $$ = cr_node(FUN, 2, $2, $3); 
        }

    | FUN id stmt_list END_FUNCTION fn_list
        {
            if (insert_map(fmap, $2->strVal)==-1)
                yyerror("error:function redefined\n");  
            node *f = cr_node(FUN, 2, $2, $3);
            $$ = cr_node(SEQ, 2, f, $5); 
        }

state_list:
      STATE id FIRST_STATE event_list END_STATE state_list
            { if (insert_map(smap, $2->strVal)==-1)
                yyerror("error: state redefined");
              node *s = cr_node(STATE, 3, $2, int_node(1), $4); 
              $$ = cr_node(SEQ, 2, s, $6); }
    | STATE id event_list END_STATE state_list
            { if (insert_map(smap, $2->strVal)==-1)
                yyerror("error: state redefined");
              node *s = cr_node(STATE, 3, $2, int_node(0), $3); 
              $$ = cr_node(SEQ, 2, s, $5); }
    | STATE id FIRST_STATE event_list END_STATE 
            { if (insert_map(smap, $2->strVal)==-1)
                yyerror("error: state redefined");
              $$ = cr_node(STATE, 3, $2, int_node(1), $4); }
    | STATE id event_list END_STATE
            { if (insert_map(smap, $2->strVal)==-1)
                yyerror("error: state redefined");
              $$ = cr_node(STATE, 3, $2, int_node(0), $3); }

stmt_list:  
      stmt              {$$ = $1;}
    | stmt stmt_list    {$$ = cr_node(SEQ, 2, $1, $2); }

stmt:
    //Flow
      branch            { $$ = $1; }
    | GOTO id           { $$ = cr_node(GOTO, 1, $2); }
    //Mutation
    | SET id INT        { $$ = cr_node(SET, 3, $2, int_node(1), 
                          int_node($3)); }
    | SET id id         { $$ = cr_node(SET, 3, $2, int_node(0), $3); }
    | SET_HARNESS INT   { $$ = cr_node(SET_HARNESS, 1, int_node($2)); }
    | SET_TEAM INT      { $$ = cr_node(SET_TEAM, 1, int_node($2)); }
    | SET_TEAM id       { $$ = cr_node(SET_TEAM, 1, $2); }
    | INC id            { $$ = cr_node(INC, 1, $2); }
    | DEC id            { $$ = cr_node(DEC, 1, $2); }
    //HUD/sound/motor/etc
    | HUD_DIGIT INT         { $$ = cr_node(HUD_DIGIT, 1, int_node($2)); } 
    | HUD_DIGIT id          { $$ = cr_node(HUD_DIGIT, 1, $2); } 
    | HUD_DIGIT_BLINK INT   { $$ = cr_node( HUD_DIGIT_BLINK, 
                                            1, int_node($2)  ); }
    | HUD_DIGIT_BLINK id    { $$ = cr_node(HUD_DIGIT_BLINK,1,$2); } 
    | HUD_DIGIT_OFF         { $$ = cr_node(HUD_DIGIT_OFF, 0); }
    | HUD_JAUGE INT         { $$ = cr_node(HUD_JAUGE, 1, int_node($2)); } 
    | HUD_JAUGE id          { $$ = cr_node(HUD_JAUGE, 1, $2);  } 
    | HUD_JAUGE_BLINK INT   { $$ = cr_node( HUD_JAUGE_BLINK, 
                                            1, int_node($2) ); } 
    | HUD_JAUGE_BLINK id    { $$ = cr_node(HUD_JAUGE_BLINK, 1, $2); } 
    | HUD_ICON_ON ITYPE     { $$ = cr_node(HUD_ICON_ON, 1, int_node($2)); }
    | HUD_ICON_OFF ITYPE    { $$ = cr_node(HUD_ICON_OFF,1, int_node($2)); }
    | ANIM RTYPE            { if (res_loc > RES_COUNT) 
                                yyerror("Too many resources.");
                              if (rmap[$2] == -1)
                                rmap[$2] = res_loc++;  
                              $$ = cr_node(ANIM, 1, int_node($2)); }
    | ANIM_LOOP RTYPE       { if (res_loc > RES_COUNT) 
                                yyerror("Too many resources.");
                              if (rmap[$2] == -1)
                                rmap[$2] = res_loc++;  
                              $$ = cr_node(ANIM_LOOP, 1, int_node($2)); }
    | ANIM_OFF              { $$ = cr_node(ANIM_OFF, 0); }
    | SND RTYPE             { if (res_loc > RES_COUNT) 
                                yyerror("Too many resources.");
                              if (rmap[$2] == -1)
                                rmap[$2] = res_loc++;  
                              $$ = cr_node(SND, 1, int_node($2)); }
    | SND_PRIO RTYPE        { if (res_loc > RES_COUNT) 
                                yyerror("Too many resources.");
                              if (rmap[$2] == -1)
                                rmap[$2] = res_loc++;  
                              $$ = cr_node(SND_PRIO, 1, int_node($2)); }
    | LED_ON INT INT        { $$ =  cr_node(LED_ON, 2, 
                                    int_node($2), int_node($3)); }
    | LED_OFF               { $$ = cr_node(LED_OFF, 0); }
    | LED_INFINITE INT      { $$ = cr_node(LED_INFINITE, 1,int_node($2)); }
    | FLASH_ORANGE INT      { node *in = int_node($2);
                              node *n1 = cr_node(FLASH_RED,1,in);
                              node *n2 = cr_node(FLASH_GREEN,1,in);
                              $$ = cr_node(SEQ, 2, n1, n2);   }
    | FLASH_RED INT         { $$ = cr_node(FLASH_RED, 1, int_node($2)); }
    | FLASH_GREEN INT       { $$ = cr_node(FLASH_GREEN, 1, int_node($2)); }
    | IR                    { $$ = cr_node(IR, 0); }
    | MOTOR INT             { $$ = cr_node(MOTOR, 1, int_node($2)); }
    | RFID_SCAN id          { $$ = cr_node(RFID_SCAN, 1, $2); }
    | RFID_TYPE_MAJOR id    { $$ = cr_node(RFID_TYPE_MAJOR, 1, $2); }
    | RFID_TYPE_MINOR id    { $$ = cr_node(RFID_TYPE_MINOR, 1, $2); }
    | TIMER INT             { $$ = cr_node(TIMER, 1, int_node($2)); }
    | id                    { $$ = cr_node(CALL, 1, $1); }
    //State/event code



id:
      ID    { $$ = id_node($1);}



event_list: 
      EVENT ETYPE stmt_list END_EVENT             
            { $$ = cr_node(EVENT, 2, int_node($2), $3); } 
    | EVENT ETYPE stmt_list END_EVENT event_list 
            { node *e = cr_node(EVENT, 2, int_node($2), $3);
              $$ = cr_node(SEQ, 2, e, $5); }
    | EVENT TIMER stmt_list END_EVENT             
            { $$ = cr_node(EVENT, 2, int_node($2), $3); } 
    | EVENT TIMER stmt_list END_EVENT event_list 
            { node *e = cr_node(EVENT, 2, int_node($2), $3);
              $$ = cr_node(SEQ, 2, e, $5); }
    | EVENT ETYPE END_EVENT
            { node *e = cr_node(EVENT, 1, int_node($2)); }
    | EVENT ETYPE END_EVENT event_list 
            { node *e = cr_node(EVENT, 1, int_node($2));
              $$ = cr_node(SEQ, 2, e, $4); }


branch:
      IF id COMP INT stmt_list END_IF   
            { $$ = cr_node( IF, 5, $2, int_node(1), 
                            int_node($4), int_node($3), $5); }

    | IF id COMP INT stmt_list ELSE stmt_list END_IF 
            { $$ = cr_node( IF, 6, $2, int_node(1), int_node($4),
                            int_node($3), $5, $7); }
    | IF id COMP id stmt_list END_IF   
            { $$ = cr_node(IF, 5, $2, int_node(0), $4, int_node($3), $5); }

    | IF id COMP id stmt_list ELSE stmt_list END_IF 
            { $$ = cr_node( IF, 6, $2, int_node(0), $4, 
                            int_node($3), $5, $7); }

%%


 
void yyerror(char *s)
{
    fprintf(stderr, "%s\n", s); 
}       


