%{

#include "btasm.h"
#include "userdef_y.tab.h"

/* handle locations */
int yycolumn = 1;

#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn+yyleng-1; \
    yycolumn += yyleng; yylloc.fname = fname;

//Hexidecimal version of atoi.  Assumes that it will be passed
//a well-formed string of the form 0x[0-9a-fA-F].  Will fail
//catastrophically otherwise.
int hatoi(char *s);

%}

%option yylineno

%%



 /* Declarations */ 
VAR                     { return VAR; }
CONFIG                  { yylval.iVal = kCONFIG; return VARATTR; }
RECEIVE                 { yylval.iVal = kRECEIVE; return VARATTR; }
SEND                    { yylval.iVal = kSEND; return VARATTR; }

FUNCTION                { return FUN; }

STATE                   { return STATE; }
FIRST_STATE             { return FIRST_STATE; }

EVENT                   { return EVENT; }


 /* Conditional */
IF                      { return IF; }
COMP                    { yylval.iVal = kCOMP; return COMP; }
DIFF                    { yylval.iVal = kDIFF; return COMP; }
INF                     { yylval.iVal = kINF; return COMP; }
SUP                     { yylval.iVal = kSUP; return COMP; }
ELSE                    { return ELSE; }
END_IF                  { return END_IF; }

 /* Control flow */

END_EVENT               { return END_EVENT; }
END_FUNCTION            { return END_FUNCTION; }
END_STATE               { return END_STATE; }

GOTO                    { return GOTO; }


 /* Event types */
BUTTON_1_JUST_PRESSED   {   yylval.iVal = kBUTTON_1_JUST_PRESSED; 
                            return ETYPE; } 
BUTTON_2_JUST_PRESSED   {   yylval.iVal = kBUTTON_2_JUST_PRESSED; 
                            return ETYPE; } 
BUTTON_3_JUST_PRESSED   {   yylval.iVal = kBUTTON_3_JUST_PRESSED; 
                            return ETYPE; }
TIMER                   { yylval.iVal = kTIMER; return TIMER; }
TICK                    { yylval.iVal = kTICK; return ETYPE; }
HIT                     { yylval.iVal = kHIT; return ETYPE; }
ENTER_STATE             { yylval.iVal = kENTER_STATE; return ETYPE; }
ANIM_FINISHED           { yylval.iVal = kANIM_FINISHED; return ETYPE; }
DATA_CHANGE             { yylval.iVal = kDATA_CHANGE; return DATA_CHANGE; }
             
 /* Mutation/settings */
SET                     { return SET; }
DEC                     { return DEC; }
INC                     { return INC; }

SET_HARNESS             { return SET_HARNESS; }
SET_TEAM                { return SET_TEAM; }


 /* HUD */
HUD_DIGIT               { return HUD_DIGIT; }
HUD_DIGIT_BLINK         { return HUD_DIGIT_BLINK; }
HUD_DIGIT_OFF           { return HUD_DIGIT_OFF; }

HUD_JAUGE               { return HUD_JAUGE; }
HUD_JAUGE_BLINK         { return HUD_JAUGE_BLINK; }
HUD_GAUGE               { return HUD_JAUGE; }
HUD_GAUGE_BLINK         { return HUD_JAUGE_BLINK; }

HUD_ICON_ON             { return HUD_ICON_ON; }
HUD_ICON_OFF            { return HUD_ICON_OFF; }

BULLET                  { yylval.iVal = kBULLET; return ITYPE; }
GOAL                    { yylval.iVal = kGOAL; return ITYPE; }
LIFE                    { yylval.iVal = kLIFE; return ITYPE; }

LED_ON                  { return LED_ON; }
LED_INFINITE            { return LED_INFINITE; }
LED_OFF                 { return LED_OFF; }

ANIM                    { return ANIM; }
ANIM_LOOP               { return ANIM_LOOP; }
ANIM_OFF                { return ANIM_OFF; }


FLASH_GREEN             { return FLASH_GREEN; }
FLASH_ORANGE            { return FLASH_ORANGE; }
FLASH_RED               { return FLASH_RED; }

 /* Sound/motor/IR */

IR                      { return IR; }
MOTOR                   { return MOTOR; }
SND                     { return SND; }
SND_PRIO                { return SND_PRIO; }

 /* Sounds */
