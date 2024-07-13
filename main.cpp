#include <iostream>
using namespace std;
#include <math.h>
#include "piece.h"
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "nullpiece.h"
#include "Board.h"
#include <typeinfo>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <filesystem>

void play() {
	system("cls");
	int ox = 0, oy = 0, dx = -1, dy = -1;
	Board b1;
	b1.print_board();
	while (ox != dx || oy != dy) {
		cout << "\nInput the move you want to make in the format: 'old_y old_x new_y new_x'" << endl;
		try 
		{
			cin >> ox >> oy >> dx >> dy;

			while (cin.fail())
			{
				cout << "ERROR -- Input the move you want to make in the format: 'old_y old_x new_y new_x'" << endl;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> ox >> oy >> dx >> dy;
			}

			if (((ox < 1 || ox>8) || (oy < 1 || oy>8) || (dx < 1 || dx>8) || (dy < 1 || dy>8))) {
				throw - 1;
			}

			b1.move(ox, oy, dx, dy);
		}
		catch (int e) {
			if (e == -1) {
				cout << "move input is out of bounds try again!" << endl;
			}
		}
	}
	
}

void solve() 
{
	system("cls");
	Board bp1(1);
	int ox = 0, oy = 0, dx = -1, dy = -1;
	bp1.print_board();
	cout << endl << "Input the best move for white in the format: 'old_y old_x new_y new_x'!" << endl;
	cin >> ox >> oy >> dx >> dy;
	while ((ox == 1 && oy == 5 && dx == 8 && dy == 5) == 0) 
	{
		if (cin.fail())
		{
			cout << "ERROR -- Input the move you want to make in the format: 'old_y old_x new_y new_x'" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			cout << "Wrong move, try again." << endl;
		}
		cin >> ox >> oy >> dx >> dy;
	}
	bp1.move_puzzle(1, 5, 8, 5);
	bp1.move_puzzle(8, 6, 8, 5);
	cout << "Good move! Black responds with this. What's your next move?" << endl;
	
	
	cin >> ox >> oy >> dx >> dy;
	while ((ox == 5 && oy == 6 && dx == 6 && dy == 4) == 0)
	{
		if (cin.fail())
		{
			cout << "ERROR -- Input the move you want to make in the format: 'old_y old_x new_y new_x'" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			cout << "Wrong move, try again." << endl;
		}
		cin >> ox >> oy >> dx >> dy;
	}
	bp1.move_puzzle(ox, oy, dx, dy);
	bp1.move_puzzle(8, 5, 7, 4);
	cout << "Good move! Black responds with this. What's your next move?" << endl;
	

	cin >> ox >> oy >> dx >> dy;
	while ((ox == 6 && oy == 4 && dx == 4 && dy == 3) == 0)
	{
		if (cin.fail())
		{
			cout << "ERROR -- Input the move you want to make in the format: 'old_y old_x new_y new_x'" << endl;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			cout << "Wrong move, try again." << endl;
		}
		cin >> ox >> oy >> dx >> dy;
	}
	bp1.move_puzzle(ox, oy, dx, dy);
	cout << "Congratulations! You played the best moves" << endl;
}

int main() {
	int i;
	cout << "What would you like to do? Enter 1 to play a game, enter 2 to solve puzzles." << endl;
	cin >> i;
	while (cin.fail() || ((i != 1) && (i != 2)))
	{
		cout << "ERROR -- Input can only be 1 or 2, try again!" << endl;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cin >> i;
	}

	switch (i) {
	case 1:
		play();
		break;
	case 2:
		solve();
		break;
	default:
		return 0;
	}
	return 0;
}
