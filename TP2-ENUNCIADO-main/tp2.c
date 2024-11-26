#include "extra/engine.h"
#include "extra/ansi.h"
#include <stdio.h>
#include "src/menu.h"
#include "src/pokedex.h"
#include <time.h>

#define MAX_FIL 32
#define MAX_COL 15

typedef struct coordenada{
	int x;
	int y;
} coordenada_t;

typedef struct monstruos{
	coordenada_t posicion;
	char caracter;
	char *color;
	size_t cantidad;
	pokemon_t *pokemon;
} monstruos_t;


struct jugador {
	coordenada_t posicion;
	int iteraciones;
};

typedef struct juego{
	struct jugador *jugador;
	monstruos_t *poke;
} juego_t;


typedef struct tablero{
	char letra;
	char* color;
} tablero_t;

//post: devuelve un coordenada_t con una fila y una columna, generadas de forma aleatoria.
coordenada_t crear_fil_col_aleatorias()
{
    coordenada_t coordenada_aleatoria_i_j;
    coordenada_aleatoria_i_j.x = rand() % (MAX_FIL);
    coordenada_aleatoria_i_j.y = rand() % (MAX_COL);
    return coordenada_aleatoria_i_j;
}

// pre: Asumimos que los argumentos que le pasamos son validos (o sea le pasamos
// un archivo .csv y el ejecutable). post: Devuelve false en caso de que le
// pasemos menos de dos arguemntos, sino devolvemos true.
bool son_argumentos_validos(int argc, const char *argv[])
{
	if (argc < 2) {
		printf("Error, el archivo %s<archivo> No existe, paseme uno que sea valido",
		       argv[0]);
		return false;
	}
	return true;
}

void liberar_pokemon(void *elemento)
{
	struct pokemon *pokemon = elemento;
	if (pokemon != NULL) {
		free(pokemon->nombre);
		free(pokemon->color);
		free(pokemon->patron_movimientos);
		free(pokemon);
	}
}

bool imprimir_pokemon(void *elemento, void *ctx)
{
	struct pokemon *poke = elemento;
	printf("Nombre: %s, puntaje: %i, color: %s\n",
	       poke->nombre, poke->puntaje, poke->color);
	return true;
}

