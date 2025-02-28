#include "pila.h"
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

struct pila {
	Lista *lista;
};

void inicializar_campos_nodo_pila(Nodo *nodo, void *cosa)
{
	nodo->siguiente = NULL;
	nodo->elemento = cosa;
}

Nodo *crear_nuevo_nodo_en_pila(void *cosa)
{
	Nodo *nodo = malloc(sizeof(Nodo));
	if (nodo == NULL) {
		return NULL;
	}
	inicializar_campos_nodo_pila(nodo, cosa);
	return nodo;
}

void inicializar_campos_pila(Pila *pila)
{
	pila->lista->nodo_inicio = NULL;
	pila->lista->nodo_final = NULL;
	pila->lista->cantidad = 0;
}

Pila *pila_crear()
{
	Pila *pila = malloc(sizeof(Pila));
	if (pila == NULL) {
		return NULL;
	}
	pila->lista = malloc(sizeof(Lista));
	if (pila->lista == NULL) {
		free(pila);
		return NULL;
	}
	inicializar_campos_pila(pila);
	return pila;
}

void liberar_nodos_en_pila(Pila *pila)
{
	Nodo *nodo_actual = pila->lista->nodo_inicio;
	while (nodo_actual != NULL) {
		Nodo *nodo_siguiente = nodo_actual->siguiente;
		free(nodo_actual);
		nodo_actual = nodo_siguiente;
	}
}

void pila_destruir(Pila *pila)
{
	if (pila != NULL) {
		liberar_nodos_en_pila(pila);
		free(pila->lista);
		free(pila);
	}
}

void liberar_nodos_y_elementos_en_pila(Lista *lista, void (*destructor)(void *))
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

void pila_destruir_todo(Pila *pila, void (*f)(void *))
{
	if (pila != NULL) {
		liberar_nodos_y_elementos_en_pila(pila->lista, f);
		free(pila->lista);
		free(pila);
	}
}

size_t pila_cantidad(Pila *pila)
{
	if (pila == NULL) {
		return 0;
	}
	return pila->lista->cantidad;
}

void *pila_tope(Pila *pila)
{
	if (pila == NULL || pila->lista->cantidad == 0 ||
	    pila->lista->nodo_inicio == NULL) {
		return NULL;
	}
	return pila->lista->nodo_inicio->elemento;
}

bool pila_apilar(Pila *pila, void *cosa)
{
	if (pila == NULL || cosa == NULL || pila->lista == NULL) {
		return false;
	}
	return lista_agregar_elemento(pila->lista, 0, cosa);
}

void *pila_desapilar(Pila *pila)
{
	if (pila == NULL || pila->lista == NULL || pila->lista->cantidad == 0) {
		return NULL;
	}
	void *elemento_quitado = NULL;
	if (lista_quitar_elemento(pila->lista, 0, &elemento_quitado)) {
		return elemento_quitado;
	}
	return NULL;
}

bool pila_esta_vacía(Pila *pila)
{
	if (pila == NULL) {
		return NULL;
	}
	return pila->lista->cantidad == 0;
}