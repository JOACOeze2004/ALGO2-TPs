#ifndef RACHA_H
#define RACHA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct racha racha_t;

/*
    *Crea la racha.
*/
racha_t *racha_crear();

/*
    *Destruye la racha.
*/
void racha_destruir(racha_t *racha);

/**
 * Destruye la racha aplicando la funcion destructora (si no es NULL) a cada elemento.
 * 
*/
void racha_destruir_todo(racha_t *racha, void (*destructor)(void *));

/**
 * Inserta un combo ( qeu en nuestro caso es un monstruo_t) a la racha.
 * 
 *
 * Devuelve true si pudo agregar al combo,o false en caso de error.
 *
 */
bool racha_agregar(racha_t *racha, void *combo);

/*
*   Devuelve Cuantos combos hay en la racha.
*
*/
size_t racha_cantidad_combos(racha_t *racha);

/*
*   Elimina un combo (o monstruo en nuestro caso) de la racha. Y se guarda el pokemon eliminado en eliminado, siempre que este no sea NULL.
*/
bool racha_eliminar(racha_t *racha, void *combo, size_t posicion,
		    void **eliminado);

/*
*   Vacia la racha siempre que esta no sea NULL. 
*
*	Recomendacion: ES bastante uil si se quiere tener una lista sin nada sin tener que destuir la vieja y crear otra nueva.
*/
bool racha_vaciar(racha_t *racha);

/*
*		
*   Itera la racha. Si la funcion que le pasamos devuleve false, se corta el recorrido y se devuelve false.
*	
*/
bool racha_iterar(racha_t *racha, bool (*f)(void *, void *), void *ctx);

#endif /* RACHA */