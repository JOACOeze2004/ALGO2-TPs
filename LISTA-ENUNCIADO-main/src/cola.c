#include "cola.h"
#include "lista.h"

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} Nodo;

struct lista {
	Nodo *nodo_inicio;
	Nodo *nodo_final;
	size_t cantidad;
};

struct cola {
	Lista *lista;
};

void inicializar_campos_nodo_cola(Nodo *nodo, void *cosa)
{
	nodo->siguiente = NULL;
	nodo->elemento = cosa;
}

Nodo *crear_nuevo_nodo_en_cola(void *cosa)
{
	Nodo *nodo = malloc(sizeof(Nodo));
	if (nodo == NULL) {
		return NULL;
	}
	inicializar_campos_nodo_cola(nodo, cosa);
	return nodo;
}

void inicializar_campos_cola(Cola *cola)
{
	cola->lista->nodo_inicio = NULL;
	cola->lista->nodo_final = NULL;
	cola->lista->cantidad = 0;
}

Cola *cola_crear()
{
	Cola *cola = malloc(sizeof(Cola));
	if (cola == NULL) {
		return NULL;
	}
	cola->lista = malloc(sizeof(Lista));
	if (cola->lista == NULL) {
		free(cola);
		return NULL;
	}
	inicializar_campos_cola(cola);
	return cola;
}

void liberar_nodos_en_cola(Lista *lista)
{
	Nodo *nodo_actual = lista->nodo_inicio;
	while (nodo_actual != NULL) {
		Nodo *nodo_siguiente = nodo_actual->siguiente;
		free(nodo_actual);
		nodo_actual = nodo_siguiente;
	}
}

void cola_destruir(Cola *cola)
{
	if (cola != NULL) {
		liberar_nodos_en_cola(cola->lista);
		free(cola->lista);
		free(cola);
	}
}

void liberar_nodos_y_elementos_en_cola(Lista *lista, void (*destructor)(void *))
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

void cola_destruir_todo(Cola *cola, void (*f)(void *))
{
	if (cola != NULL) {
		liberar_nodos_y_elementos_en_cola(cola->lista, f);
		free(cola->lista);
		free(cola);
	}
}

size_t cola_cantidad(Cola *cola)
{
	if (cola == NULL) {
		return 0;
	}
	return lista_cantidad_elementos(cola->lista);
}

void *cola_frente(Cola *cola)
{
	if (cola == NULL || cola->lista->nodo_inicio == NULL ||
	    cola->lista->cantidad == 0) {
		return NULL;
	}
	return cola->lista->nodo_inicio->elemento;
}

bool cola_encolar(Cola *cola, void *cosa)
{
	if (cola == NULL || cosa == NULL || cola->lista == NULL) {
		return false;
	}
	return lista_agregar_al_final(cola->lista, cosa);
}

void *cola_desencolar(Cola *cola)
{
	if (cola == NULL || cola->lista == NULL || cola->lista->cantidad == 0) {
		return NULL;
	}
	void *elemento_quitado = NULL;
	if (lista_quitar_elemento(cola->lista, 0, &elemento_quitado)) {
		return elemento_quitado;
	}
	return NULL;
}

bool cola_esta_vacía(Cola *cola)
{
	if (cola == NULL) {
		return NULL;
	}
	return cola->lista->cantidad == 0;
}