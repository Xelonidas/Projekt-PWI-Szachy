#include <stdbool.h>
#include <stdlib.h>
#include <ncurses.h>
#include "structure.h"
#include "gamerules.h"
#include "front.h"

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
void gameHoardInit() {
	ChessPiece whitePawn = getChessPiece(0, 6);
	for(int i = 0; i <= 7; i++)
		if(i != 4)
			setChessPiece(whitePawn, i, 7);
			
	for(int i = 0; i <= 7; i++) {
		setChessPiece(whitePawn, i, 5);
		setChessPiece(whitePawn, i, 4);
	}
	setChessPiece(whitePawn, 1, 3);
	setChessPiece(whitePawn, 2, 3);
	setChessPiece(whitePawn, 5, 3);
	setChessPiece(whitePawn, 6, 3);
}
void gameRevoltInit() {
	for(int i = 0; i <= 7; i++) {
		if(i != 4) {
			removeChessPiece(i, 7);
			removeChessPiece(i, 1);
		}
	}
	ChessPiece blackKnight = getChessPiece(1, 0);
	setChessPiece(blackKnight, 0, 0);
	removeChessPiece(1, 0);
	setChessPiece(blackKnight, 2, 0);
	removeChessPiece(3, 0);
	removeChessPiece(5, 0);
	setChessPiece(blackKnight, 6, 0);
	removeChessPiece(7, 0);
}

bool performMove(int xA, int yA, int xB, int yB) {
	//nie można wykonać ruchu w miejscu
	if(xA == xB && yA == yB) return false;
	ChessPiece chessPiece = getChessPiece(xA, yA);
	if(!getChessPiece(xA, yA).moveFunctionPointer(chessPiece.color, xA, yA, xB, yB)) {
		return false;
	}
	if(chessPiece.color == getChessPiece(xB, yB).color)
			return false;

	chessPiece = getChessPiece(xA, yA);
	removeChessPiece(xA, yA);
	setChessPiece(chessPiece, xB, yB);
	return true;
}

//Podejście "branchless" bo ifowanie jest mniej czytelne
bool emptyTileMove(int color, int xA, int yA, int xB, int yB) {
	return false;
}

bool checkPawnsMove(int color, int xA, int yA, int xB, int yB) {
    if(getChessPiece(xA, yA).color == 1){
        //sprawdzenie ruchu po skosie w przypadku bicia
        if((xB == xA-1 || xB == xA+1) && yB == yA+1){
            if(getChessPiece(xB, yB).color != 2) return false;
        }
        //ruch o 2 pola do przodu
        else if(yB == yA+2){
            if(getChessPiece(xA, yA+1).type != 0 || getChessPiece(xB, yB).type !=0 || yA != 1) return false;
        }
        else if(yB == yA+1){
            if(getChessPiece(xB, yB).type != 0) return false;
        }
        else return false;

        if(yB == 7){

			int choice = choosePiece();
			ChessPiece new;
			new.color = 1;
			switch(choice) {
				case 2: //wieża
					new.type = 2;
					new.moveFunctionPointer = &checkRookMove;
				break;
				case 3: //koń
					new.type = 3;
					new.moveFunctionPointer = &checkKnightMove;
				break;
				case 4: //goniec
					new.type = 4;
					new.moveFunctionPointer = &checkBishopMove;
				break;
				default: //królowa
					new.type = 5;
					new.moveFunctionPointer = &checkQueenMove;
			}

			setChessPiece(new, xA, yA);
		}
        return true;
	}
	if(getChessPiece(xA, yA).color == 2){
	//sprawdzenie ruchu po skosie w przypadku bicia
		if((xB == xA-1 || xB == xA+1) && yB == yA-1){
			if(getChessPiece(xB, yB).color != 1) return false;
		}
		//ruch o 2 pola do przodu
		else if(yB == yA-2){
			if(getChessPiece(xA, yA-1).type != 0 || getChessPiece(xB, yB).type !=0 || yA != 6) return false;
		}
		else if(yB == yA-1){
			if(getChessPiece(xB, yB).type != 0) return false;
		}
		else return false;

		if(yB == 0){
			int choice = choosePiece();
			ChessPiece new;
			new.color = 2;
			switch(choice) {
				case 2: //wieża
					new.type = 2;
					new.moveFunctionPointer = &checkRookMove;
				break;
				case 3: //koń
					new.type = 3;
					new.moveFunctionPointer = &checkKnightMove;
				break;
				case 4: //goniec
					new.type = 4;
					new.moveFunctionPointer = &checkBishopMove;
				break;
				default: //królowa
					new.type = 5;
					new.moveFunctionPointer = &checkQueenMove;
			}

			setChessPiece(new, xA, yA);
		}
		return true;
	}
	return false;
}

//goniec
//TODO sprawdzenie czy pola pomiędzy A i B są puste
bool checkBishopMove(int color, int xA, int yA, int xB, int yB) {
	//sprawdzenie czy ruch jest po skosie
	if(xA - yA == xB - yB || xA + yA == xB + yB) {
        if(xB > xA && yB > yA){ //down & right
            for(int i=1;i<(xB-xA-1);i++){
				if(getChessPiece(xA+i,yA+i).type != 0) return false;
			}
		}
        if(xB > xA && yB < yA){ //up & right
            for(int i=1;i<(xB-xA-1);i++){
				if(getChessPiece(xA+i,yA-i).type != 0) return false;
			}
		}
        if(xB < xA && yB > yA){ //down & left
            for(int i=1;i<(xA-xB-1);i++){
				if(getChessPiece(xB+i,yB-i).type != 0) return false;
			}
		}
        if(xB < xA && yB < yA){ //up & left
            for(int i=1;i<(xA-xB-1);i++){
				if(getChessPiece(xB+i,yB+i).type != 0) return false;
			}
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
    ChessPiece Queen = getChessPiece(xA, yA);
	return checkRookMove(Queen.color, xA, yA, xB, yB) | checkBishopMove(Queen.color, xA, yA, xB, yB);
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

int checkWinCondition() {
	if(isKingChecked(1) == 0) return 2;
	if(isKingChecked(2) == 0) return 1;
	return 0;
}

int isKingChecked(int color) {
	int kingx, kingy, status = 0;
	for(int y = 0; y < 8; y++) {
		for(int x = 0; x < 8; x++) {
			if(getChessPiece(x, y).type == 6 && getChessPiece(x, y).color == color) {
				kingx = x; kingy = y; status = 1;
			}
		}
	}
	if(status == 0) return 0;
	
	ChessPiece cp;
	for(int y = 0; y < 8; y++) {
		for(int x = 0; x < 8; x++) {
			cp = getChessPiece(x, y);
			if(cp.color + color == 3 && cp.moveFunctionPointer(cp.color, x, y, kingx, kingy)) return 1;
		}
	}
	return 2;
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
