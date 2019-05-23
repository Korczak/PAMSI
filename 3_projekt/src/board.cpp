#include "board.hh"

using namespace std;

Board::Board()
{
    int temp[8][8]= 
        {
            {0,-1,0,-1,0,-1,0,-1},
            {-1,0,-1,0,-1,0,-1,0},
            {0,-1,0,-1,0,-1,0,-1},
            {0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0},
            {1,0,1,0,1,0,1,0},
            {0,1,0,1,0,1,0,1},
            {1,0,1,0,1,0,1,0}
        };

    for(int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            board[i][j]=temp[i][j];
        }
    }
    this->actualPlayer = PLAYER;
}
Board::Board(Board &b)
{
    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            this->board[x][y]=b.Board[x][y];
        }
    }
    this->actualPlayer = b.actualPlayer;
}

Board& Board::operator=(Board const &b)
{
    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            this->board[x][y]=b.board[x][y];
        }
    }
    this->actualPlayer = b.actualPlayer;
    return *this;
}

void Board::PrintBoard()
{
    int row_num[8]= {8,7,6,5,4,3,2,1};
    cout<<endl<<"    A      B      C      D      E      F      G      H"<<endl;
    for(int i=0; i<8; i++)
    {
        cout<<row_num[i];
        for(int j=0; j<8; j++)
        {
            if(board[i][j]==-1)
                cout<<"  [B]  ";
            if(board[i][j]==-2)
                cout<<" [Q_B] ";
            if(board[i][j]==0)
                cout<<"  [ ]  ";
            if(board[i][j]==1)
                cout<<"  [W]  ";
            if(board[i][j]==2)
                cout<<" [Q_W] ";
        }
        cout<<row_num[i]<<endl;
    }
    cout<<"    A      B      C      D      E      F      G      H"<<endl;
}


bool Board::IsPlayerChecker(int x, int y) {
    if(!(x >= 0 && x <= 7))
        return false;
    if(actualPlayer == PLAYER && board[x][y] > 0)
        return true;
    if(actualPlayer == AI && board[x][y] < 0)
        return true;
    return false;
}

bool Board::IsEmpty(int x, int y) {
    if(board[x][y] == 0)
        return true;
    return false;
}

bool Board::IsPositionCorrect(int x, int y) {
    if((x >= 0 && x <= 7) && (y >= 0 && y <= 7))
        return true;
    return false;
}

bool Board::IsMovePossible(Move move) {
    IsMovePossible(move.x, move.y, move.dx, move.dy);
} 

