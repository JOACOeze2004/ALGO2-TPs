#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    void* elemento;
    struct nodo* siguiente;
}Nodo;

//typedef struct nodo Nodo;

struct lista {
    Nodo* nodo_inicio;
    Nodo* nodo_final; //a ver si lo dejamos xq puede que ni lo usemos.
    size_t cantidad;
};


typedef struct lista_iterador {
    Nodo* nodo_actual_iterador;
}lista_iterador;

//pre:
//post:
void inicializar_campos_nodo(Nodo *nodo, void *cosa)
{
    nodo->siguiente = NULL;
    nodo->elemento = cosa;
}

Nodo *crear_nuevo_nodo(void* cosa)
{
    Nodo *nodo = malloc(sizeof(Nodo));
    if (nodo == NULL )
    {
        return NULL;
    }
    inicializar_campos_nodo(nodo, cosa);
    return nodo;
}

//pre:
//post:
void inicializar_campos_lista(Lista *lista)
{
    lista->cantidad = 0;
    lista->nodo_inicio = NULL;
    lista->nodo_final = NULL;
}

Lista *lista_crear(){
    Lista *lista  = malloc(sizeof(Lista));
    if (lista == NULL)
    {
        return NULL;
    }
    inicializar_campos_lista(lista);
    return lista;    
}

//pre:
//post:
void liberar_nodos(Lista * lista)
{
    Nodo *nodo_actual = lista->nodo_inicio;
    while (nodo_actual != NULL)
    {
        Nodo *nodo_siguiente = nodo_actual->siguiente;
        free(nodo_actual);
        nodo_actual= nodo_siguiente;
    }
}

void lista_destruir(Lista * lista){
    if (lista != NULL)
    {
        liberar_nodos(lista);
        free(lista);
    }
}

void destructor(void* elemento)
{
    free (elemento);
}

void liberar_nodos_y_elementos(Lista *lista, void (*destructor)(void *))
{
    Nodo *nodo_actual = lista->nodo_inicio;
    while (nodo_actual != NULL)
    {
        Nodo *nodo_siguiente = nodo_actual->siguiente;
        if (destructor != NULL)
        {
            destructor(nodo_actual->elemento);
        }
        free(nodo_actual);
        nodo_actual= nodo_siguiente;
    }
}

void lista_destruir_todo(Lista *lista, void (*destructor)(void *)){
    if (lista != NULL)
    {
        liberar_nodos_y_elementos(lista,destructor);
        free(lista);
    }  
}

size_t lista_cantidad_elementos(Lista *lista){
    if (lista == NULL){
        return 0;
    }
    return lista->cantidad;    
}

//pre:
//post:
void agregar_al_inicio(Lista *lista, Nodo * nodo_nuevo)
{
    nodo_nuevo->siguiente = lista->nodo_inicio;
    lista->nodo_inicio = nodo_nuevo;
}

//pre:
//post:
void agregar_en_posicion_intermedia(Lista *lista, size_t posicion, Nodo *nodo_nuevo)
{
    Nodo *nodo_anterior = lista->nodo_inicio;
    for (size_t i = 0; i < posicion - 1; i++)
    {
        nodo_anterior = nodo_anterior->siguiente; 
    }
    nodo_nuevo->siguiente = nodo_anterior->siguiente;
    nodo_anterior->siguiente = nodo_nuevo;    
}


bool lista_agregar_elemento(Lista *lista, size_t posicion, void *cosa){
    if (posicion > lista->cantidad || lista == NULL || cosa == NULL){
        return false;
    }
    Nodo *nodo_nuevo = crear_nuevo_nodo(cosa);
    if (nodo_nuevo == NULL)
    {
        return NULL;
    }
    nodo_nuevo->elemento = cosa;    
    if (posicion == 0){
        agregar_al_inicio(lista,nodo_nuevo);
    }
    else{
        agregar_en_posicion_intermedia(lista,posicion,nodo_nuevo);
    }
    (lista->cantidad)++; 
    return true;  
}

//pre:
//post:
void inicializar_lista_con_nodo(Lista *lista, Nodo *nodo_nuevo){
    lista->nodo_inicio = nodo_nuevo;
    lista->nodo_final = nodo_nuevo;
}

//pre:
//post:
void agregar_nodo_al_final(Lista *lista, Nodo *nodo_nuevo){
    lista->nodo_final->siguiente = nodo_nuevo;
    lista->nodo_final = nodo_nuevo;
}

bool lista_agregar_al_final(Lista *lista, void *cosa){    
    if (lista == NULL || cosa == NULL)
    {
        return false;
    }
    Nodo *nodo_nuevo = crear_nuevo_nodo(cosa);
    if (nodo_nuevo == NULL)
    {
        return false;
    }
    if (lista->cantidad == 0){
        inicializar_lista_con_nodo(lista,nodo_nuevo);
    }else{
        agregar_nodo_al_final(lista,nodo_nuevo);
    }
    (lista->cantidad)++;
    return true;
}

// void eliminar_en_inicio(Lista *lista)
// {
//     Nodo *nodo_aux;
//     nodo_aux = lista->nodo_inicio;
//     lista->nodo_inicio = nodo_aux->siguiente;
// }

