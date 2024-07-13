#include "board.h"

Board::Board()
{
	counter = 0;
	board[0][0] = new rook(1, 1, 1);
	board[0][1] = new knight(1, 2, 1);
	board[0][2] = new bishop(1, 3, 1);
	board[0][3] = new queen(1);
	board[0][4] = new king(1);
	board[0][5] = new bishop(1, 6, 1);
	board[0][6] = new knight(1, 7, 1);
	board[0][7] = new rook(1, 8, 1);
	for (int i = 0; i < 8; i++) {
		board[1][i] = new pawn(2, i + 1, 1);
		board[6][i] = new pawn(7, i + 1, 0);
	}
	board[7][0] = new rook(8, 1, 0);
	board[7][1] = new knight(8, 2, 0);
	board[7][2] = new bishop(8, 3, 0);
	board[7][3] = new queen(0);
	board[7][4] = new king(0);
	board[7][5] = new bishop(8, 6, 0);
	board[7][6] = new knight(8, 7, 0);
	board[7][7] = new rook(8, 8, 0);

	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = new nullpiece(j + 1, i + 1);
		}
	}

}

Board::Board(int i)
{
	counter = 0;
	for (int j = 0; j < 8; j++) {
		for (int k = 0; k < 8; k++) {
			board[j][k] = new nullpiece(j + 1, k + 1);//initializes the board with empty sqaures
		}
	}
	ifstream myfile;
	myfile.open("..\\puzzle.txt", ifstream::in); // reads from text file the positions of the pieces for this custom board
	if (myfile.is_open()) {
		int ox, oy, n, c;
		piece* p = NULL;
		while (myfile.eof() == 0) {

			myfile >> ox >> oy >> n >> c;
			p = board[ox - 1][oy - 1];
			switch (n) {
			case 1:
				board[ox - 1][oy - 1] = new pawn(ox, oy, c);
				break;
			case 2:
				board[ox - 1][oy - 1] = new knight(ox, oy, c);
				break;
			case 3:
				board[ox - 1][oy - 1] = new bishop(ox, oy, c);
				break;
			case 4:
				board[ox - 1][oy - 1] = new rook(ox, oy, c);
				break;
			case 5:
				board[ox - 1][oy - 1] = new queen(ox, oy, c);
				break;
			case 6:
				board[ox - 1][oy - 1] = new king(ox, oy, c);
				break;
			}
		}
		delete p;
	}
	else
	{
		printf("file is not open\n");
	}
}

bool Board::nopieceObstruct(int ox, int oy, int dx, int dy) {
	//checks for diagnol moves
	if (abs(dx - ox) == abs(dy - oy)) {
		if (dx > ox && dy > oy) { //top-right diagnol moves 
			for (int i = 1; i < abs(dx - ox); i++) {
				if (board[ox - 1 + i][oy - 1 + i]->pieceType != "nullpiece") {
					return 0;
				}
			}
		}
		if (dx > ox && dy < oy) { //top-left diagnol moves
			for (int i = 1; i < abs(dx - ox); i++) {
				if (board[ox - 1 + i][oy - 1 - i]->pieceType != "nullpiece") {
					return 0;
				}
			}
		}
		if (dx < ox && dy < oy) { //bottom-left diagnol moves
			for (int i = 1; i < abs(dx - ox); i++) {
				if (board[ox - 1 - i][oy - 1 - i]->pieceType != "nullpiece") {
					return 0;
				}
			}
		}
		if (dx < ox && dy > oy) { //bottom-right diagnol moves
			for (int i = 1; i < abs(dx - ox); i++) {
				if (board[ox - 1 - i][oy - 1 + i]->pieceType != "nullpiece") {
					return 0;
				}
			}
		}
		return 1;
	}
	//checks for vertical moves
	if (oy - dy == 0) {
		for (int i = 1; i < abs(dx - ox); i++) {
			if (dx > ox) { //vertical upwards moves
				if (board[ox - 1 + i][oy - 1]->pieceType != "nullpiece") {
					return 0;
				}
			}
			if (dx < ox) { //vertical downwards moves
				if (board[ox - 1 - i][oy - 1]->pieceType != "nullpiece") {
					return 0;
				}
			}
		}
		return 1;
	}
	//checks for horizental moves
	if (ox - dx == 0) {
		for (int i = 1; i < abs(dy - oy); i++) {
			if (oy > dy) { //horizental to left moves
				if (board[ox - 1][oy - 1 - i]->pieceType != "nullpiece") {
					return 0;
				}
			}
			if (oy < dy) { //horizental to right moves
				if (board[ox - 1][oy - 1 + i]->pieceType != "nullpiece") {
					return 0;
				}
			}
		}
		return 1;
	}
	return 1;
}

