#include "hash.h"
#include <stdlib.h>

#define FACTOR_CARGA_MAX 0.75

struct par{
    char *clave;
    void* valor;
};
typedef struct par par_t;

struct hash{
    par_t **pares;
    size_t capacidad;
    size_t cantidad;
};

par_t **crear_par(hash_t *hash,size_t cap_inicial_max){
    hash->pares = calloc(1,sizeof(par_t));
    hash->capacidad = cap_inicial_max;
    return hash->pares;
}

hash_t* hash_crear(size_t capacidad_inicial)
{
    size_t cap_inicial_max = capacidad_inicial < 5 ? 5 : capacidad_inicial;
    hash_t *hash =  calloc(1,sizeof(hash_t));
    if (hash == NULL){
        return NULL;
    }
    par_t **par = crear_par(hash,cap_inicial_max);
    if (par == NULL)
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
//bool hash_insertar(hash_t* hash, char* clave, void* valor, void** encontrado);

/**
 * Busca el elemento asociado a la clave en la tabla.
 **/
//void* hash_buscar(hash_t* hash, char* clave);

/**
 *Devuelve si la clave existe en la tabla o no
 */
//bool hash_contiene(hash_t* hash, char* clave);

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
        if (destructor != NULL)
        {
            for (size_t i = 0; i < hash->capacidad; i++){
                par_t *par_actual = hash->pares[i];
                destructor(par_actual);   
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