#include "minmax.hh"


using namespace std;

int Minmax::CalculateScore(Board b) {
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


int Minmax::Min_Max(Board b, int depth, int player, vector<Move>& result) {
	if(depth == 0)
		return CalculateScore(b);
    cout << "A" << endl;

	vector<Board> boards;
	vector<vector<Move>> moves;

    b.GetAllBoards(boards, moves);
	cout << "A" << endl;
    cout << boards.size() << endl;

    int min = 99999;
    int max = -99999;

	for(vector<Board>::size_type i = 0; i != boards.size(); i++) {
       	int score = CalculateScore(boards[i]);
       	cout << score << " for: " << endl;
       	for(auto move : moves[i]) {
       		move.printMove();
       	}
    	if(player == AI) {
    		if(min > score) {
    			min = score;
    			result = moves[i];
    		}

    	}
    	else {
    		if(max < score) {
    			max = score;
    			result = moves[i];
    		}
    	}
    }

    if(player)
    	return min;
    return max;
}