int comparador(void *a, void *b)
{
	if (a == NULL && b == NULL) {
		return 0;
	}
	if (a == NULL) {
		return -1;
	}
	if (b == NULL) {
		return 1;
	}
	struct pokemon *poke_a = (struct pokemon *)a;
	struct pokemon *poke_b = (struct pokemon *)b;
	return strcmp(poke_a->nombre, poke_b->nombre);
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

void porcesar_entrada(int entrada, juego_t *juego){
	struct jugador *jugador = juego->jugador; 
	if (entrada == TECLA_DERECHA)
		jugador->posicion.x++;
	else if (entrada == TECLA_IZQUIERDA)
		jugador->posicion.x--;
	else if (entrada == TECLA_ARRIBA)
		jugador->posicion.y--;
	else if (entrada == TECLA_ABAJO)
		jugador->posicion.y++;
}

void imprimir_cabezera(juego_t *juego){
	struct jugador *jugador = juego->jugador; 
		printf("Utilizar " ANSI_COLOR_CYAN ANSI_COLOR_BOLD
	       "⬆⬇⬅➡" ANSI_COLOR_RESET " para moverse\n");
	printf("Presionar " ANSI_COLOR_RED ANSI_COLOR_BOLD "Q" ANSI_COLOR_RESET
	       " para salir\n");
	printf("Iteraciones: %d Tiempo: %d\n", jugador->iteraciones,
	       jugador->iteraciones / 5);
}

//pre:
//post:
void imrpimir_terreno(tablero_t terreno[MAX_COL][MAX_FIL]){
	for (int y = 0; y < MAX_COL; y++){
		for (int x = 0; x < MAX_FIL; x++){
			tablero_t elemento_tablero = terreno[y][x];
			if (elemento_tablero.letra != 0){
				printf("%s%c" ANSI_COLOR_RESET, elemento_tablero.color ,elemento_tablero.letra);
			}			
			else{
				printf(".");
			}
		}
		printf("\n");
	}	
}

int logica(int entrada, void *datos)
{
	juego_t *juego = datos;
	struct jugador *jugador = juego->jugador; 
	monstruos_t *pokemon = juego->poke; 

	borrar_pantalla();
	
	porcesar_entrada(entrada,juego);

	jugador->posicion.x = min(MAX_FIL -1, max(0, jugador->posicion.x));
	jugador->posicion.y = min(MAX_COL -1, max(0, jugador->posicion.y));

	pokemon->posicion.x = min(MAX_FIL -1, max(0, pokemon->posicion.x));
	pokemon->posicion.y = min(MAX_COL -1, max(0, pokemon->posicion.y));

	jugador->iteraciones++;

	imprimir_cabezera(juego);

	tablero_t terreno[MAX_COL][MAX_FIL];
	memset(terreno,0,sizeof(terreno));

	tablero_t jugador_tablero = {.letra = '@',.color = ANSI_COLOR_BOLD ANSI_COLOR_RED};
	tablero_t pokemon_tablero = {.letra = pokemon->caracter,.color = pokemon->color};

	terreno[pokemon->posicion.y][pokemon->posicion.x] = pokemon_tablero;
	terreno[jugador->posicion.y][jugador->posicion.x] = jugador_tablero;


	imrpimir_terreno(terreno);
	
	if (jugador->iteraciones/5 == 60){
		entrada = 'q';
	}
	printf("\n");
	esconder_cursor();

	return entrada == 'q' || entrada == 'Q';
}

void mostrar_pokedex(void *ctx[]){
	printf("Aqui estan los pokemones que se ingresaron... \n");
	int *opcion = (int*)((void**)ctx)[0];
	pokedex_t *pokedex = *(pokedex_t **)ctx[1]; 
	pokedex_mostrar_ordenados(pokedex,imprimir_pokemon,	NULL);
	*opcion = -1;
	return;	
}

void avanzar_juego(void *ctx[]){
	printf("Inicializando el juego... \n");
	int *opcion = (int*)((void**)ctx)[0];
	*opcion = 1;
}

void elegir_semilla(void *ctx[]){
	printf("Ahora deberias ingresar una semilla (que sea un entero) --------->");
	int *semilla = (int*)((void**)ctx)[3];
	int entrada;
	if (scanf(" %i", &entrada) == 1) {
		*semilla = entrada;
	}
	return;
}

void cerrar_juego(void *ctx[]){
	printf("Saliendo del juego...\n");
	pokedex_t *pokedex = *(pokedex_t **)ctx[1]; 
   	menu_t *menu = *(menu_t **)ctx[2];
	pokedex_destruir_todo(pokedex,liberar_pokemon);
	menu_destruir(menu);
	exit(-1);
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
	printf("|" ANSI_COLOR_CYAN"[J]: Empezar Juego\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED"|" ANSI_COLOR_CYAN"[S]: Empezar Juego usando una semilla que eligas\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED"|" ANSI_COLOR_CYAN"[P]: Mostrar todos los pokemones en la pokedex\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED"|" ANSI_COLOR_CYAN"[Q]: Salir del juego\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED"===================================================\n"ANSI_COLOR_RESET);
}

//pre:
//post:
void agregar_todas_opciones(menu_t *menu,void *ctx[]){
	menu_agregar_opciones(menu,'P',mostrar_pokedex,ctx);
	menu_agregar_opciones(menu,'p',mostrar_pokedex,ctx);

	menu_agregar_opciones(menu,'J',avanzar_juego,ctx);
	menu_agregar_opciones(menu,'j',avanzar_juego,ctx);

	menu_agregar_opciones(menu,'S',elegir_semilla,ctx);
	menu_agregar_opciones(menu,'s',elegir_semilla,ctx);

	menu_agregar_opciones(menu,'Q',cerrar_juego,ctx);
	menu_agregar_opciones(menu,'q',cerrar_juego,ctx);
}

char *setear_color(const char *color){
	if (strcmp(color,"ROJO") == 0){
		return ANSI_COLOR_RED;
	}
	else if (strcmp(color,"NEGRO") == 0){
		return ANSI_COLOR_BLACK;
	}
	else if (strcmp(color,"VERDE") == 0){
		return ANSI_COLOR_GREEN;
	}
	else if (strcmp(color,"AMARILLO") == 0){
		return ANSI_COLOR_YELLOW;
	}
	else if (strcmp(color,"AZUL") == 0){
		return ANSI_COLOR_BLUE;
	}
	else if (strcmp(color,"MAGENTA") == 0){
		return ANSI_COLOR_MAGENTA;
	}
	else if (strcmp(color,"CYAN") == 0){
		return ANSI_COLOR_CYAN;
	}
	else{
		return ANSI_COLOR_WHITE;
	}
}

void setear_atributos_pokemon(monstruos_t *poke, pokemon_t *pokemon_nuevo){
	poke->pokemon = pokemon_nuevo;
	poke->posicion = crear_fil_col_aleatorias();
	poke->caracter = pokemon_nuevo->nombre[0];
	poke->color = setear_color(pokemon_nuevo->color);
}

int main(int argc, const char *argv[])
{
	if (!son_argumentos_validos(argc, argv)) {
		return -1;
	}
	menu_t *menu = menu_crear();
	pokedex_t *pokedex = pokedex_crear(comparador);
	char entrada;
	int opcion = -1;
	int semilla = 0;
	void *ctx[] = {&opcion,&pokedex,&menu, &semilla};
	
	imprimir_inicio();	
	agregar_todas_opciones(menu,ctx);

	if(!pokedex_cargar_pokemones_desde_csv(pokedex,argv,',',4)){
		pokedex_destruir_todo(pokedex,liberar_pokemon);
		menu_destruir(menu);
		return -1;
	}	
	while (opcion == -1) {
		printf("\nIngrese la opcion que quiera ------------> ");
		if (scanf(" %c", &entrada) == 1) {
			if (!menu_ejecutar_entrada(menu, entrada,ctx)) {
                printf("\nERROR 405, por favor ingrese una opcion correcta");
            }
		}
	}	
	if (semilla == 0){
		srand ((unsigned int)time(NULL));
	}else{
		srand ((unsigned int)semilla);
	}	
	struct jugador jugador = { 0 };
	monstruos_t poke = {.cantidad = 0};
	pokemon_t *pokemon_nuevo = pokedex_devolver_pokemon_aleatorio(pokedex);
	setear_atributos_pokemon(&poke,pokemon_nuevo);




	juego_t juego = {.jugador = &jugador,.poke = &poke };




	game_loop(logica, &juego);

	mostrar_cursor();

	pokedex_destruir_todo(pokedex,liberar_pokemon);
	menu_destruir(menu);
	return 0;
}