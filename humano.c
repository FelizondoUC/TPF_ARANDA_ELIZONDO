/*
 * humano.c
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


// JUEGA HUMANO. Elegir fila y columna
void juegaHumano(int player) {
	int i, j;
	do {
		printf("\nIntroduce tu jugada (fila columna): ");
		scanf("%d %d", &i, &j);
	} while (i < 0 || i > TAM_MAX || j < 0 || j > TAM_MAX
			|| board[i][j] != VACIO);
	if (player == PLAYER1) // Player1, dados 1-6
		board[i][j] = 1;
	else
		// Player2, dados 7-12
		board[i][j] = 7;
	// Si se puede, comer
	comeAdyacente(i, j, MAINBOARD, player);
}
