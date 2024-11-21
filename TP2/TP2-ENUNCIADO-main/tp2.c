#include "extra/engine.h"
#include "extra/ansi.h"
#include <stdio.h>
#include "src/menu.h"
#include "src/pokedex.h"



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


void mostrar_pokedex(){
	printf("Aqui estan los pokemones que se ingresaron... \n");
}

void avanzar_juego(){
	printf("Inicializando el juego... \n");
}

void elegir_semilla(){
	printf("deberias ingresar una semilla... \n");
}

void cerrar_juego(){
	printf("Saliendo del juego...\n");
	return;
}


//post: Imprime una pequeña intro para que el usuario sepa que comandos pasarle y como "reaccionan" al mismo.
void imprimir_inicio()
{
	printf(ANSI_COLOR_BLUE"\t\t\t\t\t\t\t-----------------------------------------------------\n"); 
    printf("\t\t\t\t\t\t\t|" ANSI_COLOR_GREEN ANSI_COLOR_BOLD"    BIENVENIDO A POKEMON GO 2: AHORA ES PERSONAL"ANSI_COLOR_BLUE "   |\n");
    printf(ANSI_COLOR_BLUE"\t\t\t\t\t\t\t-----------------------------------------------------\n"ANSI_COLOR_RESET);
    printf("\n");

	printf(ANSI_COLOR_MAGENTA"Hola jugador,bienvenido a " ANSI_COLOR_BOLD "Pokemon go 2\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_GREEN ANSI_COLOR_BOLD"El objetivo del juego es que atrapes pokemones, antes de que se acabe el tiempo.\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_GREEN"Lo ideal es que trapes a pokemones con el mismo color, asi obtendras un multiplicador al puntaje al capturarlos.\n");
	printf(ANSI_COLOR_GREEN"Los pokemones se mueven a lo largo del tablero, pero no se mueven si no te moves.\n");
	printf(ANSI_COLOR_GREEN"Por ultimo tenes 60 segundos de juego en total, una vez llegado a 0, finaliza el juego.\n");
	printf(ANSI_COLOR_RED ANSI_COLOR_BOLD"A continuacion veras un menu en el cual podras elegir entre 4 opciones.\n");
	printf(ANSI_COLOR_RED "Cabe aclarar que tambien se aceptan las minusculas\n"ANSI_COLOR_RESET);

	printf(ANSI_COLOR_YELLOW"Una vez sabida esta informacion, ya puedes empezar a jugar, suerte!\n"ANSI_COLOR_RESET);
	
	printf(ANSI_COLOR_RED"====================================================\n"); 
	printf(ANSI_COLOR_CYAN"| [J]: Empezar Juego\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN"| [S]: Empezar Juego usando una semilla que eligas\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN"| [P]: Mostrar todos los pokemones en la pokedex\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_CYAN"| [Q]: Salir del juego\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED"===================================================\n"ANSI_COLOR_RESET);
}


int main()
{
	imprimir_inicio();


	menu_t *menu = menu_crear();
	menu_agregar_opciones(menu,'P',mostrar_pokedex);
	menu_agregar_opciones(menu,'p',mostrar_pokedex);

	menu_agregar_opciones(menu,'J',avanzar_juego);
	menu_agregar_opciones(menu,'j',avanzar_juego);

	menu_agregar_opciones(menu,'S',elegir_semilla);
	menu_agregar_opciones(menu,'s',elegir_semilla);

	menu_agregar_opciones(menu,'Q',cerrar_juego);
	menu_agregar_opciones(menu,'q',cerrar_juego);

	char entrada;
	int opcion = -1;
	while (opcion == -1) {
		printf("\nIngrese la opcion que quiera ------------> ");
		if (scanf(" %c", &entrada) == 1) {
			if (!menu_ejecutar_entrada(menu, entrada)) {
                printf("\nERROR 405, por favor ingrese una opcion correcta");
            } else {
                opcion = 0; 
            }
		}
	}	


	//struct jugador jugador = { 0 };

	//game_loop(logica, &jugador);

	//mostrar_cursor();


	menu_destruir(menu);
	return 0;
}
