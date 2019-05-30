#include<iostream>
#include "board.hh"

using namespace std;

int main() {
	Board board;
	board.PrintBoard();
	int temp;
	while(!board.IsEnd()) {
		cout << string(50, '\n');
		board.PrintBoard();
		//board.PlayerMove();
		//board.PrintBoard();
		board.PlayerMove();
		//board.AiMove(5);
		if(board.IsEnd())
			break;
		board.AiMove(5);
	}
	return 0;
}
