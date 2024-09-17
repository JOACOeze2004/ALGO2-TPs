#include "pila.h"
#include "lista.h"

typedef struct nodo{
    void* elemento;
    struct nodo* siguiente;
}Nodo;

struct lista {
    Nodo* nodo_inicio;
    Nodo* nodo_final;
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

Nodo *crear_nuevo_nodo_en_pila(void* cosa)
{
    Nodo *nodo = malloc(sizeof(Nodo));
    if (nodo == NULL )
    {
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
    if (pila == NULL)
    {
        return NULL;
    }
    pila->lista = malloc(sizeof(Lista));
    if (pila->lista == NULL)
    {
        free(pila);
        return NULL;
    }
    inicializar_campos_pila(pila);
    return pila;    
}

void liberar_nodos_en_pila(Pila * pila)
{
    Nodo *nodo_actual = pila->lista->nodo_inicio;
    while (nodo_actual != NULL)
    {
        Nodo *nodo_siguiente = nodo_actual->siguiente;
        free(nodo_actual);
        nodo_actual= nodo_siguiente;
    }
}


void pila_destruir(Pila *pila)
{
    if (pila != NULL)
    {
        liberar_nodos_en_pila(pila);
        free(pila->lista);
        free(pila);
    }
}
// void pila_destruir_todo(Pila *pila, void (*f)(void *));

// //cada una de estas funciones es O(1)
size_t pila_cantidad(Pila *pila)
{
    if (pila == NULL)
    {
        return 0;
    }
    return pila->lista->cantidad;    
}

void *pila_tope(Pila *pila)
{
    if (pila == NULL)
    {
        return NULL;
    } 
    return pila->lista->nodo_final->elemento;
}

bool pila_apilar(Pila *pila, void *cosa)
{
    if (pila == NULL || cosa == NULL || pila->lista == NULL)
    {
        return false;
    }
    return lista_agregar_al_final(pila->lista,cosa);
}

void *pila_desapilar(Pila *pila)
{
    void* elemento_quitado = NULL;
    if (lista_quitar_elemento(pila->lista,pila->lista->cantidad - 1,&elemento_quitado))
    {
        return elemento_quitado;
    }
    return NULL;
}

bool pila_esta_vacía(Pila *pila)
{
    return pila->lista->cantidad == 0;
}