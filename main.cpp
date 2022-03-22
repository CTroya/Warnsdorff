#include <iostream>
#include <iomanip>
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
	void print() {
		for (int i = 0; i < sizeI; i++) {
			for (int j = 0; j < sizeJ; j++)
				cout << matrix[i][j] << setw(3);
			cout << '\n';
		}
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
    int posicI,posicJ,k,jumps=0;
    Horse(int i,int j) : posicI(i),posicJ(j){}
    Horse() : posicI(0),posicJ(0){}
    
    int wMoves[8];
	const int moves[8][2] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1} };
//Calculate the warnsdorff value of a specific cell determined by the function parameters
    int inBounds(Board board,int i, int j){
        return ((i >= 0 && j >= 0) && (i < board.sizeI && j < board.sizeJ));
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
        k = 9999;
        for(int i = 0; i < 8;i++){
            if(k > wMoves[i]) k = wMoves[i];
        }
        board.matrix[posicI + moves[k][0]][posicJ + moves[k][1]] = jumps++;
    }
};

   


int main(void) {
	Board board(8,8);
	board.print();
    Horse horse;

}