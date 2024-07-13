#pragma once
#include "piece.h"
#include<string>
#include <iostream>
using namespace std;

class rook :
    public piece
{
private:
public:
	rook(int x, int y, bool col);
	bool isvalidmove(int destx, int desty);

};

