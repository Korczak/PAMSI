#include "minmax.hh"

using namespace std;

int Minmax::CalculateScore(Board b, int player) {
	int score = 0;
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if(b.board[i][j] == 1)
				score += checkerValue;
			if(b.board[i][j] == -1)
				score -= checkerValue;
			if(b.board[i][j] == 2)
				score += queenValue;
			if(b.board[i][j] == -2)
				score -= queenValue;
		}
	}

	return score;
}

int Minmax::Min_Max(Board b, int depth, int player, Move& result) {
	if(depth == 0)
		return CalculateScore(b, player);

	vector<Board> boards;
    boards = b.GetAllBoards();

    int min = 99999;
    int max = -99999;

    for(auto &board : boards) {
    	int score = CalculateScore(board, player);
    	if(player == AI) {
    		if(min > score) {
    			min = score;
    		}
    	}
    }
}