#include<iostream>
#include "board.hh"

using namespace std;

int main() {
	Board board;
	board.PrintBoard();
	int temp;
	while(!board.IsEnd()) {
		board.PrintBoard();
		board.PlayerMove();
		//board.AiMove(5);
		board.AiMove(5);
	}
	return 0;
}
