#ifndef POKEDEX_H
#define POKEDEX_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct pokedex pokedex_t;

struct pokemon {
	char *nombre;
	int puntaje;
	char *color;
	char *patron_movimientos;
};

typedef struct pokemon pokemon_t;

typedef struct monstruo monstruos_t;

/*
    *Crea la pokedex.
*/
pokedex_t *pokedex_crear(int (*comparador)(void *, void *));

/*
    *Destruye la pokedex.
*/
void pokedex_destruir(pokedex_t *pokedex);

/**
 * Destruye el menu aplicando la funcion destructora (si no es NULL) a cada elemento.
 * 
*/
void pokedex_destruir_todo(pokedex_t *pokedex, void (*destructor)(void *));

/**
 * Inserta un pokemon a la pokedex.
 * 
 *
 * Devuelve true si pudo agregar al pokemon,o false en caso de error.
 *
 */
bool pokedex_agregar_pokemon(pokedex_t *pokedex, void *pokemon);

/*
*   Devuelve Cuantos pokemones hay en la pokedex.
*
*/
size_t pokedex_cantidad_pokemones(pokedex_t *pokedex);

/*
*   Elimina un pokemon de la pokedex. Y se guarda el pokemon eliminado en eliminado, siempre que este no sea NULL.
*/
bool pokedex_eliminar_pokemon(pokedex_t *pokedex, void *pokemon,
			      void **eliminado);

/*
*   
*   Obtiene el pokemon pasado a la funcion y lo devuelve.
*   
*/
void *pokedex_buscar_pokemon(pokedex_t *pokedex, void *pokemon_buscado);

/*
*   
*   Devuelve True si pudo aplicarle la funcion f a los elementos dentro de la pokedex.
*
*   Caso contrario de que sea false la funcion, devuelve false. 
*
*   Recomendacion: usar para el menu al pedir los pokemones leidos del csv en orden alfabetico.
*
*/
bool pokedex_mostrar_ordenados(pokedex_t *pokedex, bool (*f)(void *, void *),
			       void *ctx);

/*
*   
*
*   Devuelve un pokemon aleatorio. Siempre que pokedex no sea NULL.
*   
*
*/
pokemon_t *pokedex_devolver_pokemon_aleatorio(pokedex_t *pokedex);

/*
*   
*	Devuelve True si pudo cargar los pokemones que estaban en el archivo que le pasamos.
*
*	Internamente, snos encargamos de setear las cosas, pero se espera que el archivo tenga el siguiente formato:
*
*	NombrePokemon,puntaje,color,patron de Movimientos.
*
*	Obvio que pueden poner el separador que quieran, pero se espera ese formato.
*
*	Es tu responsabilidad porporcionarle una funcion destructora que libere lo pedido para el nombre, color y patron de movimientos. QUEDAS ADVERTIDO.
*/
bool pokedex_cargar_pokemones_desde_csv(pokedex_t *pokedex, const char *argv[],
					char separador, size_t columnas);

/*
*		
*   Itera la pokedex con el recorrido PREORDEN. Si la funcion que le pasamos devuleve false, se corta el recorrido y devuelve false la funcion.
*	
*/
bool pokedex_iterar(pokedex_t *pokedex, bool (*f)(void *, void *), void *ctx);

#endif /* POKEDEX */
