#include "pokedex.h"
#include <string.h>
#include <stdio.h>

const size_t CAPACIDAD_INICIAL = 10;
const size_t FACTOR_DE_CRECIMIENTO = 2;

struct pokedex {
	struct pokemon *pokemones;
	size_t capacidad;
	size_t cantidad;
};

struct pokedex *pokedex_crear()
{
	struct pokedex *nueva_pokedex = malloc(sizeof(struct pokedex));
	if (nueva_pokedex == NULL) {
		return NULL;
	}
	nueva_pokedex->pokemones = NULL;
	nueva_pokedex->capacidad = 0;
	nueva_pokedex->cantidad = 0;
	return nueva_pokedex;
}

bool es_pokemon_repetido(struct pokedex *pokedex, struct pokemon pokemon)
{
	bool esta_repetido = false;
	for (size_t i = 0; i < pokedex->cantidad; i++) {
		if (strcmp(pokedex->pokemones[i].nombre, pokemon.nombre) == 0) {
			esta_repetido = true;
		}
	}
	return esta_repetido;
}

bool setear_nuevo_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	pokedex->pokemones[pokedex->cantidad].nombre =
		malloc(strlen(pokemon.nombre) + 1);
	if (pokedex->pokemones[pokedex->cantidad].nombre == NULL) {
		return false;
	}
	strcpy(pokedex->pokemones[pokedex->cantidad].nombre, pokemon.nombre);
	pokedex->pokemones[pokedex->cantidad].tipo = pokemon.tipo;
	pokedex->pokemones[pokedex->cantidad].fuerza = pokemon.fuerza;
	pokedex->pokemones[pokedex->cantidad].destreza = pokemon.destreza;
	pokedex->pokemones[pokedex->cantidad].resistencia = pokemon.resistencia;
	pokedex->cantidad++;
	return true;
}

//pre:
//post:
bool es_tipo_esperado(struct pokemon pokemon)
{
	return (pokemon.tipo == TIPO_AGUA || pokemon.tipo == TIPO_FUEGO || pokemon.tipo == TIPO_ELECTRICO || pokemon.tipo == TIPO_LUCHA || pokemon.tipo == TIPO_NORMAL || pokemon.tipo == TIPO_PLANTA || pokemon.tipo == TIPO_ROCA );
}


//pre:
//post: 
bool es_entrada_adecuada(struct pokemon pokemon)
{
	return (strcmp(pokemon.nombre,"") != 0 && es_tipo_esperado(pokemon) && pokemon.fuerza >= 0 && pokemon.destreza >= 0 && pokemon.resistencia >= 0);
}

bool pokedex_agregar_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	if (pokedex == NULL) {
		return false;
	}
	if (pokedex->capacidad <= pokedex->cantidad) {
		size_t nueva_capacidad_pokedex =
			(pokedex->capacidad == 0) ?
				CAPACIDAD_INICIAL :
				pokedex->capacidad * FACTOR_DE_CRECIMIENTO;
		struct pokemon *pokemon_redimensionados = realloc(
			pokedex->pokemones,
			nueva_capacidad_pokedex * sizeof(struct pokemon));
		if (pokemon_redimensionados == NULL) {
			return false;
		}
		pokedex->pokemones = pokemon_redimensionados;
		pokedex->capacidad = nueva_capacidad_pokedex;
	}
	if (!es_pokemon_repetido(pokedex, pokemon) && es_entrada_adecuada(pokemon)) {
		if (setear_nuevo_pokemon(pokedex, pokemon)) {
			return true;
		}
		return false;
	}
	return false;
}

size_t pokedex_cantidad_pokemones(struct pokedex *pokedex)
{
	if (pokedex == NULL) {
		return 0;
	}
	return pokedex->cantidad;
}

//pre:
//post:
int comparar_strs(const char *str1, const char *str2)
{
	return strcmp(str1, str2);
}

//pre:
//post:
size_t calcular_centro(size_t inicio, size_t fin)
{
	return (inicio + fin) / 2;
}

const struct pokemon *pokedex_buscar_pokemon(struct pokedex *pokedex,
					     const char *nombre)
{
	if (pokedex == NULL || nombre == NULL || (pokedex->cantidad <= 0) || (strcmp(nombre,"") == 0)) {
		return NULL;
	}
	int se_encontro_pokemon = false;
	size_t pos_pokemon_buscado = 0;
	size_t inicio = 0;
	size_t fin = pokedex->cantidad - 1;
	while (inicio <= fin && !se_encontro_pokemon) {
		size_t centro = calcular_centro(inicio, fin);
		int resultado_entr_strs = comparar_strs(
			pokedex->pokemones[centro].nombre, nombre);
		if (resultado_entr_strs == 0) {
			se_encontro_pokemon = true;
			pos_pokemon_buscado = centro;
		} else if (resultado_entr_strs < 0) {
			inicio = centro + 1;
		} else {
			fin = centro - 1;
		}
	}
	if (se_encontro_pokemon) {
		return &pokedex->pokemones[pos_pokemon_buscado];
	}
	return NULL;
}

//pre:
//post:
void intercambiar_pokemones(struct pokemon *poke_1, struct pokemon *poke_2)
{
	struct pokemon aux = *poke_1;
	*poke_1 = *poke_2;
	*poke_2 = aux;
}

//pre:
//post:
void ordenar_pokemones(struct pokedex *pokedex)
{
	for (size_t i = 0; i < pokedex->cantidad - 1; i++) {
		for (size_t j = 0; j < pokedex->cantidad - i - 1; j++) {
			if (strcmp(pokedex->pokemones[j].nombre,
				   pokedex->pokemones[j + 1].nombre) > 0) {
				intercambiar_pokemones(
					&pokedex->pokemones[j],
					&pokedex->pokemones[j + 1]);
			}
		}
	}
}

size_t pokedex_iterar_pokemones(struct pokedex *pokedex,
				bool (*funcion)(struct pokemon *, void *),
				void *ctx)
{
	if (pokedex == NULL) {
		return 0;
	}
	if (pokedex->cantidad > 0) {
		ordenar_pokemones(pokedex);
	}
	size_t cant_iterada = 0;
	size_t i = 0;
	int finalizar_iteracion = 0;
	while (i < pokedex->cantidad && !finalizar_iteracion) {
		bool continuar_iteracion = funcion(&pokedex->pokemones[i], ctx);
		if (!continuar_iteracion) {
			finalizar_iteracion = 1;
		}
		cant_iterada++;
		i++;
	}
	return cant_iterada;
}

void pokedex_destruir(struct pokedex *pokedex)
{
	for (size_t i = 0; i < pokedex->cantidad; i++) {
		free(pokedex->pokemones[i].nombre);
	}
	free(pokedex->pokemones);
	free(pokedex);
}