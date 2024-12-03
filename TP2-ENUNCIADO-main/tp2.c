#include "extra/engine.h"
#include "extra/ansi.h"
#include <stdio.h>
#include "src/menu.h"
#include "src/pokedex.h"
#include <time.h>
#include "src/racha.h"

#define MAX_ANCHO 32
#define MAX_ALTO 15
#define CANT_INICIAL_POKE 7
#define UN_MINUTO 60
#define MOV_ARRIBA 'N'
#define MOV_ABAJO 'S'
#define MOV_DERECHO 'E'
#define MOV_IZQUIERDA 'O'
#define MOV_JUGADOR 'J'
#define MOV_JUGADOR_INVERTIDO 'I'
#define MOV_RANDOM 'R'

typedef struct coordenada {
	int x;
	int y;
} coordenada_t;

struct monstruo {
	coordenada_t posicion;
	char caracter;
	char *color;
	pokemon_t *pokemon;
	size_t indice_patron;
	int id;
};

struct jugador {
	coordenada_t posicion;
	int iteraciones;
	coordenada_t ultima_coordenada;
	int puntaje;
	int multiplicador;
};

typedef struct juego {
	struct jugador *jugador;
	int semilla;
	pokedex_t *pokedex_nueva;
	pokedex_t *pokedex_vieja;
	pokedex_t *pokedex_pokes_eliminados;
	racha_t *racha_actual;
	racha_t *racha_maxima;
	size_t max_racha;
	monstruos_t *pokemon_eliminado;
	monstruos_t *poke_aux;
	bool hay_poke_a_eliminar;
	int multiplicador_maximo;
} juego_t;

typedef struct tablero {
	char letra;
	char *color;
} tablero_t;

//post: devuelve un coordenada_t con una fila y una columna, generadas de forma aleatoria.
coordenada_t crear_fil_col_aleatorias()
{
	coordenada_t coordenada_aleatoria_i_j;
	coordenada_aleatoria_i_j.x = rand() % (MAX_ANCHO);
	coordenada_aleatoria_i_j.y = rand() % (MAX_ALTO);
	return coordenada_aleatoria_i_j;
}

// pre: Asumimos que los argumentos que le pasamos son validos (o sea le pasamos
// un archivo .csv y el ejecutable). post: Devuelve false en caso de que le
// pasemos menos de dos arguemntos, sino devolvemos true.
bool son_argumentos_validos(int argc, const char *argv[])
{
	if (argc < 2) {
		printf("Error, el archivo %s <archivo> No existe, paseme uno que sea valido",
		       argv[0]);
		return false;
	}
	return true;
}

//pre:	El elemento pasado debe ser valido.
//post:	Libera lo pedido para guardarnos el nombre, color y patron de los pokemones y libera el mismo pokemon.
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

//pre:	El elemento pasado debe ser valido.
//post:	Libera lo pdido para los mostruos.
void liberar_monstruos(void *elemento)
{
	monstruos_t *pokemon = elemento;
	if (pokemon != NULL) {
		free(pokemon);
	}
}

//pre:	Los argumentos pasado debe ser validos. Y al pasarle como argumentos, deben tener un campo nombre o un string.
//post:	En caso de que algun element sea NULL retorna 0, o -1. Y sino devolvemos segun lo que nos de de comparar los nombres de los pokemones.
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

//pre:	Los argumentos pasado debe ser validos. Y al pasarle como argumentos, deben tener un campo nombre o un string.
//post:	En caso de que algun element sea NULL retorna 0, o -1. Y sino, devolvemos segun cual sea mayor o menor id de los elementos pasados.
int comparador_monstruos(void *a, void *b)
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
	monstruos_t *poke_a = (monstruos_t *)a;
	monstruos_t *poke_b = (monstruos_t *)b;
	if (poke_a->id != poke_b->id) {
		return poke_a->id - poke_b->id;
	}
	if (poke_a->posicion.x !=
	    poke_b->posicion
		    .x) { //seria poco probable que ocurra pero por las dudas, comparamos depues por posicion
		return poke_a->posicion.x - poke_b->posicion.x;
	}
	return poke_a->posicion.y - poke_b->posicion.y;
}

//pre:	Los elementos pasados deben ser validos, y deberian tener un campo nombre, puntaje y color.
//post:	Imprimimos el nombre, puntaje o color del pokemon.
bool imprimir_pokemon(void *elemento, void *ctx)
{
	pokemon_t *poke = elemento;
	printf("Nombre: %s \t puntaje: %i \t color: %s\n", poke->nombre,
	       poke->puntaje, poke->color);
	return true;
}

