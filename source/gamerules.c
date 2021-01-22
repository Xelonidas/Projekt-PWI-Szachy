#include <stdbool.h>
#include <stdlib.h>
#include "structure.h"
#include "gamerules.h"

void gameInit() {
	ChessPiece newChessPiece;
	//------WIEŻE---------
	newChessPiece.color = 1;
	newChessPiece.type = 2;
	newChessPiece.moveFunctionPointer = &checkRookMove;
	setChessPiece(newChessPiece, 0, 0);
	setChessPiece(newChessPiece, 7, 0);

	newChessPiece.color = 2;
	setChessPiece(newChessPiece, 0, 7);
	setChessPiece(newChessPiece, 7, 7);
	//--------KONIE---------
	newChessPiece.type = 3;
	newChessPiece.color = 1;
	newChessPiece.moveFunctionPointer = &checkKnightMove;
	setChessPiece(newChessPiece, 1, 0);
	setChessPiece(newChessPiece, 6, 0);

	newChessPiece.color = 2;
	setChessPiece(newChessPiece, 1, 7);
	setChessPiece(newChessPiece, 6, 7);

	//--------GOŃCE-----------
	newChessPiece.color = 1;
	newChessPiece.type = 4;
	newChessPiece.moveFunctionPointer = &checkBishopMove;
	setChessPiece(newChessPiece, 2, 0);
	setChessPiece(newChessPiece, 5, 0);

	newChessPiece.color = 2;
	setChessPiece(newChessPiece, 2, 7);
	setChessPiece(newChessPiece, 5, 7);

	//--------KRÓLOWE----------
	newChessPiece.color = 1;
	newChessPiece.type = 5;
	newChessPiece.moveFunctionPointer = &checkQueenMove;
	setChessPiece(newChessPiece, 3, 0);

	newChessPiece.color = 2;
	setChessPiece(newChessPiece, 3, 7);

	//--------KRÓLOWIE----------

	newChessPiece.color = 1;
	newChessPiece.type = 6;
	newChessPiece.moveFunctionPointer = &checkKingMove;
	setChessPiece(newChessPiece, 4, 0);
	newChessPiece.color = 2;
	setChessPiece(newChessPiece, 4, 7);

	//-------PIONKI-----------

	newChessPiece.color = 1;
	newChessPiece.type = 1;
	newChessPiece.moveFunctionPointer = &checkPawnsMove;
	for(int i = 0 ; i < 8; i++) {
		setChessPiece(newChessPiece, i, 1);
	}
	newChessPiece.color = 2;
	for(int i = 0 ; i < 8; i++) {
		setChessPiece(newChessPiece, i, 6);
	}
	//-----PUSTE POLA--------

	newChessPiece.color = 0;
	newChessPiece.type = 0;
	newChessPiece.moveFunctionPointer = &emptyTileMove;
	for(int i = 0 ; i < 8; i++) {
		for(int j = 2; j < 6; j++)
		setChessPiece(newChessPiece, i, j);
	}

	return;
}

bool performMove(int xA, int yA, int xB, int yB) {
	//nie można wykonać ruchu w miejscu
	if(xA == xB && yA == yB) return false;
	ChessPiece chessPiece = getChessPiece(xA, yA);
	if(!chessPiece.moveFunctionPointer(chessPiece.color, xA, yA, xB, yB)) {
		return false;
	}
	if(getChessPiece(xA, yA).color == getChessPiece(xB, yB).color)
			return false;
	removeChessPiece(xA, yA); removeChessPiece(xB, yB);
	setChessPiece(chessPiece, xB, yB);
	return true;
}

//Podejście "branchless" bo ifowanie jest mniej czytelne
bool emptyTileMove(int color, int xA, int yA, int xB, int yB) {
	return false;
}

bool checkPawnsMove(int color, int xA, int yA, int xB, int yB) {
	return false;
}

//goniec
//TODO sprawdzenie czy pola pomiędzy A i B są puste
bool checkBishopMove(int color, int xA, int yA, int xB, int yB) {
	//sprawdzenie czy ruch jest po skosie
	if(xA - yA == xB - yB) {
        for(int i = min(xB, xA) + 1; i < max(xB, xA); i++) {
            if(getChessPiece(i, yA).type != 0) return false;
        }
        return true;
    }
    return false;
}

//koń
bool checkKnightMove(int color, int xA, int yA, int xB, int yB) {
	//koń może się poruszyć o -/+ 1/2 pola w pionie i -/+ 2/1 pola w poziomie
	//suma musi być równa 3 i każdy z dystansów minimum 1
	if(abs(xA-xB) + abs(yA-yB) == 3 && abs(xA-xB) > 0 && abs(yA- yB) > 0)
		return true;
	return false;
}

