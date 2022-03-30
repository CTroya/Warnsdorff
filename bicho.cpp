#pragma comment(lib, "winmm.lib")
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <ctime>
#include <mmsystem.h>
#include <io.h>
#include <fcntl.h>
#define ln '\n'
using namespace std;

class Board {
public:
	int** matrix;
	int sizeI, sizeJ;
  //Constructor
	Board(int sizeI, int sizeJ, int initValue) : sizeI(sizeI), sizeJ(sizeJ) {
		matrix = new  int* [sizeI];
		for (int i = 0; i < sizeI; i++) {
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
  //Para verificar si la posicion esta dentro del tablero
	bool inBounds(int i, int j){
        return ((i >= 0 && j >= 0) && (i < sizeI && j < sizeJ && matrix[i][j] == -1));
    }
  //Recorre todo el tablero para verificar si esta lleno, la condicion para esto es que ninguna posicion tenga un cero.
	bool isFull(){
		for(int i = 0; i < sizeI;i++){
			for(int j = 0; j < sizeJ;j++){
				if(matrix[i][j]==0) return false;
			}
		}
    return true;
	}
  //Funcion de printeo para el tablero
	void print(int posicI, int posicJ) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_BLUE);	
	for (int i = 0; i < sizeI; i++) { 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		for(int p = 0; p < 3;p++){
			if(p == 1){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_BLUE);
                if(i + 1 < 10)
			    	cout << "                                             " << i+1 << setw(2)<<".";
                else
                    cout << "                                            " << i+1 << setw(2)<<".";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				for (int j = 0; j < sizeJ; j++) {
					((j + i) % 2) ? SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_BLUE) :
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE );
			    		cout.width(4);
						if(matrix[i][j] == -1) cout <<' ' << setw(2);
						else if(posicI == i && posicJ == j){
							cout.width(2);
							cout << " |&&|";
						}else cout << matrix[i][j] << setw(2);
						cout <<' ';
           			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				}
				cout << endl; 
			}else{
				cout << "						" ;
				for (int j = 0; j < sizeJ; j++) {
					((j + i) % 2) ? SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_BLUE) :
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE );
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
	cout << endl;
	}

  ~Board()//Destructor
  {
    for(int i = 0; i < sizeI; i++){
			delete [] matrix[i];
		}
		delete[]matrix;
  }
};
void banner(const char* prompt) {
    int i=0;
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, 1500, 800, TRUE); // 800 width, 100 height
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_BLUE);
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
int main(void){
	system("chcp 65001 < nul");
	cout <<" " << endl;
  int M,N;
  banner("bugBanner.txt");
   do {
     PlaySound(TEXT("siuuu.wav"),0,SND_ASYNC);
     for(int i = 0; i < 4; i++){
      system("color 50");
      Sleep(1);
      system("color 05");
    }
    std::cout << "El numero de filas debe estar dentro del rango 2<=M<=41 y las columnas dentro del rango 2<=M<=21"<<endl;
    std::cout << "Inserte el numero de filas: ";
    std::cin >> M;
    std::cout << "Inserte el numero de columnas: ";
    std::cin >> N;
  } while (M<= 2 || M >= 41|| N <= 2 || N >= 21);
  //PlaySound(TEXT("SystemStart"), NULL, SND_ALIAS);
  //PlaySound(TEXT("siuuu.wav"), NULL, SND_ASYNC);  
  //mciSendString("play siuuu.wav", NULL, 0, NULL);
  Board room(M,N,0);
  srand(time(NULL));
  int moves = 0;
  int posicI = rand() % M;
  int posicJ = rand() % N;
  int candidateI;
  int candidateJ;
  if (M == 15 && N == 15) {
    posicI = 10;
    posicJ = 10;
  } else if (M == 40 && N == 20) {
    posicI = 1;
    posicJ = 1;
  }
  room.print(posicI, posicJ);
  do {
    // printRoom(room, posicI, posicJ);
    do {
      candidateI = posicI + rand() % 3 - 1;
      candidateJ = posicJ + rand() % 3 - 1;
    } while (candidateI > M - 1 || candidateJ > N - 1 || candidateI < 0 || candidateJ < 0);
    posicI = candidateI;
    posicJ = candidateJ;
    room.matrix[posicI][posicJ]++;
    moves++;
    if (moves % 100 == 0)
      room.print(posicI, posicJ);
  } while (moves < 25000 && !room.isFull());
  room.print(posicI, posicJ);
  if (room.isFull()) {
    std::cout << "El BICHOOOOOOO recorrio el cuarto en " << (int)moves
              << " pasos \n SIUUUUUUUUUUUU\n";
  } else {
    std::cout << "El bichito no recorrio el cuarto en " << (int)moves
              << " pasos \n SIUUUUUUUUUUUU\n";
  }
  system("Pause");
  banner("bugBanner.txt");
  PlaySound(TEXT("siuuu.wav"),0,SND_ASYNC);
  for(int i = 0; i < 5; i++){
    system("color 05");
    Sleep(1);
    system("color 50");
  }
  return 0;
}
