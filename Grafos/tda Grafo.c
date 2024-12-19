#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    hash_t* vertices;
}grafo_t;

typedef struct{
    char* nombre; //Clave del vertice en el diccionario del grafo.
    hash_t* aristas_entrantes;
    hash_t* aristas_salientes;
}vertice_t;

// las arista_t van dentro de los hash del vertice
typedef struct{
    vertice_t* origen; //el nombre del vertice de destino seria la clave en los hash de aristas entrantes
    vertice_t* destino; //el nombre del vertice de destino seria la clave en los hash de aristas salientes
    int peso;
}arista_t;


grafo_t* grafo_crear() {
    grafo_t* grafo = malloc(sizeof(grafo_t));
    if (!grafo) return NULL;
    grafo->vertices = hash_crear(5); // Crear el hash vacío para los vértices.
    if (!grafo->vertices) {
        free(grafo);
        return NULL;
    }
    return grafo;
}

bool grafo_insertar(grafo_t* grafo, char* nombre_vertice) {
    if (!grafo || !nombre_vertice) return false;

    vertice_t* vertice = malloc(sizeof(vertice_t));
    if (!vertice) return false;

    vertice->nombre = nombre_vertice; // Guardamos directamente el puntero.
    vertice->aristas_entrantes = hash_crear(0);
    vertice->aristas_salientes = hash_crear(0);

    if (!vertice->aristas_entrantes || !vertice->aristas_salientes) {
        hash_destruir(vertice->aristas_entrantes);
        hash_destruir(vertice->aristas_salientes);
        free(vertice);
        return false;
    }

    return hash_insertar(grafo->vertices, nombre_vertice, vertice, NULL);
}


bool grafo_insertar_arista(grafo_t* grafo, char* origen, char* destino, int peso) {
    if (!grafo || !origen || !destino) return false;

    vertice_t* vertice_origen = hash_buscar(grafo->vertices, origen);
    vertice_t* vertice_destino = hash_buscar(grafo->vertices, destino);
    if (!vertice_origen || !vertice_destino) return false; // Ambos vértices deben existir.

    arista_t* arista = malloc(sizeof(arista_t));
    if (!arista) return false;

    arista->origen = vertice_origen;
    arista->destino = vertice_destino;
    arista->peso = peso;

    if (!hash_insertar(vertice_origen->aristas_salientes, destino, arista,NULL) ||
        !hash_insertar(vertice_destino->aristas_entrantes, origen, arista,NULL)) {
        free(arista);
        return false;
    }
    return true;
}


bool grafo_borrar_arista(grafo_t* grafo, char* origen, char* destino) {
    if (!grafo || !origen || !destino) return false;

    vertice_t* vertice_origen = hash_buscar(grafo->vertices, origen);
    vertice_t* vertice_destino = hash_buscar(grafo->vertices, destino);
    if (!vertice_origen || !vertice_destino) return false;

    // Obtener y liberar la arista.
    arista_t* arista = hash_quitar(vertice_origen->aristas_salientes, destino);
    hash_quitar(vertice_destino->aristas_entrantes, origen);
    if (!arista) return false;

    free(arista);
    return true;
}


void grafo_destruir(grafo_t* grafo) {
    if (!grafo) return;

    hash_destruir(grafo->vertices);
    free(grafo);
}