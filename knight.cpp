#include "knight.h"

knight::knight(int x, int y, bool col) 
{
	pieceType = "knight";
	current_x = x;
	current_y = y;
	color = col;
}

bool knight::isvalidmove(int destx, int desty) 
{
	return ((abs(destx - current_x) == 2 && abs(desty - current_y) == 1)
		|| (abs(destx - current_x) == 1 && abs(desty - current_y) == 2));
}