bool Board::pawncapturevalid(int ox, int oy, int dx, int dy)
{ // returns 1 if its a valid pawn move or a non pawn move, returns 0 if its not a valid pawn move
	if (board[ox - 1][oy - 1]->pieceType == "pawn") { // if pieces moved is a pawn
		if (abs(ox - dx) == 1 && abs(oy - dy) == 1) {
			if (board[dx - 1][dy - 1]->pieceType != "nullpiece") {
				return 1; // if its a diagnol move, return 1 if it captures a piece
			}
		}
		if ((abs(ox - dx) == 1 || abs(ox - dx) == 2) && abs(oy - dy) == 0) {
			if (board[dx - 1][dy - 1]->pieceType == "nullpiece") {
				return 1; // if its a normal(forward) move, return 1 if it doesnt capture a piece (does not land on a nullpiece)
			}
		}
		else return 0;
	}
	else return 1;
}

bool Board::incheck(int dx, int dy) { //checks if moving a piece puts their king in check
	int x_king = 0;
	int y_king = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((board[i][j]->pieceType == "king") && (board[i][j]->color == board[dx - 1][dy - 1]->color)) {
				x_king = i;
				y_king = j;
				//saves where the king is
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->pieceType == "pawn") {
				if (board[i][j]->isvalidmove((x_king + 1), (y_king + 1)) && nopieceObstruct(i + 1, j + 1, x_king + 1, y_king + 1) && (board[i][j]->color != board[dx - 1][dy - 1]->color) && pawncapturevalid(i + 1, j + 1, x_king + 1, y_king + 1)) {
					return 1; // return 1 if any opposing pawn on the board can legally capture the king
				}
			}
			else {
				if (board[i][j]->isvalidmove((x_king + 1), (y_king + 1)) && nopieceObstruct(i + 1, j + 1, x_king + 1, y_king + 1) && (board[i][j]->color != board[dx - 1][dy - 1]->color)) {
					return 1; // return 1 if any opposing piece on the board can legally capture the king
				}
			}
		}
	}
	return 0;
}

bool Board::turn(int ox, int oy) {
	if (counter % 2 == 0) {
		return (board[ox - 1][oy - 1]->color == 1);
		// if the piece moved is white and the counter is even return 1, else return 0
	}
	else return(board[ox - 1][oy - 1]->color == 0);
	//if the piece moved is black and the counter is odd return 1, else return 0
}

