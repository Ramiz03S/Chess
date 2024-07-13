#pragma once
#include "piece.h"
#include<string>
#include <iostream>
using namespace std;

class pawn :
    public piece
{

public:
	pawn(int x, int y, bool col);
	bool isvalidmove(int destx, int desty);
	
};

