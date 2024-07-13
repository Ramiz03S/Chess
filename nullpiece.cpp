#include "nullpiece.h"

nullpiece::nullpiece(int x, int y) {
    pieceType = "nullpiece";
    current_x = x;
    current_y = y;
}

bool nullpiece::isvalidmove(int destx, int desty) {
    return 0;
}