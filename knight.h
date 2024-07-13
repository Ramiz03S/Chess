#pragma once
#include "piece.h"
#include<string>
#include <iostream>
#include<cstdlib>
using namespace std;

class knight :
    public piece
{
public:
	knight(int x, int y, bool col);
	bool isvalidmove(int destx, int desty);
};