bool Board::IsMovePossible(int x, int y, int dx, int dy) {
    if(!IsPlayerChecker(x, y)) //if checker belongs to player
        return false;                              //and check if destination cell is empty
    if(!IsPositionCorrect(dx, dy))  //check if move is outside the board
        return false;
    
    bool isMoveCorrectlyCreated = false;

    //Check if move is correctly created
    if(board[x][y] == QUEEN_PLAYER || board[x][y] == QUEEN_AI) //queen move
        if((dx == x + 1 && dy == y - 1) || (dx == x - 1 && dy == y - 1) ||
           (dx == x + 1 && dy == y + 1) || (dx == x - 1 && dy == y + 1))
            isMoveCorrectlyCreated = true;
    if(actualPlayer == PLAYER)
        if(board[x][y] == NORMAL_PLAYER) //normal checker
            if((dx == x + 1 && dy == y - 1) || (dx == x - 1 && dy == y - 1))  //Move towards ai
                isMoveCorrectlyCreated = true;
    else if(actualPlayer == AI)
        if(board[x][y] == NORMAL_AI) //normal checker
            if((dx == x + 1 && dy == y + 1) || (dx == x - 1 && dy == y + 1))  //Move towards player
                isMoveCorrectlyCreated = true;
            
    if(!isMoveCorrectlyCreated)
        return false;

    if(IsEmpty(dx, dy)) //without enemy checker move is possible
        return true;

    //BEAT ENEMY CHECKER
    if(IsPlayerChecker(dx, dy)) //trying to go in player checker
        return false;
    
    if(!IsPlayerChecker(dx, dy)) { //attacking enemy checker
        if(board[x][y] == QUEEN_PLAYER || board[x][y] == QUEEN_AI) { //Check queens move
            if(dy > y && dx > x) { //move bottom right
                if(!IsPositionCorrect(dx + 1, dy + 1))
                    return false;
                if(IsEmpty(dx + 1, dy + 1))
                    return true;
            }
            if(dy < y && dx > x) { //move top right
                if(!IsPositionCorrect(dx + 1, dy - 1))
                    return false;
                if(IsEmpty(dx + 1, dy - 1))
                    return true;
            }
            if(dy < y && dx < x) { //move top left
                if(!IsPositionCorrect(dx - 1, dy - 1))
                    return false;
                if(IsEmpty(dx - 1, dy - 1))
                    return true;
            }
            if(dy > y && dx < x) { //move bottom left
                if(!IsPositionCorrect(dx - 1, dy + 1))
                    return false;
                if(IsEmpty(dx - 1, dy + 1))
                    return true;
            }
        }

        if(actualPlayer == PLAYER) {
            if(dx > x) { //move towards right side
                if(!IsPositionCorrect(dx + 1, dy - 1)) //outside of the board
                    return false;
                if(IsEmpty(dx + 1, dy - 1))
                    return true;
            }
            else if(dx < x) {// move towards left side
                if(!IsPositionCorrect(dx - 1, dy - 1))
                    return false;
                if(IsEmpty(dx - 1, dy - 1))
                    return true;
            }
        }
        else if(actualPlayer == AI) {
            if(dx > x) { //move towards right side
                if(!IsPositionCorrect(dx + 1, dy + 1)) //outside of the board
                    return false;
                if(IsEmpty(dx + 1, dy + 1))
                    return true;
            }
            else if(dx < x) {// move towards left side
                if(!IsPositionCorrect(dx - 1, dy + 1))
                    return false;
                if(IsEmpty(dx - 1, dy + 1))
                    return true;
            }
        }
    }
    return true;
}

bool Board::IsEnd() {
    int numWhite = 0;
    int numBlack = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] < 0)
                numBlack++;
            if(board[i][j] > 0)
                numWhite++;
        }
    }

    if(numWhite == 0 || numBlack == 0)
        return true;
    return false;
}

vector<Board> Board::GetAllMoves() {
    vector < Board > boards;

    Move newMove;
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {            
            if(IsMovePossible(x, y, x+1, y+1)) {
                newMove = CreateMove(x, y, x+1, y+1);
                boards.push_back(board.MakeMove(board, newMove));   
            }
            if(IsMovePossible(x, y, x-1, y+1)) {
                newMove = CreateMove(x, y, x-1, y+1);
                boards.push_back(board.MakeMove(board, newMove));   
            }
            if(IsMovePossible(x, y, x+1, y-1)) {
                newMove = CreateMove(x, y, x+1, y-1);
                boards.push_back(board.MakeMove(board, newMove));   
            }
            if(IsMovePossible(x, y, x-1, y-1)) {
                newMove = CreateMove(x, y, x-1, y-1);
                boards.push_back(board.MakeMove(board, newMove));   
            }
        }
    }
}

Move Board::CreateMove(int x, int y, int dx, int dy) {
    return Move(x, y, dx, dy);
}

Board Board::MakeMove(const Board b, Move move) {
    Board newBoard(b);
    if(!IsMovePossible(move))
        return null;

    int actualChecker = b.board[move.x][move.y];
    newBoard.board[move.x][move.y] = 0;
    newBoard.board[move.dx][move.dy] = actualChecker;

    return newBoard;
}

Move Board::PlayerMove(Board b) {
    std::cout << "Podaj wspolrzedne pionka: wiersz kolumna (np. 3 3 ), ktory chcesz ruszyc: "  << std::endl;
    int x, y, dx, dy;  


    do {
        std::cin >> x >> y;
    } while(!IsPlayerChecker(x, y));

    std::cout << "Podaj gdzie chcesz sie ruszyc"  << std::endl;
    
    do {
        std::cin >> dx >> dy;
    } while(!IsMovePossible(x, y, dx, dy));



}



