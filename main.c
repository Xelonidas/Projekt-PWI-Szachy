#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdbool.h>

#include "source/structure.h"
#include "source/gamerules.h"
#include "source/front.h"

int main()
{
    initscr();
    //noecho();
    //cbreak();
    
    gameInit();
    /*
    printf("Test\n");
    
    for(int i = 0; i < 8; i++) {
		removeChessPiece(i,1);
		removeChessPiece(i,6);
		ChessPiece cp = getChessPiece(i, 0);
		performMove(i, 0, i, 2);
	}
    performMove(7, 7, 7, 2);
    performMove(0, 2, 4, 2);
    
    printf("%d %d\n", isKingChecked(1), isKingChecked(2));
    
    DisplayArrayContent();
    */
    //draw_board();
    //main_loop();
    main_menu();
    getch();
    endwin();
}