void Board::move(int ox, int oy, int dx, int dy) {
	try {
		if ((board[ox - 1][oy - 1]->isvalidmove(dx, dy) && (pawncapturevalid(ox, oy, dx, dy))) == 0) {
			throw 1; // if the move is not valid for the piece throw error 1
		}
		if (((board[dx - 1][dy - 1]->color) != (board[ox - 1][oy - 1]->color) || (board[dx - 1][dy - 1]->pieceType == "nullpiece")) == 0) {
			throw 2; //if user moves piece to sqaure of same-color piece or if its not an empty sqaure throw error 2
		}
		if (nopieceObstruct(ox, oy, dx, dy) == 0) {
			throw 3; // if the piece is obstructed from moving to that sqaure throw error 3
		}
		if (turn(ox, oy) == 0) {
			throw 4; // if its not the colors turn to move then throw error 4
		}
	}
	catch (int e) {
		if (e == 1) { cout << "That's an illegal move, try again!" << endl; }
		if (e == 2) { cout << "You cannot capture a piece of your own color!" << endl; }
		if (e == 3) { cout << "This piece is obstructed from moving to that sqaure!" << endl; }
		if (e == 4) { cout << "It's not your turn right now!" << endl; }
	}
	try {
		if  ( // conditions that decide if a move is legal or not
			(board[ox - 1][oy - 1]->isvalidmove(dx, dy) && pawncapturevalid(ox, oy, dx, dy)) &&
			((board[dx - 1][dy - 1]->color) != (board[ox - 1][oy - 1]->color) || (board[dx - 1][dy - 1]->pieceType == "nullpiece")) &&
			(nopieceObstruct(ox, oy, dx, dy)) &&
			(turn(ox, oy) == 1)
			) {
			// if all conditions are true then it checks what piece is being moved
			piece* p = NULL;
			piece* q = NULL;
			if (board[ox - 1][oy - 1]->pieceType == "pawn") {
				//if piece to move is a pawn
				if (dx == 8 || dx == 1) {
					//checks if the pawn is on the first or eigth row, if they are pawn is promoted.
					int i;
					cout << endl << "promote pawn to? (1=Q,2=R,3=B,4=N)" << endl;
					cin >> i;
					while (cin.fail() || ((i != 1) && (i != 2) && (i != 3) && (i != 4)))
					{
						cout << "ERROR -- Input can only be 1, 2, 3, or 4. Try again!" << endl;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						cin >> i;
					}
					if (i == 1) { //promotes pawn to a queen
						p = board[dx - 1][dy - 1];
						board[dx - 1][dy - 1] = new queen(dx, dy, board[ox - 1][oy - 1]->color);
						q = board[ox - 1][oy - 1];
						board[ox - 1][oy - 1] = new nullpiece(ox, oy);
						if (incheck(dx, dy) == 0) {
							delete p;
							delete q;
						}
					}
					if (i == 2) { //promotes pawn to a rook
						p = board[dx - 1][dy - 1];
						board[dx - 1][dy - 1] = new rook(dx, dy, board[ox - 1][oy - 1]->color);
						q = board[ox - 1][oy - 1];
						board[ox - 1][oy - 1] = new nullpiece(ox, oy);
						if (incheck(dx, dy) == 0) {
							delete p;
							delete q;
						}
					}
					if (i == 3) { //promotes pawn to bishop
						p = board[dx - 1][dy - 1];
						board[dx - 1][dy - 1] = new bishop(dx, dy, board[ox - 1][oy - 1]->color);
						q = board[ox - 1][oy - 1];
						board[ox - 1][oy - 1] = new nullpiece(ox, oy);
						if (incheck(dx, dy) == 0) {
							delete p;
							delete q;
						}
					}
					if (i == 4) { //promotes pawn to a knight
						p = board[dx - 1][dy - 1];
						board[dx - 1][dy - 1] = new knight(dx, dy, board[ox - 1][oy - 1]->color);
						q = board[ox - 1][oy - 1];
						board[ox - 1][oy - 1] = new nullpiece(ox, oy);
						if (incheck(dx, dy) == 0) {
							delete p;
							delete q;
						}
					}
				}
				else
				{
					
					p = board[dx - 1][dy - 1];
					board[dx - 1][dy - 1] = new pawn(dx, dy, board[ox - 1][oy - 1]->color);

					q = board[ox - 1][oy - 1];
					board[ox - 1][oy - 1] = new nullpiece(ox, oy);
					if (incheck(dx, dy) == 0) {
						board[dx - 1][dy - 1]->moved = 1;
						delete p;
						delete q;

					}
				}
				if (incheck(dx, dy) == 1) {
					//if after the move is made, the king is in check, then reverse the move
					piece* n = board[dx - 1][dy - 1];
					board[dx - 1][dy - 1] = p;
					piece* m = board[ox - 1][oy - 1];
					board[ox - 1][oy - 1] = q;
					delete n;
					delete m;
					throw 6;
					// turn is not incremented since user has to try another move
				}
				else {
					system("CLS");
					print_board();
				}
				++counter; //increments the counter to give the turn to the opponenet
			}
			if (board[ox - 1][oy - 1]->pieceType == "knight") {
				p = board[dx - 1][dy - 1];
				board[dx - 1][dy - 1] = new knight(dx, dy, board[ox - 1][oy - 1]->color);

				q = board[ox - 1][oy - 1];
				board[ox - 1][oy - 1] = new nullpiece(ox, oy);
				if (incheck(dx, dy) == 0) {
					delete p;
					delete q;
				}
				if (incheck(dx, dy) == 1) {
					piece* n = board[dx - 1][dy - 1];
					board[dx - 1][dy - 1] = p;
					piece* m = board[ox - 1][oy - 1];
					board[ox - 1][oy - 1] = q;
					delete n;
					delete m;
					throw 6;
				}
				else {
					system("CLS");
					print_board();
				}
				++counter;
			}
			if (board[ox - 1][oy - 1]->pieceType == "bishop") {
				p = board[dx - 1][dy - 1];
				board[dx - 1][dy - 1] = new bishop(dx, dy, board[ox - 1][oy - 1]->color);

				q = board[ox - 1][oy - 1];
				board[ox - 1][oy - 1] = new nullpiece(ox, oy);
				if (incheck(dx, dy) == 0) {
					delete p;
					delete q;
				}
				if (incheck(dx, dy) == 1) {
					piece* n = board[dx - 1][dy - 1];
					board[dx - 1][dy - 1] = p;
					piece* m = board[ox - 1][oy - 1];
					board[ox - 1][oy - 1] = q;
					delete n;
					delete m;
					throw 6;
				}
				else {
					system("CLS");
					print_board();
				}
				++counter;
			}
			if (board[ox - 1][oy - 1]->pieceType == "rook") {
				p = board[dx - 1][dy - 1];
				board[dx - 1][dy - 1] = new rook(dx, dy, board[ox - 1][oy - 1]->color);

				q = board[ox - 1][oy - 1];
				board[ox - 1][oy - 1] = new nullpiece(ox, oy);
				if (incheck(dx, dy) == 0) {
					delete p;
					delete q;
				}
				if (incheck(dx, dy) == 1) {
					piece* n = board[dx - 1][dy - 1];
					board[dx - 1][dy - 1] = p;
					piece* m = board[ox - 1][oy - 1];
					board[ox - 1][oy - 1] = q;
					delete n;
					delete m;
					throw 6;
				}
				else {
					system("CLS");
					print_board();
				}
				++counter;
			}
			if (board[ox - 1][oy - 1]->pieceType == "queen") {
				p = board[dx - 1][dy - 1];
				board[dx - 1][dy - 1] = new queen(dx, dy, board[ox - 1][oy - 1]->color);

				q = board[ox - 1][oy - 1];
				board[ox - 1][oy - 1] = new nullpiece(ox, oy);
				if (incheck(dx, dy) == 0) {
					delete p;
					delete q;
				}
				if (incheck(dx, dy) == 1) {
					piece* n = board[dx - 1][dy - 1];
					board[dx - 1][dy - 1] = p;
					piece* m = board[ox - 1][oy - 1];
					board[ox - 1][oy - 1] = q;
					delete n;
					delete m;
					throw 6;
				}
				else {
					system("CLS");
					print_board();
				}
				++counter;
			}
			if (board[ox - 1][oy - 1]->pieceType == "king") {
				p = board[dx - 1][dy - 1];
				board[dx - 1][dy - 1] = new king(dx, dy, board[ox - 1][oy - 1]->color);
				q = board[ox - 1][oy - 1];
				board[ox - 1][oy - 1] = new nullpiece(ox, oy);
				if (incheck(dx, dy) == 0) {
					delete p;
					delete q;

				}
				if (incheck(dx, dy) == 1) {
					piece* n = board[dx - 1][dy - 1];
					board[dx - 1][dy - 1] = p;
					piece* m = board[ox - 1][oy - 1];
					board[ox - 1][oy - 1] = q;
					delete n;
					delete m;
					throw 6;
				}
				else {
					system("CLS");
					print_board();
				}
				++counter;
			}

		}
	}
	catch (int e) {
		if (e == 6) {
			//asks the user to try inputting another move 
			system("CLS");
			print_board();
			cout << "You are currently in check! This move endangers your king, try again!" << endl;
		}
	}
}

