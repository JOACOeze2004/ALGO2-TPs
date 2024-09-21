#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "src/lista.h"
#include "src/csv.h"

#define TIPO_AGUA 'A'
#define TIPO_FUEGO 'F'
#define TIPO_PLANTA 'P'
#define TIPO_ROCA 'R'
#define TIPO_ELECTRICO 'E'
#define TIPO_NORMAL 'N'
#define TIPO_LUCHA 'L'
#define BUSCAR "buscar"
#define LISTAR "listar"
#define OPCION_LISTAR 1
#define OPCION_BUSCAR 0

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};

int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = _p1;
	struct pokemon *p2 = _p2;

	return strcmp(p1->nombre, p2->nombre);
}

bool castear_a_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

bool castear_a_char(const char *str, void *ctx)
{
	*(char *)ctx = *(char *)str;
	return true;
}

//pre: Asumimos que los argumentos que le pasamos son validos (poque se los pasamos nosotros al ejecutar el programa).
//post: Devuelve false en caso de que le pasemos menos de dos arguemntos, sino devolvemos true.
bool son_argumentos_validos(int argc, const char *argv[])
{
	if (argc < 2) {
		printf("Error, el archivo %s<archivo> No existe, paseme uno que sea valido",
		       argv[0]);
		return false;
	}
	return true;
}

//pre:	El nombre pasado debe ser valido al igual que el pokemon.
//post:	Reserva memoria para el nombre del pokemon a guardar y copia el nombre que le pasemos al campo nombre del pokemon.
void reservar_copiar_nombre_pokemon(struct pokemon *pokemon, char *nombre)
{
	pokemon->nombre = malloc(strlen(nombre) + 1);
	if (pokemon->nombre != NULL) {
		strcpy(pokemon->nombre, nombre);
	}
}

//pre:	Asumimos que el struct pokemon y los demas argumentos pasados fueron inicalizados y/o casteados correctamente.
//post:	Seteamos los campos del pokemon con lo que fuismo casteando del archivo csv.
void setear_pokemon(struct pokemon *pokemon, char *nombre, char tipo,
		    int fuerza, int destreza, int resistencia)
{
	reservar_copiar_nombre_pokemon(pokemon, nombre);
	pokemon->tipo = tipo;
	pokemon->fuerza = fuerza;
	pokemon->destreza = destreza;
	pokemon->resistencia = resistencia;
}

//pre:	Asumimos que el puntero al struct pokemones  no es NULL, y que los campos e cada pokemon fuern completados exitosamente.
//post:	Devolvemos true si pudimos pudimos imprimir cada campo correctamente.
bool imprimir_pokemon(void *elemento, void *ctx)
{
	struct pokemon *poke = elemento;
	printf("Nombre: %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
	       poke->nombre, poke->tipo, poke->fuerza, poke->destreza,
	       poke->resistencia);
	return true;
}

//pre:	Asumimos que le pasamos un tipo de pokemon valido, y que se inicializo correctamente el vector de contador_tipos.
//post:	Le aumentamos en uno al contador dependiendo del tipo que sea el pokemon, llendo del 0 al 7 ( tipo agua = 0, fuego = 1, planta = 2, roca = 3, electrico = 4, normal = 5, lucha = 6)
void actualizar_contadores(char tipo, size_t *contador_tipos)
{
	switch (tipo) {
	case TIPO_AGUA:
		contador_tipos[0]++;
		break;
	case TIPO_FUEGO:
		contador_tipos[1]++;
		break;
	case TIPO_PLANTA:
		contador_tipos[2]++;
		break;
	case TIPO_ROCA:
		contador_tipos[3]++;
		break;
	case TIPO_ELECTRICO:
		contador_tipos[4]++;
		break;
	case TIPO_NORMAL:
		contador_tipos[5]++;
		break;
	case TIPO_LUCHA:
		contador_tipos[6]++;
		break;
	}
}

//pre:	El puntero al struct pokedex, deberia ser valido, ademas de que debe funcionar correctamente la funcion de pokedex_cantidad_pokemones.
//post:	sacamos la cantidad total de pokemones en la pokedex.
void impirmir_cantidad_total_pokemones(Lista *lista)
{
	printf("Total de pokémones en la Pokédex: %zu\n",
	       lista_cantidad_elementos(lista));
}

