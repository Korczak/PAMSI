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
    Move() : x(0), y(0), dx(0), dy(0) {}
    Move(int x, int y, int dx, int dy)
    {
        this->x=x;
        this->y=y;
        this->dx=dx;
        this->dy=dy;
    }
    Move& operator=(const Move &move) {
        this->x = move.x;
        this->y = move.y;
        this->dx = move.dx;
        this->dy = move.dy;
    }
    void printMove() {
        std::cout << "from: " << x << " " << y << " to: " << dx << " " << dy << std::endl;
    }
};

class Board
{
public:
    int board[8][8];
    int actualPlayer = PLAYER;
    
    Board(); //Creates an empty board
    Board(const Board &p); //Creates copied board
    Board& operator=(const Board &); //Creates copied board
    void PrintBoard(); //Prints board
    
    /*
    *Check if move is attacking enemy
    *
    *:param x: actual x
    *:param y: actual y
    *:param dx: new x
    *:param dy: new y
    *   
    *:return: true if is attacking, false otherwise
    */
    bool IsAttackingEnemyChecker(int x, int y, int dx, int dy);
    bool IsAttackingEnemyChecker(Move move);
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
    *Get all possible moves on board
    *
    *:return: vector of possible moves
    */
    std::vector<Move> GetAllMoves();

    /*
    *Get all possible moves on board from specific position
    *
    *:return: vector of possible moves
    */
    std::vector<Move> GetAllMoves(int x, int y);
    std::vector<Move> GetAllMoves(Move move);

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
    * Check if black won
    */
    bool IsBlackWinner();

    /* 
    * Check if white won
    */
    bool IsWhiteWinner();

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
    *Check if any of checker should change to queen
    *If so, change it to queen
    */
    void ChangeToQueen();
    
    /*
    *Makes a move on board specified by move
    *!!! Move has to be correct !!!
    * 
    *:param move: move by player or computer
    *   
    *:return: board after move
    */
    Board MakeMove(Move move);
    
    /*
    *Choose move that ai will make, , updates board
    *
    *:param maxDepth: max depth of minimax tree - higher means AI is looking further
    */
    void AiMove(int maxDepth);
    
    /*
    *Move by player, updates board
    */
    void PlayerMove();

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

    /*
    *Jump over checker (moves and deletes enenemy checker)
    */
    void JumpOverChecker(int x, int y, int& dx, int& dy);
    void JumpOverChecker(Move& move);


    /*
    *Update actual player
    */
    void ChangePlayer();
    void ChangePlayer(int player);

    /*
    *Get all atacker boards, pushes new boards to vector of boards
    *
    *:param prevMoves: all previous moves from the beggining of turn
    *:param prevMove: previous move
    *:param boards: vector of all boards
    *:param result: moves that corresponds to board
    */
    void GetAllAtackerBoard(std::vector<Move> prevMoves, Move prevMove, 
                            std::vector<Board>& boards, std::vector<std::vector<Move>>& result);

    /*
    *Get all boards (including after attack and only move)
    *
    *:param boards: all boards that are possible from actual board
    *:param result: all moves to achieve specific board status
    */
    void GetAllBoards(std::vector<Board>& boards, std::vector<std::vector<Move>>& result);

};
#endif