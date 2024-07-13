#include "king.h"

king::king(bool col)
{
	pieceType = "king";
	if (col == 1) {
		current_x = 1;
		current_y = 5;
		color = col;
	}
	else
		current_x = 8;
		current_y = 5;
		color = col;
}

king::king(int x, int y, bool col)
{
	pieceType = "king";
	current_x = x;
	current_y = y;
	color = col;
}

bool king::isvalidmove(int destx, int desty) {
	return ((abs(destx - current_x) <= 1) && (abs(desty - current_y) <= 1));
}