//pre:	El vector de contadores debe estar inicializado y deberia haberse aumentado con la funcion de aumentar_contadores.
//post:	Imprimimos las cantidades de cada tipo de los pokemones en la pokedex.
void imprimir_cant_tipos_pokemones(size_t *contador_tipos)
{
	printf("\nCantidad de Pokemones de cada tipo:\n");
	printf("Tipo Agua: %zu\n", contador_tipos[0]);
	printf("Tipo Fuego: %zu\n", contador_tipos[1]);
	printf("Tipo Planta: %zu\n", contador_tipos[2]);
	printf("Tipo Roca: %zu\n", contador_tipos[3]);
	printf("Tipo Eléctrico: %zu\n", contador_tipos[4]);
	printf("Tipo Normal: %zu\n", contador_tipos[5]);
	printf("Tipo Lucha: %zu\n", contador_tipos[6]);
}

//pre:	El puntero a lista y el vector de contador no son NULL.
//post:	Imrpimimos los resultados obtenidos de los contadores. Ayudandonos de la funcion de iterar que venia en el .h.
void imprimir_resultados(Lista *lista, size_t *contador_tipos)
{
	printf("\n");
	printf("Pokémones en la Pokédex:\n");
	lista_iterar_elementos(lista, imprimir_pokemon, NULL);
	printf("\n");
	impirmir_cantidad_total_pokemones(lista);

	imprimir_cant_tipos_pokemones(contador_tipos);
	printf("\n");
}

//post: Imprime una pequeña intro para que el usuario sepa que comandos pasarle y como "reaccionan" al mismo.
void imprimir_inicio_pokedex()
{
	printf("\n");
	printf("Bienvenido Ash, aqui estan todos los pokemones que cargaste, las estadisticas de los mismos y la cantidad que hay de cada tipo.\n");
	printf("En esta version 1.2 de la pokedex, tienes dos opciones de momento, o buscar un pokemon de los que ingresaste o mostrarte todos los pokemones que haya\n");
	printf("Entonces, si desea buscar un pokemon, debe insertar la palabra 'buscar, para listar los pokemones que haya en la pokedex con sus estadisticas \nponga la palabra 'listar'");
}

//pre:	La entrada deberia ser un string valido.
//post:	Si la entrada es listar, devolvemos la opcion como un 1, si es buscar devolvemos la opcion como un 0 para luego procesarla.
int porcesar_entrada(char *entrada, int opcion)
{
	if (strcmp(entrada, LISTAR) == 0) {
		opcion = OPCION_LISTAR;
	} else if ((strcmp(entrada, BUSCAR)) == 0) {
		opcion = OPCION_BUSCAR;
	} else {
		printf("\nERROR 405, por favor ingrese una opcion correcta");
	}
	return opcion;
}

//post:	Tenemos un while que mientras la entrada no sea la esperada (listar o buscar) persiste en que le des una entrada valida. Y retornamos la opcion que el usuario eligio (0 es buscar y 1 es listar).
int definir_opcion()
{
	char entrada[20];
	int opcion = -1;
	while (opcion == -1) {
		printf("\nIngrese la opcion que quiera ------------> ");
		if (scanf("%s", entrada) == 1) {
			opcion = porcesar_entrada(entrada, opcion);
		}
	}
	return opcion;
}

//post:	Imprime un pequeño manual de como usar el buscador de la pokedex para el usuario.
void imprimir_manual_busqueda()
{
	printf("\n");
	printf("Bien has elegido buscar, explicacion breve de lo que deberias entar\n");
	printf("Ahora tiene que meter el nombre del pokemon a buscar y yo te devuelvo el pokemon y sus estats, como estandar, los nombres empeizan en mayuscula, pero depende de como hayas cargado los pokemones\n");
	printf("Por ejemplo proba buscando a Pikachu asi como lo escribi, luego proba con el que quieras ");
	printf("bien, ahora puedes usar el buscador de pokemones\n");
}

//pre:	La lista debe haberse inicializado con algun pokemon, sino no encontrariamos nunca nada.
//post:	Le pedimos un nombre al usuario y nos guardamos el nombre del pokemon en un struct pokemon auxiliar, le pasamos el buscado a la funcion de busar en la lista, si lo encuentra, devuelve el struct sino devuleve null.
struct pokemon *buscar_pokemon_deseado(Lista *lista)
{
	char entrada[20];
	printf("\nIngrese el nombre del pokemon a buscar -------------> ");
	if (scanf("%s", entrada) != 1) {
		printf("Hubo un error con la entrada.\n");
	}
	struct pokemon buscado;
	buscado.nombre = entrada;
	struct pokemon *resultado =
		lista_buscar_elemento(lista, &buscado, comparar_nombre_pokemon);
	if (resultado != NULL) {
		return resultado;
	} else {
		return NULL;
	}
}

