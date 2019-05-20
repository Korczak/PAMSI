#ifndef MINMAX_HH
#define MINMAX_HH

#include <iostream>

class Minmax
{
	int checkerValue = 1;
	int queenValue = 5;
public:
	Minmax();
	~Minmax();

	/*
	*Calculates score of players board
	*	1 for player checker, -1 for enemy checker, 0.01 for every possible move
	*
	*:return: score of board calculated via formula
	*/
	int CalculateScore(Board b, int player);

	/*
	*Min_Max
	*	Recognize the best possible move for player, works on min_max algorithm
	*
	*:param b: board
	*:param depth: depth of minmax - last is 0
	*:param player: player id, depends whos move is currently
	*:param result: the best move for player 
	*
	*:return: score of best possible move
	*/
	int Min_Max(Board b, int depth, int player, Move& result);
};




#endif