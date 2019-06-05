#ifndef MINMAX_HH
#define MINMAX_HH

#include "board.hh"
#include <iostream>
#include <vector>

class Minmax
{
	int inf = 99999;
	int checkerValue = 1;
	int queenValue = 5;

	/*
	*Calculates score of players board
	*	1 for player checker, -1 for enemy checker
	*
	*:return: score of board calculated via formula
	*/
	int CalculateScore(Board b);



	/*
	*Min_Max
	*	Recognize the best possible move for player, works on min_max algorithm
	*
	*:param b: board
	*:param maxDepth: starting depth
	*:param depth: depth of minmax - last is 0
	*:param player: player id, depends whos move is currently
	*:param alfa: max val, best value of move for pc
	*:param beta: min val, best value move for player
	*:param result: the best vector of moves for ai 
	*
	*:return: score of best possible move
	*/
	int alfa_beta(Board b, int depth, int maxDepth, int player,
				int alfa, int beta, std::vector<Move>& result);

public:
	Minmax() {}
	~Minmax() {}

	/*
	*Min_Max
	*	Recognize the best possible move for player, works on min_max algorithm
	*
	*:param b: board
	*:param maxDepth: starting depth
	*:param depth: depth of minmax - last is 0
	*:param player: player id, depends whos move is currently
	*:param result: the best vector of moves for ai 
	*
	*:return: score of best possible move
	*/
	int Min_Max(Board b, int depth, int maxDepth, int player, std::vector<Move>& result);
};




#endif