//pre:	La lista debe tener algun pokemon, sino no encontrariamos nunca nada.
//post:	Imprimimos lo que haya en la pokedex sobre ese pokemon que encontramos(nombre, tipo, stast,etc) pero si no lo encontramos, imprimimos algo para avisarle al usuario que no se encontro.
void procesar_pokemon_buscado(Lista *pokedex, void *ctx)
{
	void *resultado = buscar_pokemon_deseado(pokedex);
	if (resultado != NULL) {
		printf("El pokemon que buscabas es:\n");
		imprimir_pokemon(resultado, ctx);
	} else {
		printf("\nEl pokemon que buscabas no ha sido encontrado en la pokedex :C\n");
	}
}

//pre:	La lista, el contador y el ctx debn ser validos.
//post:	Segun la entrada del usuario, definimso que hacemos, si es 0, llamamos a las funciones que se encarguen de buscar al pokemon, si la opcion fue 1, imprimimos los resultados que obtubimos de porcesar el archivo.
void ejecutar_opciones(Lista *pokedex, size_t *contador_tipos, void *ctx)
{
	int opcion = definir_opcion();
	if (opcion == OPCION_LISTAR) {
		imprimir_resultados(pokedex, contador_tipos);
	} else if (opcion == OPCION_BUSCAR) {
		imprimir_manual_busqueda();
		procesar_pokemon_buscado(pokedex, ctx);
		printf("\n");
	}
}

//pre:	El elemento debe ser valido (no NULL).
//post:	Si el pokemon o elemento no son NULL, y si el nombre del mismo no fuera NULL, libera primero el espacio pedio para el nombre del pokemon, y luego liberamos al epsacio pedido para almacenar al pokemon/elemento.
void liberar_pokemon(void *elemento)
{
	struct pokemon *pokemon = elemento;
	if (pokemon != NULL) {
		if (pokemon->nombre != NULL) {
			free(pokemon->nombre);
		}
		free(pokemon);
	}
}

int main(int argc, const char *argv[])
{
	if (!son_argumentos_validos(argc, argv)) {
		return -1;
	}
	Lista *pokedex = lista_crear();
	struct archivo_csv *archivo = abrir_archivo_csv(argv[1], ';');
	size_t contador_tipos[7] = { 0, 0, 0, 0, 0, 0, 0 };
	size_t columnas = 5;
	char *nombre_pokemon = NULL;
	char tipo;
	int fuerza, destreza, resistencia;
	bool (*funciones[])(const char *,
			    void *) = { crear_string_nuevo, castear_a_char,
					castear_a_int, castear_a_int,
					castear_a_int };
	void *ctx[] = { &nombre_pokemon, &tipo, &fuerza, &destreza,
			&resistencia };
	while (leer_linea_csv(archivo, columnas, funciones, ctx) == 5) {
		struct pokemon *nuevo_pokemon = malloc(sizeof(struct pokemon));
		setear_pokemon(nuevo_pokemon, nombre_pokemon, tipo, fuerza,
			       destreza, resistencia);
		if (!lista_agregar_al_final(pokedex, nuevo_pokemon)) {
			printf("\nError al agregar al Pokémon %s a la Pokédex, es posible que hayas metido un nombre vacio, un tipo invalido o una estadistica negativa.\n ",
			       nuevo_pokemon->nombre);
		} else {
			actualizar_contadores(nuevo_pokemon->tipo,
					      contador_tipos);
		}
		free(nombre_pokemon);
	}
	cerrar_archivo_csv(archivo);
	imprimir_inicio_pokedex();
	ejecutar_opciones(pokedex, contador_tipos, ctx);
	lista_destruir_todo(pokedex, liberar_pokemon);

	// //Recorrer lista
	// //Posibilidad 3
	// //TDA iterador externo
	// Lista_iterador *i;
	// for (i = lista_iterador_crear(pokedex); //O(1)
	//      lista_iterador_hay_siguiente(i); //O(1)
	//      lista_iterador_avanzar(i)) { //O(1)
	// 	struct pokemon *p;
	// 	p = lista_iterador_obtener_elemento_actual(i); //O(1)
	// 	///hacer algo
	// }
	// lista_iterador_destruir(i);

	return 0;
}