#include "pokedex.h"
#include "abb.h"
#include "csv.h"


struct pokedex {
	abb_t *almacen;
	size_t cant_pokemones;
};

struct pokemon {
	char *nombre;
	int puntaje;
	char *color;
	char *patron_movimientos;
	//char primer_letra;
};


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


pokedex_t *pokedex_crear(int (*comparador)(void *, void *))
{
	pokedex_t *pokedex = calloc(1, sizeof(pokedex_t));
	if (!pokedex) {
		return NULL;
	}
	pokedex->almacen = abb_crear(comparador);
	if (!pokedex->almacen) {
		free(pokedex);
		return NULL;
	}
	return pokedex;
}

bool pokedex_agregar_pokemon(pokedex_t *pokedex, pokemon_t *pokemon)
{
	if (!pokedex || !pokemon) {
		return false;
	}
	if (!abb_insertar(pokedex->almacen, pokemon)) {
		return false;
	}
	pokedex->cant_pokemones++;
	return true;
}

size_t pokedex_cantidad_pokemones(pokedex_t *pokedex)
{
	return pokedex == NULL ? 0 : pokedex->cant_pokemones;
}

bool pokedex_eliminar_pokemon(pokedex_t *pokedex, pokemon_t *pokemon,
			      void **eliminado)
{
	if (!pokedex || !pokemon || pokedex->cant_pokemones == 0 ||
	    !eliminado) {
		return false;
	}
	if (abb_quitar(pokedex->almacen, pokemon, eliminado)) {
		pokedex->cant_pokemones--;
		return true;
	}
	return false;
}

void *pokedex_buscar_pokemon(pokedex_t *pokedex, void *pokemon_buscado)
{
	if (!pokedex || !pokemon_buscado) {
		return NULL;
	}
	return abb_obtener(pokedex->almacen, pokemon_buscado);
}

bool pokedex_mostrar_ordenados(pokedex_t *pokedex, bool (*f)(void *, void *),
			       void *ctx)
{
	if (!pokedex || !f) {
		return false;
	}
	if (abb_iterar_inorden(pokedex->almacen, f, ctx) == pokedex->cant_pokemones) {
		return true;
	}
	return false;
}

//pre:
//post:
bool seleccionar_pokemon(void *elemento,void* ctx){
    size_t *contador = ((size_t **)ctx)[0];
    size_t *indice_objetivo = ((size_t **)ctx)[1];
    pokemon_t **resultado = ((pokemon_t ***)ctx)[2];
    if (*contador == *indice_objetivo) {
        *resultado = elemento;
        return false;
    }
    (*contador)++;
    return true;
}

pokemon_t *pokedex_devolver_pokemon_aleatorio(pokedex_t *pokedex)
{
    if (!pokedex){
        return NULL;
    }
    size_t indice_random = (size_t)rand() % (pokedex->cant_pokemones);
    size_t i = 0;
    pokemon_t *pokemon_aleatorio = NULL;
    void *ctx[] = {&i, &indice_random, &pokemon_aleatorio};
    abb_iterar_postorden(pokedex->almacen, seleccionar_pokemon, ctx);
	return pokemon_aleatorio;
}

void reservar_copiar_nombre_pokemon(pokemon_t *pokemon, char *nombre)
{
	pokemon->nombre = malloc(strlen(nombre) + 1);
	if (pokemon->nombre != NULL) {
		strcpy(pokemon->nombre, nombre);
	}
}

void reservar_copiar_color_pokemon(pokemon_t *pokemon, char *color)
{
	pokemon->color = malloc(strlen(color) + 1);
	if (pokemon->color != NULL) {
		strcpy(pokemon->color, color);
	}
}

void reservar_copiar_patron_movimientos(pokemon_t *pokemon, char *patron_movimientos)
{
	pokemon->patron_movimientos = malloc(strlen(patron_movimientos) + 1);
	if (pokemon->patron_movimientos != NULL) {
		strcpy(pokemon->patron_movimientos, patron_movimientos);
	}
}

// pre:	Asumimos que el struct pokemon y los demas argumentos pasados fueron
// inicalizados y/o casteados correctamente. post:	Seteamos los campos del
// pokemon con lo que fuismo casteando del archivo csv.
void setear_pokemon(pokemon_t *pokemon, char *nombre, int puntaje,
		    char* color, char* patron_movimientos)
{
	reservar_copiar_nombre_pokemon(pokemon, nombre);
	pokemon->puntaje = puntaje;
	reservar_copiar_color_pokemon(pokemon,color);
	reservar_copiar_patron_movimientos(pokemon,patron_movimientos);
}


bool pokedex_cargar_pokemones_desde_csv(pokedex_t *pokedex, const char *nombre_archivo, char separador, size_t columnas){
	if (!pokedex || !nombre_archivo){
		return false;
	}
	struct archivo_csv *archivo = abrir_archivo_csv(nombre_archivo, separador);
	char *nombre_pokemon = NULL;
	int puntaje;
	char *color = NULL;
	char *patron_movimientos = NULL;
	bool (*funciones[])(const char *,
			    void *) = { crear_string_nuevo, castear_a_int, crear_string_nuevo,
					crear_string_nuevo };
	void *ctx[] = { &nombre_pokemon, &puntaje, &color, &patron_movimientos };
	while (leer_linea_csv(archivo, columnas, funciones, ctx) == columnas) {
		struct pokemon *nuevo_pokemon = malloc(sizeof(pokemon_t));
		setear_pokemon(nuevo_pokemon, nombre_pokemon, puntaje,color, patron_movimientos);
		if (!pokedex_agregar_pokemon(pokedex,nuevo_pokemon)) {
			return false;
		}
		printf("Nombre: %s, puntaje: %i, color: %s, patron: %s\n",
	       nuevo_pokemon->nombre, nuevo_pokemon->puntaje, nuevo_pokemon->color, nuevo_pokemon->patron_movimientos);
		free(nombre_pokemon);
		free(color);
        free(patron_movimientos);
	}
	cerrar_archivo_csv(archivo);
	return true;
}

//pre:
//post:
void destruir_con_destructor(pokedex_t *pokedex, void (*destructor)(void *))
{
	if (pokedex) {
		abb_destruir_todo(pokedex->almacen, destructor);
		free(pokedex);
	}
}


void pokedex_destruir(pokedex_t *pokedex)
{
	if(pokedex){
		destruir_con_destructor(pokedex, NULL);	
	}	 	
}

void pokedex_destruir_todo(pokedex_t *pokedex, void (*destructor)(void *))
{
	if (pokedex)
	{
		destruir_con_destructor(pokedex, destructor);
	}
}