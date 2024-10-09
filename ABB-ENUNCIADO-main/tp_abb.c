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

typedef struct nodo {
    void* elemento;        // Puntero a un elemento
    struct nodo* izq;     // Subárbol izquierdo
    struct nodo* der;     // Subárbol derecho
} nodo_t;

struct abb {
	size_t nodos;
	nodo_t *raiz;
	int (*comparador)(void*, void*);
};

void imprimir_arbol(nodo_t* nodo, int espacio) {
    if (nodo == NULL) {
        return;
    }
    // Aumenta el espacio entre niveles
    espacio += 10;

    // Imprime el subárbol derecho primero
    imprimir_arbol(nodo->der, espacio);

    // Imprime el nodo actual
    printf("\n");
    for (int i = 10; i < espacio; i++) {
        printf(" ");
    }
    printf("%s\n", ((struct pokemon*)nodo->elemento)->nombre); // Cambia esto según lo que necesites imprimir

    // Imprime el subárbol izquierdo
    imprimir_arbol(nodo->izq, espacio);
}

void imprimir_abb(nodo_t* raiz) {
    imprimir_arbol(raiz, 0);
}

int comparador(void* a, void* b) {
    struct pokemon* poke_a = (struct pokemon*)a;
    struct pokemon* poke_b = (struct pokemon*)b;

	// if(!poke_a || !poke_b){
	// 	return 0;
    // }
	
    // if (poke_a->fuerza < poke_b->fuerza) {
    //     return 1; // poke_a es menor
    // } else if (poke_a->fuerza > poke_b->fuerza) {
    //     return -1; // poke_a es mayor
    // } else {
    //     return 0; // Son iguales
    // }
    return (strcmp(poke_a->nombre, poke_b->nombre)); //con el - el inorder es alfabeticamente ascendente
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

	struct pokemon pikachu = { "Pikachu", 'E', 8, 40, 50 };
	//struct pokemon pikachu2 = { "Pikachu2", 'E', 55000, 40, 50 };
	//struct pokemon blas2 = { "Blastoise2", 'E', 55000, 40, 50 };
	struct pokemon bulbasur = { "Bulbasur", 'P', 59, 24, 71 };


	
	struct pokemon charizard = { "Charizard", 'F', 10, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 5, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	struct pokemon wartortle = { "Wartortle", 'A', 8, 167, 220 };

	struct pokemon raichu = { "Raichu", 'A', 8, 167, 220 };
	struct pokemon psyduck = { "Psyduck", 'A', 8, 167, 220 };



	abb_insertar(abb,&pikachu);
	abb_insertar(abb,&bulbasur);

	abb_insertar(abb,&charizard);
	abb_insertar(abb,&venusaur);
	abb_insertar(abb,&blastoise);

	abb_insertar(abb,&wartortle);
	abb_insertar(abb,&raichu);
	abb_insertar(abb,&psyduck);

	void *enocntado = NULL;


	imprimir_abb(abb->raiz);	

	printf("despues de sacar un nodo con dos hijos");

	abb_quitar(abb, &venusaur ,&enocntado);

	imprimir_abb(abb->raiz);	

	printf("\nahora vamos con Inorden\n");
	abb_iterar_inorden(abb,mostrar_pokemones,NULL);

	printf("\nvamos con Preorden\n");

	abb_iterar_preorden(abb,mostrar_pokemones,NULL);

	printf("\nahora vamos con Postorden\n");
	abb_iterar_postorden(abb,mostrar_pokemones,NULL);

	abb_destruir(abb);
	return 0;
}
