%{

#include "btasm.h"
#include "y.tab.h"



void tok(char *tstr)
{
    if (tstr && tstr[0] != '!') {
        printf("%s\n",tstr);
    } else {
        printf("(%s:%s)\n",++tstr,yytext);
    }
}

void error(char *msg) 
{
    printf("%s",msg);
}

%}


%%


 /* ID/numbers */
[a-z][a-zA-Z0-9_]*      { yylval.sVal = yytext; return ID; } //!
[0-9]+                  { yylval.iVal = atoi(yytext); return INT; }

 /* Declarations */ 
VAR                     { return VAR; }
CONFIG                  { yylval.iVal = 3; return VARATTR; }
SEND                    { yylval.iVal = 1; return VARATTR; }
RECEIVE                 { yylval.iVal = 2; return VARATTR; }
FUNCTION                { return FUN; }
STATE                   { return STATE; }
FIRST_STATE             { return FIRST_STATE; }
EVENT                   { return EVENT; }


 /* Conditional */
IF                      { return IF; }
COMP                    { yylval.iVal = 2; return COMP; }
DIFF                    { yylval.iVal = 3; return COMP; }
SUP                     { yylval.iVal = 0; return COMP; }
ELSE                    { return ELSE; }
END_IF                  { return END_IF; }

 /* Control flow */
GOTO                    { return GOTO; }
END_FUNCTION            { return END_FUNCTION; }
END_STATE               { return END_STATE; }
END_EVENT               { return END_EVENT; }
 /*TIMER*/

 /* Event types */
BUTTON_1_JUST_PRESSED   { yylval.iVal = 0; return ETYPE; } 
BUTTON_2_JUST_PRESSED   { yylval.iVal = 1; return ETYPE; } 
BUTTON_3_JUST_PRESSED   { yylval.iVal = 2; return ETYPE; }
TIMER                   { yylval.iVal = 9; return ETYPE; }
TICK                    { yylval.iVal = 10; return ETYPE; }
HIT                     { yylval.iVal = 11; return ETYPE; }
ENTER_STATE             { yylval.iVal = 13; return ETYPE; }
ANIM_FINISHED           { yylval.iVal = 14; return ETYPE; }
DATA_CHANGE             { yylval.iVal = 15; return ETYPE; }
             
 /* Mutation */
SET                     { return SET; }
DEC                     { return DEC; }
INC                     { return INC; }

 /* HUD */
HUD_DIGIT               { return HUD_DIGIT; }
 /*OFF                     { return OFF; }*/
HUD_DIGIT_BLINK         { return HUD_DIGIT_BLINK; }
HUD_DIGIT_OFF           { return HUD_DIGIT_OFF; }
HUD_JAUGE               { return HUD_JAUGE; }
HUD_JAUGE_BLINK         { return HUD_JAUGE_BLINK; }
HUD_ICON_ON             { return HUD_ICON_ON; }
HUD_ICON_OFF            { return HUD_ICON_OFF; }
BULLET                  { yylval.iVal = 3; return ITYPE; }
LIFE                    { yylval.iVal = 2; return ITYPE; }
LED_ON                  { return LED_ON; }
LED_OFF                 { return LED_OFF; }
LED_INFINITE            { return LED_INFINITE; }
ANIM                    { return ANIM; }
ANIM_OFF                { return ANIM_OFF; }
ASHT                    { return RTYPE; }
ARAM                    { return RTYPE; }
AMED                    { return RTYPE; }

FLASH_ORANGE            { return FLASH_ORANGE; }
FLASH_GREEN             { return FLASH_GREEN; }
FLASH_RED               { return FLASH_RED; }


 /* Sound/motor */
MOTOR                   { return MOTOR; }
SND                     { return SND; }
SND_PRIO                { return SND_PRIO; }

 /* Sounds */
HURT                    { return RTYPE; }
ASSIST_SCANAMMO         { return RTYPE; }
SCAN_BAD                { return RTYPE; }
SCAN_GOOD               { return RTYPE; }
BIP                     { return RTYPE; }
RELOAD_CLIP             { return RTYPE; }
RELOAD                  { return RTYPE; }
OK                      { return RTYPE; }
ASSIST_BACKINGAME       { return RTYPE; }
RESPAWN                 { return RTYPE; }
START                   { return RTYPE; }
ASSIST_SCANLIFE         { return RTYPE; }
DEAD                    { return RTYPE; }
SG01                    { return RTYPE; }
SG02                    { return RTYPE; }
SG03                    { return RTYPE; }
SG04                    { return RTYPE; }
SC11                    { return RTYPE; }
ASSIST_BASE1            { return RTYPE; }
ASSIST_BASE2            { return RTYPE; }
ASSIST_BASE3            { return RTYPE; }
ASSIST_BASE4            { return RTYPE; }
ASSIST_UBICONNECT       { return RTYPE; }
SHOOT                   { return RTYPE; }
EMPTY                   { return RTYPE; }



 /* Vest */
HARNESS                 { return HARNESS; }


 /* RFID */
RFID_SCAN               { return RFID_SCAN; }
RFID_TYPE_MAJOR         { return RFID_TYPE_MAJOR; }
RFID_TYPE_MINOR         { return RFID_TYPE_MINOR; }

[ \n\t]+                /* Ingore whitespace */

[A-Z]*                 { printf("%d:Unrecognized language keyword:%s\n",yylineno,yytext); }
[A-Z0-9_][A-Za-z0-9_]* { printf("%d:Illegal identifier:%s\n", yylineno,yytext); }

%%
