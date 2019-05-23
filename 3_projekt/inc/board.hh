#ifndef BOARD_HH
#define BOARD_HH

#include <iostream>
#include <vector>

#define AI -1
#define PLAYER 1
#define NORMAL_PLAYER 1
#define QUEEN_PLAYER 2
#define NORMAL_AI -1
#define QUEEN_AI -2

struct Move
{
    int x,y,dx,dy;
    Move(int x, int y, int dx, int dy)
    {
        this.x=x;
        this.y=y;
        this.dx=dx;
        this.dy=dy;
    }
};

class Board
{
    int board[8][8];
    int actualPlayer = PLAYER;
public:
    
    Board(); //Creates an empty board
    Board(Board &p); //Creates copied board
    Board& operator=(Board const&); //Creates copied board
    void PrintBoard(); //Prints board
    
    /*
    *Check if move is correct
    *
    *:param x: actual x
    *:param y: actual y
    *:param dx: new x
    *:param dy: new y
    *   
    *:return: true if is correct, false if is incorrect
    */
    bool IsMovePossible(int x, int y, int dx, int dy); 
    bool IsMovePossible(Move move); 


    /*
    *Get all possible moves from board
    *
    *:return: vector of possible boards
    */
    vector<Board> GetAllMoves();


    /*
    *Check if cell is empty
    *
    *:param x: position x on board
    *:param y: position y on board
    *   
    *:return: true if its empty cell
    */
    bool IsEmpty(int x, int y);

    /*
    *Check if checker belongs to player
    *
    *:param x: actual x
    *:param y: actual y
    *   
    *:return: true if its player's checker
    */
    bool IsPlayerChecker(int x, int y);

    /*
    *Check if is end of game
    *   
    *:return: true if game ended, false if it is still running
    */
    bool IsEnd();

    /*
    *Check if position on board is correct
    *   
    *:return: true if position is correct, false if it is outside of the board
    */
    bool IsPositionCorrect(int x, int y);
    
    /*
    *Makes a move on board specified by move
    *
    *:param b: actual board
    *:param move: move by player or computer
    *   
    *:return: board after move
    */
    Board MakeMove(const Board b, Move move);
    
    /*
    *Choose move that ai will make
    *
    *:param b: actual board
    *
    *:return: AI move
    */
    Move AiMove(Board b);
    
    /*
    *Move by player
    *
    *:param b: actual board
    *
    *:return: Player move
    */
    Move PlayerMove(Board);

    /*
    *Move by player
    *
    *:param x: actual pos x
    *:param y: actual pos y
    *:param dx: destinated pos x
    *:param dy: destinated pos y
    *
    *:return: Move created by parameters
    */
    Move CreateMove(int x, int y, int dx, int dy);
};
#endif