#include "pokedex.h"
#include <string.h>

struct pokedex {
	struct pokemon* pokemones;
	size_t capacidad;
	size_t cantidad;
};

struct pokedex *pokedex_crear(){
	struct pokedex* nueva_pokedex = malloc(sizeof(struct pokedex));
	if (nueva_pokedex == NULL){
		return NULL;
	}
	nueva_pokedex->pokemones = NULL;
	nueva_pokedex->capacidad = 0;
	nueva_pokedex->cantidad = 0;
	return nueva_pokedex;	
}

bool pokedex_agregar_pokemon(struct pokedex *pokedex, struct pokemon pokemon){
	if (pokedex->capacidad <= pokedex->cantidad ){
		size_t nueva_capacidad_pokedex = (pokedex->capacidad == 0) ? 10 : pokedex->capacidad * 2;
		struct pokemon* pokemon_nuevo = realloc(pokedex->pokemones, nueva_capacidad_pokedex * sizeof(struct pokemon));
		if (pokemon_nuevo == NULL){
			return false;
		}
		pokedex->pokemones = pokemon_nuevo;
		pokedex->capacidad = nueva_capacidad_pokedex;
	}
	pokedex->pokemones[pokedex->cantidad] = pokemon;
	pokedex->cantidad++;
	return true; 
}

size_t pokedex_cantidad_pokemones(struct pokedex *pokedex){
	if (pokedex == NULL){
		return 0;
	}
	return pokedex->cantidad;
}

const struct pokemon *pokedex_buscar_pokemon(struct pokedex *pokedex,
					     const char *nombre)
{
	int se_encontro_pokemon = 0;
	size_t i = 0;
	size_t pos_pokemon_buscado = 0;
	while (i < pokedex->cantidad && !se_encontro_pokemon){
		if (strcmp(pokedex->pokemones[i].nombre,nombre) == 0){
			se_encontro_pokemon = 1;
			pos_pokemon_buscado = i;
		}
		i++;
	}
	if (se_encontro_pokemon){
		return &pokedex->pokemones[pos_pokemon_buscado];
	}	
	return NULL;
}

//pre:
//post:
void intercambiar_pokemones(struct pokemon *poke_1 ,struct pokemon *poke_2){
	struct pokemon aux = *poke_1;
	*poke_1 = *poke_2;
	*poke_2 = aux;
}

//pre:
//post:
void ordenar_pokemones(struct pokedex *pokedex){
	for (size_t i = 0; i < pokedex->cantidad - 1; i++){
		for (size_t j = 0; j < pokedex->cantidad - i - 1; j++){
			if (strcmp(pokedex->pokemones[j].nombre,pokedex->pokemones[j+1].nombre) > 0){
				intercambiar_pokemones(&pokedex->pokemones[j],&pokedex->pokemones[j+1]);
			}	
		}		
	}	
}

size_t pokedex_iterar_pokemones(struct pokedex *pokedex,
				bool (*funcion)(struct pokemon *, void *),
				void *ctx)
{
	ordenar_pokemones(pokedex);
	size_t cant_iterada=0;
	size_t i = 0;
	int finalizar_iteracion = 0;
	while (i < pokedex->cantidad && !finalizar_iteracion){
		bool continuar_iteracion = funcion(&pokedex->pokemones[i], ctx);
		if (!continuar_iteracion){
			finalizar_iteracion = 1;
		}
		cant_iterada++;
		i++;
	}	
	return cant_iterada;
}

void pokedex_destruir(struct pokedex *pokedex)
{
	free(pokedex->pokemones);
	free(pokedex);
}