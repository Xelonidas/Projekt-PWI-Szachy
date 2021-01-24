//Funkcja wczytuje domyślny stan planszy
void gameInit();
void gameHoardInit();
void gameRevoltInit();
//Poniższe funkcje sprawdzają czy dany pionek może się poruszyć z pola A na pole B
//Jeśli może to funkcja zwraca true w przeciwnym przypadku zwracany jest false
bool emptyTileMove(int color, int xA, int yA, int xB, int yB);
bool checkPawnsMove(int color, int xA, int yA, int xB, int yB);
bool checkBishopMove(int color, int xA, int yA, int xB, int yB);
bool checkKnightMove(int color, int xA, int yA, int xB, int yB);
bool checkRookMove(int color, int xA, int yA, int xB, int yB);
bool checkQueenMove(int color, int xA, int yA, int xB, int yB);
bool checkKingMove(int color, int xA, int yA, int xB, int yB);
/*
 *	0 - król zbity
 *  1 - król szachowany 
 *  2 - król bezpieczny
 */
int isKingChecked(int color);

//performMove przyjmuje informacje o ruchy który trzeba wykonać.
//sprawdzi za pomocą powyższych funkcji ckeckXYZMove(...) czy ruch może zostać wykonany
//jeśli można go wykonać, to stan planszy zostanie zaktualizowany i zwrócony zostanie true
bool performMove(int xA, int yA, int xB, int yB);

//Funkcja sprawdza planszę i zwraca informacje o ewentualnym końcu gry
// 0 - Nikt nie wygrał
// 1 - wygrał gracz 1
// 2 - wygrał gracz 2
int checkWinCondition();

#ifndef abs
	#define abs(x) (((x) > 0)? (x) : (-(x)))
#endif
#ifndef min
	#define min(x, y) (((y) > (x))? (x) : (y))
#endif
#ifndef max
	#define max(x, y) (((y) > (x))? (y) : (x))
#endif

//Tymczasowa funkcja pomocnicza
void DisplayArrayContent();
