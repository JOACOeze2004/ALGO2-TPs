#include "extra/engine.h"
#include "extra/ansi.h"
#include <stdio.h>

struct jugador {
	int x;
	int y;
	int iteraciones;
};

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int logica(int entrada, void *datos)
{
	struct jugador *jugador = datos;
	borrar_pantalla();

	if (entrada == TECLA_DERECHA)
		jugador->x++;
	else if (entrada == TECLA_IZQUIERDA)
		jugador->x--;
	else if (entrada == TECLA_ARRIBA)
		jugador->y--;
	else if (entrada == TECLA_ABAJO)
		jugador->y++;

	jugador->x = min(20, max(0, jugador->x));
	jugador->y = min(10, max(0, jugador->y));

	jugador->iteraciones++;

	printf("Utilizar " ANSI_COLOR_CYAN ANSI_COLOR_BOLD
	       "⬆⬇⬅➡" ANSI_COLOR_RESET " para moverse\n");

	printf("Presionar " ANSI_COLOR_RED ANSI_COLOR_BOLD "Q" ANSI_COLOR_RESET
	       " para salir\n");

	printf("Iteraciones: %d Tiempo: %d\n", jugador->iteraciones,
	       jugador->iteraciones / 5);

	for (int i = 0; i < jugador->y; i++)
		printf("\n");

	for (int i = 0; i < jugador->x; i++)
		printf(" ");

	printf(ANSI_COLOR_MAGENTA ANSI_COLOR_BOLD "Ω" ANSI_COLOR_RESET);

	printf("\n");
	esconder_cursor();

	return entrada == 'q' || entrada == 'Q';
}

int main()
{
	struct jugador jugador = { 0 };

	game_loop(logica, &jugador);

	mostrar_cursor();

	return 0;
}
