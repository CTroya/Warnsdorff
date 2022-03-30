# Warnsdorff
Taller de Lenguajes de programacion 2, ejercicios del bicho en el cuarto y del recorrido del caballo.
## TP1: EL RECORRIDO DEL BICHO
## Clase: Board
Clase que representa a un tablero de juegos de mesa, se puede definir el tamaño al declarar una instancia, el valor inicial de las posiciones del array que representa el tablero.

### bool Board::inBounds(int i, int j)
Verifica si las coordenadas (i,j) representan una casilla vacia en el tablero.(También verifica desbordamientos) <br />
Retorna: Verdadero si representa una casilla vacia, de lo contrario retorna falso.
### bool Board::isFull()
  Verifica si el tablero esta vacio o no.
  Retorno: true si esta vacio, false si no.
### void Board::print()
Imprime el tablero con un diseño de tablero de ajedrez
### void banner(const char* prompt)
Imprime los contenidos de un archivo en la terminal <br />
Prompt: Directorio del archivo a imprimir
## Desafio 1: EL RECORRIDO DEL CABALLO
## Clase: Board
Clase que representa a un tablero de juegos de mesa, se puede definir el tamaño al declarar una instancia, el valor inicial de las posiciones del array que representa el tablero.
### bool Board::inBounds(int i, int j)
Verifica si las coordenadas (i,j) representan una casilla vacia en el tablero.(También verifica desbordamientos) <br />
Retorna: Verdadero si representa una casilla vacia, de lo contrario retorna falso.
### bool Board::isFull()
  Verifica si el tablero esta vacio o no
## Clase : wBoard
Clase derivada de Board, es un tablero que marca los numeros de Warnsdorff de cada casilla, se utilizó con intenciones de depuración. <br />
No es utilizada en el codigo final.
### int wBoard::warnsdorff(int posicI, int posicJ,Board board)
Calcula el valor Warnsdorff de una casilla(posicI,posicJ) dentro del tablero board.
Retorna el valor Warnsdorff
### void wBoard::calculateBoard(Board board)
Calcula el valor Warnsdorff para todas las casillas del tablero board.
## Clase: Horse
Representa al caballo que se encuentra dentro de un tablero
### int Horse::warnsdorff(int posicI, int posicJ,Board board)
Calcula el valor Warnsdorff de la casilla(i,j) en el tablero board y retorna ese valor. <br />
retorna 99 si no encuenta saltos, se utiliza para calcular las jugadas del caballo.
### void Horse::calculateWVector(Board board)
Calcula el valor Warnsdorff de cada casilla adjacente valida del caballo.

### int Horse::makeMove(Board board)
Realiza un movimiento bajo el criterio del algoritmo de Warnsdorff
### int Horse::solveBoard(Board board)
Halla el camino de recorrido del caballo y lo deja guardado en el tablero board
### void banner(const char* prompt)
Imprime un archivo de texto en la consola. <br />
prompt: direccion del archivo

# Casos de prueba
## EL RECORRIDO DEL BICHO
Matriz 40x20 con posicion inicial en (1,1) <br />
Posicion inicial
![image](https://user-images.githubusercontent.com/67608871/160844468-a6df7361-dfd6-4ccc-9875-5cca36581fec.png)
Posicion final
![image](https://user-images.githubusercontent.com/67608871/160845268-e2d883ed-0267-463f-a5b2-a42e0ce008db.png)
Matrix 15x15 con inicio en (10,10) <br />
Posicion inicial
![image](https://user-images.githubusercontent.com/67608871/160853599-6abc081a-23f9-45a2-9a31-b53655f3013e.png)

Posicion final
![image](https://user-images.githubusercontent.com/67608871/160852416-09e91061-6541-4904-8158-14f61d432af6.png)
## WARNSDORFF
Posicion Inicial
![image](https://user-images.githubusercontent.com/67608871/160856621-d52914f3-2967-44db-9729-465dc841972a.png)

Posicion Final
![image](https://user-images.githubusercontent.com/67608871/160857415-1f20f6d3-de72-4239-83a1-c55f8911c16b.png)


