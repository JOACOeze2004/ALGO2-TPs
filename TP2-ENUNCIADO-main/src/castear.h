#ifndef CASTEAR_H
#define CASTEAR_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
*
*   El string y el ctx deben ser validos. 
*
*
*   Se parsea el string a un entero.Devuelve tru si el casteo fue exitoso o en caso contario devuelve false.
*
*/
bool castear_a_int(const char *str, void *ctx);

/*
*
*   El string y el ctx deben ser validos. 
*
*
*   Se pide memoria para el string pasado y se lo copia en ctx. Devuelve true si fue exitoso el casteo o caso contrario devuelve false.
*
*/
bool crear_string_nuevo(const char *str, void *ctx);

/*
*
*   El string y el ctx deben ser validos. 
*
*
*   Se transforma el string en un char. Devuelve true si fue exitoso el casteo o caso contrario devuelve false.
*
*/
bool castear_a_char(const char *str, void *ctx);

#endif /* CASTEAR */