/*
 ============================================================================
 Name        : 0.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "variables.h"
#include "tablero.h"
#include "humano.h"
#include "jugabilidad.h"
#include "computadora.h"

//Tablero del juego
int board[TAM_MAX][TAM_MAX];
//Tablero espejo que se usa para evaluar jugadas
int mirror[TAM_MAX][TAM_MAX];
// modojuego define quienes juegan. Util que sea externo para cuando se come, ya que si es PC vs PC, se come automáticamente sin consultar posiciones.
int modoJuego = 9;

// Permite seleccionar el menu del juego:
// 1 - HUMANO VS PC
// 2 - PC VS HUMANO
// 3 - PC VS PC
int menuJuego() {
	int opcion;
	do {
		printf("\n¡Bienvenido a Cephalopod!");
		printf("\nMENU DEL JUEGO");
		printf("\n--------------\n");
		printf("\n 1 - HUMANO VS PC (Empieza humano)");
		printf("\n 2 - PC VS HUMANO (Empieza PC)");
		printf("\n 3 - PC VS PC");
		printf("\n 9 - SALIR");
		printf("\n\n Elegir opcion (1,2,3 o 9): ");
		scanf("%d", &
		opcion);
	} while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 9);
	return (opcion);
}
// Menú de inteligencia de la PC
// Sólo válido cuando juega la PC
int menuPCIA() {
	int opcion;
	do {
		printf("\n\nSELECCIÓN ESTRATEGIA DE IA");
		printf("\n--------------------------\n");
		printf("\n 1 - ALEATORIA (Sin IA, solo al azar)");
		printf("\n 2 - Estrategia FIRST FREE SPACE (Ocupa primer espacio libre encontrado)");
		printf("\n 3 - Con IA (Juega inteligentemente)");
		printf("\n 9 - SALIR");
		printf("\n\n Elegir opcion (1,2,3 o 9): ");
		scanf("%d", &
		opcion);
	} while (opcion != 1 && opcion != 2 && opcion != 3 && opcion != 9);
	return (opcion);
}
//Módulo principal: MAIN
int main() {
	// Que player juega
	int turno = 0;
	// Estrategia de IA para la PC
	int modoIA = 0;
	// Semilla para la generación de números aleatorios
	srand(time(NULL));
	do {
		//Opciones de juego
		modoJuego= menuJuego();
		// Si juega la PC, elegir estrategia IA
		if( modoJuego == 1 || modoJuego == 2 || modoJuego == 3)
		modoIA= menuPCIA();
	//Inicializar e imprimir el tablero
	initBoard();
	printBoard();
	//Jugar segun la opcion deseada
	switch (modoJuego) {
	case 1: //HUMANO VS PC
		while (!finDelJuego()) {
			if (turno++ % 2 == 0)
				juegaHumano(PLAYER1);
			else
				juegaPc(PLAYER2, modoIA);
			printBoard();
		}
		if (checkWinner() == PLAYER1) {
			printf("\n¡Ganaste! La PC lo mira por TV");
		} else {
			printf("\n¡Perdiste! Sos el Tito Torres de este juego");
		}
		break;
	case 2: //PC VS HUMANO
		while (!finDelJuego()) {
			if (turno++ % 2 == 0)
				juegaPc(PLAYER1, modoIA);
			else
				juegaHumano(PLAYER2);
			printBoard();
		}
		if (checkWinner() == PLAYER2) {
			printf("\n¡Ganaste! La PC lo mira por TV");
		} else {
			printf("\n¡Perdiste! Sos peor que Huguito Fernandez tirando un centro");
		}
		break;
	case 3: //PC1 VS PC2
		while (!finDelJuego()) {
			if (turno++ % 2 == 0)
				juegaPc(PLAYER1, modoIA);
			else
				juegaPc(PLAYER2, modoIA);
			printBoard();
		}
		if (checkWinner() == PLAYER1) {
			printf("\n¡Ganaste! La PC lo mira por TV");
		} else {
			printf("\n¡Perdiste! Sos peor que Paiva frente al arco");
		}
		break;
		break;
	case 9: //Salir
		break;
	default:
		break;
	}
} while(modoJuego != 9);
	return 0;
}