void Board::move_puzzle(int ox, int oy, int dx, int dy) {
	piece* p = NULL;
	piece* q = NULL;
	if (board[ox - 1][oy - 1]->pieceType == "pawn") {
		//if piece to move is a pawn
		if (dx == 8 || dx == 1) {
			//checks if the pawn is on the first or eigth row, if they are pawn is promoted.
			int i;
			cout << endl << "promote pawn to?(1=Q,2=R,3=B,4=N)" << endl;
			scanf_s("%d", &i);
			if (i == 1) { //promotes pawn to a queen
				p = board[dx - 1][dy - 1];
				board[dx - 1][dy - 1] = new queen(dx, dy, board[ox - 1][oy - 1]->color);
				q = board[ox - 1][oy - 1];
				board[ox - 1][oy - 1] = new nullpiece(ox, oy);
				if (incheck(dx, dy) == 0) {
					delete p;
					delete q;
				}
			}
			if (i == 2) { //promotes pawn to a rook
				p = board[dx - 1][dy - 1];
				board[dx - 1][dy - 1] = new rook(dx, dy, board[ox - 1][oy - 1]->color);
				q = board[ox - 1][oy - 1];
				board[ox - 1][oy - 1] = new nullpiece(ox, oy);
				if (incheck(dx, dy) == 0) {
					delete p;
					delete q;
				}
			}
			if (i == 3) { //promotes pawn to bishop
				p = board[dx - 1][dy - 1];
				board[dx - 1][dy - 1] = new bishop(dx, dy, board[ox - 1][oy - 1]->color);
				q = board[ox - 1][oy - 1];
				board[ox - 1][oy - 1] = new nullpiece(ox, oy);
				if (incheck(dx, dy) == 0) {
					delete p;
					delete q;
				}
			}
			if (i == 4) { //promotes pawn to a knight
				p = board[dx - 1][dy - 1];
				board[dx - 1][dy - 1] = new knight(dx, dy, board[ox - 1][oy - 1]->color);
				q = board[ox - 1][oy - 1];
				board[ox - 1][oy - 1] = new nullpiece(ox, oy);
				if (incheck(dx, dy) == 0) {
					delete p;
					delete q;
				}
			}
		}
		else
		{
			p = board[dx - 1][dy - 1];
			board[dx - 1][dy - 1] = new pawn(dx, dy, board[ox - 1][oy - 1]->color);
			q = board[ox - 1][oy - 1];
			board[ox - 1][oy - 1] = new nullpiece(ox, oy);
			if (incheck(dx, dy) == 0) {
				delete p;
				delete q;
			}
		}
		system("CLS");
		print_board();
		++counter; //increments the counter to give the turn to the opponenet
	}
	if (board[ox - 1][oy - 1]->pieceType == "knight") {
		p = board[dx - 1][dy - 1];
		board[dx - 1][dy - 1] = new knight(dx, dy, board[ox - 1][oy - 1]->color);
		q = board[ox - 1][oy - 1];
		board[ox - 1][oy - 1] = new nullpiece(ox, oy);
		if (incheck(dx, dy) == 0) {
			delete p;
			delete q;
		}
		system("CLS");
		print_board();
		++counter;
	}
	if (board[ox - 1][oy - 1]->pieceType == "bishop") {
		p = board[dx - 1][dy - 1];
		board[dx - 1][dy - 1] = new bishop(dx, dy, board[ox - 1][oy - 1]->color);
		q = board[ox - 1][oy - 1];
		board[ox - 1][oy - 1] = new nullpiece(ox, oy);
		if (incheck(dx, dy) == 0) {
			delete p;
			delete q;
		}
		system("CLS");
		print_board();
		++counter;
	}
	if (board[ox - 1][oy - 1]->pieceType == "rook") {
		p = board[dx - 1][dy - 1];
		board[dx - 1][dy - 1] = new rook(dx, dy, board[ox - 1][oy - 1]->color);
		q = board[ox - 1][oy - 1];
		board[ox - 1][oy - 1] = new nullpiece(ox, oy);
		if (incheck(dx, dy) == 0) {
			delete p;
			delete q;
		}
		system("CLS");
		print_board();
		++counter;
	}
	if (board[ox - 1][oy - 1]->pieceType == "queen") {
		p = board[dx - 1][dy - 1];
		board[dx - 1][dy - 1] = new queen(dx, dy, board[ox - 1][oy - 1]->color);
		q = board[ox - 1][oy - 1];
		board[ox - 1][oy - 1] = new nullpiece(ox, oy);
		if (incheck(dx, dy) == 0) {
			delete p;
			delete q;
		}
		system("CLS");
		print_board();
		++counter;
	}
	if (board[ox - 1][oy - 1]->pieceType == "king") {
		p = board[dx - 1][dy - 1];
		board[dx - 1][dy - 1] = new king(dx, dy, board[ox - 1][oy - 1]->color);
		q = board[ox - 1][oy - 1];
		board[ox - 1][oy - 1] = new nullpiece(ox, oy);
		if (incheck(dx, dy) == 0) {
			delete p;
			delete q;
		}
		system("CLS");
		print_board();
		++counter;
	}
}

