#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FACTOR_CARGA_MAX 0.75
#define LIMITE_PARES 10
#define CAPACIDAD_BORDE 3
#define FACTOR_CRECIMIENTO 2

typedef struct par par_t;

struct par {
	char *clave;
	void *valor;
	par_t *siguiente;
};

struct hash {
	par_t **pares;
	size_t *contador_pares;
	size_t capacidad;
	size_t cantidad;
};

// pre: La clave es un string valido (nada de null).
// post:	devuelve una posicion que sera usada como posicion para el vector
// de pares asi determinamos donde va a parar cada par al querer insertarlos.
size_t funcion_hash(const char *clave, size_t capacidad)
{
	size_t hash_posicion = 0;
	size_t i = 0;
	while (clave[i] != '\0') {
		hash_posicion = (hash_posicion * 73 + (unsigned char)clave[i]) %
				capacidad;
		i++;
	}
	return hash_posicion;
}

// pre: La clave y el contenido son validas.
// post:	Devuelve un nodo que almacena una clave y su contenido.
par_t *crear_nuevo_par(char *clave, void *contenido)
{
	par_t *nodo = calloc(1, sizeof(par_t));
	if (nodo == NULL) {
		return NULL;
	}
	nodo->clave = calloc(1, strlen(clave) + 1);
	if (nodo->clave == NULL) {
		free(nodo);
		return NULL;
	}
	strcpy(nodo->clave, clave);
	nodo->valor = contenido;
	return nodo;
}

hash_t *hash_crear(size_t capacidad_inicial)
{
	size_t cap_inicial_max = capacidad_inicial < CAPACIDAD_BORDE ?
					 CAPACIDAD_BORDE :
					 capacidad_inicial;
	hash_t *hash = calloc(1, sizeof(hash_t));
	if (hash == NULL) {
		return NULL;
	}
	hash->pares = calloc(cap_inicial_max, sizeof(par_t));
	if (hash->pares == NULL) {
		free(hash);
		return NULL;
	}
	hash->contador_pares = calloc(cap_inicial_max, sizeof(size_t));
	if (hash->contador_pares == NULL) {
		free(hash->pares);
		free(hash);
		return NULL;
	}
	hash->capacidad = cap_inicial_max;
	return hash;
}

size_t hash_cantidad(hash_t *hash)
{
	return hash == NULL ? 0 : hash->cantidad;
}

// pre: Todos los parametros que recibimos son validos.
// post:	Devuelve true si se encontro la clave y false en caso contrario. Si
// la encontro, pisa el contenido viejo por el nuevo.
bool buscar_y_editar_valor_clave_repetida(char *clave, void *valor,
					  par_t *pos_actual, void **encontrado)
{
	if (strcmp(clave, pos_actual->clave) == 0) {
		if (encontrado != NULL) {
			*encontrado = pos_actual->valor;
		}
		pos_actual->valor = valor;
		return true;
	}
	return false;
}

// pre:	Se supone que los paraetros pasados son validos y/o fueron
// inicializados. post:	Devuelve true si pudo crear el nodo con la clave y
// contenido pasados a la funcion, devulveriafalse en caso de que falla la
// asignacion de memoria para el nodo.
bool agregar_par_no_repetido(hash_t *hash, char *clave, void *valor,
			     size_t indice_hash)
{
	par_t *par_nuevo = crear_nuevo_par(clave, valor);
	if (par_nuevo == NULL) {
		return false;
	}
	par_nuevo->siguiente = hash->pares[indice_hash];
	hash->pares[indice_hash] = par_nuevo;
	hash->contador_pares[indice_hash]++;
	hash->cantidad++;
	return true;
}

// pre:	Los parametros pasados son validos.
// post:	Devuelve true si se pudo insertar el nuevo par, independientemente
// del caso en el que caiga.
bool agregar_par(hash_t *hash, char *clave, void *valor, void **encontrado)
{
	size_t indice_hash = funcion_hash(clave, hash->capacidad);
	par_t *pos_actual = hash->pares[indice_hash];
	bool encontre_clave_repetida = false;
	while (pos_actual != NULL && !encontre_clave_repetida) {
		if (buscar_y_editar_valor_clave_repetida(
			    clave, valor, pos_actual, encontrado)) {
			encontre_clave_repetida = true;
		}
		pos_actual = pos_actual->siguiente;
	}
	if (!encontre_clave_repetida) {
		if (!agregar_par_no_repetido(hash, clave, valor, indice_hash)) {
			return false;
		}
	}
	return true;
}