// void eliminar_en_intermedio(Lista *lista,size_t posicion ,Nodo *nodo_anterior)
// {
//     Nodo *nodo_aux;
//     nodo_anterior = lista->nodo_inicio;
//     for (size_t i = 1; i < posicion; i++) {
//         nodo_anterior = nodo_anterior->siguiente;
//     }
//     nodo_aux =nodo_anterior->siguiente;
//     nodo_anterior->siguiente = nodo_aux->siguiente;  
// }

bool lista_quitar_elemento(Lista *lista, size_t posicion,void **elemento_quitado){
    if (lista == NULL || posicion > lista->cantidad || lista->cantidad == 0)    //corregir si elemento quitado no puede ser null y deveria devolver false.
    {
        return false;
    }
    Nodo *nodo_aux;
    Nodo *nodo_anterior = NULL;
    if (posicion == 0)
    {
       nodo_aux = lista->nodo_inicio;
       lista->nodo_inicio = nodo_aux->siguiente;
    }   
    else{
        nodo_anterior = lista->nodo_inicio;
        for (size_t i = 1; i < posicion; i++) {
            nodo_anterior = nodo_anterior->siguiente;
        }
        nodo_aux = nodo_anterior->siguiente;
        nodo_anterior->siguiente = nodo_aux->siguiente;      
    }
    if (elemento_quitado != NULL)
    {
        *elemento_quitado = nodo_aux->elemento;
    }
    free(nodo_aux);
    (lista->cantidad)--;    
    return true;    
}

void *lista_buscar_elemento(Lista *lista, void *buscado, int (*comparador)(void *, void *)){
    if (lista == NULL || buscado == NULL || comparador == NULL || lista->cantidad == 0)
    {
        return NULL;
    }
    bool encontre_elemento = false;
    Nodo *nodo_actual = lista->nodo_inicio;
    Nodo *elemento_buscado;
    while ( nodo_actual != NULL && !encontre_elemento)
    {
        if (comparador(buscado,nodo_actual->elemento) == 0)
        {
            elemento_buscado = nodo_actual;
            encontre_elemento = true;
        }
        nodo_actual = nodo_actual->siguiente;   
    }
    if (encontre_elemento)
    {
        return elemento_buscado->elemento;
    }
    return NULL;    
}

//pre:
//post:
Nodo *obtener_el_nodo_en_posicion(Lista *lista, size_t posicion)
{
    Nodo *nodo_actual = lista->nodo_inicio;
    for (size_t i = 0; i < posicion; i++)
    {
        nodo_actual = nodo_actual->siguiente;   
    }
    return nodo_actual;
}

bool lista_obtener_elemento(Lista *lista, size_t posicion, void **elemento_encontrado){
    if (lista == NULL || posicion > lista->cantidad || lista->cantidad == 0) 
    {
        return false;
    }
    Nodo *nodo_actual = obtener_el_nodo_en_posicion(lista,posicion);
    if (elemento_encontrado != NULL)
    {
        *elemento_encontrado = nodo_actual->elemento;
    }
    
    return true;
}

size_t lista_iterar_elementos(Lista *lista, bool (*f)(void *, void *), void *ctx){  //Si me cagan a pedos en el tp1 q podria modularizar, modulariza.
    if (lista == NULL)
    {
        return 0;
    }
   	size_t cantidad_iterada = 0;
	bool finalizar_iteracion = false;
    Nodo *nodo_actual = lista->nodo_inicio;
    while ( nodo_actual != NULL && !finalizar_iteracion)
    {
        bool continuar_iteracion = f(nodo_actual->elemento,ctx);
        if (!continuar_iteracion)
        {
            finalizar_iteracion = true;
        }
        cantidad_iterada++;
		nodo_actual = nodo_actual->siguiente;
    }
    return cantidad_iterada;    
}

Lista_iterador *lista_iterador_crear(Lista *lista){
    if (lista == NULL)
    {
        return NULL;
    }
    Lista_iterador* iterador_externo = malloc(sizeof(Lista_iterador));
    if (iterador_externo == NULL)
    {
        return NULL;
    }
    iterador_externo->nodo_actual_iterador = lista->nodo_inicio;
    return iterador_externo;
}

bool lista_iterador_hay_siguiente(Lista_iterador *iterador_externo){
    return iterador_externo != NULL && iterador_externo->nodo_actual_iterador != NULL && iterador_externo->nodo_actual_iterador->siguiente != NULL;
}


void lista_iterador_avanzar(Lista_iterador *iterador_externo){
    if (lista_iterador_hay_siguiente(iterador_externo))
    {
        iterador_externo->nodo_actual_iterador = iterador_externo->nodo_actual_iterador->siguiente;
    }
}

void *lista_iterador_obtener_elemento_actual(Lista_iterador *iterador_externo){
    if (iterador_externo != NULL && iterador_externo->nodo_actual_iterador != NULL)
    {
        return iterador_externo->nodo_actual_iterador->elemento;
    }
    return NULL;  
}

void lista_iterador_destruir(Lista_iterador * iterador_externo){
    if (iterador_externo != NULL)
    {
        free(iterador_externo); 
    }    
}