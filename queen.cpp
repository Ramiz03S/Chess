#include "queen.h"

queen::queen(bool col)
{
	pieceType = "queen";
	if (col == 1) {
		current_x = 1;
		current_y = 4;
		color = col;

	}
	else
	{
		current_x = 8;
		current_y = 4;
		color = col;
	}
}

queen::queen(int x, int y, bool col) {
	pieceType = "queen";
	current_x = x;
	current_y = y;
	color = col;
}

bool queen::isvalidmove(int destx, int desty)
{
	return (
		(abs(destx - current_x) > 0 && (desty - current_y) == 0)
		||
		(abs(desty - current_y) > 0 && (destx - current_x) == 0)
		||
		(abs(destx - current_x) == abs(desty - current_y))
		);
}