//wieża
bool checkRookMove(int color, int xA, int yA, int xB, int yB) {
	//wieża przesuwa się wzdłuz jednej osi
	if(xA != xB && yA != yB) return false;

	if(xA == xB) {
		for(int i = min(yB, yA) + 1; i < max(yB, yA); i++) {
			if(getChessPiece(xA, i).type != 0) return false;
		}
		return true;
	}
	//else
	for(int i = min(xB, xA) + 1; i < max(xB, xA); i++) {
		if(getChessPiece(i, yA).type != 0) return false;

	}

	return true;
}

bool checkQueenMove(int color, int xA, int yA, int xB, int yB) {
	//można wykorzystać gotowe funkcje dla gońca i wieży
	if(xA != xB && yA != yB && (xA - yA) != (xB - yB)) return false;

	if(xA == xB) {
		for(int i = min(yB, yA) + 1; i < max(yB, yA); i++) {
			if(getChessPiece(xA, i).type != 0) return false;
		}
		return true;
	}
	if(yA == yB) {
        for(int i = min(xB, xA) + 1; i < max(xB, xA); i++) {
            if(getChessPiece(i, yA).type != 0) return false;
        }
        return true;
    }
    else if(xA - yA == xB - yB) {
        for(int i = min(xB, xA) + 1; i < max(xB, xA); i++) {
            if(getChessPiece(i, yA).type != 0) return false;
        }
        return true;
    }

	return false;
}

bool checkKingMove(int color, int xA, int yA, int xB, int yB) {
	if(abs(xA-xB) <= 1 && abs(yA-yB) <= 1) return true;
	//próba wykonania roszady
	if(color == 1 && xA == 4 && yA == 0 && yB == 0 && abs(xA-xB) == 2) {
		if(xB == 2) {
			ChessPiece Rook = getChessPiece(0, 0);
			if(Rook.color == 1 && Rook.type == 2 &&
				 getChessPiece(1, 0).type == 0 &&
				 getChessPiece(2, 0).type == 0 &&
				 getChessPiece(3, 0).type ==  0) {
				
				removeChessPiece(0,0);
				setChessPiece(Rook ,3, 0);
				return true;
			 }
		}
		if(xB == 6) {
			ChessPiece Rook = getChessPiece(7, 0);
			if(Rook.color == 1 && Rook.type == 2 &&
				 getChessPiece(6, 0).type == 0 &&
				 getChessPiece(4, 0).type == 0) {
				removeChessPiece(7,0);
				setChessPiece(Rook ,5, 0);
				return true;
			 }
		}
	}
	if(color == 2 && xA == 4 && yA == 7 && yB == 7 && abs(xA-xB) == 2) {
		if(xB == 2) {
			ChessPiece Rook = getChessPiece(7, 0);
			if(Rook.color == 1 && Rook.type == 2 &&
				 getChessPiece(1, 7).type == 0 &&
				 getChessPiece(2, 7).type == 0 &&
				 getChessPiece(3, 7).type ==  0) {
				
				removeChessPiece(0,7);
				setChessPiece(Rook ,3, 7);
				return true;
			 }
		}
		if(xB == 6) {
			ChessPiece Rook = getChessPiece(7, 7);
			if(Rook.color == 1 && Rook.type == 2 &&
				 getChessPiece(6, 7).type == 0 &&
				 getChessPiece(4, 7).type == 0) {
				removeChessPiece(7,7);
				setChessPiece(Rook ,5, 7);
				return true;
			 }
		}
	}
	
	return false;  
}

int checkWinCondition(int color) {
	return 0;
}

bool isKingChecked(int color) {
	int kingx, kingy;
	for(int y = 0; y < 8; y++) {
		for(int x = 0; x < 8; x++) {
			if(getChessPiece(x, y).type == 6 && getChessPiece(x, y).color == color) {
				kingx = x; kingy = y;
			}
		}
	}
	ChessPiece cp;
	for(int y = 0; y < 8; y++) {
		for(int x = 0; x < 8; x++) {
			cp = getChessPiece(x, y);
			if(cp.color + color == 3 && cp.moveFunctionPointer(cp.color, x, y, kingx, kingy)) return true;
		}
	}
	return false;
}

void DisplayArrayContent() {
	for(int y = 0; y < 8; y++) {
		for(int x = 0; x < 8; x++) {
			ChessPiece cp = getChessPiece(x, y);
			printf("%d:%d ",cp.type, cp.color);
		}
		putchar('\n');
	}
}
