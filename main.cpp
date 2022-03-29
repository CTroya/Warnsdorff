#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
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
	int inBounds(int i, int j){
        return ((i >= 0 && j >= 0) && (i < sizeI && j < sizeJ && matrix[i][j] == -1));
    }
	bool isFull(){
		for(int i = 0; i < sizeI;i++){
			for(int j = 0; j < sizeJ;j++){
				if(matrix[i][j]==0) return false;
			}
		}
    return true;
	}
	void print(int posicI, int posicJ) {
		static int bruh = -1;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN);	
		cout <<"						   A:    B:    C:    D:    E:    F:    G:    H: " << ln;
	for (int i = 0; i < 8; i++) { 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		for(int p = 0; p < 3;p++){
			
			if(p == 1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN);
				cout << "                                              " << i+1 <<".";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				for (int j = 0; j < 8; j++) {
					((j + i) % 2) ? SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED) :
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN );
			    		cout.width(4);
						if(matrix[i][j] == -1) cout <<' ' << setw(2);
						else if(posicI == i && posicJ == j){
							cout.width(1);
							cout << " |&&|";
						}else cout << matrix[i][j] << setw(2);
						cout <<' ';
           			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				}
				cout << endl; 
			}else{
				cout << "						" ;
						
				for (int j = 0; j < 8; j++) {
					((j + i) % 2) ? SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED) :
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN );
			    		cout.width(4);
						if(j == posicJ && i == posicI)cout <<"--" << setw(2);
						else cout <<' ' << setw(2);
						cout <<' ';
           			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				}
				cout << endl;
			}
		}
		
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN);	
	cout << "						  		     Move:" << ++bruh << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
};
class Wboard : public Board {
	using Board::Board;
	const int moves[8][2] = { {-2,1},{-1,2},{1,2},{2,1},{2,-1},{1,-2},{-1,-2},{-2,-1} };
//Calculate the warnsdorff value of a specific cell determined by the function parameters
public:
	int warnsdorff(int posicI, int posicJ,Board board) {
		int jumps = 0;
		if(board.inBounds(posicI,posicJ)){
			for (int i = 0; i < 8; i++) {
				if(board.inBounds(posicI+moves[i][0],posicJ+moves[i][1])) jumps++;
			}
		}else return 99;
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
	int warnsdorff(int posicI, int posicJ,Board board) {
		int jumps = 0;
		if(board.inBounds(posicI,posicJ)){
			for (int i = 0; i < 8; i++) {
				if(board.inBounds(posicI+moves[i][0],posicJ+moves[i][1])) jumps++;
			}
		}else return 99;
		return jumps;
	}
//Update warnsdorff's values of every cell on the board and stores them into the class's matrix
	void calculateWVector(Board board) {
    int newI,newJ, min_deg_idx = 9999,min_deg=69;
	for (int i = 0; i < 8; i++) {
            newI = posicI + moves[i][0];
            newJ = posicJ + moves[i][1];
            if(board.inBounds(newI,newJ))
                wMoves[i] = warnsdorff(newI,newJ,board);
            else
                wMoves[i] = 99;
		}
	}
    int makeMove(Board board){
		calculateWVector(board);
		int newI,newJ,c;
        k = 99; int kvalue = 99;
        for(int i = 0; i < 8;i++){
			newI = posicI + moves[i][0];
			newJ = posicJ + moves[i][1];
			if (board.inBounds(newI,newJ) && wMoves[i] <kvalue){
				kvalue = wMoves[i]; 
				k = i;
        	}
        }
		if(kvalue == 99) {
			return 0;
		}
		newI = posicI + moves[k][0];
		newJ = posicJ + moves[k][1];
        board.matrix[newI][newJ] = board.matrix[posicI][posicJ] + 1;
		posicI = newI;
		posicJ = newJ;
		return 1;
	}
	int solveBoard(Board board){
		for(int i = 0; i < 64;++i){
			if(makeMove(board) == 0) return 0;
			//board.print(posicI,posicJ);
			board.print(posicI,posicJ);
		}
		
	}
};
/*Printea archivos de texto
*/
void banner(const char* prompt) {
    int i=0;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN);
    FILE * title;
    int c,end;
    int counter = 0;
    end = 1215;
    title = fopen(prompt, "r");
    c = fgetc(title);
    while (c != EOF) {
        printf("%c", c);
        c = fgetc(title);
        }
    fclose(title);
    printf("\n");
}

int main(void) {
	HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 1210, 800, TRUE); // 800 width, 100 height
	int startPosic[2];
	Board board(8,8);
	Wboard woard(8,8);
	//board.print();
	banner("banner.txt");
	board.print(10,10);
	//Cambia los colores de la consola
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN);
	do{
		cout << "Inserte la posicion de columnas del inicio: ";
		cin >> startPosic[0];
		cout << "Inserte la posicion de filas del inicio: ";
		cin >> startPosic[1];
	}while(!board.inBounds(startPosic[0],startPosic[1]));
    Horse horse(startPosic[0],startPosic[1],board);
	horse.solveBoard(board);
	system("PAUSE");
	//Resetea los colores de la consola
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	return 0;
}
