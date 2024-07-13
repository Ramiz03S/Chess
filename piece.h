#pragma once
#include<string>
#include<iostream>
#include <iostream>
using namespace std;
class piece
{
protected:
	friend class Board;
	bool color; //0 is black, 1 is white
	int current_x;//the piece's current vertical position from 1 to 8
	int current_y; //the piece's current horizental position from 1 to 8
	string pieceType;//type of the piece 
	bool moved=0; //only used for pawns as of now

	virtual bool isvalidmove(int destx, int desty) = 0;

	
};

