#ifndef RESTAB_H
#define RESTAB_H

#include "../btasm.h"

char *resources[RES_COUNT];

void fillrestab() {


    resources[kbkAGB1]              = "\x41\x47\x42\x31\x00\x00";    
    resources[kbkAGB2]              = "\x41\x47\x42\x32\x00\x00";    
    resources[kbkAGB3]              = "\x41\x47\x42\x33\x00\x00";    
    resources[kbkAGB4]              = "\x41\x47\x42\x34\x00\x00";    
    resources[kbkAMED]              = "\x41\x4d\x45\x44\x00\x00";    
    resources[kbkAOUT]              = "\x41\x4f\x55\x54\x00\x00";    
    resources[kbkARAM]              = "\x41\x52\x41\x4d\x00\x00";    
    resources[kbkASHT]              = "\x41\x53\x48\x54\x00\x00";    
    resources[kbkAUBI]              = "\x41\x44\x42\x49\x00\x00";    
    resources[kbkASSIST_BACKINGAME] = "\x53\x44\x30\x32\x00\x00";    

    resources[kbkASSIST_BASE1]      = "\x53\x44\x30\x39\x00\x00";    
    resources[kbkASSIST_BASE2]      = "\x53\x44\x31\x30\x00\x00";    
    resources[kbkASSIST_BASE3]      = "\x53\x44\x31\x31\x00\x00";    
    resources[kbkASSIST_BASE4]      = "\x53\x44\x31\x32\x00\x00";    
    resources[kbkASSIST_SCANAMMO]   = "\x53\x44\x31\x33\x00\x00";    
    resources[kbkASSIST_SCANLIFE]   = "\x53\x44\x31\x34\x00\x00";    
    resources[kbkASSIST_UBICONNECT] = "\x53\x44\x31\x35\x00\x00";    
    resources[kbkBIP]               = "\x53\x43\x30\x32\x00\x00";    
    resources[kbkDEAD]              = "\x53\x44\x30\x33\x00\x00";    
    resources[kbkEMPTY]             = "\x53\x57\x32\x32\x00\x00";    
    resources[kbkHURT]              = "\x53\x43\x30\x35\x00\x00";    
    resources[kbkOK]                = "\x53\x43\x31\x30\x00\x00";    
    resources[kbkRELOAD]            = "\x53\x57\x31\x32\x00\x00";    
    resources[kbkRELOAD_CLIP]       = "\x53\x57\x34\x32\x00\x00";    
    resources[kbkRESPAWN]           = "\x53\x43\x30\x37\x00\x00";    
    resources[kbkSC11]              = "\x53\x43\x31\x31\x00\x00";    
    resources[kbkSCAN_BAD]          = "\x53\x43\x30\x38\x00\x00";    
    resources[kbkSCAN_GOOD]         = "\x53\x43\x30\x39\x00\x00";    
    resources[kbkSG01]              = "\x53\x47\x30\x31\x00\x00";    
    resources[kbkSG02]              = "\x53\x47\x30\x32\x00\x00";    
    resources[kbkSG03]              = "\x53\x47\x30\x33\x00\x00";    
    resources[kbkSG04]              = "\x53\x47\x30\x34\x00\x00";    
    resources[kbkSHOOT]             = "\x53\x57\x35\x36\x00\x00";    
    resources[kbkSTART]             = "\x53\x43\x30\x33\x00\x00";    

/*
    resources[kbkHURT]              = "\x53\x43\x30\x35\x00\x00";    
    resources[kbkSTART]             = "\x53\x43\x30\x33\x00\x00";    
    resources[kbkASHT]              = "\x41\x53\x48\x54\x00\x00";    
    resources[kbkSHOOT]             = "\x53\x57\x35\x36\x00\x00";    
    resources[kbkASSIST_SCANAMMO]   = "\x53\x44\x31\x33\x00\x00";    
    resources[kbkEMPTY]             = "\x53\x57\x32\x32\x00\x00";    
    resources[kbkSCAN_BAD]          = "\x53\x43\x30\x38\x00\x00";    
    resources[kbkBIP]               = "\x53\x43\x30\x32\x00\x00";    
    resources[kbkASSIST_SCANLIFE]   = "\x53\x44\x31\x34\x00\x00";    
    resources[kbkRELOAD]            = "\x53\x57\x31\x32\x00\x00";    
    resources[kbkRELOAD_CLIP]       = "\x53\x57\x34\x32\x00\x00";    
    resources[kbkARAM]              = "\x41\x52\x41\x4d\x00\x00";    
    resources[kbkOK]                = "\x53\x43\x31\x30\x00\x00";    
    resources[kbkAOUT]              = "\x41\x4f\x55\x54\x00\x00";    
    resources[kbkDEAD]              = "\x53\x44\x30\x33\x00\x00";    
    resources[kbkSCAN_GOOD]         = "\x53\x43\x30\x39\x00\x00";    
    resources[kbkAMED]              = "\x41\x4d\x45\x44\x00\x00";    
    resources[kbkRESPAWN]           = "\x53\x43\x30\x37\x00\x00";    
    resources[kbkASSIST_BACKINGAME] = "\x53\x44\x30\x32\x00\x00";    
    resources[kbkSG01]              = "\x53\x47\x30\x31\x00\x00";    
    resources[kbkSG02]              = "\x53\x47\x30\x32\x00\x00";    
    resources[kbkSG03]              = "\x53\x47\x30\x33\x00\x00";    
    resources[kbkSG04]              = "\x53\x47\x30\x34\x00\x00";    
    resources[kbkSC11]              = "\x53\x43\x31\x31\x00\x00";    
    resources[kbkASSIST_BASE1]      = "\x53\x44\x30\x39\x00\x00";    
    resources[kbkASSIST_BASE2]      = "\x53\x44\x31\x30\x00\x00";    
    resources[kbkASSIST_BASE3]      = "\x53\x44\x31\x31\x00\x00";    
    resources[kbkASSIST_BASE4]      = "\x53\x44\x31\x32\x00\x00";    
    resources[kbkASSIST_UBICONNECT] = "\x53\x44\x31\x35\x00\x00";    
    resources[kbkAGB1]              = "\x41\x47\x42\x31\x00\x00";    
    resources[kbkAGB2]              = "\x41\x47\x42\x32\x00\x00";    
    resources[kbkAGB3]              = "\x41\x47\x42\x33\x00\x00";    
    resources[kbkAGB4]              = "\x41\x47\x42\x34\x00\x00";    
    resources[kbkAUBI]              = "\x41\x44\x42\x49\x00\x00";    
*/
}


#endif
