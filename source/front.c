#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structure.h"
#include "gamerules.h"
#include "front.h"

bool is_valid_coord(int c)
{
    //sprawdza poprawnosc wprowadzonego koordynatu
    return (c >= 0 && c <= 7);
}

bool owns_piece(int color, int x, int y)
{
    ChessPiece piece = getChessPiece(x, y);
    /*if (!piece.color)
        return false;
    else*/
        return (piece.color-1 == color % 2);
}

bool convert_coordinates(int color, char *from, char *to)
{
    //jezeli wprowadzono niepoprawne wartosci zwraca false by ponownie wczytac input
    //wpp zwraca wywoluje funkcje perform move z podanymi koordynatami
    //zamienia a-h na 0-7 oraz 1-8 na 0-7
    int coords[4];
    coords[0] = (tolower(from[0]) - 'a'); //coords "from"
    coords[1] = -from[1] + ('1')+7;
    coords[2] = (tolower(to[0]) - 'a'); //coords "to"
    coords[3] = -to[1] + ('1')+7;
    
    ///// Zostawić na wypadek konieczności debugowania
    /*FILE *f = fopen("out.txt", "w+");
	fprintf( f, "%d %d %d %d\n", coords[0], coords[1], coords[2], coords[3]);
	fclose(f);*/
	
    for (int i = 0; i < 4; i++)
    {
        if (!is_valid_coord(coords[i]))
        {
            return 0;
        }
    }
    
    if (owns_piece(color, coords[0], coords[1]))
    {
        return performMove(coords[0], coords[1], coords[2], coords[3]);
    }
    return 0;
}
//funkcja wyswietla interfejs wybierania figury
//oraz zwraca jaką figure wybrano następnie ponownie
//laduje plansze
//nie podlaczona do niczego
int choosePiece()
{
    noecho();
    WINDOW *SelectPiece =  newwin(6,16,47,33);
    box(SelectPiece,0,0);

    refresh();
    wrefresh(SelectPiece);

    keypad(SelectPiece,true);
    char choices[4][10] = {
        "Wieza",
        "Kon",
        "Goniec",
        "Hetman"
    };
    int ch;
    int highlight = 0;
    bool isPicekd = false;
    
    init_pair(20, COLOR_WHITE, 124);
    init_pair(21,124, COLOR_WHITE);
    wbkgd(SelectPiece, COLOR_PAIR(20));

    mvwaddstr(SelectPiece, 0, 1, "Wybierz figure");
    while(!isPicekd)
    {
        for(int i = 0; i < 4; i++)
        {
            if(i == highlight)
            {   
                wattron(SelectPiece,COLOR_PAIR(21));
                mvwaddstr(SelectPiece, i+1, 1, choices[i]);
                wattroff(SelectPiece,COLOR_PAIR(21));
            }
            else
                mvwprintw(SelectPiece, i+1, 1, "%s", choices[i]);
        }
        wrefresh(SelectPiece);
        refresh();

        ch = wgetch(SelectPiece);
        switch (ch)
        {
            case KEY_UP:
                highlight--;
                break;
            case KEY_DOWN:
                highlight++;
                break;
            case 10://enter
                isPicekd = true;
                break;
            default:
                continue;
        }
        if(highlight > 3) highlight--;
        if(highlight < 0) highlight++;
    }
    wclear(SelectPiece);
    wbkgd(SelectPiece,COLOR_PAIR(25));
    wrefresh(SelectPiece);
    delwin(SelectPiece);

    draw_board();
    return 2 + highlight;//zgodnie z oznaczeniem typów figur
}
void main_loop()
{
    WINDOW *coords_input = newwin(4, 21, 47, 10);
    WINDOW *From = newwin(1, 3, 48, 19);
    WINDOW *To = newwin(1, 3, 49, 20);

    box(coords_input, 0, 0);
    char from[2];
    char to[2];
    int i = 1;
    bool game_over = false;

    box(coords_input, 0, 0);
    mvwprintw(coords_input, 1, 1, "Ruch z:  ");
    mvwprintw(coords_input, 2, 1, "Ruch na: ");
    wrefresh(coords_input);
    draw_board();
    while (!game_over)
    {
        echo();
        do
        { //petla wczytujaca koordynaty wykona sie minimum raz, az do wprowadzenia "poprawnych"
			wrefresh(coords_input);
            box(coords_input, 0, 0);
            if (i % 2 == 0)
                mvwprintw(coords_input, 0, 4, "Ruch-czarnego");
            else
                mvwprintw(coords_input, 0, 4, "Ruch-bialego");
            wrefresh(coords_input);

            wscanw(From, "%s", from);
            move(49, 20);
            wscanw(To, "%s", to);
            wclear(From);
            wclear(To);
            draw_board();
		if(tolower(from[0]) == 'e' && tolower(from[1]) == 'x' &&
		tolower(to[0]) == 'i' && tolower(to[1]) == 't') return;
        } while (!convert_coordinates(i, from, to));
		 draw_board();
		 
		 int status =  checkWinCondition();
		 if(status == 1) {
			//Wygrywa gracz 2
			game_over = true;
		 } 
		 if(status == 2) {
			//Wygrywa gracz 1
			game_over = true;
		 } 
    
        i++;
    }
}
void draw_coordinates(WINDOW *board)
{
    init_pair(3, COLOR_WHITE, 239);
    char coord_arts[16][3][4] = {

        {//8
         {' ', '_', ' ', ' '},
         {'(', '_', ')', ' '},
         {'(', '_', ')', ' '}},
        {//7
         {'_', '_', ' ', ' '},
         {' ', '/', ' ', ' '},
         {'/', ' ', ' ', ' '}},
        {//6
         {' ', ' ', ' ', ' '},
         {' ', '/', ' ', ' '},
         {'(', '_', ')', ' '}},
        {//5
         {' ', '_', ' ', ' '},
         {'|', '_', ' ', ' '},
         {' ', '_', ')', ' '}},
        {//4
         {' ', ' ', '.', ' '},
         {' ', '/', '|', ' '},
         {'\'', '-', '|', ' '}},
        {//3
         {'_', ' ', ' ', ' '},
         {'_', ')', ' ', ' '},
         {'_', ')', ' ', ' '}},
        {//2
         {'_', ' ', ' ', ' '},
         {' ', ')', ' ', ' '},
         {'/', '_', ' ', ' '}},
        {//1
         {' ', '.', ' ', ' '},
         {'/', '|', ' ', ' '},
         {' ', '|', ' ', ' '}},
        {//A
         {' ', ' ', ' ', ' '},
         {' ', '/', '\\', ' '},
         {'/', '-', '-', '\\'}},
        {//B
         {' ', '_', ' ', ' '},
         {'|', '_', ')', ' '},
         {'|', '_', ')', ' '}},
        {//C
         {' ', '_', ' ', ' '},
         {'/', ' ', ' ', ' '},
         {'\\', '_', ' ', ' '}},
        {//D
         {' ', '_', ' ', ' '},
         {'|', ' ', '\\', ' '},
         {'|', '_', '/', ' '}},
        {//E
         {' ', '_', '_', ' '},
         {'|', '_', ' ', ' '},
         {'|', '_', '_', ' '}},
        {//F
         {' ', '_', '_', ' '},
         {'|', '_', ' ', ' '},
         {'|', ' ', ' ', ' '}},
        {//G
         {' ', '_', ' ', ' '},
         {'/', '_', ' ', ' '},
         {'\\', '_', '|', ' '}},
        {//H
         {' ', ' ', ' ', ' '},
         {'|', '_', '|', ' '},
         {'|', ' ', '|', ' '}}};
    attron(COLOR_PAIR(1));
    for (int k = 0; k < 8; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mvaddch(i + (5 * k) + 6, j + 3, coord_arts[k][i][j]);
            }
        }
    }
    for (int k = 8; k < 16; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mvaddch(i + 1, j - 82 + (12 * k), coord_arts[k][i][j]);
            }
        }
    }
    attroff(COLOR_PAIR(1));
}
//funkcja sprawdza kolor pola na ktorym ma byc wyrysowana figura
bool field_color(int x, int y)
{ //jesli szare zwraca true, jesli czerwone zwraca false
    return !((x + y) % 2);
}
void draw_pieces(WINDOW *board)
{
    int color;
    init_pair(10, COLOR_BLACK, b_b);
    init_pair(11, COLOR_WHITE, b_b);
    init_pair(12, COLOR_BLACK, 239);
    init_pair(13, COLOR_WHITE, 239);

    char pieces[7][4][11] = {
        {//pionek
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}},
        {//pionek
         {' ', ' ', ' ', '(', ' ', ' ', ' ', ')', ' ', ' ', ' '},
         {' ', ' ', ' ', ')', ')', '|', '(', '(', ' ', ' ', ' '},
         {' ', ' ', '(', ' ', ' ', ' ', ' ', ' ', ')', ' ', ' '},
         {' ', '[', '|', '|', '|', '|', '|', '|', '|', ']', ' '}},
        {//wieza
         {' ', '[', '`', '\'', '`', '\'', '`', '\'', '`', ']', ' '},
         {' ', ' ', '|', '+', '+', '+', '+', '+', '|', ' ', ' '},
         {' ', ' ', '|', '+', '+', '+', '+', '+', '|', ' ', ' '},
         {' ', ' ', '|', '+', '+', '+', '+', '+', '|', ' ', ' '}},
        {//kon
         {' ', ' ', ' ', '\\', '`', '~', '\'', '/', ' ', ' ', ' '},
         {' ', ' ', ' ', '(', 'o', ' ', 'o', ')', ' ', ' ', ' '},
         {' ', ' ', ' ', '/', '\\', ' ', '/', '\\', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', ' ', '"', ' ', ' ', ' ', ' ', ' '}},
        {//goniec
         {' ', ' ', ' ', '/', ' ', '+', ' ', '\\', ' ', ' ', ' '},
         {' ', ' ', ' ', '\\', ' ', ' ', ' ', '/', ' ', ' ', ' '},
         {' ', ' ', ' ', '(', 'o', ' ', 'o', ')', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', '(', '_', ')', ' ', ' ', ' ', ' '}},
        {//hetman
         {' ', ' ', ' ', ' ', '_', '_', '_', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', '/', '\\', '*', '/', '\\', ' ', ' ', ' '},
         {' ', ' ', '/', '(', 'o', ' ', 'o', ')', '\\', ' ', ' '},
         {' ', ' ', ' ', ' ', '(', '_', ')', ' ', ' ', ' ', ' '}},
        {//krol
         {' ', ' ', ' ', ' ', ' ', '+', ' ', ' ', ' ', ' ', ' '},
         {' ', ' ', ' ', '/', '\\', '^', '/', '\\', ' ', ' ', ' '},
         {' ', ' ', ' ', '(', '-', '_', '-', ')', ' ', ' ', ' '},
         {' ', ' ', ' ', ' ', '(', '_', ')', ' ', ' ', ' ', ' '}}};
    attron(A_BOLD);
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            ChessPiece piece_to_draw = getChessPiece(x, y);
            color = piece_to_draw.color + (field_color(x, y) * 2) + 9;
            if(!piece_to_draw.color) color++;

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 11; j++)
                {
                        mvwaddch(board, i + (y * 5) + 1, j + (x * 12) + 1, pieces[piece_to_draw.type][i][j] | COLOR_PAIR(color));
                }
            }
        }
    }
    attroff(A_BOLD);
}

