# Warnsdorff
Taller de Lenguajes de programacion 2, ejercicios del bicho en el cuarto y del recorrido del caballo.
## TP1: EL RECORRIDO DEL INSECTO
### Clase: Board
Clase que representa a un tablero de juegos de mesa, se puede definir el tamaño al declarar una instancia, el valor inicial de las posiciones del array que representa el tablero.

#### bool Board::inBounds(int i, int j)
Verifica si las coordenadas (i,j) representan una casilla vacia en el tablero.(También verifica desbordamientos) <br />
Retorna: Verdadero si representa una casilla vacia, de lo contrario retorna falso.
#### bool Board::isFull()
  Verifica si el tablero esta vacio o no
#### void Board::print()
Imprime el tablero con un diseño de tablero de ajedrez
#### void banner(const char* prompt)
Imprime los contenidos de un archivo en la terminal <br />
Prompt: Directorio del archivo a imprimir
## Desafio 1: EL RECORRIDO DEL CABALLO
### Clase: Board
Clase que representa a un tablero de juegos de mesa, se puede definir el tamaño al declarar una instancia, el valor inicial de las posiciones del array que representa el tablero.
#### bool Board::inBounds(int i, int j)
Verifica si las coordenadas (i,j) representan una casilla vacia en el tablero.(También verifica desbordamientos) <br />
Retorna: Verdadero si representa una casilla vacia, de lo contrario retorna falso.
#### bool Board::isFull()
  Verifica si el tablero esta vacio o no
### Clase : wBoard
Clase derivada de Board, es un tablero que marca los numeros de Warnsdorff de cada casilla, se utilizó con intenciones de depuración. <br />
No es utilizada en el codigo final.
#### int wBoard::warnsdorff(int posicI, int posicJ,Board board)
Calcula el valor Warnsdorff de una casilla(posicI,posicJ) dentro del tablero board. 
#### void calculateBoard(Board board)
Calcula el valor Warnsdorff para todas las casillas del tablero board.
### Clase: Horse
Representa al caballo que se encuentra dentro de un tablero
#### int Horse::warnsdorff(int posicI, int posicJ,Board board)
Calcula el valor Warnsdorff de una la casilla(i,j) en el tablero board. <br />
retorna 99 si no encuenta saltos, se utiliza para calcular las jugadas del caballo.
### void calculateWVector(Board board)
Calcula el valor Warnsdorff de cada casilla adjacente valida del caballo.

### int makeMove(Board board)
Realiza un movimiento bajo el criterio del algoritmo de Warnsdorff
### int solveBoard(Board board)
Halla el camino de recorrido del caballo y lo deja guardado en el tablero board
### void banner(const char* prompt)
Imprime un archivo de texto en la consola. <br />
prompt: direccion del archivo


