#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>

#include "source/structure.h"
#include "source/gamerules.h"
#include "source/front.h"

#if 0
	#define DEBUG
#endif

int main()
{
    initscr();
    //noecho();
    //cbreak();
    start_color();

    //printf("Test\n");
    #ifdef DEBUG
		setChessPiece(getChessPiece(7,6), 7, 1);
		setChessPiece(getChessPiece(0,1), 0, 6);
	#endif
    
   /* performMove(7, 7, 7, 2);
    performMove(0, 2, 4, 2);
    
    printf("%d %d\n", isKingChecked(1), isKingChecked(2));
    
    DisplayArrayContent();*/
    #ifndef DEBUG
		main_menu();
	#endif
	
	#ifdef DEBUG
	    gameInit();
		main_loop();
	#endif
    endwin();
}