void draw_board()
{
    start_color();
    char board[9][9];
    WINDOW *playing_board = newwin(41, 97, 5, 10);

    // RYSOWANIE PLANSZY

    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // linie kolor
    init_pair(2, COLOR_WHITE, b_b);          // background kolor (czerwony)
    init_pair(3, COLOR_WHITE, 239);          //kolor szary

    wattron(playing_board, COLOR_PAIR(1));
    box(playing_board, 0, 0);
    for (int y = 5; y < 48; y += 5) // podzial poziomy
    {
        mvwhline(playing_board, y, 1, 0, 95);
    }
    for (int x = 12; x < 96; x += 12) // podzial pionowy
    {
        mvwvline(playing_board, 0, x, 0, 40);
    }
    for (int x = 12; x < 96; x += 12)
        mvwhline(playing_board, 40, x, ACS_BTEE, 1); // laczenia dolne
    for (int x = 12; x < 96; x += 12)
        mvwhline(playing_board, 0, x, ACS_TTEE, 1); // laczenia gorne
    for (int y = 5; y < 40; y += 5)
        mvwvline(playing_board, y, 96, ACS_RTEE, 1); // laczenia prawe
    for (int y = 5; y < 40; y += 5)
        mvwvline(playing_board, y, 0, ACS_LTEE, 1); // laczenia lewe
    for (int i = 12; i < 96; i += 12)
        for (int j = 5; j < 40; j += 5) // laczenia wewnetrzne
            mvwaddch(playing_board, j, i, ACS_PLUS);
    wattroff(playing_board, COLOR_PAIR(1));

    draw_coordinates(playing_board);
    draw_pieces(playing_board);
    refresh();
    wrefresh(playing_board);
}
void main_menu()
{
    WINDOW *MenuContainer = newwin(LINES, COLS, 0, 0);
    WINDOW *MenuPanel = subwin(MenuContainer, 10, 15, LINES/2-5, COLS/2-8);
    WINDOW *MenuAscii = subwin(MenuContainer, LINES/2-5,101,1,COLS/2-49);
    FILE *chess;
    char ch;
    
    init_pair(23, 89, 107);                     //font-roz, backg- zielen
    init_pair(24, 107, 89);                     //na odwrot^
    init_pair(25,COLOR_WHITE,COLOR_BLACK);      //standardowy kolor terminala
    bkgd(COLOR_PAIR(23));                       //bgcolor MenuContainer
    wbkgd(MenuAscii,COLOR_PAIR(23));            //bgcolor MenuAscii
    wbkgd(MenuPanel,COLOR_PAIR(23));            //bgcolor MenuPanel

    chess = fopen("obrazek.txt","r");
    if(chess == NULL)
    {   wprintw(MenuAscii,"Error, nie udalo otworzyc sie pliku");
        wrefresh(MenuAscii);
    }
    wmove(MenuAscii,0,0);

    // WYSWIETLENIE ASCII ART
    wattron(MenuAscii,COLOR_PAIR(23) | A_BOLD);
    while((ch = fgetc(chess)) != EOF)
        waddch(MenuAscii,ch);
    wattroff(MenuAscii,COLOR_PAIR(23) | A_BOLD);

    fclose(chess);
    refresh();
    wrefresh(MenuPanel);
    wrefresh(MenuAscii);
    
    // OPCJE MENU
    keypad(MenuPanel,true);
    char choices[4][12] = {
        "Zwykla gra",
        "Horda",
        "Rewolucja",
        "Wyjdz z gry"
    };
    bool isPicked = false;
    int highlight = 0;
    int act;
    wmove(MenuPanel,1,1);

    // PETLA WYBORU
    while(!isPicked)
    {
        for(int i = 0; i < 4; i++)
        {
            if(i == highlight)
            {   
                wattron(MenuPanel,COLOR_PAIR(24));
                mvwaddstr(MenuPanel, i+1, 1, choices[i]);
                wattroff(MenuPanel,COLOR_PAIR(24));
            }
            else
                mvwprintw(MenuPanel, i+1, 1, "%s", choices[i]);
        }
        wrefresh(MenuPanel);
        refresh();

        act = wgetch(MenuPanel);
        switch (act)
        {
            case KEY_UP:
                highlight--;
                break;
            case KEY_DOWN:
                highlight++;
                break;
            case 10://enter
                isPicked = true;
                break;
            default:
                continue;
        }
        if(highlight > 3) highlight--;
        if(highlight < 0) highlight++;
    }
    
	wclear(MenuContainer);
	bkgd(COLOR_PAIR(25));
	delwin(MenuContainer);
	clear();
    
    switch (highlight)
    {
        case 0:
            gameInit();
            main_loop();
            break;
        case 1:
			gameInit();
			gameHoardInit();
            main_loop();
            break;
        case 2:
			gameInit();
			gameRevoltInit();
            main_loop();
            break;
        case 3:
            exit(0);
            break;
        default:
            break;
    }
}
