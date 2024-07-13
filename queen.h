#pragma once
#include "piece.h"
#include<string>
#include <iostream>
using namespace std;

class queen :
    public piece
{
public:
	queen(bool col);
	queen(int x, int y, bool col);
	bool isvalidmove(int destx, int desty);
};

