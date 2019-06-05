#include<iostream>
#include "board.hh"

using namespace std;

int main() {
	Board board;
	board.PrintBoard();

	while(!board.IsEnd()) {
		cout << string(50, '\n');
		board.PrintBoard();
		board.PlayerMove();
		if(board.IsEnd())
			break;
		board.AiMove(5);
	}

	if(board.IsBlackWinner())
		cout << "BLACK WON" << endl;
	if(board.IsWhiteWinner())
		cout << "WHITE WON" << endl;
	return 0;
}
