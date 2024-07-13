#pragma once
#include "piece.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "nullpiece.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Board
{private:
	piece* board[8][8]; 
	int counter;
public:
	Board();

	Board(int i);

	bool nopieceObstruct(int ox, int oy, int dx, int dy);

	bool pawncapturevalid(int ox, int oy, int dx, int dy);

	bool incheck(int dx, int dy);

	bool turn(int ox, int oy);

	void move(int ox, int oy, int dx, int dy);

	void move_puzzle(int ox, int oy, int dx, int dy);

	void print_board();
};
