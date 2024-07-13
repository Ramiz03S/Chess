#include "pawn.h"

pawn::pawn(int x, int y, bool col) {
	pieceType = "pawn";
	current_x = x;
	current_y = y;
	color = col;
}

bool pawn::isvalidmove(int destx, int desty)
{
	if (color == 1) {
		if (moved == 0) {
			if (0 < (destx - current_x) && (destx - current_x) < 3 && (desty - current_y == 0)) {
				return 1;
			}
			if (0 < (destx - current_x) && (destx - current_x) < 2 && abs(desty - current_y) == 1) {
				return 1;
			}
		}
		if (moved == 1) {
			if (0 < (destx - current_x) && (destx - current_x) < 2 && (desty - current_y == 0)) {
				return 1;
			}
			if (0 < (destx - current_x) && (destx - current_x) < 2 && abs(desty - current_y) == 1) {
				return 1;
			}
		}
	}
	if (color == 0) {
		if (moved == 0) {
			if ((0 < (current_x - destx)) && ((current_x - destx) < 3) && (desty - current_y == 0)) {
				return 1;
			}
			if (0 < (current_x - destx) && (current_x - destx) < 2 && abs(desty - current_y) == 1) {
				return 1;
			}
		}
		if (moved == 1) {
			if (0 < (current_x - destx) && (current_x - destx) < 2 && (desty - current_y == 0)) {
				return 1;
			}
			if (0 < (current_x - destx) && (current_x - destx) < 2 && abs(desty - current_y) == 1) {
				return 1;
			}
		}
	}
	return 0;
}