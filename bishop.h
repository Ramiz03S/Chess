#pragma once
#include "piece.h"
#include<string>
#include <iostream>
using namespace std;

class bishop : 
    public piece
{
public:
	bishop(int x, int y, bool col);
	bool isvalidmove(int destx, int desty);
};

