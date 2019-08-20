/* DUNGEON-- MAIN PROGRAM */

/*COPYRIGHT 1980, INFOCOM COMPUTERS AND COMMUNICATIONS, CAMBRIDGE MA. 02142*/
/* ALL RIGHTS RESERVED, COMMERCIAL USAGE STRICTLY PROHIBITED */
/* WRITTEN BY R. M. SUPNIK */

#define EXTERN
#define INIT

#ifdef VITA
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <stdio.h>
#include <vita2d.h>
#include "common/debugScreen.h"
#include "common/button-keyboard.h"
#endif

#include "funcs.h"
#include "vars.h"


void main(argc, argv)
int argc;
char **argv;
{
/* 1) INITIALIZE DATA STRUCTURES */
/* 2) PLAY GAME */
    #ifdef VITA
    vita2d_init();
    init_keyboard();

    psvDebugScreenInit();
    #endif
    
    if (init_()) {
	game_();
    }
/* 						!IF INIT, PLAY GAME. */
    exit_();
/* 						!DONE */
} /* MAIN__ */
