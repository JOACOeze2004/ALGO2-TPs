#ifndef MENU_H
#define MENU_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct menu menu_t;
typedef struct opcion opcion_t;

/*
    *Crea el menu.
*/
menu_t *menu_crear();

/*
    *Destruye el menu. 
*/
void menu_destruir(menu_t *menu);

/**
 * Inserta una opcion al menu, y una funcion como valor del mismo. Se le debe pasar un ctx que contengan los parametros que usaran para las funciones que metan.
 * 
 * En caso de meter la misma opcion, modifica la funcion que habia antes por la que le pasaste ahora y devuelve true. *
 *
 * Devuelve true si pudo agregar la opcion junto con su funcion,o false en caso de error.
 *
 */
bool menu_agregar_opciones(menu_t *menu, char opcion, void (*funcion)(void **),
			   void *ctx[]);

/*
*   Ejecuta la opcion que se ingrese.
*
*   Devuelve true si pudo ejecutar la funcion asociada a la opcion o false en caso contrario.
*/
bool menu_ejecutar_entrada(menu_t *menu, char opcion, void *ctx[]);

/*
*   Devuelve Cuantas opciones hay en el menu.
*
*/
size_t menu_cantidad_opciones(menu_t *menu);

/*
*   Elimina una opcion del menu.
*/
bool menu_eliminar_opcion(menu_t *menu, char opcion);

/*
*   Obtiene la funcion asociada a la opcion.
*/
void (*menu_obtener_funcion_opcion(menu_t *menu, char opcion))(void **);

#endif /* MENU */