// pre:	El par actual no puede ser NULL
// post:	Libera lo que habia en la tabla vieja, es decir libera la clave del
// nodo y el mismo nodo.
void liberar_tabla_vieja(par_t *par_actual)
{
	free(par_actual->clave);
	free(par_actual);
}

// pre:	Los parametros pasados no pueden ser null y/o deben haber sido
// inicializados. post:	Va reinsertando los elementos que habia en la tabla
// vieja pero en la nueva.
void actualizar_nueva_tabla(hash_t *hash, par_t **tabla_vieja, size_t i)
{
	par_t *par_actual = tabla_vieja[i];
	while (par_actual != NULL) {
		par_t *par_aux = par_actual->siguiente;
		agregar_par(hash, par_actual->clave, par_actual->valor, NULL);
		liberar_tabla_vieja(par_actual);
		par_actual = par_aux;
	}
}

// pre:	El hash no puede ser null, y las funciones involucradas no deberian
// haber fallado. post:	Devolvemos un hash que tiene loselementos que tenia
// antes pero con un vector de pares con mayor capacidad para evitar coaliciones
// encadenadas.
hash_t *rehash(hash_t *hash)
{
	par_t **tabla_vieja = hash->pares;
	size_t *contador_viejo = hash->contador_pares;
	size_t capacidad_vieja = hash->capacidad;
	hash->capacidad *= FACTOR_CRECIMIENTO;
	hash->pares = calloc(hash->capacidad, sizeof(par_t));
	if (hash->pares == NULL) {
		return NULL;
	}
	hash->contador_pares = calloc(hash->capacidad, sizeof(size_t));
	if (hash->contador_pares == NULL) {
		free(hash->pares);
		return NULL;
	}
	hash->cantidad = 0;
	for (size_t i = 0; i < capacidad_vieja; i++) {
		actualizar_nueva_tabla(hash, tabla_vieja, i);
	}
	free(contador_viejo);
	free(tabla_vieja);
	return hash;
}

bool hash_insertar(hash_t *hash, char *clave, void *valor, void **encontrado)
{
	if (hash == NULL || clave == NULL) {
		return false;
	}
	if (encontrado != NULL) {
		*encontrado = NULL;
	}
	size_t indice_hash = funcion_hash(clave, hash->capacidad);
	if ((float)hash->cantidad / (float)hash->capacidad >=
		    FACTOR_CARGA_MAX ||
	    hash->contador_pares[indice_hash] > LIMITE_PARES) {
		hash_t *diccionario_rehasheado = rehash(hash);
		if (diccionario_rehasheado == NULL) {
			return false;
		}
		hash = diccionario_rehasheado;
	}
	if (!agregar_par(hash, clave, valor, encontrado)) {
		return false;
	}
	return true;
}

// pre:	El hash y la cloave no pueden ser NULL.
// post:	Si encontramos la clave devolvemos el elemento, en caso de no
// encontrarla, devolvemos NULL.
par_t *dict_buscar_par(hash_t *hash, char *clave)
{
	size_t indice = funcion_hash(clave, hash->capacidad);
	par_t *par_actual = hash->pares[indice];
	bool clave_encontrada = false;
	void *par_buscado = NULL;
	while (par_actual != NULL && !clave_encontrada) {
		if (strcmp(clave, par_actual->clave) == 0) {
			par_buscado = par_actual;
			clave_encontrada = true;
		}
		par_actual = par_actual->siguiente;
	}
	return par_buscado;
}

void *hash_buscar(hash_t *hash, char *clave)
{
	if (hash == NULL || clave == NULL || hash->cantidad == 0) {
		return NULL;
	}
	par_t *par = dict_buscar_par(hash, clave);
	return par ? par->valor : NULL;
}

bool hash_contiene(hash_t *hash, char *clave)
{
	return (hash != NULL && clave != NULL &&
		hash_buscar(hash, clave) != NULL) ?
		       true :
		       false;
}