HURT                    { yylval.iVal = kbkHURT; return RTYPE; }
ASSIST_SCANAMMO         { yylval.iVal = kbkASSIST_SCANAMMO; return RTYPE; }
SCAN_BAD                { yylval.iVal = kbkSCAN_BAD;  return RTYPE; }
SCAN_GOOD               { yylval.iVal = kbkSCAN_GOOD;  return RTYPE; }
BIP                     { yylval.iVal = kbkBIP;  return RTYPE; }
RELOAD_CLIP             { yylval.iVal = kbkRELOAD_CLIP;  return RTYPE; }
RELOAD                  { yylval.iVal = kbkRELOAD;  return RTYPE; }
OK                      { yylval.iVal = kbkOK;  return RTYPE; }
ASSIST_BACKINGAME       { yylval.iVal = kbkASSIST_BACKINGAME;return RTYPE; }
RESPAWN                 { yylval.iVal = kbkRESPAWN;  return RTYPE; }
START                   { yylval.iVal = kbkSTART; return RTYPE; }
ASSIST_SCANLIFE         { yylval.iVal = kbkASSIST_SCANLIFE; return RTYPE; }
DEAD                    { yylval.iVal = kbkDEAD; return RTYPE; }
SG01                    { yylval.iVal = kbkSG01; return RTYPE; }
SG02                    { yylval.iVal = kbkSG02; return RTYPE; }
SG03                    { yylval.iVal = kbkSG03; return RTYPE; }
SG04                    { yylval.iVal = kbkSG04; return RTYPE; }
SC11                    { yylval.iVal = kbkSC11; return RTYPE; }
ASSIST_BASE1            { yylval.iVal = kbkASSIST_BASE1; return RTYPE; }
ASSIST_BASE2            { yylval.iVal = kbkASSIST_BASE2; return RTYPE; }
ASSIST_BASE3            { yylval.iVal = kbkASSIST_BASE3; return RTYPE; }
ASSIST_BASE4            { yylval.iVal = kbkASSIST_BASE4; return RTYPE; }
ASSIST_UBICONNECT       { yylval.iVal = kbkASSIST_UBICONNECT; return RTYPE; }
SHOOT                   { yylval.iVal = kbkSHOOT; return RTYPE; }
EMPTY                   { yylval.iVal = kbkEMPTY; return RTYPE; }
ASHT                    { yylval.iVal = kbkASHT; return RTYPE; }
ARAM                    { yylval.iVal = kbkARAM; return RTYPE; }
AMED                    { yylval.iVal = kbkAMED; return RTYPE; }
AOUT                    { yylval.iVal = kbkAOUT; return RTYPE; }
AGB1                    { yylval.iVal = kbkAGB1; return RTYPE; }
AGB2                    { yylval.iVal = kbkAGB2; return RTYPE; }
AGB3                    { yylval.iVal = kbkAGB3; return RTYPE; }
AGB4                    { yylval.iVal = kbkAGB4; return RTYPE; }
AUBI                    { yylval.iVal = kbkAUBI; return RTYPE; }



 /* RFID */
RFID_SCAN               { return RFID_SCAN; }
RFID_TYPE_MAJOR         { return RFID_TYPE_MAJOR; }
RFID_TYPE_MINOR         { return RFID_TYPE_MINOR; }

RFID_AMMO_PACK          { yylval.iVal = kRFID_AMMO_PACK; return INT; }
RFID_BASE_PACK          { yylval.iVal = kRFID_BASE_PACK; return INT; }
RFID_LIFE_PACK          { yylval.iVal = kRFID_LIFE_PACK; return INT; }

RFID_AMMO1              { yylval.iVal = kRFID_AMMO1; return INT; }
RFID_BASE1              { yylval.iVal = kRFID_BASE1; return INT; }


[ \n\t]+                /* Ingore whitespace */

\/\/.*\n                  /* Ignore comments */

 /* ID/numbers */
[0-9]+                  { yylval.iVal = atoi(yytext); return INT; }
0x[0-9a-fA-F]+          { yylval.iVal = hatoi(yytext); return INT; }
[A-Z]*                  { fprintf(stderr, "%d:Illegal keyword:%s",
                                    yylineno, yytext); }
[a-zA-Z0-9_]*           { yylval.sVal = yytext; return ID; } //!
 
%%

int hatoi(char *s) {

    int len = strlen(s);
    int i;
    int val = 0;
    int mult = 1;

    //work from the back
    for (i=len-1; i>0; i--) {
    
        char c = s[i];
        
        //We've reached the end of the number
        if (c=='x')
            break;

        int temp = c - '0';
        int temp2 = c - 'a' + 10;

        //If temp is between 0 and 9, then
        //the character must have been a digit
        if (temp < 0 || temp > 9) {
            val += temp2 * mult;
        } else {
            val += temp * mult; 
        }

        //Move one hex place over
        mult *= 0x10;
    }

    //printf("%s to 0x%x", s, val);
    return val;

}
