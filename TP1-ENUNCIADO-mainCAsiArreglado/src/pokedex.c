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

//pre:	Asumimos que el puntero al struct pokedex, ya fue validado de que fuera NULL.
//post:	Devuelve true en caso de que la asignacion de memoria haya sido exitosa, sino devuelve falso.
bool asignar_memoria_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	pokedex->pokemones[pokedex->cantidad].nombre =
		malloc(strlen(pokemon.nombre) + 1);
	if (pokedex->pokemones[pokedex->cantidad].nombre == NULL) {
		return false;
	}
	return true;
}

//pre:	Asumimos que el puntero al struct pokedex, ya fue validado de que fuera NULL.
//post:	Setea los atributos de los campos del struct pokemon.
void setear_atributos_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	strcpy(pokedex->pokemones[pokedex->cantidad].nombre, pokemon.nombre);
	pokedex->pokemones[pokedex->cantidad].tipo = pokemon.tipo;
	pokedex->pokemones[pokedex->cantidad].fuerza = pokemon.fuerza;
	pokedex->pokemones[pokedex->cantidad].destreza = pokemon.destreza;
	pokedex->pokemones[pokedex->cantidad].resistencia = pokemon.resistencia;
	pokedex->cantidad++;
}

//pre:	Asumimos que el puntero al struct pokedex, ya fue validado de que fuera NULL.
//post:	devuelve false en caos de que la asignacion de memoria haya fallado.
bool setear_nuevo_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	if (!asignar_memoria_pokemon(pokedex, pokemon)) {
		return false;
	}
	setear_atributos_pokemon(pokedex, pokemon);
	return true;
}

//pre:	Asumimos que la entrada es casteable a char, o sea no ponemos fuego O ALGO DE ESE ESTILO.
//post:	Devuelve true en caso de que el tipo es valido (fuego, agua,planta, etc).
bool es_tipo_esperado(struct pokemon pokemon)
{
	return (pokemon.tipo == TIPO_AGUA || pokemon.tipo == TIPO_FUEGO ||
		pokemon.tipo == TIPO_ELECTRICO || pokemon.tipo == TIPO_LUCHA ||
		pokemon.tipo == TIPO_NORMAL || pokemon.tipo == TIPO_PLANTA ||
		pokemon.tipo == TIPO_ROCA);
}

//pre:	Asumimos que el archivo se casto correctamnete.
//post: devuelve true si el nombre del pokemon no es vacio, y si las demas estadisticas del pokemon son mayores o iguales a 0.
bool es_entrada_adecuada(struct pokemon pokemon)
{
	if (pokemon.nombre == NULL) {
		return false;
	}
	return (strcmp(pokemon.nombre, "") != 0 && es_tipo_esperado(pokemon) &&
		pokemon.fuerza >= 0 && pokemon.destreza >= 0 &&
		pokemon.resistencia >= 0);
}

//pre:	Se aume que el puntero al struct pokedex, ya es valido, y que se inicializaron y se actualizaron los campos cantidad  y capacidad.
//post:	redimensiona el arreglo, usando realloc, de la pokedex para guardar los pkemones, si es 0 la capacidad, la nueva capacidad va a ser de 10, sino se va multiplicando capacidad*2. Y devuelve true si se logro hacer todo esto.
bool redimensionar_pokedex(struct pokedex *pokedex)
{
	size_t nueva_capacidad_pokedex =
		(pokedex->capacidad == 0) ?
			CAPACIDAD_INICIAL :
			pokedex->capacidad * FACTOR_DE_CRECIMIENTO;
	struct pokemon *pokemones_redimensionados =
		realloc(pokedex->pokemones,
			nueva_capacidad_pokedex * sizeof(struct pokemon));
	if (pokemones_redimensionados == NULL) {
		return false;
	}
	pokedex->pokemones = pokemones_redimensionados;
	pokedex->capacidad = nueva_capacidad_pokedex;
	return true;
}

bool pokedex_agregar_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	if (pokedex == NULL) {
		return false;
	}
	if (pokedex->capacidad <= pokedex->cantidad) {
		if (!redimensionar_pokedex(pokedex)) {
			return false;
		}
	}
	if (es_entrada_adecuada(pokemon)) {
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

//pre:	Los dos strings deberian ser validos.
//post:	Retorna el resultado de la comparacion entre los ds strings.
int comparar_strs(const char *str1, const char *str2)
{
	return strcmp(str1, str2);
}

//pre:	El inicio y el fin deberian ser validos.
//post:	Devuelve el calculo del centro del arreglo.
size_t calcular_centro(size_t inicio, size_t fin)
{
	return (inicio + fin) / 2;
}

const struct pokemon *pokedex_buscar_pokemon(struct pokedex *pokedex,
					     const char *nombre)
{
	if (pokedex == NULL || nombre == NULL || (pokedex->cantidad <= 0) ||
	    (strcmp(nombre, "") == 0)) {
		return NULL;
	}
	int se_encontro_pokemon = false;
	size_t pos_pokemon_buscado = 0;
	size_t inicio = 0;
	size_t fin = pokedex->cantidad - 1;
	while (inicio <= fin && !se_encontro_pokemon) {
		size_t centro = calcular_centro(inicio, fin);
		if (centro >= pokedex->cantidad ||
		    pokedex->pokemones[centro].nombre == NULL) {
			return NULL;
		}
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

//pre:	Los punteros al struct pokemones deberian ser validos.
//post:	intercambiamos de lugar los punteros 1 y 2.
void intercambiar_pokemones(struct pokemon *poke_1, struct pokemon *poke_2)
{
	struct pokemon aux = *poke_1;
	*poke_1 = *poke_2;
	*poke_2 = aux;
}

//pre:	Suponemos que el puntero al struct pokedex es valido.
//post:	Ordenamos por burbujeo los strings.
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
	if (pokedex->cantidad > 1) {
		ordenar_pokemones(pokedex);
	}
	size_t cant_iterada = 0;
	size_t i = 0;
	bool finalizar_iteracion = false;
	while (i < pokedex->cantidad && !finalizar_iteracion) {
		bool continuar_iteracion = funcion(&pokedex->pokemones[i], ctx);
		if (!continuar_iteracion) {
			finalizar_iteracion = true;
		}
		cant_iterada++;
		i++;
	}
	return cant_iterada;
}

void pokedex_destruir(struct pokedex *pokedex)
{
	if (pokedex != NULL) {
		if (pokedex->pokemones != NULL) {
			for (size_t i = 0; i < pokedex->cantidad; i++) {
				free(pokedex->pokemones[i].nombre);
			}
			free(pokedex->pokemones);
		}
		free(pokedex);
	}
}