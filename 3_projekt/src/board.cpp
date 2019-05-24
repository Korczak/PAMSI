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
Board::Board(const Board &b)
{
    for(int x=0; x<8; x++)
    {
        for(int y=0; y<8; y++)
        {
            this->board[x][y]=b.board[x][y];
        }
    }
    this->actualPlayer = b.actualPlayer;
}

Board& Board::operator=(const Board &b)
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
    int row_num[8]= {0,1,2,3,4,5,6,7};
    cout<<endl<<"    0      1      2      3      4      5      6      7"<<endl;
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
    cout<<"    0      1      2      3      4      5      6      7"<<endl;
}


bool Board::IsPlayerChecker(int x, int y) {
    if(!(x >= 0 && x <= 7 && y >= 0 && y <= 7))
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

bool Board::IsAttackingEnemyChecker(Move move) {
    return IsAttackingEnemyChecker(move.x, move.y, move.dx, move.dy);
}
bool Board::IsAttackingEnemyChecker(int x, int y, int dx, int dy) {
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
            if(dy > y) { //move towards right side
                if(!IsPositionCorrect(dx + 1, dy + 1)) //outside of the board
                    return false;
                if(IsEmpty(dx + 1, dy + 1))
                    return true;
            }
            else if(dy < y) {// move towards left side
                if(!IsPositionCorrect(dx + 1, dy - 1))
                    return false;
                if(IsEmpty(dx + 1, dy - 1))
                    return true;
            }
        }
        else if(actualPlayer == AI) {   
            if(dy > y) { //move towards right side
                if(!IsPositionCorrect(dx + 1, dy + 1)) //outside of the board
                    return false;
                if(IsEmpty(dx + 1, dy + 1))
                    return true;
            }
            else if(dy < y) {// move towards left side
                if(!IsPositionCorrect(dx + 1, dy - 1))
                    return false;
                if(IsEmpty(dx + 1, dy - 1))
                    return true;
            }
        }
    }

    return false;
}

bool Board::IsMovePossible(int x, int y, int dx, int dy) {
    if(!IsPlayerChecker(x, y)) //if checker belongs to player
        return false;                              //and check if destination cell is empty
    if(!IsPositionCorrect(dx, dy))  //check if move is outside the board
        return false;

    bool isMoveCorrectlyCreated = false;

    //Check if move is correctly created
    if(board[x][y] == QUEEN_PLAYER || board[x][y] == QUEEN_AI) { //queen move
        if((dx == x + 1 && dy == y - 1) || (dx == x - 1 && dy == y - 1) ||
           (dx == x + 1 && dy == y + 1) || (dx == x - 1 && dy == y + 1)) {
            isMoveCorrectlyCreated = true;
        }
    }
    if(actualPlayer == PLAYER) {
        if(board[x][y] == NORMAL_PLAYER) { //normal checker
            if((dx == x - 1 && dy == y - 1) || (dx == x - 1 && dy == y + 1)) {  //Move towards ai
                isMoveCorrectlyCreated = true;
            }
        }
    }
    else if(actualPlayer == AI) {
        if(board[x][y] == NORMAL_AI) { //normal checker
            if((dx == x + 1 && dy == y - 1) || (dx == x + 1 && dy == y + 1)) { //Move towards player
                isMoveCorrectlyCreated = true;
            }
        }
    }
    
    if(!isMoveCorrectlyCreated)
        return false;

    if(IsEmpty(dx, dy)) //without enemy checker move is possible
        return true;

    if(IsAttackingEnemyChecker(x, y, dx, dy)) //attacking enemy player
        return true;

    return false;
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

vector<Move> Board::GetAllMoves() {
    vector < Move > moves;
    
    Move newMove; 
    
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {      
            if(IsMovePossible(x, y, x+1, y+1))
                moves.push_back(CreateMove(x, y, x+1, y+1));   
            if(IsMovePossible(x, y, x-1, y+1))
                moves.push_back(CreateMove(x, y, x-1, y+1));
            if(IsMovePossible(x, y, x+1, y-1))
                moves.push_back(CreateMove(x, y, x+1, y-1));
            if(IsMovePossible(x, y, x-1, y-1))
                moves.push_back(CreateMove(x, y, x-1, y-1));
        }
    }
    return moves;
}

vector<Move> Board::GetAllMoves(Move move) {
    GetAllMoves(move.x, move.y);
}

vector<Move> Board::GetAllMoves(int x, int y) {
    vector < Move > moves;
    
    Move newMove; 
    if(IsMovePossible(x, y, x+1, y+1))
        moves.push_back(CreateMove(x, y, x+1, y+1));   
    if(IsMovePossible(x, y, x-1, y+1))
        moves.push_back(CreateMove(x, y, x-1, y+1));
    if(IsMovePossible(x, y, x+1, y-1))
        moves.push_back(CreateMove(x, y, x+1, y-1));
    if(IsMovePossible(x, y, x-1, y-1))
        moves.push_back(CreateMove(x, y, x-1, y-1));

    return moves;
}

