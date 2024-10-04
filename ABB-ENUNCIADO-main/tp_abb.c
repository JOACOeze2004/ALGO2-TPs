#include "src/abb.h"
#include <stdio.h>


#define TIPO_AGUA 'A'
#define TIPO_FUEGO 'F'
#define TIPO_PLANTA 'P'
#define TIPO_ROCA 'R'
#define TIPO_ELECTRICO 'E'
#define TIPO_NORMAL 'N'
#define TIPO_LUCHA 'L'

#define BUSCAR "buscar"
#define LISTAR "listar"
#define OPCION_BUSCAR 1
#define OPCION_LISTAR 2

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};

// bool mostrar_pokemones( void *a, void *ctx)
// {
// 	struct pokemon *poke = a;
// 	printf("Nombre: %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
// 	       poke->nombre, poke->tipo, poke->fuerza, poke->destreza,
// 	       poke->resistencia);
// 	return true;
	
// }

// int main(int argc, char *argv[])
// {
// 	abb_t *abb = abb_crear(NULL);

// 	return 0;
// }
