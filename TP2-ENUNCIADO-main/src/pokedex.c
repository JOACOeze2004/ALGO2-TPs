#include "pokedex.h"
#include "abb.h"
#include "csv.h"
#include "castear.h"

struct pokedex {
	abb_t *almacen;
	size_t cant_pokemones;
};

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

bool pokedex_agregar_pokemon(pokedex_t *pokedex, void *pokemon)
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

bool pokedex_eliminar_pokemon(pokedex_t *pokedex, void *pokemon,
			      void **eliminado)
{
	if (!pokedex || !pokemon || pokedex->cant_pokemones == 0) {
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
	if (abb_iterar_inorden(pokedex->almacen, f, ctx) ==
	    pokedex->cant_pokemones) {
		return true;
	}
	return false;
}

//pre:	Obvio que los elemntos pasados son validos y estan inicialziados. Ademas de habverse inicializado una semilla previamnete asi rand devuelve un numero aleatorio.
//post:	Devuelve true si se llego al indice q devolvio rand, y se pisa el pokemon que le pasamos con el contexto para asi quedarnos con el pokemon que estaba en ese nodo.
bool seleccionar_pokemon(void *elemento, void *ctx)
{
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
	if (!pokedex || pokedex->cant_pokemones == 0) {
		return NULL;
	}
	size_t indice_random = (size_t)rand() % (pokedex->cant_pokemones);
	size_t i = 0;
	pokemon_t *pokemon_aleatorio = NULL;
	void *ctx[] = { &i, &indice_random, &pokemon_aleatorio };
	abb_iterar_postorden(pokedex->almacen, seleccionar_pokemon, ctx);
	return pokemon_aleatorio;
}

//pre: pokemon y el nombre deberian ser parametros validos e inicializados.
//post:	Reserva memoria para el nombre del pokemon a guardar y copia el nombre que le pasemos al campo nombre del pokemon.
void reservar_copiar_nombre_pokemon(pokemon_t *pokemon, char *nombre)
{
	pokemon->nombre = malloc(strlen(nombre) + 1);
	if (pokemon->nombre != NULL) {
		strcpy(pokemon->nombre, nombre);
	}
}

//pre:	pokemon y el color deberian ser parametros validos e inicializados.
//post:	Reserva memoria para el color del pokemon a guardar y copia el mismo al campo color del pokemon.
void reservar_copiar_color_pokemon(pokemon_t *pokemon, char *color)
{
	pokemon->color = malloc(strlen(color) + 1);
	if (pokemon->color != NULL) {
		strcpy(pokemon->color, color);
	}
}

//pre:	pokemon y el patron deberian ser parametros validos e inicializados.
//post:	Reserva memoria para el paton del pokemon a guardar y copia el mismo al campo patron del pokemon.
void reservar_copiar_patron_movimientos(pokemon_t *pokemon,
					char *patron_movimientos)
{
	pokemon->patron_movimientos = malloc(strlen(patron_movimientos) + 1);
	if (pokemon->patron_movimientos != NULL) {
		strcpy(pokemon->patron_movimientos, patron_movimientos);
	}
}

// pre:	Asumimos que el struct pokemon y los demas argumentos pasados fueron  inicalizados y/o casteados correctamente.
// post:	Seteamos los campos del pokemon con lo que fuismo casteando del archivo csv.
void setear_pokemon(pokemon_t *pokemon, char *nombre, int puntaje, char *color,
		    char *patron_movimientos)
{
	reservar_copiar_nombre_pokemon(pokemon, nombre);
	pokemon->puntaje = puntaje;
	reservar_copiar_color_pokemon(pokemon, color);
	reservar_copiar_patron_movimientos(pokemon, patron_movimientos);
}

//pre:	Los parametros pasados deben ser validos, obvio.
//post:	devuelve un pokemon con todos los atributos que se le pasaron por el csv. O devuleve NULL si fallo el malloc.
pokemon_t *crear_y_configurar_pokemon(char *nombre, int puntaje, char *color,
				      char *patron_movimientos)
{
	pokemon_t *nuevo_pokemon = malloc(sizeof(pokemon_t));
	if (!nuevo_pokemon) {
		return NULL;
	}
	setear_pokemon(nuevo_pokemon, nombre, puntaje, color,
		       patron_movimientos);
	return nuevo_pokemon;
}

//pre:	Los parametros pasados deben ser validos.
//post:	Libera lo pedido para el parseo del nombre, color y patron del pokemon.
void liberar_recursos_csv(char *nombre, char *color, char *patron)
{
	free(nombre);
	free(color);
	free(patron);
}

bool pokedex_cargar_pokemones_desde_csv(pokedex_t *pokedex, const char *argv[],
					char separador, size_t columnas)
{
	if (!pokedex || !argv) {
		return false;
	}
	struct archivo_csv *archivo = abrir_archivo_csv(argv[1], separador);
	if (!archivo) {
		return false;
	}
	char *nombre_pokemon = NULL;
	int puntaje;
	char *color = NULL;
	char *patron_movimientos = NULL;
	bool (*funciones[])(const char *, void *) = { crear_string_nuevo,
						      castear_a_int,
						      crear_string_nuevo,
						      crear_string_nuevo };
	void *ctx[] = { &nombre_pokemon, &puntaje, &color,
			&patron_movimientos };
	while (leer_linea_csv(archivo, columnas, funciones, ctx) == columnas) {
		pokemon_t *nuevo_pokemon = crear_y_configurar_pokemon(
			nombre_pokemon, puntaje, color, patron_movimientos);
		if (!nuevo_pokemon) {
			cerrar_archivo_csv(archivo);
			liberar_recursos_csv(nombre_pokemon, color,
					     patron_movimientos);
			return false;
		}
		if (!pokedex_agregar_pokemon(pokedex, nuevo_pokemon)) {
			cerrar_archivo_csv(archivo);
			liberar_recursos_csv(nombre_pokemon, color,
					     patron_movimientos);
			free(nuevo_pokemon);
			return false;
		}
		liberar_recursos_csv(nombre_pokemon, color, patron_movimientos);
	}
	cerrar_archivo_csv(archivo);
	return true;
}

bool pokedex_iterar(pokedex_t *pokedex, bool (*f)(void *, void *), void *ctx)
{
	if (!pokedex || !f) {
		return false;
	}
	if (abb_iterar_preorden(pokedex->almacen, f, ctx) > 0) {
		return true;
	}
	return false;
}

//pre:	La pokedex debe ser valida. Y si queremos aplicarle la funcion destructora no hya que pasarle null.
//post:	Liberamos la pokedex aplciandole la funcion destructora.
void destruir_pokedex_con_destructor(pokedex_t *pokedex,
				     void (*destructor)(void *))
{
	if (pokedex) {
		abb_destruir_todo(pokedex->almacen, destructor);
		free(pokedex);
	}
}

void pokedex_destruir(pokedex_t *pokedex)
{
	if (pokedex) {
		destruir_pokedex_con_destructor(pokedex, NULL);
	}
}

void pokedex_destruir_todo(pokedex_t *pokedex, void (*destructor)(void *))
{
	if (pokedex) {
		destruir_pokedex_con_destructor(pokedex, destructor);
	}
}