//pre: Los elementos pasados deben ser validos, y deberian tener un campo nombre y color.
//post:	Imprime el color y el nombre del monstruo.
bool imprimir_pokemon2(void *elemento, void *ctx)
{
	monstruos_t *poke = elemento;
	printf("%s<--->%s<--->\n", poke->color, poke->pokemon->nombre);
	return true;
}

//pre:	el elemento no deberia ser NULL, al igual que el ctx.
//post:	Mete en la racha que se le pasa como ctx, el elemnto que le pasamos. Util para transladar informacion de una lista a otra.
bool iterar_y_agregar(void *elemento, void *ctx)
{
	racha_t *lista_destino = ctx;

	racha_agregar(lista_destino, elemento);

	return true;
}

//post: Imprime una pequeña intro para que el usuario sepa que comandos pasarle y como "reaccionan" al mismo.
void imprimir_inicio()
{
	printf(ANSI_COLOR_BLUE
	       "\t\t\t\t\t\t\t-----------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t|" ANSI_COLOR_GREEN ANSI_COLOR_BOLD
	       "    BIENVENIDO A POKEMON GO 2: AHORA ES PERSONAL" ANSI_COLOR_BLUE
	       "   |\n");
	printf(ANSI_COLOR_BLUE
	       "\t\t\t\t\t\t\t-----------------------------------------------------\n" ANSI_COLOR_RESET);
	printf("\n");

	printf(ANSI_COLOR_MAGENTA ANSI_COLOR_BOLD
	       "Hola jugador,bienvenido a " ANSI_COLOR_CYAN ANSI_COLOR_BOLD
	       "Pokemon go 2\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_GREEN ANSI_COLOR_BOLD
	       "El objetivo del juego es que atrapes pokemones, antes de que se acabe el tiempo.\n");
	printf("Lo ideal es que trapes a pokemones con el mismo color o que tengan la primera letra igual , asi obtendras un multiplicador al puntaje al capturarlos.\n");
	printf("Los pokemones se mueven a lo largo y ancho del tablero, cada uno con sus respectivos movimientos, pero no se mueven si no te moves.\n");
	printf("Por ultimo tenes 60 segundos de juego en total, una vez llegado a 0, finaliza el juego.\n");
	printf(ANSI_COLOR_RED ANSI_COLOR_BOLD
	       "A continuacion veras un menu en el cual podras elegir entre 4 opciones.\n");
	printf(ANSI_COLOR_RED
	       "Cabe aclarar que tambien se aceptan las minusculas\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_YELLOW ANSI_COLOR_BOLD
	       "Una vez sabida esta informacion, ya puedes empezar a jugar, suerte!\n" ANSI_COLOR_RESET);
	printf("\n");
	printf(ANSI_COLOR_RED
	       "=====================================================\n");
	printf("| " ANSI_COLOR_CYAN "[J]: Empezar Juego" ANSI_COLOR_RED
	       "                                |\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED
	       "| " ANSI_COLOR_CYAN
	       "[S]: Elegir una semilla para el juego" ANSI_COLOR_RED
	       "             |\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED
	       "| " ANSI_COLOR_CYAN
	       "[P]: Mostrar todos los pokemones en la pokedex" ANSI_COLOR_RED
	       "    |\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED
	       "| " ANSI_COLOR_CYAN "[Q]: Salir del juego" ANSI_COLOR_RED
	       "                              |\n" ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED
	       "=====================================================\n" ANSI_COLOR_RESET);
}

//pre:	El ctx debe ser valido.
//post:	Se setea la opcion para salir del while del main, y se ivoca a la funcion de pokedex_mostrar_ordenados.
void mostrar_pokedex(void *ctx[])
{
	printf("Aqui estan los pokemones que se ingresaron... \n");
	int *opcion = (int *)((void **)ctx)[0];
	pokedex_t *pokedex = *(pokedex_t **)ctx[1];
	pokedex_mostrar_ordenados(pokedex, imprimir_pokemon, NULL);
	*opcion = -1;
	return;
}

//pre:	El ctx debe ser valido.
//post:	Se setea la opcion para salir del while del main.
void avanzar_juego(void *ctx[])
{
	printf("Inicializando el juego... \n");
	int *opcion = (int *)((void **)ctx)[0];
	*opcion = 1;
}

//pre:	El ctx debe ser valido.
//post:	Se setea la semilla que el jugador ingreso.
void elegir_semilla(void *ctx[])
{
	printf("Ahora deberias ingresar una semilla (que sea un entero) --------->");
	int *semilla = (int *)((void **)ctx)[3];
	int entrada;
	if (scanf(" %i", &entrada) == 1) {
		*semilla = entrada;
	}
	return;
}

