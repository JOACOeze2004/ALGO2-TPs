#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} Nodo;

struct lista {
	Nodo *nodo_inicio;
	Nodo *nodo_final;
	size_t cantidad;
};

typedef struct lista_iterador {
	Nodo *nodo_actual_iterador;
} lista_iterador;

//pre:  Ya se asume que los punteros fueron validados antes de ser usados en esta funcion.
//post: Inicializa los campos del struct nodo de siguiente como null y a elemento como cosa.
void inicializar_campos_nodo(Nodo *nodo, void *cosa)
{
	nodo->siguiente = NULL;
	nodo->elemento = cosa;
}

Nodo *crear_nuevo_nodo(void *cosa)
{
	Nodo *nodo = malloc(sizeof(Nodo));
	if (nodo == NULL) {
		return NULL;
	}
	inicializar_campos_nodo(nodo, cosa);
	return nodo;
}

//pre:  Se asume que el puntero a lista ya fue validado antes de invocarse a esta funcion.
//post: Inicializa la cantidad como 0, y el puntero a nodo inicio y fin como NULL (ya que al estar vacia serian ambos el "fin" de la lista enlazada).
void inicializar_campos_lista(Lista *lista)
{
	lista->cantidad = 0;
	lista->nodo_inicio = NULL;
	lista->nodo_final = NULL;
}

Lista *lista_crear()
{
	Lista *lista = malloc(sizeof(Lista));
	if (lista == NULL) {
		return NULL;
	}
	inicializar_campos_lista(lista);
	return lista;
}

//pre:  Se asume que al menos se reservo memoria para 1 nodo, la lista no es NULL (o se atajo eso antes de llamarse  al funcion) y que el nodo final apunte a NULL.
//post:  libera la memoria que se fue pidiendo para cada nodo y avanza al siguiente nodo, hasta que llega a que el nodo actul sea == NULL (que seria que llega al final).
void liberar_nodos(Lista *lista)
{
	Nodo *nodo_actual = lista->nodo_inicio;
	while (nodo_actual != NULL) {
		Nodo *nodo_siguiente = nodo_actual->siguiente;
		free(nodo_actual);
		nodo_actual = nodo_siguiente;
	}
}

void lista_destruir(Lista *lista)
{
	if (lista != NULL) {
		liberar_nodos(lista);
		free(lista);
	}
}

//pre: se asume que el puntero a lista no va a ser NULL igual que con la funcion destructora.
//post: HAce exactamente lo mismo que liberar_nodos pero va aplica la funcion destructora a los elementos que hay en los nodos (util para el main que reservas memoria para cada elemento del archivo).
void liberar_nodos_y_elementos(Lista *lista, void (*destructor)(void *))
{
	Nodo *nodo_actual = lista->nodo_inicio;
	while (nodo_actual != NULL) {
		Nodo *nodo_siguiente = nodo_actual->siguiente;
		if (destructor != NULL) {
			destructor(nodo_actual->elemento);
		}
		free(nodo_actual);
		nodo_actual = nodo_siguiente;
	}
}

void lista_destruir_todo(Lista *lista, void (*destructor)(void *))
{
	if (lista != NULL) {
		liberar_nodos_y_elementos(lista, destructor);
		free(lista);
	}
}

size_t lista_cantidad_elementos(Lista *lista)
{
	if (lista == NULL) {
		return 0;
	}
	return lista->cantidad;
}

//pre:  Los punteros recibidos deberian haber sido atajados antes de llamr a esta funcion.
//post: Setea al siguiente del nuevo nodo como el nodo inicio y al puntero de inicio de la lista como al nuevo nodo agregado.
void agregar_al_inicio(Lista *lista, Nodo *nodo_nuevo)
{
	nodo_nuevo->siguiente = lista->nodo_inicio;
	lista->nodo_inicio = nodo_nuevo;
}

//pre:  Se asume que los punteros recibidos ya fueron validados, y que la posicon no esta mas alla de la cantidad que hay.
//post: Recorremos los nodos hasta la posicon que queremos agregar, inserto el nuevo nodo despues del nodo en la posicion que estabamos.
void agregar_en_posicion_intermedia(Lista *lista, size_t posicion,
				    Nodo *nodo_nuevo)
{
	Nodo *nodo_anterior = lista->nodo_inicio;
	for (size_t i = 0; i < posicion - 1; i++) {
		nodo_anterior = nodo_anterior->siguiente;
	}
	nodo_nuevo->siguiente = nodo_anterior->siguiente;
	nodo_anterior->siguiente = nodo_nuevo;
}

bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa)
{
	if (posicion > lista->cantidad || lista == NULL || cosa == NULL) {
		return false;
	}
	Nodo *nodo_nuevo = crear_nuevo_nodo(cosa);
	if (nodo_nuevo == NULL) {
		return NULL;
	}
	nodo_nuevo->elemento = cosa;
	if (posicion == 0) {
		agregar_al_inicio(lista, nodo_nuevo);
	} else {
		agregar_en_posicion_intermedia(lista, posicion, nodo_nuevo);
	}
	(lista->cantidad)++;
	return true;
}

//pre:  Se asume que los punteros ya fueron validados antes de llamr a esta funcion.
//post: Es basicamente un agregar al final pero el caso borde donde no haya ningun nodo, entones el nodo final e inicial apuntarian al nodo nuevo y ell siguiente de ese neuvo nodo seria NULL (para marcar el final de la lista).
void inicializar_lista_con_nodo(Lista *lista, Nodo *nodo_nuevo)
{
	lista->nodo_inicio = nodo_nuevo;
	lista->nodo_final = nodo_nuevo;
	nodo_nuevo->siguiente = NULL;
}

//pre:  Se asume que la lista y el nuevo nodo no son NULL, ademas de que esta seteado al puntero nodo_final como null (sino no funciona agregar).
//post: Al siguiente del puntero nodo_final, apuntaria a nodo_nuevo, el puntero a nodo_final apunta al nuevo nodo que esta al final y el siguiente de este nuevo nodo, apunta a NULL (marcando el final de la lista).
void agregar_nodo_al_final(Lista *lista, Nodo *nodo_nuevo)
{
	if (lista->nodo_final != NULL) {
		lista->nodo_final->siguiente = nodo_nuevo;
		lista->nodo_final = nodo_nuevo;
		nodo_nuevo->siguiente = NULL;
	}
}

bool lista_agregar_al_final(Lista *lista, void *cosa)
{
	if (lista == NULL || cosa == NULL) {
		return false;
	}
	Nodo *nodo_nuevo = crear_nuevo_nodo(cosa);
	if (nodo_nuevo == NULL) {
		return false;
	}
	if (lista->cantidad == 0) {
		inicializar_lista_con_nodo(lista, nodo_nuevo);
	} else {
		agregar_nodo_al_final(lista, nodo_nuevo);
	}
	(lista->cantidad)++;
	return true;
}

//pre:  Los punteros recibidos obvio que ya fueron atajados. Ademas deberian pasar una posicion que no exceda la maxima la cantidad de elemento que hay en la lista.
//post: Basicamente, recorremos la lista hasta llegar a la posicion -1 a eliminar, en nodo aux, nos guardamos el siguiente del nodo en al posicon actual. y el siguiente al anterior va a ser igual al siguiente de aux.
Nodo *lista_quitar_nodo_en_posicion(Lista *lista, size_t posicion)
{
	Nodo *nodo_anterior = lista->nodo_inicio;
	for (size_t i = 1; i < posicion; i++) {
		nodo_anterior = nodo_anterior->siguiente;
	}
	Nodo *nodo_aux = nodo_anterior->siguiente;
	nodo_anterior->siguiente = nodo_aux->siguiente;
	return nodo_aux;
}

//pre:  Obvio que si queremos guardar el elemento quitado, este no debe ser NULL (sino no lo retorna)ademad de que nodo aux, ya deberia haberse validado antes.
//post: si elemento_quitado no es NULL, me guardo el elemento en aux que recibimos en la funcion.
void setear_elemento_quitado(void **elemento_quitado, Nodo *nodo_aux)
{
	if (elemento_quitado != NULL) {
		*elemento_quitado = nodo_aux->elemento;
	}
}

//pre:  los punteros deben ser validos. Y se debe haber seteado al nodo aux asi no hacemos un invalid free.
//post: Liberamos el nodo a eliminar (nodo aux en nuestro caso) y decrementamos la cantidad de elementos en la lista.
void liberar_nodo_y_decrementar_cantidad(Lista *lista, Nodo *nodo_aux)
{
	free(nodo_aux);
	(lista->cantidad)--;
}

