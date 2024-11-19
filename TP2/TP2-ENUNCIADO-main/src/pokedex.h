#ifndef POKEDEX_H
#define POKEDEX_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct pokedex pokedex_t;

typedef struct pokemon pokemon_t;

/*
    *Crea la pokedex.
*/
pokedex_t *pokedex_crear(int (*comparador)(void*, void*));

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
bool pokedex_agregar_pokemon(pokedex_t *pokedex, pokemon_t *pokemon);

/*
*   Devuelve Cuantos pokemones hay en la pokedex.
*
*/
size_t pokedex_cantidad_pokemones(pokedex_t *pokedex);

/*
*   Elimina un pokemon de la pokedex. Y se guarda el pokemon eliminado en eliminado, siempre que este no sea NULL.
*/
bool pokedex_eliminar_pokemon(pokedex_t *pokedex, pokemon_t *pokemon,void **eliminado);

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
bool pokedex_mostrar_ordenados(pokedex_t *pokedex,bool(*f)(void*, void*),void* ctx);


/*
*   
*   Devuelve True si pudo aplicarle la funcion f a los elementos dentro de la pokedex.
*
*   Caso contrario de que sea false la funcion, devuelve false. 
*
*   Recomendacion: usar para el menu al pedir los pokemones leidos del csv en orden alfabetico.
*
*/
pokemon_t *pokedex_devolver_pokemon_aleatorio(pokedex_t *pokedex);


#endif /* POKEDEX */