// pre: Todos los parametros fueron inicializados y no son validos.
// post:	Ajusta las posiciones afecradas por la eliminacion del par, libera
// la clave y luego el par/nodo en cuestion que queriamos eliminar, y restamos
// la cantidad de elemntos en el hash.
void reajustar_destruir_par(hash_t *hash, par_t *par_actual, par_t *par_aux,
			    size_t indice)
{
	if (par_aux == NULL) {
		hash->pares[indice] = par_actual->siguiente;
	} else {
		par_aux->siguiente = par_actual->siguiente;
	}
	free(par_actual->clave);
	free(par_actual);
	hash->contador_pares[indice]--;
	hash->cantidad--;
}

// pre:	Obvio que todos los parametros son validos o fueron inicializados.
// post:	Devolvemos el valor que tenia esa clave que queriamos eliminar, en
// caso de existir obvio, caso de que no existiera la clave a eliminar,
// devolvemos NULL.
void *eliminar_par(hash_t *hash, char *clave, par_t *par_actual, size_t indice)
{
	void *valor_eliminado = NULL;
	bool elimine_par = false;
	par_t *par_aux = NULL;
	while (par_actual != NULL && !elimine_par) {
		if (strcmp(par_actual->clave, clave) == 0) {
			valor_eliminado = par_actual->valor;
			reajustar_destruir_par(hash, par_actual, par_aux,
					       indice);
			elimine_par = true;
		}
		par_aux = par_actual;
		par_actual = par_actual->siguiente;
	}
	return valor_eliminado;
}

void *hash_quitar(hash_t *hash, char *clave)
{
	if (hash == NULL || clave == NULL || hash->cantidad == 0) {
		return NULL;
	}
	size_t indice = funcion_hash(clave, hash->capacidad);
	par_t *par_actual = hash->pares[indice];
	if (par_actual == NULL) {
		return NULL;
	}
	void *valor_eliminado = eliminar_par(hash, clave, par_actual, indice);
	return valor_eliminado;
}

size_t hash_iterar(hash_t *hash, bool (*f)(char *, void *, void *), void *ctx)
{
	if (hash == NULL || f == NULL) {
		return 0;
	}
	size_t cantidad_iteraciones = 0;
	bool finalizar_iteracion = false;
	for (size_t i = 0; i < hash->capacidad && !finalizar_iteracion; i++) {
		par_t *par_actual = hash->pares[i];
		while (par_actual != NULL && !finalizar_iteracion) {
			if (!f(par_actual->clave, par_actual->valor, ctx)) {
				finalizar_iteracion = true;
			}
			cantidad_iteraciones++;
			par_actual = par_actual->siguiente;
		}
	}
	return cantidad_iteraciones;
}

// pre:	Obvio que el hash no es NULL y que I fue inicializado, NULL puede ser
// NULL en caso de no haber pedido memoria para un elemento.
// post:	Liberamos la clave y el elemento, y si el destructor pasado no es
// NULL tambien aplicamos el destructor. Pasar NULL si no tenemos un destructor
// o si no reservamos memoria para algun contenido.
void liberar_pares(hash_t *hash, void (*destructor)(void *), size_t i)
{
	par_t *par_actual = hash->pares[i];
	while (par_actual != NULL) {
		par_t *par_siguiente = par_actual->siguiente;
		if (destructor != NULL) {
			destructor(par_actual->valor);
		}
		free(par_actual->clave);
		free(par_actual);
		par_actual = par_siguiente;
	}
}

// pre:	El hash no puede ser NULL.
// post:	Vamos liberando los pares (aplicandoles o no el destructor), y
// luego liberamos el vector de pares y el struct del hash.
void destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (hash != NULL) {
		for (size_t i = 0; i < hash->capacidad; i++) {
			liberar_pares(hash, destructor, i);
		}
		free(hash->pares);
		free(hash->contador_pares);
		free(hash);
	}
}

void hash_destruir(hash_t *hash)
{
	if (hash != NULL) {
		destruir_todo(hash, NULL);
	}
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (hash != NULL) {
		destruir_todo(hash, destructor);
	}
}