bool lista_quitar_elemento(Lista *lista, size_t posicion,
			   void **elemento_quitado)
{
	if (lista == NULL || posicion >= lista->cantidad ||
	    lista->cantidad ==
		    0) //corregir si elemento quitado no puede ser null y deveria devolver false.
	{
		return false;
	}
	Nodo *nodo_aux;
	if (posicion == 0) {
		nodo_aux = lista->nodo_inicio;
		lista->nodo_inicio = nodo_aux->siguiente;
	} else {
		nodo_aux = lista_quitar_nodo_en_posicion(lista, posicion);
	}
	setear_elemento_quitado(elemento_quitado, nodo_aux);
	liberar_nodo_y_decrementar_cantidad(lista, nodo_aux);
	return true;
}

void *lista_buscar_elemento(Lista *lista, void *buscado,
			    int (*comparador)(void *, void *))
{
	if (lista == NULL || buscado == NULL || comparador == NULL ||
	    lista->cantidad == 0) {
		return NULL;
	}
	if (comparador(buscado, lista->nodo_inicio->elemento) == 0) {
    	return lista->nodo_inicio->elemento;
	}
	bool encontre_elemento = false;
	Nodo *nodo_actual = lista->nodo_inicio;
	Nodo *elemento_buscado;
	while (nodo_actual != NULL && !encontre_elemento) {
		if (comparador(buscado, nodo_actual->elemento) == 0) {
			elemento_buscado = nodo_actual;
			encontre_elemento = true;
		}
		nodo_actual = nodo_actual->siguiente;
	}
	if (encontre_elemento) {
		return elemento_buscado->elemento;
	}
	return NULL;
}

//pre:  El puntero a lista deberia ser valido. Ademas de que de nuevo, la posicion no debe exceder la cantidad de elementos en la lista.
//post: devuelve el nodo en la posicion que le pasamos.
Nodo *obtener_el_nodo_en_posicion(Lista *lista, size_t posicion)
{
	Nodo *nodo_actual = lista->nodo_inicio;
	for (size_t i = 0; i < posicion; i++) {
		nodo_actual = nodo_actual->siguiente;
	}
	return nodo_actual;
}

bool lista_obtener_elemento(Lista *lista, size_t posicion,
			    void **elemento_encontrado)
{
	if (lista == NULL || posicion >= lista->cantidad ||
	    lista->cantidad == 0) {
		return false;
	}	
	Nodo *nodo_actual = obtener_el_nodo_en_posicion(lista, posicion);
	if (elemento_encontrado != NULL) {
		*elemento_encontrado = nodo_actual->elemento;
	}
	return true;
}

size_t lista_iterar_elementos(Lista *lista, bool (*f)(void *, void *),
			      void *ctx)
{
	if (lista == NULL) {
		return 0;
	}
	size_t cantidad_iterada = 0;
	bool finalizar_iteracion = false;
	Nodo *nodo_actual = lista->nodo_inicio;
	while (nodo_actual != NULL && !finalizar_iteracion) {
		bool continuar_iteracion = f(nodo_actual->elemento, ctx);
		if (!continuar_iteracion) {
			finalizar_iteracion = true;
		}
		cantidad_iterada++;
		nodo_actual = nodo_actual->siguiente;
	}
	return cantidad_iterada;
}

Lista_iterador *lista_iterador_crear(Lista *lista)
{
	if (lista == NULL) {
		return NULL;
	}
	Lista_iterador *iterador_externo = malloc(sizeof(Lista_iterador));
	if (iterador_externo == NULL) {
		return NULL;
	}
	iterador_externo->nodo_actual_iterador = lista->nodo_inicio;
	return iterador_externo;
}

bool lista_iterador_hay_siguiente(Lista_iterador *iterador_externo)
{
	return iterador_externo != NULL &&
	       iterador_externo->nodo_actual_iterador != NULL &&
	       iterador_externo->nodo_actual_iterador->siguiente != NULL;
}

void lista_iterador_avanzar(Lista_iterador *iterador_externo)
{
	if (lista_iterador_hay_siguiente(iterador_externo)) {
		iterador_externo->nodo_actual_iterador =
			iterador_externo->nodo_actual_iterador->siguiente;
	}
}

void *lista_iterador_obtener_elemento_actual(Lista_iterador *iterador_externo)
{
	if (iterador_externo != NULL &&
	    iterador_externo->nodo_actual_iterador != NULL) {
		return iterador_externo->nodo_actual_iterador->elemento;
	}
	return NULL;
}

void lista_iterador_destruir(Lista_iterador *iterador_externo)
{
	if (iterador_externo != NULL) {
		free(iterador_externo);
	}
}