Move Board::CreateMove(int x, int y, int dx, int dy) {
    return Move(x, y, dx, dy);
}

Board Board::MakeMove(Move move) {
    Board newBoard;
    newBoard = *this;

    int actualChecker = (*this).board[move.x][move.y];
    newBoard.board[move.x][move.y] = 0;
    newBoard.board[move.dx][move.dy] = actualChecker;

    return newBoard;
}

void Board::ChangePlayer() {
    if(actualPlayer == PLAYER)
        actualPlayer = AI;
    else
        actualPlayer = PLAYER;
}

void Board::JumpOverChecker(Move& move) {
    JumpOverChecker(move.x, move.y, move.dx, move.dy);
}

void Board::JumpOverChecker(int x, int y, int& dx, int& dy) {
    if(!IsEmpty(dx, dy)) {
        if(IsAttackingEnemyChecker(x, y, dx, dy)) { //make 'jump' over checker
            isAttackingEnemy = true;

            if(dy > y)
                dy += 1;
            else 
                dy -= 1;

            if(dx > x)
                dx += 1;
            else
                dx -= 1;

            this->board[(x+dx)/2][(y+dy)/2] = 0; //erase attacked checker
        }
    }
}

vector<Board> Board::GetAllBoards() {
    vector<Board> boards;
    vector<Move> moves;

    moves = GetAllMoves();

    Board newBoard;
    bool isAttackingEnemy = false;

    for(auto &move : moves) {
        newBoard = MakeMove(move);

        if(newBoard.IsAttackingEnemyChecker(move))
            isAttackingEnemy = true;


        vector<Move> newMoves;
        newMoves = newBoard.GetAllMoves(move);

        newBoard.GetAllAtackerBoard(newMoves, boards);
    }

    return boards;
}

void Board::GetAllAtackerBoard(vector<Move> moves, vector<Board>& boards) {
    vector<Board> newBoards;
    Board newBoard = *this; 

    for(auto &move : moves) {
        vector<Move> newMoves;
        newBoard.JumpOverChecker(move);

        newMoves = newBoard.GetAllMoves(move);

        for(auto &move : newMoves) {
            attackerMoves.push_back(move);

            if(newBoard.IsAttackingEnemyChecker(move))
                newBoard.GetAllAtackerBoard(moves, boards);
        }

        boards.push_back(newBoard);
    }
}

Move Board::AIMove() {
    
    


}

Move Board::PlayerMove() {
    int x, y, dx, dy;  

    bool isPossibleMove = false;
    bool isCorrectChecker = false;
    bool isAttackingEnemy = false;
    vector<Move> possibleMoves;
    vector<Move> allMoves;
    cout << "Aktualnie przy ruchu: " << actualPlayer << endl;

    while(!isPossibleMove) {
        while(!isCorrectChecker) {   
            cout << "Podaj wspolrzedne pionka: wiersz kolumna (np. 3 3 ), ktory chcesz ruszyc: "  << endl;
            cin >> x >> y;
            if(IsPlayerChecker(x, y))
                isCorrectChecker = true; //Check if chosen checker is correct
        } 

        possibleMoves.clear();
        possibleMoves = GetAllMoves(x, y);

        for(auto &move : possibleMoves)
            move.printMove();

        if(possibleMoves.empty()) { //Check if move there are possible moves from this checker
            cout << "Brak mozliwosci ruchu dla pionka, wybierz inny pionek" << endl; 
            isCorrectChecker = false;
        }
        else 
            isPossibleMove = true;
    }

    
    do {    
        cout << "Podaj gdzie chcesz sie ruszyc"  << endl;
        cin >> dx >> dy;
    } while(!IsMovePossible(x, y, dx, dy));

    JumpOverChecker(x, y, dx, dy);

    *this = MakeMove(CreateMove(x, y, dx, dy)); //make move
    

    while(isAttackingEnemy) {
        isAttackingEnemy = false;

        x = dx;
        y = dy;
        possibleMoves.clear();
        allMoves.clear();
        allMoves = GetAllMoves(x, y);

        for(auto &move : allMoves) {
            if(IsAttackingEnemyChecker(move))
                possibleMoves.push_back(move);
        }

        if(!possibleMoves.empty()) {
            isAttackingEnemy = true;
            cout << "Wybierz mozliwy ruch z podanych:" << endl;
            for(auto &move : possibleMoves) {
                move.printMove();
            }
            
            int index = 9999;
            while(index >= possibleMoves.size()) {      
                cout << "Podaj index ruchu" << endl;          
                cin >> index; 
            }

            dx = possibleMoves[index].dx;
            dy = possibleMoves[index].dy;

            JumpOverChecker(x, y, dx, dy);

            *this = MakeMove(CreateMove(x, y, dx, dy)); 
        }
    }

    ChangePlayer();
}


