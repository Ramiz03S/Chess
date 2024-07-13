#pragma once
#include "piece.h"
#include<string>
#include <iostream>
using namespace std;

class nullpiece :
    public piece
{
public:
    nullpiece(int x, int y);
    bool isvalidmove(int destx, int desty);
};

