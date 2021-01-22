#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/*	Dane:
 * 		color:
 * 			0 - puste pole
 * 			1 - białe
 * 			2 - czarne
 * 		typ:
 * 			0 - puste pole
 * 			1 - pionek/pawn
 * 			2 - wieża/rook
 * 			3 - koń/knight
 * 			4 - goniec/bishop
 * 			5 - dama/quenn
 * 			6 - król/king
 */
 
// struktura pionka szachowego
typedef struct cp {
    int X; // przechowuje wiersz
    int Y; // przechowuje kolumne
    int color; // przechowuje kolor
    int type; // przechowuje typ
    bool (*moveFunctionPointer)(int color, int xA, int yA, int xB, int yB); // przechowuje funkcje ruchu pionka
} ChessPiece;

// allokuje pamiec na pionek i przypisuje mu wartosci poczatkowe
ChessPiece *initChessPiece(int xA, int yA, int color, int type, bool (*moveFunctionPointer)(int color, int xA, int yA, int xB, int yB));

// zwraca pionek znajdujacy sie na danym polu
ChessPiece getChessPiece(int xA, int yA);

// usuwa pionek znajdujacy sie na danym polu
void removeChessPiece(int xA, int yA);

// ustawia pionek na dane pole
void setChessPiece(ChessPiece piece, int xB, int yB);
