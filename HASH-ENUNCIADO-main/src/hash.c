#include "hash.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define FACTOR_CARGA_MAX 0.75
#define CAPACIDAD_BORDE 3
#define FACTOR_CRECIMIENTO 2

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
        hash_posicion = (hash_posicion * 73 + (unsigned char)clave[i]) % capacidad;
        i++;
    }
    //printf("valor hash:%zu\n",hash_posicion);
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

bool agregar_par(hash_t* hash, char* clave, void* valor, void** encontrado){
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

hash_t *rehash(hash_t *hash){
    par_t **tabla_vieja = hash->pares;
    hash->capacidad *= FACTOR_CRECIMIENTO; 
    hash->pares = calloc(hash->capacidad,sizeof(par_t));
    if (hash->pares == NULL){
        return NULL;
    }
    hash->cantidad = 0;
    for (size_t i = 0; i < hash->capacidad; i++){
        par_t *par_actual = tabla_vieja[i];
        while (par_actual != NULL){
            par_t *par_aux = par_actual->siguiente;
            agregar_par(hash,par_actual->clave,par_actual->valor,NULL);
            free(par_actual->clave);
            free(par_actual);
            par_actual = par_aux;
        }        
    }
    free(tabla_vieja);
    return hash;
}

size_t hash_cantidad(hash_t* hash){
    return hash == NULL ? 0 : hash->cantidad;
}

bool hash_insertar(hash_t* hash, char* clave, void* valor, void** encontrado){
    if (hash == NULL || clave == NULL ){
        return false;
    }
    if (encontrado != NULL){
        *encontrado = NULL;
    }
    if ((float)hash->cantidad / (float)hash->capacidad >= FACTOR_CARGA_MAX)
    {
        printf("capacidad a modificar:%zu\n",hash->capacidad);
        if (rehash(hash) == NULL)
        {
            return false;
        }
        hash = rehash(hash);
        printf("capacidad actual:%zu\n",hash->capacidad);
    }
    if (!agregar_par(hash,clave,valor,encontrado)){
        return false;
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
void* hash_quitar(hash_t* hash, char* clave){
    if (hash == NULL || clave == NULL || hash->cantidad == 0){
        return NULL;
    }
    size_t indice = funcion_hash(clave,hash->capacidad);
    par_t *par_actual = hash->pares[indice];
    if (par_actual == NULL){
        return NULL;
    }
    void *encontrado = NULL;
    bool elimine_par = false;
    par_t *par_aux = NULL;
    while (par_actual != NULL && !elimine_par){
        if (strcmp(par_actual->clave,clave) == 0){
            encontrado = par_actual->valor;
            if (par_aux == NULL){
                hash->pares[indice]= par_actual->siguiente;
            }else{
                par_aux->siguiente = par_actual->siguiente;
            }
            free(par_actual->clave);
            free(par_actual);
            hash->cantidad--;
            elimine_par = true;
        }
        par_aux = par_actual;
        par_actual = par_actual->siguiente;
    }
    return encontrado;
}


size_t hash_iterar(hash_t* hash, bool (*f)(char*, void*, void*), void* ctx){
    if (hash == NULL ){
        return 0;
    }
    size_t cantidad_iteraciones = 0;
    bool finalizar_iteracion = false;
    for (size_t i = 0; i < hash->capacidad && !finalizar_iteracion; i++){
        par_t *par_actual = hash->pares[i];
        while (par_actual != NULL && !finalizar_iteracion){
            if (!f(par_actual->clave,par_actual->valor,ctx))
            {
                finalizar_iteracion = true;
            }
            cantidad_iteraciones++;
            par_actual = par_actual->siguiente;
        }        
    }
    return cantidad_iteraciones;
}

void destruir_todo(hash_t *hash,  void (*destructor)(void *)){
    if (hash != NULL){
        for (size_t i = 0; i < hash->capacidad; i++){
            par_t *par_actual = hash->pares[i];
            while (par_actual != NULL){
                par_t *par_siguiente = par_actual->siguiente;
                if (destructor != NULL){
                    destructor(par_actual);  
                }
                free(par_actual->clave);
                free(par_actual);
                par_actual = par_siguiente;
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