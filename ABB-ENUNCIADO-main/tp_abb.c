#include "src/abb.h"
#include <stdio.h>
#include <string.h>

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

int comparador(void* a, void* b) {
    struct pokemon* poke_a = (struct pokemon*)a;
    struct pokemon* poke_b = (struct pokemon*)b;

	if(!poke_a || !poke_b){
		return 0;
    }
	
    if (poke_a->fuerza < poke_b->fuerza) {
        return -1; // poke_a es menor
    } else if (poke_a->fuerza > poke_b->fuerza) {
        return 1; // poke_a es mayor
    } else {
        return 0; // Son iguales
    }
    //return (strcmp(poke_a->nombre, poke_b->nombre)); //con el - el inorder es alfabeticamente ascendente
}

bool mostrar_pokemones( void *a, void *ctx)
{
	struct pokemon *poke = a;
	printf("Nombre: %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
	       poke->nombre, poke->tipo, poke->fuerza, poke->destreza,
	       poke->resistencia);
	return true;
	
}


int main(int argc, char *argv[])
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	//struct pokemon pikachu2 = { "Pikachu", 'E', 55000, 40, 50 };

	struct pokemon charizard = { "Charizard", 'F', 10, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 4, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	abb_insertar(abb,&pikachu);
	abb_insertar(abb,&charizard);
	abb_insertar(abb,&venusaur);
	abb_insertar(abb,&blastoise);
	//abb_insertar(abb,&pikachu2);


	printf("\nahora vamos con Inorden\n");
	abb_iterar_inorden(abb,mostrar_pokemones,NULL);

	printf("\nvamos con Preorden\n");

	abb_iterar_preorden(abb,mostrar_pokemones,NULL);

	printf("\nahora vamos con Postorden\n");
	abb_iterar_postorden(abb,mostrar_pokemones,NULL);

	abb_destruir(abb);
	return 0;
}
