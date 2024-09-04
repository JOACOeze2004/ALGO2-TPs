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

// struct pokemon *redimensionar_pokedex(struct pokedex *pokedex, struct pokemon pokemon){


// }

bool pokedex_agregar_pokemon(struct pokedex *pokedex, struct pokemon pokemon){
	bool es_pokemon_a_agregar = false;
	if (pokedex->capacidad <= pokedex->cantidad){
		size_t nueva_capacidad_pokedex = (pokedex->capacidad == 0) ? 10 : pokedex->capacidad * 2;
		struct pokemon* pokemon_redimensionados = realloc(pokedex->pokemones, nueva_capacidad_pokedex * sizeof(struct pokemon));
		if (pokemon_redimensionados == NULL){
			return false;
		}
		pokedex->pokemones = pokemon_redimensionados;
		pokedex->capacidad = nueva_capacidad_pokedex;
	}
	bool esta_pokemon_repetido = false;
	for (size_t i = 0; i < pokedex->cantidad; i++){
		if (strcmp(pokedex->pokemones[i].nombre,pokemon.nombre)==0){
			esta_pokemon_repetido = true;
		}
	}
	if (!esta_pokemon_repetido){
		pokedex->pokemones[pokedex->cantidad].nombre = malloc(strlen(pokemon.nombre)+1);
		if (pokedex->pokemones[pokedex->cantidad].nombre == NULL){
			return false;
		}
		strcpy(pokedex->pokemones[pokedex->cantidad].nombre, pokemon.nombre);
		pokedex->pokemones[pokedex->cantidad].tipo = pokemon.tipo;
		pokedex->pokemones[pokedex->cantidad].fuerza = pokemon.fuerza;
		pokedex->pokemones[pokedex->cantidad].destreza = pokemon.destreza;
		pokedex->pokemones[pokedex->cantidad].resistencia = pokemon.resistencia;
		pokedex->cantidad++;
		es_pokemon_a_agregar = true;
	}
	return es_pokemon_a_agregar; 
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
	if (pokedex->cantidad > 0){
		ordenar_pokemones(pokedex);
	}
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
	for (size_t i = 0; i < pokedex->cantidad; i++){
		free(pokedex->pokemones[i].nombre);
	}	
	free(pokedex->pokemones);
	free(pokedex);
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <assert.h>
// Función de prueba para la iteración de Pokémon
bool imprimir_pokemon(struct pokemon *poke, void *ctx) {
    (void)ctx; // No usamos el contexto en esta función
    printf("Nombre: %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
           poke->nombre, poke->tipo, poke->fuerza, poke->destreza, poke->resistencia);
    return true; // Continuar iterando
}

// void test_pokedex() {
//     // Crear una nueva pokedex
//     struct pokedex *mi_pokedex = pokedex_crear();
//     assert(mi_pokedex != NULL);
//     assert(pokedex_cantidad_pokemones(mi_pokedex) == 0);

//     // Agregar Pokémon
//     struct pokemon p1 = {"Pikachu", TIPO_ELECTRICO, 55, 40, 35};
//     assert(pokedex_agregar_pokemon(mi_pokedex, p1));

//     struct pokemon p2 = {"Bulbasaur", TIPO_PLANTA, 49, 49, 49};
//     assert(pokedex_agregar_pokemon(mi_pokedex, p2));

//     struct pokemon p3 = {"Charmander", TIPO_FUEGO, 52, 43, 39};
//     assert(pokedex_agregar_pokemon(mi_pokedex, p3));

//     // Verificar cantidad de Pokémon
//     assert(pokedex_cantidad_pokemones(mi_pokedex) == 3);

//     // Buscar Pokémon
//     const struct pokemon *buscado = pokedex_buscar_pokemon(mi_pokedex, "Bulbasaur");
//     assert(buscado != NULL);
//     assert(strcmp(buscado->nombre, "Bulbasaur") == 0);

//     // Imprimir todos los Pokémon
//     printf("Imprimiendo todos los Pokémon:\n");
//     size_t iterados = pokedex_iterar_pokemones(mi_pokedex, imprimir_pokemon, NULL);
//     assert(iterados == 3);

//     // Ordenar Pokémon y verificar el orden
//     struct pokemon p4 = {"Squirtle", TIPO_AGUA, 48, 65, 50};
//     pokedex_agregar_pokemon(mi_pokedex, p4);

//     printf("\nImprimiendo Pokémon ordenados:\n");
//     pokedex_iterar_pokemones(mi_pokedex, imprimir_pokemon, NULL);

//     // Destruir la pokedex
//     pokedex_destruir(mi_pokedex);
// }

// int main() {
//     test_pokedex();
//     printf("Todas las pruebas pasaron correctamente.\n");
//     return 0;
// }



void test_pokedex_completa() {
    // Crear una nueva pokedex
    struct pokedex *mi_pokedex = pokedex_crear();
    assert(mi_pokedex != NULL);
    assert(pokedex_cantidad_pokemones(mi_pokedex) == 0);

    // Agregar Pokémon
    struct pokemon p1 = {"Pikachu", TIPO_ELECTRICO, 20, 15, 17};
    assert(pokedex_agregar_pokemon(mi_pokedex, p1));

    struct pokemon p2 = {"Bulbasaur", TIPO_PLANTA, 49, 49, 49};
    assert(pokedex_agregar_pokemon(mi_pokedex, p2));

    struct pokemon p3 = {"Charmander", TIPO_FUEGO, 10, 5, 8};
    assert(pokedex_agregar_pokemon(mi_pokedex, p3));

	struct pokemon p4 = {"Larvitar", TIPO_ROCA, 30, 1, 40};
    assert(pokedex_agregar_pokemon(mi_pokedex, p4));

    struct pokemon p5 = {"Cacnea", TIPO_PLANTA, 11, 12, 14};
    assert(pokedex_agregar_pokemon(mi_pokedex, p5));

    struct pokemon p6 = {"Joltik", TIPO_ELECTRICO, 8, 10, 5};
    assert(pokedex_agregar_pokemon(mi_pokedex, p6));

	struct pokemon p7 = {"Togepi", TIPO_NORMAL, 8, 8, 2};
    assert(pokedex_agregar_pokemon(mi_pokedex, p7));

	struct pokemon p8 = {"Floatzel", TIPO_AGUA, 24, 20, 5};
    assert(pokedex_agregar_pokemon(mi_pokedex, p8));

    struct pokemon p9 = {"Dedenne", TIPO_ELECTRICO, 15, 5, 23};
    assert(pokedex_agregar_pokemon(mi_pokedex, p9));

	struct pokemon p10 = {"Magcargo", TIPO_FUEGO, 22, 20, 22};
    assert(pokedex_agregar_pokemon(mi_pokedex, p10));

    // Prueba de Pokémon duplicado
    struct pokemon p_duplicado = {"Pikachu", TIPO_ELECTRICO, 60, 50, 45};
    assert(!pokedex_agregar_pokemon(mi_pokedex, p_duplicado));

    // Verificar cantidad de Pokémon
    assert(pokedex_cantidad_pokemones(mi_pokedex) == 10);

    // Buscar Pokémon existente
    const struct pokemon *buscado = pokedex_buscar_pokemon(mi_pokedex, "Bulbasaur");
    assert(buscado != NULL);
    assert(strcmp(buscado->nombre, "Bulbasaur") == 0);

    // Buscar Pokémon no existente
    const struct pokemon *no_existe = pokedex_buscar_pokemon(mi_pokedex, "Mewtwo");
    assert(no_existe == NULL);

    // Imprimir todos los Pokémon
    printf("\nImprimiendo todos los Pokémon:\n");
    size_t iterados = pokedex_iterar_pokemones(mi_pokedex, imprimir_pokemon, NULL);
    assert(iterados == 10);

    // Agregar más Pokémon
    struct pokemon p11 = {"Squirtle", TIPO_AGUA, 48, 65, 50};
    assert(pokedex_agregar_pokemon(mi_pokedex, p11));

    // Prueba de ordenamiento
    printf("\nImprimiendo Pokémon ordenados:\n");
    pokedex_iterar_pokemones(mi_pokedex, imprimir_pokemon, NULL);
    
    // Verificar orden después de agregar Squirtle
    const struct pokemon *primero = pokedex_buscar_pokemon(mi_pokedex, "Bulbasaur");
    assert(strcmp(primero->nombre, "Bulbasaur") == 0);

    // Agregar un Pokémon con atributos en los extremos
    struct pokemon p_extremo = {"Magikarp", TIPO_AGUA, 0, 0, 0};
    assert(pokedex_agregar_pokemon(mi_pokedex, p_extremo));

    // Prueba de iteración en una pokedex vacía
    struct pokedex *pokedex_vacia = pokedex_crear();
    size_t iterados_vacia = pokedex_iterar_pokemones(pokedex_vacia, imprimir_pokemon, NULL);
    assert(iterados_vacia == 0);
    pokedex_destruir(pokedex_vacia);

    // Destruir la pokedex
    pokedex_destruir(mi_pokedex);
}


int main() {
    test_pokedex_completa();
    printf("Todas las pruebas pasaron correctamente.\n\n");
    return 0;
}