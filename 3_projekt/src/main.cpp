#include<iostream>
#include "board.hh"

using namespace std;

int main() {
	Board board;
	board.PrintBoard();
	while(!board.IsEnd()) {
		board.PlayerMove();
		board.PrintBoard();
	}
	return 0;
}
