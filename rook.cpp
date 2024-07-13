#include "rook.h"

rook::rook(int x, int y, bool col)
{
	pieceType = "rook";
	current_x = x;
	current_y = y;
	color = col;
}

bool rook::isvalidmove(int destx, int desty)
{
	return ((abs(destx - current_x) > 0 && (desty - current_y) == 0)
		|| (abs(desty - current_y) > 0 && (destx - current_x) == 0));

}