//pre:	El ctx debe ser valido.
//post:	Se libera lo pedido para la pokedex y se abandona el programa con exit().
void cerrar_juego(void *ctx[])
{
	printf("Saliendo del juego...\n");
	pokedex_t *pokedex = *(pokedex_t **)ctx[1];
	menu_t *menu = *(menu_t **)ctx[2];
	pokedex_destruir_todo(pokedex, liberar_pokemon);
	menu_destruir(menu);
	exit(0);
	return;
}

//pre:	Menu y ctx deben ser validos.
//post:	Agrega las opciones estandar y sus respectivas funciones al menu.
void agregar_todas_opciones(menu_t *menu, void *ctx[])
{
	menu_agregar_opciones(menu, 'P', mostrar_pokedex, ctx);
	menu_agregar_opciones(menu, 'p', mostrar_pokedex, ctx);

	menu_agregar_opciones(menu, 'J', avanzar_juego, ctx);
	menu_agregar_opciones(menu, 'j', avanzar_juego, ctx);

	menu_agregar_opciones(menu, 'S', elegir_semilla, ctx);
	menu_agregar_opciones(menu, 's', elegir_semilla, ctx);

	menu_agregar_opciones(menu, 'Q', cerrar_juego, ctx);
	menu_agregar_opciones(menu, 'q', cerrar_juego, ctx);
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

//pre:  recibe dos coordenadas_t, que son dos posiciones.
//post: retorna true si las filas y columnas de amobs puntos es la misma.
bool son_posiciones_iguales(coordenada_t posicion1, coordenada_t posicion2)
{
	return (posicion1.x == posicion2.x && posicion1.y == posicion2.y);
}

//pre:	El juego debe ser valido y debe tener sus campos inicializados.
//post:	Imprme informacion arriba del tablero.
void imprimir_cabezera(juego_t *juego)
{
	struct jugador *jugador = juego->jugador;
	printf("Utilizar " ANSI_COLOR_CYAN ANSI_COLOR_BOLD
	       "⬆⬇⬅➡" ANSI_COLOR_RESET " para moverse\n");
	printf("Presionar " ANSI_COLOR_RED ANSI_COLOR_BOLD "Q" ANSI_COLOR_RESET
	       " para salir\n");
	printf("Iteraciones:" ANSI_COLOR_BOLD ANSI_COLOR_CYAN
	       " %d" ANSI_COLOR_RESET
	       " Tiempo restante: " ANSI_COLOR_BOLD ANSI_COLOR_GREEN
	       "%d " ANSI_COLOR_RESET "Puntaje: " ANSI_COLOR_BOLD ANSI_COLOR_RED
	       "%i" ANSI_COLOR_RESET
	       " Multiplicador: " ANSI_COLOR_BOLD ANSI_COLOR_BLUE
	       "%i\n" ANSI_COLOR_RESET,
	       jugador->iteraciones, UN_MINUTO - jugador->iteraciones / 5,
	       jugador->puntaje, jugador->multiplicador);
}

//pre:	Las coordenadas que le pasamos deben estar inicializadas.
//post:	limita el moimiento de las coordenadas q el pasamos para que los pokemones y el jugador no se salgan del tablero.
void limitar_movimiento(coordenada_t *posicion)
{
	posicion->x = min(MAX_ANCHO - 1, max(0, posicion->x));
	posicion->y = min(MAX_ALTO - 1, max(0, posicion->y));
}

//pre:	El color pasado deben ser validos.
//post:	Devuelve un string que vendria a ser el color que se supone que debe tener.
char *setear_color(const char *color)
{
	if (strcmp(color, "ROJO") == 0) {
		return ANSI_COLOR_RED;
	} else if (strcmp(color, "NEGRO") == 0) {
		return ANSI_COLOR_BLACK;
	} else if (strcmp(color, "VERDE") == 0) {
		return ANSI_COLOR_GREEN;
	} else if (strcmp(color, "AMARILLO") == 0) {
		return ANSI_COLOR_YELLOW;
	} else if (strcmp(color, "AZUL") == 0) {
		return ANSI_COLOR_BLUE;
	} else if (strcmp(color, "MAGENTA") == 0) {
		return ANSI_COLOR_MAGENTA;
	} else if (strcmp(color, "CYAN") == 0) {
		return ANSI_COLOR_CYAN;
	} else {
		return ANSI_COLOR_WHITE;
	}
}

//pre:	el monstruo y el pokemon, deben haverse inicializado y deben ser validos.
//post:	setea los distintos campos del monstruo, con algunos datos del pokemon leido del csv, y otros cargados manualmente.
void setear_atributos_pokemon(monstruos_t *poke, pokemon_t *pokemon_nuevo)
{
	poke->pokemon = pokemon_nuevo;
	poke->posicion = crear_fil_col_aleatorias();
	poke->id = rand();
	poke->caracter = pokemon_nuevo->nombre[0];
	poke->color = setear_color(pokemon_nuevo->color);
	poke->pokemon->patron_movimientos = pokemon_nuevo->patron_movimientos;
	poke->indice_patron = 0;
	poke->pokemon->puntaje = pokemon_nuevo->puntaje;
}

//pre:	El monstruo, el jugador y la letra deben ser validos e inicializados. Ademas se debe haber inicializado una semilla en el main para que rand devuelva aleatoriamente un numero.
//post:	Dependiendo de la letra que le pasemos, el monstruo se mueve arriba,abajo, derecha, izquierda, el mismo movimiento que hizo el jugador, el movimiento inverso que hizo el jugador o un movimiento random dependiendo que devuelve rand.
void accionar_patron(monstruos_t *poke, struct jugador *jugador, char letra)
{
	int direccion_random = rand() % 4;
	switch (letra) {
	case MOV_ARRIBA:
		poke->posicion.y -= 1;
		break;
	case MOV_ABAJO:
		poke->posicion.y += 1;
		break;
	case MOV_DERECHO:
		poke->posicion.x += 1;
		break;
	case MOV_IZQUIERDA:
		poke->posicion.x -= 1;
		break;
	case MOV_JUGADOR_INVERTIDO:
		poke->posicion.x -= jugador->ultima_coordenada.x;
		poke->posicion.y -= jugador->ultima_coordenada.y;
		break;
	case MOV_JUGADOR:
		poke->posicion.x += jugador->ultima_coordenada.x;
		poke->posicion.y += jugador->ultima_coordenada.y;
		break;
	case MOV_RANDOM:
		if (direccion_random == 0) {
			poke->posicion.y -= 1;
		} else if (direccion_random == 1) {
			poke->posicion.y += 1;
		} else if (direccion_random == 2) {
			poke->posicion.x += 1;
		} else {
			poke->posicion.x -= 1;
		}
		break;
	default:
		break;
	}
}

//pre:	Juego y el mosntruo deben ser validos y deben estar inicializados. Ademas debe tener un patron de movimientos valido, de lo contrario no se ejecutaria ningun movimiento.
//post: Vamos pasando letra a letra del patron del movimeintos que tiene el pokemon y se va avanzando con el contador de letra para porcesar la siguiente. SI se llegara a una letra previa del final (porque creo que cuenta el \n del csv), se setea el contador de la letra del pokemon a 0 asi se repite el ciclo.
void aplicar_patron_movimiento(juego_t *juego, monstruos_t *poke)
{
	size_t letra_a_ejecutar = poke->indice_patron;
	size_t longitud_patron = strlen(poke->pokemon->patron_movimientos);
	poke->indice_patron++;
	accionar_patron(poke, juego->jugador,
			poke->pokemon->patron_movimientos[letra_a_ejecutar]);
	if (poke->indice_patron >= longitud_patron - 1) {
		poke->indice_patron = 0;
	}
}

//pre:	El pokemon y el ctx deben ser validos.
//post:	Se le aplica el patron de movimientos a cada pokemon de la pokedex. Util para usar con iterar_pokedex.
bool aplicar_patron_a_pokemon(void *pokemon_void, void *ctx)
{
	monstruos_t *poke = (monstruos_t *)pokemon_void;
	juego_t *juego = (juego_t *)ctx;
	if (poke->pokemon->patron_movimientos != NULL) {
		aplicar_patron_movimiento(juego, poke);
	}
	return true;
}

//pre:	La entrada deberia ser valida y el juego tambien y sus campos deben estar inicializados.
//post:	Ejecuta el movimiento del jugador segun la entrada y mueve a los pokemones iterando en al pokedex.
void procesar_entrada(int entrada, juego_t *juego)
{
	struct jugador *jugador = juego->jugador;
	jugador->ultima_coordenada.x = 0;
	jugador->ultima_coordenada.y = 0;
	if (entrada == TECLA_DERECHA) {
		jugador->posicion.x++;
		jugador->ultima_coordenada.x = 1;
		pokedex_iterar(juego->pokedex_nueva, aplicar_patron_a_pokemon,
			       juego);
	} else if (entrada == TECLA_IZQUIERDA) {
		jugador->posicion.x--;
		jugador->ultima_coordenada.x = -1;
		pokedex_iterar(juego->pokedex_nueva, aplicar_patron_a_pokemon,
			       juego);
	} else if (entrada == TECLA_ARRIBA) {
		jugador->posicion.y--;
		jugador->ultima_coordenada.y = -1;
		pokedex_iterar(juego->pokedex_nueva, aplicar_patron_a_pokemon,
			       juego);
	} else if (entrada == TECLA_ABAJO) {
		jugador->posicion.y++;
		jugador->ultima_coordenada.y = 1;
		pokedex_iterar(juego->pokedex_nueva, aplicar_patron_a_pokemon,
			       juego);
	}
}

//pre:	El pokemon y el terreno deben ser validos. Ademas se deberian tener los campos de posicion de los monstruos inicializados y dentro del tamaño que tiene el terreno.
//post:	Dibuja en el terreno, al pokemon en cuestion.
bool imprimir_pokemon_en_terreno(void *pokemon_void, void *terreno)
{
	monstruos_t *pokemon = (monstruos_t *)pokemon_void;
	tablero_t(*tablero)[MAX_ALTO][MAX_ANCHO] =
		(tablero_t(*)[MAX_ALTO][MAX_ANCHO])terreno;

	tablero_t pokemon_tablero = { .letra = pokemon->caracter,
				      .color = pokemon->color };

	limitar_movimiento(&pokemon->posicion);

	(*tablero)[pokemon->posicion.y][pokemon->posicion.x] = pokemon_tablero;

	return true;
}

//pre:	El terreno deberia estar ya inicializado.
//post:	Imprme los caracteres (juento con sus colores) de los monstruos y el jugador. Si no hay nada en la posicion, imprime un puntito.
void imprimir_terreno(tablero_t terreno[MAX_ALTO][MAX_ANCHO])
{
	for (int y = 0; y < MAX_ALTO; y++) {
		for (int x = 0; x < MAX_ANCHO; x++) {
			tablero_t elemento_tablero = terreno[y][x];
			if (elemento_tablero.letra != 0) {
				printf("%s%c" ANSI_COLOR_RESET,
				       elemento_tablero.color,
				       elemento_tablero.letra);
			} else {
				printf(".");
			}
		}
		printf("\n");
	}
}

//pre:	Ambas pokedex, deben haber sido creadas, ademas de no ser NULL.
//post:	Pedimos memoria para el monstruo, seteamos sus campos y lo agregamos a la pokedex que contiene a los monstruos.
void crear_setear_monstruo(pokedex_t *pokedex, pokedex_t *nueva_pokedex)
{
	pokemon_t *pokemon_nuevo = pokedex_devolver_pokemon_aleatorio(pokedex);
	if (!pokemon_nuevo) {
		return;
	}
	monstruos_t *poke_nuevo = calloc(1, sizeof(monstruos_t));
	if (!poke_nuevo) {
		return;
	}
	setear_atributos_pokemon(poke_nuevo, pokemon_nuevo);
	if (!pokedex_agregar_pokemon(nueva_pokedex, poke_nuevo)) {
		free(poke_nuevo);
		return;
	}
}

//pre:	Poke y poke_eliminado deben estar inicializados.
//post:	Si se cumplen las condiciones para aumentar el mutiplicador, se devuelve true, caso contrario devuelve false.
bool se_aumenta_multiplicador(monstruos_t *poke, monstruos_t *poke_eliminado)
{
	if (!poke_eliminado) {
		return false;
	}
	return (poke->caracter == poke_eliminado->caracter ||
		(strcmp(poke->color, poke_eliminado->color) == 0));
}

//pre:	juego y sus campos deben estar inicializados.
//post:	Se aumenta el mutiplicador y si ocurre, tambien el mutiplicador maximo.
void actualizar_multiplicador(juego_t *juego)
{
	juego->jugador->multiplicador++;
	if (juego->jugador->multiplicador > juego->multiplicador_maximo) {
		juego->multiplicador_maximo = juego->jugador->multiplicador;
	}
}

//pre:	juego y sus campos deben estar inicializados.
//post:	Verificamos si la cantidad de elementos en racha es mayor al numero de la racha maxima registrada. Si es asi, vaciamos la racha maxima y
//	copiamos los elemntos de la racha actual en la racha maxima.
void actualizar_racha_maxima(juego_t *juego)
{
	size_t numero_racha = racha_cantidad_combos(juego->racha_actual);
	if (numero_racha > juego->max_racha) {
		juego->max_racha = numero_racha;
		if (juego->racha_maxima) {
			racha_vaciar(juego->racha_maxima);
		}
		racha_iterar(juego->racha_actual, iterar_y_agregar,
			     juego->racha_maxima);
	}
}

//pre:	juego y poke deben ser validos e inicializados.
//post:	Si el pokemon al que capturamos cumple con mismo color o primera letra igual al ultimo pokemon en ser atrapado, se actualiza el mutiplicador del jugador,
//	y se agrega a la racha el pokemon que acabamos de atrapar. Caso donde se rompe la racha, se actualiza la racha maxima (si es necesario), se vacia la racha actual
//	y el mutiplicador se resetea a 1.
void actualizar_multiplicador_y_racha(juego_t *juego, monstruos_t *poke)
{
	if (se_aumenta_multiplicador(poke, juego->pokemon_eliminado)) {
		actualizar_multiplicador(juego);
		racha_agregar(juego->racha_actual, poke);
	} else {
		actualizar_racha_maxima(juego);
		racha_vaciar(juego->racha_actual);
		juego->jugador->multiplicador = 1;
	}
}

//pre:	El pokemon y ctx deben ser validos.
//post:	Si el pokemon y el jugador tiene la misma posicion, se actualiza el multiplicador, se guarda el pokemon para ser eliminado y se devuelve true.
bool capturar_pokemon(void *pokemon_void, void *ctx)
{
	monstruos_t *poke = pokemon_void;
	juego_t *juego = ctx;

	if (son_posiciones_iguales(juego->jugador->posicion, poke->posicion)) {
		actualizar_multiplicador_y_racha(juego, poke);
		juego->poke_aux = poke;
		juego->hay_poke_a_eliminar = true;
		return false;
	}
	return true;
}

//pre:	Juego debe estar inicializado y debe ser valido.
//post:	Imprime un pie con la informacion del ultimo pokemon capturado.
void imprimir_pie(juego_t *juego)
{
	if (juego->pokemon_eliminado == NULL) {
		printf("No has captudaro a ningun pokemon aun\n");
	} else {
		printf("Ultimo pokemon capturado: %s%s\n" ANSI_COLOR_RESET,
		       juego->pokemon_eliminado->color,
		       juego->pokemon_eliminado->pokemon->nombre);
	}
}

//pre:	Juego debe eser valido y debe estar inicializado.
//post:	si hay algun pokemon que debe ser eliminado, y si se pudo eliminar, se suma el puntaje dl mismo al jugador, se agrega un nuevo mosntruo al tablero y se guarda en
// un arbol el pokemon eliminado para liberarlo al final del programa sin que haya invalids reads o memory leaks.
void eliminar_y_agregar_pokemon(juego_t *juego)
{
	if (juego->hay_poke_a_eliminar) {
		if (pokedex_eliminar_pokemon(
			    juego->pokedex_nueva, juego->poke_aux,
			    (void *)&juego->pokemon_eliminado)) {
			juego->jugador->puntaje +=
				(juego->pokemon_eliminado->pokemon->puntaje *
				 juego->jugador->multiplicador);
			pokedex_agregar_pokemon(juego->pokedex_pokes_eliminados,
						juego->pokemon_eliminado);
			crear_setear_monstruo(juego->pokedex_vieja,
					      juego->pokedex_nueva);
		}
	}
}

int logica(int entrada, void *datos)
{
	juego_t *juego = datos;
	struct jugador *jugador = juego->jugador;
	juego->hay_poke_a_eliminar = false;
	tablero_t terreno[MAX_ALTO][MAX_ANCHO];
	memset(terreno, 0, sizeof(terreno));

	borrar_pantalla();

	procesar_entrada(entrada, juego);

	limitar_movimiento(&jugador->posicion);

	pokedex_iterar(juego->pokedex_nueva, capturar_pokemon, juego);

	eliminar_y_agregar_pokemon(juego);

	jugador->iteraciones++;
	imprimir_cabezera(juego);

	tablero_t jugador_tablero = { .letra = '@',
				      .color = ANSI_COLOR_BOLD ANSI_COLOR_RED };

	pokedex_iterar(juego->pokedex_nueva, imprimir_pokemon_en_terreno,
		       terreno);

	terreno[jugador->posicion.y][jugador->posicion.x] = jugador_tablero;

	imprimir_terreno(terreno);

	if (jugador->iteraciones / 5 == UN_MINUTO) {
		entrada = 'q';
	}

	printf("\n");

	imprimir_pie(juego);

	esconder_cursor();

	return entrada == 'q' || entrada == 'Q';
}

//pre:	A prior el restraso deberia estar inicializado. (auque no es estrictamente necesario)
//post:	Hace un for con el uso del tipo volatile (que le dice al compilador que no optimice los for asi tarda mas en hacerlo y da la sensacion de un delay) y seteamos a 0 el retraso para poder reutilizarlo despues.
void aplciar_delay(volatile long *retraso)
{
	for (long i = 0; i < 99999999; i++) {
		(*retraso)++;
	}
	*retraso = 0;
}

//pre:	Promedio debe estar inicializado.
//post:	Imprme segun el pormedio que te de, un mensaje con la calificacion q obtuviste
void porcesar_calificacion(int promedio)
{
	if (promedio <= 10) {
		printf("Obtuviste una " ANSI_COLOR_BOLD ANSI_COLOR_RED
		       "F" ANSI_COLOR_RESET ANSI_COLOR_GREEN
		       ", te falta mucho para ser un maestro pokemon,debes practicar mucho\n");
	} else if (promedio > 10 && promedio <= 50) {
		printf("Obtuviste una " ANSI_COLOR_BOLD ANSI_COLOR_RED
		       "E" ANSI_COLOR_RESET ANSI_COLOR_GREEN
		       ", Nada mal, pero debes practicar mas para ser un maestro pokemon\n");
	} else if (promedio > 50 && promedio <= 100) {
		printf("Obtuviste una " ANSI_COLOR_BOLD ANSI_COLOR_RED
		       "D" ANSI_COLOR_RESET ANSI_COLOR_GREEN
		       ", Bien es un buen inicio para ser un maestro pokemon aunque aun te falta practica, sigue practicando\n");
	} else if (promedio > 100 && promedio <= 250) {
		printf("Obtuviste una " ANSI_COLOR_BOLD ANSI_COLOR_RED
		       "C" ANSI_COLOR_RESET ANSI_COLOR_GREEN
		       ", Muy Bien, ¿Estuviste practicando mas, no?, sigue asi y algun dia podras ser un maestro pokemon\n");
	} else if (promedio > 250 && promedio <= 500) {
		printf("Obtuviste una " ANSI_COLOR_BOLD ANSI_COLOR_RED
		       "B" ANSI_COLOR_RESET ANSI_COLOR_GREEN
		       ", Excelente, estas muy cerca de poder comvertirte en un maestro pokemon, ya podrias inentra ir a tu primer gimnasio\n");
	} else if (promedio >= 1000) {
		printf("Obtuviste una " ANSI_COLOR_BOLD ANSI_COLOR_RED
		       "A" ANSI_COLOR_RESET ANSI_COLOR_GREEN
		       ", ¡Sorprendente! ,practicamente estas listo para ser un maestro poekmon, tu primer gimnasio sera facil para vos\n");
	}
}

//pre:	juego deberia estar inicializado y se deberian haber modificado su campos durante la ejecuccion del programa.
//post:	Imprime varias estadisticas de la partida.
void mostrar_outro(juego_t juego)
{
	printf(ANSI_COLOR_GREEN
	       "Bueno se acabo el tiempo, veamos tus estadisticas...\n" ANSI_COLOR_RESET);
	volatile long retraso =
		0; //tengo entendido que es C99, pero queria como meter un delay para simular una carga de datos, quedo bien igual. Aunque es posible q time.h tenga algun delay mejor del que hice yo.
	aplciar_delay(&retraso);

	printf(ANSI_COLOR_BOLD ANSI_COLOR_BLUE
	       "Tu puntaje fue de: " ANSI_COLOR_RED ANSI_COLOR_BOLD "%i\n",
	       juego.jugador->puntaje);

	aplciar_delay(&retraso);

	printf(ANSI_COLOR_BLUE
	       "Tu multiplicador maximo fue de: " ANSI_COLOR_RED ANSI_COLOR_BOLD
	       "%i\n",
	       juego.multiplicador_maximo);

	aplciar_delay(&retraso);

	printf(ANSI_COLOR_BLUE
	       "Tu combo mas largo (sin contar al primero que capturaste de la racha) fue: " ANSI_COLOR_RED ANSI_COLOR_BOLD
	       "\n" ANSI_COLOR_RESET);
	size_t combo_mas_largo = 0;
	if (juego.racha_maxima &&
	    racha_cantidad_combos(juego.racha_maxima) >
		    racha_cantidad_combos(juego.racha_actual)) {
		combo_mas_largo = racha_iterar(juego.racha_maxima,
					       imprimir_pokemon2, NULL);
	} else {
		combo_mas_largo = racha_iterar(juego.racha_actual,
					       imprimir_pokemon2, NULL);
	}
	if (combo_mas_largo == 0) {
		printf(ANSI_COLOR_MAGENTA
		       "Que paso? no capturaste pokemones del mismo color o con misma inicial consecutivamente\n");
	}

	printf(ANSI_COLOR_CYAN
	       "Ahora veamos tu calificacion...\n" ANSI_COLOR_GREEN);
	int promedio = ((int)combo_mas_largo + juego.jugador->puntaje +
			juego.multiplicador_maximo) /
		       3;

	aplciar_delay(&retraso);

	porcesar_calificacion(promedio);
	printf(ANSI_COLOR_YELLOW
	       "Espero que el juego hay funcionado correctamente y que quieras volver a jugar :D\n" ANSI_COLOR_RESET);
}

//pre:	Los parametros deberian estar inicializados, auqnue tambien funciona si alguno es NULL.
//post:	Va liberando uno a uno las estructuras usadas del main.
void liberar_estructuras(menu_t *menu, pokedex_t *pokedex,
			 pokedex_t *nueva_pokedex,
			 pokedex_t *pokedex_pokes_eliminados,
			 racha_t *racha_max, racha_t *racha_actual)
{
	if (racha_actual) {
		racha_destruir_todo(racha_actual, NULL);
	}
	if (racha_max) {
		racha_destruir_todo(racha_max, NULL);
	}
	if (pokedex_pokes_eliminados) {
		pokedex_destruir_todo(pokedex_pokes_eliminados,
				      liberar_monstruos);
	}
	if (nueva_pokedex) {
		pokedex_destruir_todo(nueva_pokedex, liberar_monstruos);
	}
	if (pokedex) {
		pokedex_destruir_todo(pokedex, liberar_pokemon);
	}
	if (menu) {
		menu_destruir(menu);
	}
}

int main(int argc, const char *argv[])
{
	if (!son_argumentos_validos(argc, argv)) {
		return -1;
	}
	borrar_pantalla();
	menu_t *menu = menu_crear();
	if (!menu) {
		return -1;
	}
	pokedex_t *pokedex = pokedex_crear(comparador);
	if (!pokedex) {
		menu_destruir(menu);
		return -1;
	}
	char entrada;
	int opcion = -1;
	int semilla = 0;
	void *ctx[] = { &opcion, &pokedex, &menu, &semilla };

	imprimir_inicio();
	agregar_todas_opciones(menu, ctx);

	if (!pokedex_cargar_pokemones_desde_csv(pokedex, argv, ',', 4)) {
		liberar_estructuras(menu, pokedex, NULL, NULL, NULL, NULL);
		return -1;
	}

	while (opcion == -1) {
		printf("\nIngrese la opcion que quiera ------------> ");
		if (scanf(" %c", &entrada) == 1) {
			if (!menu_ejecutar_entrada(menu, entrada, ctx)) {
				printf("\nERROR 405, por favor ingrese una opcion correcta");
			}
		}
	}
	if (semilla == 0) {
		srand((unsigned int)time(NULL));
	} else {
		srand((unsigned int)semilla);
	}
	struct jugador jugador = { 0 };
	jugador.multiplicador = 1;

	pokedex_t *nueva_pokedex = pokedex_crear(comparador_monstruos);
	if (!nueva_pokedex) {
		liberar_estructuras(menu, pokedex, NULL, NULL, NULL, NULL);
	}
	pokedex_t *pokedex_pokes_eliminados =
		pokedex_crear(comparador_monstruos);
	if (!pokedex_pokes_eliminados) {
		liberar_estructuras(menu, pokedex, nueva_pokedex, NULL, NULL,
				    NULL);
	}
	racha_t *racha_max = racha_crear();
	if (!racha_max) {
		liberar_estructuras(menu, pokedex, nueva_pokedex,
				    pokedex_pokes_eliminados, NULL, NULL);
	}
	racha_t *racha_actual = racha_crear();
	if (!racha_actual) {
		liberar_estructuras(menu, pokedex, nueva_pokedex,
				    pokedex_pokes_eliminados, racha_max, NULL);
	}

	juego_t juego = { .jugador = &jugador,
			  .pokedex_nueva = nueva_pokedex,
			  .pokedex_vieja = pokedex,
			  .pokemon_eliminado = NULL,
			  .multiplicador_maximo = 1,
			  .pokedex_pokes_eliminados = pokedex_pokes_eliminados,
			  .semilla = semilla,
			  .poke_aux = NULL,
			  .max_racha = 0,
			  .racha_maxima = racha_max,
			  .racha_actual = racha_actual };
	for (size_t i = 0; i < CANT_INICIAL_POKE; i++) {
		crear_setear_monstruo(pokedex, nueva_pokedex);
	}

	game_loop(logica, &juego);

	mostrar_cursor();

	borrar_pantalla();

	mostrar_outro(juego);

	liberar_estructuras(menu, pokedex, nueva_pokedex,
			    pokedex_pokes_eliminados, racha_max, racha_actual);
	return 0;
}