#include "pokedex.h"
#include "abb.h"

struct pokedex {
	abb_t *almacen;
	size_t cant_pokemones;
};

struct pokemon {
	char *nombre;
	size_t puntaje;
	char *color;
	char *patron_movimientos;
	//char primer_letra;
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


void destruir_con_destructor(pokedex_t *pokedex, void (*destructor)(void *))
{
	if (pokedex) {
		if (!destructor) {
			abb_destruir_todo(pokedex->almacen, destructor);
		}
		free(pokedex);
	}
}

void pokedex_destruir(pokedex_t *pokedex)
{
	destruir_con_destructor(pokedex, NULL);
}

void pokedex_destruir_todo(pokedex_t *pokedex, void (*destructor)(void *))
{
	destruir_con_destructor(pokedex, destructor);
}