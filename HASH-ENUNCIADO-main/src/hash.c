#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FACTOR_CARGA_MAX 0.75
#define CAPACIDAD_BORDE 3

typedef struct par par_t;

struct par{
    char *clave;
    void* valor;
    par_t *siguiente;
};

struct hash{
    par_t **pares;
    size_t capacidad;
    size_t cantidad;
};

/*
Reeveer despues funcion hash
*/

size_t funcion_hash(const char *clave, size_t capacidad) {
    size_t hash_posicion = 0;
    size_t i = 0;
    while (clave[i] != '\0') {
        hash_posicion = (hash_posicion * 31 + (unsigned char)clave[i]) % capacidad;
        i++;
    }
    return hash_posicion; 
}


par_t *crear_nuevo_par(char* clave,void *contenido)
{
	par_t *nodo = calloc(1,sizeof(par_t));
	if (nodo == NULL) {
		return NULL;
	}
    nodo->clave = calloc(1,strlen(clave)+1);
    if (nodo->clave == NULL){
        free(nodo);
        return NULL;
    }
    strcpy(nodo->clave,clave);
    nodo->valor = contenido;
	return nodo;
}

hash_t* hash_crear(size_t capacidad_inicial)
{
    size_t cap_inicial_max = capacidad_inicial < CAPACIDAD_BORDE ? CAPACIDAD_BORDE : capacidad_inicial;
    hash_t *hash =  calloc(1,sizeof(hash_t));
    if (hash == NULL){
        return NULL;
    }
    hash->pares = calloc(cap_inicial_max,sizeof(par_t));
    hash->capacidad = cap_inicial_max;
    if (hash->pares == NULL)
    {
        free(hash);
        return NULL;
    }
    return hash;
}


size_t hash_cantidad(hash_t* hash){
    return hash == NULL ? 0 : hash->cantidad;
}

//insertar/agregar
/**
 *
 * Inserta un elemento asociado a la clave en la tabla de hash.
 *
 * Si la clave ya existe en la tabla, modificamos el valor y ponemos el nuevo.
 * Si encontrado no es NULL, se almacena el elemento reemplazado en el mismo.
 *
 * Esta funcion almacena una copia de la clave.
 *
 * No se admiten claves nulas.
 *
 * Devuelve true si se pudo almacenar el valor.
 **/
bool hash_insertar(hash_t* hash, char* clave, void* valor, void** encontrado){
    if (hash == NULL || clave == NULL ){
        return false;
    }
    if (encontrado != NULL){
        *encontrado = NULL;
    }
    if ((float)hash->cantidad / (float)hash->capacidad >= FACTOR_CARGA_MAX)
    {
        //hash = rehash(hash);
    }
    size_t indice_hash = funcion_hash(clave,hash->capacidad);
    par_t *pos_actual = hash->pares[indice_hash];
    bool clave_repetida_insertada = false;
    while (pos_actual != NULL && !clave_repetida_insertada){
        if (strcmp(clave,pos_actual->clave) == 0){
            if (encontrado != NULL){
                *encontrado = pos_actual->valor;
            }
            pos_actual->valor = valor;
            clave_repetida_insertada = true;
        }
        pos_actual = pos_actual->siguiente;        
    }
    
    if (!clave_repetida_insertada){
        par_t *par_nuevo = crear_nuevo_par(clave,valor);
        if (par_nuevo == NULL){
            return false;
        }
        par_nuevo->siguiente = hash->pares[indice_hash];
        hash->pares[indice_hash] = par_nuevo;
        hash->cantidad++;
    } 
    return true;
}

par_t *dict_buscar_par(hash_t *hash,char *clave){ 
    size_t indice = funcion_hash(clave,hash->capacidad);
    par_t *par_actual  =  hash->pares[indice];
    bool clave_encontrada = false;
    void* elemento = NULL;
    while (par_actual != NULL && !clave_encontrada){
        if (strcmp(clave,par_actual->clave)== 0){
            elemento = par_actual;
            clave_encontrada = true;
        }
        par_actual = par_actual->siguiente;      
    }
    return elemento;
}

void* hash_buscar(hash_t* hash, char* clave){
    if (hash == NULL || clave == NULL || hash->cantidad == 0){
        return NULL;
    }
    par_t *par = dict_buscar_par(hash,clave);
    return par ? par->valor : NULL; 
}

bool hash_contiene(hash_t* hash, char* clave){
    return (hash_buscar(hash,clave) != NULL || hash != NULL || clave != NULL) ? true : false;
}

/**
 * Quita el elemento asociado a la clave de la tabla y lo devuelve.
 */
//void* hash_quitar(hash_t* hash, char* clave);

/**
 * Itera cada elemento del hash y aplica la función f.
 *
 * La iteración se corta al completar el total de elementos o cuando la función devuelve false.
 *
 * Devuelve la cantidad de veces que se aplica la función.
 */
//size_t hash_iterar(hash_t* hash, bool (*f)(char*, void*, void*), void* ctx);

void destruir_todo(hash_t *hash,  void (*destructor)(void *)){
    if (hash != NULL)
    {
        for (size_t i = 0; i < hash->capacidad; i++){
            par_t *par_actual = hash->pares[i];
            while (par_actual != NULL){
                par_t *par_a_eliminar = par_actual;
                par_actual = par_actual->siguiente;
                if (destructor != NULL){
                    destructor(par_a_eliminar);  
                }
                free(par_a_eliminar->clave);
                free(par_a_eliminar);
            }
        }
        free(hash->pares);
        free(hash);
    } 
}

void hash_destruir(hash_t* hash){
    if (hash != NULL){
        destruir_todo(hash,NULL);
    }
}

void hash_destruir_todo(hash_t* hash, void (*destructor)(void*)){
    if (hash != NULL && destructor != NULL){
        destruir_todo(hash,destructor);
    }
}