#ifndef INSTRTAB_H
#define INSTRTAB_H
/*******************************************
 * Table of us to bytecode instructions 
 *  (and other compilation helper functions)
 * 4/11/12 - J. MacMillan
 *******************************************/

#include "../userdef_y.tab.h"

char instrtab[512];

//Returns true if the command
//has a length argument
inline int has_len_arg(int t) 
{
    return (t == FUN || t == IF || 
            t == EVENT || t == STATE ||
            t == FIRST_STATE);
}

//Fill the instruction table
void fillinstrtab() {

	instrtab[ANIM]              = 0xcb;
	instrtab[ANIM_LOOP]         = 0xd8;
	instrtab[ANIM_OFF]          = 0xdf;
	instrtab[CALL]              = 0xd0;
	instrtab[DEC]               = 0xc1;
	instrtab[FIRST_STATE]       = 0xd2;
	instrtab[FLASH_GREEN]       = 0xd5;
	instrtab[FLASH_RED]         = 0xd4;
	instrtab[FUN]               = 0xd0;
    instrtab[GOTO]              = 0xc3; //0xc1?????
	instrtab[HUD_DIGIT]         = 0xcd;
	instrtab[HUD_DIGIT_OFF]     = 0xd6;
	instrtab[HUD_ICON]          = 0xcf;
	instrtab[HUD_JAUGE]         = 0xce;
	instrtab[IF]                = 0xc4;
	instrtab[INC]               = 0xc2;
	instrtab[IR]                = 0xc6;
	instrtab[LED_OFF]           = 0xd7;
	instrtab[LED_ON]            = 0xca;
	instrtab[MOTOR]             = 0xd3;
	instrtab[RFID_SCAN]         = 0xc8;
	instrtab[RFID_TYPE_MAJOR]   = 0xde;
	instrtab[RFID_TYPE_MINOR]   = 0xd9;
	instrtab[SET]               = 0xc0;
	instrtab[SET_HARNESS]       = 0xdd; 
	instrtab[SET_TEAM]          = 0xdc;
	instrtab[SND]               = 0xc5;
	instrtab[STATE]             = 0xc7;
	instrtab[TIMER]             = 0xc9;
	instrtab[VAR]               = 0xcc;
	
	/*instrtab[SET]               = 0xc0;
	instrtab[SET_HARNESS]       = 0xdd; 
	instrtab[INC]               = 0xc2;
	instrtab[DEC]               = 0xc1;
	instrtab[HUD_DIGIT]         = 0xcd;
	//instrtab[HUD_DIGIT_BLINK] = 
	instrtab[HUD_DIGIT_OFF]     = 0xd6;
	instrtab[HUD_JAUGE]         = 0xce;
	//instrtab[HUD_ICON] = ;
	//instrtab[HUD_ICON_OFF] = ;
	instrtab[ANIM]              = 0xcb;
	instrtab[SND]               = 0xc5;
	instrtab[LED_ON]            = 0xca;
	//instrtab[FLASH_ORANGE] = ;
	instrtab[FLASH_RED]         = 0xd4;
	instrtab[FLASH_GREEN]       = 0xd5;
	instrtab[IR]                = 0xc6;
	instrtab[MOTOR]             = 0xd3;
	instrtab[STATE]             = 0xc7;
	instrtab[FIRST_STATE]       = 0xd2;
	//instrtab[END_STATE] = ;
	//instrtab[EVENT] = ;   //Given as an argument to the EVENT node
	//instrtab[END_EVENT] = ;
	instrtab[FUN]               = 0xd0;
	//instrtab[END_FUNCTION] = ;
	instrtab[IF]                = 0xc4;
	//instrtab[ELSE] = ;
	//instrtab[END_IF] = ;
	instrtab[VAR]               = 0xcc;
	//instrtab[SEQ] = ;
	//instrtab[HUD_JAUGE_BLINK] = ;
	//instrtab[CONFIG] = ;
	//instrtab[SEND] = ;
	//instrtab[RECEIVE] = ;
	instrtab[LED_OFF]           = 0xd7;
	//instrtab[LED_INFINITE]      = 0xca;
	instrtab[ANIM_OFF]          = 0xdf;
	//instrtab[SND_PRIO] = ;
	instrtab[RFID_SCAN]         = 0xc8;
	instrtab[RFID_TYPE_MAJOR]   = 0xde;
	instrtab[RFID_TYPE_MINOR]   = 0xd9;
	instrtab[CALL]              = 0xd0;
	instrtab[ANIM_LOOP]         = 0xd8;
	instrtab[SET_TEAM]          = 0xdc;
	instrtab[HUD_ICON]          = 0xcf;
	//instrtab[INT] = ;
	//instrtab[RTYPE] = ;
	//instrtab[COMP] = ;
	//instrtab[VARATTR] = ;
	//instrtab[ETYPE] = ;
	//instrtab[ITYPE] = ;
	instrtab[TIMER]             = 0xc9;
	//instrtab[DATA_CHANGE]       = ;
	//instrtab[ID] = ;*/

}

#endif
