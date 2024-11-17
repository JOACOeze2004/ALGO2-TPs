#include "menu.h"
#include <stdio.h>
#include "hash.h"

#define CAPACIDAD_INICIAL 10

struct menu {
	hash_t* almacen;
	opcion_t **opciones;
	size_t cantidad_opciones;
};

struct opcion {
	void (*funcion)(void);
};

menu_t *menu_crear(){
	menu_t *menu = calloc(1,sizeof(menu_t));
	if (!menu){
		return NULL;
	}
	menu->almacen = hash_crear(CAPACIDAD_INICIAL);
	if (!menu->almacen){
		free(menu);
		return NULL;
	}
	menu->opciones = calloc(CAPACIDAD_INICIAL,sizeof(opcion_t*));
	return menu;
}

bool menu_agregar_opciones(menu_t *menu, char opcion, void (*funcion)(void)){
	if (!menu || !funcion){
		return false;
	}
	opcion_t *opcion_nueva = calloc(1,sizeof(opcion_t));
	if (!opcion_nueva){
		return false;
	}
	opcion_nueva->funcion = funcion;
	menu->opciones[menu->cantidad_opciones] = opcion_nueva;
	char clave[2] = {opcion, '\0'};
	if(!hash_insertar(menu->almacen,clave,&opcion_nueva->funcion,NULL)){
		free(opcion_nueva);
		return false;
	}
	menu->cantidad_opciones++;
	return true;
}

bool menu_ejecutar_entrada(menu_t *menu,char opcion){
	if (!menu){
		return false;
	}
	char clave[2] = {opcion, '\0'};
	opcion_t *opcion_a_ejecutar = hash_buscar(menu->almacen,clave);
	if (!opcion_a_ejecutar){
		return false;
	}
	opcion_a_ejecutar->funcion();	
	return true;
}

size_t menu_cantidad_opciones(menu_t *menu){
	return menu == NULL ? 0 : menu->cantidad_opciones;
}


//pre:	
//post:	Acomodamos el arrays de opciones para que al liberar, no haya peridad de memoria por desacomodo de punteros.
void acomodar_opciones(menu_t *menu, opcion_t *opcion_eliminar){
	for (size_t i = 0; i < menu->cantidad_opciones; i++) {
        if (menu->opciones[i] == opcion_eliminar) {
            for (size_t j = i; j < menu->cantidad_opciones - 1; j++) {
                menu->opciones[j] = menu->opciones[j + 1];
            }
        }
    }
}

bool menu_eliminar_opcion(menu_t *menu, char opcion){
	if (!menu){
		return false;
	}
	char clave[2] = {opcion, '\0'};
	opcion_t *opcion_eliminar = hash_quitar(menu->almacen,clave);
	if (!opcion_eliminar){
		return false;
	}
	acomodar_opciones(menu,opcion_eliminar);
    free(opcion_eliminar);
	menu->cantidad_opciones--;
	return true;
}

void (*menu_obtener_funcion_opcion(menu_t *menu, char opcion))(void){
	if (!menu){
		return NULL;
	}
	char clave[2] = {opcion, '\0'};
	opcion_t *opcion_buscada = hash_buscar(menu->almacen,clave);
	if (!opcion_buscada){
		return NULL;
	}
	return opcion_buscada->funcion;
}

void menu_destruir(menu_t *menu){
	if (menu){
		hash_destruir(menu->almacen);	
		for (size_t i = 0; i < menu->cantidad_opciones; i++){
			free(menu->opciones[i]);
		}	
		free(menu->opciones);				
		free(menu);
	}	
}

/*

menu_t *menu_crear() {
    menu_t *menu = calloc(1, sizeof(menu_t));
    if (!menu) {
        return NULL;
    }
    menu->almacen = hash_crear(CAPACIDAD_INICIAL);
    if (!menu->almacen) {
        free(menu);
        return NULL;
    }
    return menu;
}

bool menu_agregar_opciones(menu_t *menu, char opcion, void (*funcion)(void)) {
    if (!menu || !funcion) {
        return false;
    }
    opcion_t *nueva_opcion = calloc(1, sizeof(opcion_t));
    if (!nueva_opcion) {
        return false;
    }
    nueva_opcion->funcion = funcion;

    char clave[2] = {opcion, '\0'};
    if (!hash_insertar(menu->almacen, clave, nueva_opcion, NULL)) {
        free(nueva_opcion);
        return false;
    }
    return true;
}


bool menu_eliminar_opcion(menu_t *menu, char opcion) {
    if (!menu) {
        return false;
    }
    char clave[2] = {opcion, '\0'};
    opcion_t *opcion_eliminada = hash_quitar(menu->almacen, clave);
    if (!opcion_eliminada) {
        return false;
    }
    free(opcion_eliminada);
    return true;
}

void menu_destruir(menu_t *menu) {
    if (menu) {
        hash_destruir_todo(menu->almacen, free);
        free(menu);
    }
}
*/