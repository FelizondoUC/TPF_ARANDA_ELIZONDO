/*
 * computadora.c
 *
 *  Created on: 22 oct. 2023
 *      Author: lp1-2023
 */

// Player1, tiene dados del 1 al 6
#define PLAYER1     1
// Player2, tiene dados del 7 al 12
#define PLAYER2     2
// Tableros, principal y espejo para evaluación
#define MAINBOARD   1
#define MIRRORBOARD 2
// Valor inicial mejor jugada.
#define MENOS_INFINITO  -20000
#define VACIO       0
#define TAM_MAX     5
// Valores booleanos
#define TRUE        1
#define FALSE       0
// Modo de juego de IA
#define AZAR_IA         1
#define FIRSTSPACE_IA   2
#define INTELIGENTE          3
//Tablero del juego
extern int board[TAM_MAX][TAM_MAX];
//Tablero espejo que se usa para evaluar jugadas
extern int mirror[TAM_MAX][TAM_MAX];
// modojuego define quienes juegan. Util que sea externo para cuando se come, ya que si es PC vs PC, se come automáticamente sin consultar posiciones.


// ESTRATEGIA ALEATORIA
// Cuando juega la PC, lo hace en forma aleatoria y carga en azarX,azarY la posición donde juega
// Siempre se carga en board directo.
int jugadaAleatoria(int *azarX, int *azarY) {
	int buscarSgte = FALSE;
	int i, j, count = 2;
	// Genera un número aleatorio en el rango de 0 a 4
	*azarX = rand() % 5;
	*azarY = rand() % 5;
	// Si azarX,azarY no corresponde a una posición vacía, se busca a partir de esa posición la siguiente vacía. Si no hay, se busca desde el principio.
	do {
		for (i = 0; i < TAM_MAX; i++) {
			for (j = 0; j < TAM_MAX; j++) {
				if (i == *azarX && j == *azarY &&
				!buscarSgte) {
					if (board[i][j] == VACIO)
						// Los valores random de azar son de una pos libre
						return ( TRUE);
					else
						buscarSgte = TRUE;
				}
				// La pos de azar estaba ocupada
				if (buscarSgte) {
					if (board[i][j] == VACIO) {
						*azarX = i;
						*azarY = j;
						return ( TRUE);
					}
				}
			}
		}
	} while (--count > 0);
	return ( FALSE);
}

// JUEGA PC: la función de evaluación evalua cada jugada
//Estrategia: se recorre el tablero, cada vez que hay una posición libre, se juega, se evalua el tablero con un puntaje, se borra y se busca la siguiente posición libre. Si existen posiciones de tablero que arrojan posiciones iguales y son las mejores, entonces se elije la primera que se obtuvo.
void juegaPc(int player, int modoIA) {
	int maxVal = MENOS_INFINITO, iMax, jMax;
	int valor;
	if (modoIA == FIRSTSPACE_IA) {
		for (int i = 0; i < TAM_MAX; i++) {
			for (int j = 0; j < TAM_MAX; j++) {
				//Es una posición libre, evaluar
				if (board[i][j] == VACIO) {
					//Se copia el contenido del tablero
					boardToMirror();
					// Se hace la jugada en la copia
					mirror[i][j] = (player == PLAYER1 ? 1 : 7);
					//Si se puede, comer fichas
					comeAdyacente(i, j, MIRRORBOARD, player);
					//Obtener evaluación del tablero
					if ((valor = evaluateBoard()) > maxVal) {
						maxVal = valor;
						iMax = i;
						jMax = j;
					}
				}
			}
		}
	} else if (modoIA == AZAR_IA)
		jugadaAleatoria(&iMax, &jMax);
	// Hacer la jugada con mayor valor
	board[iMax][jMax] = (player == PLAYER1 ? 1 : 7);
	comeAdyacente(iMax, jMax, MAINBOARD, player);
	// Indicar donde jugó la PC
	printf("\n La PC jugó en %d, %d \n", iMax, jMax);
}
