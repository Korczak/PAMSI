#include "minmax.hh"


using namespace std;

int Minmax::CalculateScore(Board b) {
	int score = 0;
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if(b.board[i][j] == NORMAL_AI)
				score += checkerValue;
			if(b.board[i][j] == NORMAL_PLAYER)
				score -= checkerValue;
			if(b.board[i][j] == QUEEN_AI)
				score += queenValue;
			if(b.board[i][j] == QUEEN_PLAYER)
				score -= queenValue;
		}
	}

	return score;
}

int Minmax::alfa_beta(Board b, int depth, int maxDepth, int player,
				int alfa, int beta, std::vector<Move>& result) {
	if(b.IsWhiteWinner())
		return inf;
	if(b.IsBlackWinner())
		return -inf;

	if(depth == 0)
		return CalculateScore(b);

	//b.ChangePlayer(player);

	vector<Board> boards;
	vector<vector<Move>> moves;

    b.GetAllBoards(boards, moves);

	for(vector<Board>::size_type i = 0; i != boards.size(); i++) {
		
		boards[i].actualPlayer = player;
		int score = 0;
		if(player == AI)
			score = Min_Max(boards[i], depth - 1, maxDepth, PLAYER, result);
		else
			score = Min_Max(boards[i], depth - 1, maxDepth, AI, result);
       	
    	if(player == AI) {
    		if(alfa < score) {
    			alfa = score;
    			if(depth == maxDepth)
    				result = moves[i];
    			if(alfa >= beta)
    				return alfa;
    		}

    	}
    	else {
    		if(beta > score) {
    			beta = score;
    			if(alfa >= beta)
    				return beta;
    		}
    	}
    }

    if(player == PLAYER)
    	return beta;
    return alfa;
}

int Minmax::Min_Max(Board b, int depth, int maxDepth, int player, vector<Move>& result) {
	return alfa_beta(b, depth, maxDepth, player, -inf, inf, result);
}