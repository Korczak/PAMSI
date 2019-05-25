#include<iostream>
#include "board.hh"

using namespace std;

int main() {
	Board board;
	board.PrintBoard();
	while(!board.IsEnd()) {
		board.PlayerMove();
		board.AiMove(3);
		board.PrintBoard();
	}
	return 0;
}