void Board::print_board() {
	for (int i = 7; i > -1; i--) {
		cout << "    " << i + 1 << "    "; //prints row index
		for (int j = 0; j < 8; j++) {
			if ((board[i][j])->pieceType == "pawn") {
				if ((i + j) % 2 == 0) { //if sqaure is black
					if (board[i][j]->color == 0) {
						cout << " (( p )) ";//if piece is black
					}
					else cout << " (( P )) ";//if piece is white
				}
				//if sqaure is white
				else if (board[i][j]->color == 0) {
					cout << " [[ p ]] "; //if piece is black
				}
				else cout << " [[ P ]] "; //if piece is white
			}
			if ((board[i][j])->pieceType == "knight") {
				if ((i + j) % 2 == 0) {
					if (board[i][j]->color == 0) {
						cout << " (( n )) ";
					}
					else cout << " (( N )) ";
				}
				else if (board[i][j]->color == 0) {
					cout << " [[ n ]] ";
				}
				else cout << " [[ N ]] ";
			}
			if ((board[i][j])->pieceType == "bishop") {
				if ((i + j) % 2 == 0) {
					if (board[i][j]->color == 0) {
						cout << " (( b )) ";
					}
					else cout << " (( B )) ";
				}
				else if (board[i][j]->color == 0) {
					cout << " [[ b ]] ";
				}
				else cout << " [[ B ]] ";
			}
			if ((board[i][j])->pieceType == "rook") {
				if ((i + j) % 2 == 0) {
					if (board[i][j]->color == 0) {
						cout << " (( r )) ";
					}
					else cout << " (( R )) ";
				}
				else if (board[i][j]->color == 0) {
					cout << " [[ r ]] ";
				}
				else cout << " [[ R ]] ";
			}
			if ((board[i][j])->pieceType == "queen") {
				if ((i + j) % 2 == 0) {
					if (board[i][j]->color == 0) {
						cout << " (( q )) ";
					}
					else cout << " (( Q )) ";
				}
				else if (board[i][j]->color == 0) {
					cout << " [[ q ]] ";
				}
				else cout << " [[ Q ]] ";
			}
			if ((board[i][j])->pieceType == "king") {
				if ((i + j) % 2 == 0) {
					if (board[i][j]->color == 0) {
						cout << " (( k )) ";
					}
					else cout << " (( K )) ";
				}
				else if (board[i][j]->color == 0) {
					cout << " [[ k ]] ";
				}
				else cout << " [[ K ]] ";
			}
			if ((board[i][j])->pieceType == "nullpiece") {
				if ((i + j) % 2 == 0) {
					cout << " ((   )) ";
				}
				else cout << " [[   ]] ";
			}

		} cout << endl << endl;
	}
	cout << "         ";
	for (int i = 1; i < 9; i++) {
		cout << "    " << i << "    "; //prints column index
	}cout << endl;
}