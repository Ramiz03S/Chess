#pragma once
#include "piece.h"
#include<string>
#include <iostream>
using namespace std;

class king :
    public piece
{

public:
	king(bool col);
	king(int x, int y, bool col);
	bool isvalidmove(int destx, int desty);
};

