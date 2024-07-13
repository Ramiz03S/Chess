#include "bishop.h"

bishop::bishop(int x, int y, bool col) 
{
	pieceType = "bishop";
	current_x = x;
	current_y = y;
	color = col;
}

bool bishop::isvalidmove(int destx, int desty) {
	return (abs(destx - current_x) == abs(desty - current_y));
}