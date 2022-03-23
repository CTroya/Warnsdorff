#include <iostream>
#include <iomanip>
#define ln '\n'
using namespace std;
int getKey() {
	return rand() % 7;
}
class Board {
public:
	int** matrix;
	int sizeI, sizeJ;

	Board(int sizeI, int sizeJ, int initValue) : sizeI(sizeI), sizeJ(sizeJ) {
		matrix = new  int* [sizeI];
		for (int i = 0; i < sizeJ; i++) {
			matrix[i] = new int[sizeJ];
		}
		for (int i = 0; i < sizeI; i++) {
			for (int j = 0; j < sizeJ; j++) {
				matrix[i][j] = initValue;
			}
		}
	}
	Board(int sizeI, int sizeJ) : sizeI(sizeI),sizeJ(sizeJ) {
		matrix = new  int* [sizeI];
		for (int i = 0; i < sizeJ; i++) {
			matrix[i] = new int[sizeJ];
		}
		for (int i = 0; i < sizeI;i++) {
			for (int j = 0; j < sizeJ; j++) {
				matrix[i][j] = -1;
			}
		}
	}
	bool isFull(){
		for(int i = 0; i < sizeI;i++){
			for(int j = 0; j < sizeJ;j++){
				
			}
		}
	}
	void print() {
		for (int i = 0; i < sizeI; i++) {
			for (int j = 0; j < sizeJ; j++)
				if(matrix[i][j] == -1)
					cout << '#' << setw(3);
				else 
					cout << matrix[i][j] << setw(3);
			cout << ln << setw(3);
		}
		cout << ln << setw(3);
	}
};
class Wboard : public Board {
	using Board::Board;
	const int moves[8][2] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1} };
//Calculate the warnsdorff value of a specific cell determined by the function parameters
public:
	int warnsdorff(int posicI, int posicJ,Board board) {
		int jumps = 0;
		for (int i = 0; i < 8; i++) {
			if (posicI + moves[i][0] < 8 && posicJ + moves[i][1] < 8 && posicI + moves[i][0] >= 0 && posicJ + moves[i][1] >= 0) {
				if (board.matrix[posicI + moves[i][0]][posicJ + moves[i][1]] == -1) jumps++;
			}
		}
		return jumps;
	}
//Update warnsdorff's values of every cell on the board and stores them into the class's matrix
	void calculateBoard(Board board) {
	for (int i = 0; i < sizeI; i++) {
		for (int j = 0; j < sizeJ; j++) {
			matrix[i][j]=warnsdorff(i, j,board);
			}
		}
	}
};

class Horse{
public:
    int posicI,posicJ,k,moveCounter=1;
    Horse(int i,int j,Board board) : posicI(i),posicJ(j){board.matrix[posicI][posicJ] = 0;}
    Horse(Board board) : posicI(0),posicJ(0){ board.matrix[posicI][posicJ] = 0;}
    
    int wMoves[8];
	const int moves[8][2] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1} };
//Calculate the warnsdorff value of a specific cell determined by the function parameters
    int inBounds(Board board,int i, int j){
        return ((i >= 0 && j >= 0) && (i < board.sizeI && j < board.sizeJ && board.matrix[i][j] == -1));
    }
	int warnsdorff(int posicI, int posicJ,Board board) {
		int jumps = 0;
		for (int i = 0; i < 8; i++) {
			if (posicI + moves[i][0] < 8 && posicJ + moves[i][1] < 8 && posicI + moves[i][0] >= 0 && posicJ + moves[i][1] >= 0) {
				if (board.matrix[posicI + moves[i][0]][posicJ + moves[i][1]] == -1) jumps++;
			}
		}
		return jumps;
	}
//Update warnsdorff's values of every cell on the board and stores them into the class's matrix
	void calculateWVector(Board board) {
    int newI,newJ;
	for (int i = 0; i < 8; i++) {
            newI = posicI + moves[i][0];
            newJ = posicJ + moves[i][1];
            if(inBounds(board,newI,newJ))
                wMoves[i] = warnsdorff(newI,newJ,board);
            else
                wMoves[i] = 9999;
		}
	}
    void makeMove(Board board){
		calculateWVector(board);
		int newI,newJ;
        k = 9999;
        for(int i = 0; i < 8;i++){
            if(k > wMoves[i]) k = i;
        }
		if(k == 9999) {cout << "\naiuda no me puedo mover D:" << endl;
			backTrack(board);
		}else{
			posicI = posicI + moves[k][0];
			posicJ = posicJ + moves[k][1];
        	board.matrix[posicI][posicJ] = moveCounter++;
		}
    }
	void backTrack(Board board){
		board.matrix[posicI][posicJ] = -1;
		moveCounter--;
		for(int i = 0;i < board.sizeI;i++){
			for(int j = 0; j < board.sizeJ; j++){
				if(board.matrix[i][j] == moveCounter){
					posicI = i;
					posicJ = j;
					break;
				}
			}
		}
	}
};

int main(void) {
	Board board(8,8);
	board.print();
    Horse horse(board);
	for(int i = 0; i < 64; i++){
		horse.makeMove(board);
		board.print();
	}
}