#include "pa2m.h"
#include "src/abb.h"
#include <string.h>

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

bool continuar_iteracion(void *elemento, void *ctx)
{
	struct pokemon *p = (struct pokemon *)elemento;
	if (p) {
		pa2m_afirmar(p != NULL,
			     "Se itera correctamente sobre un pokemon");
	}
	return true;
}


// int comparador(void* elem1, void* elem2){

//     if(!elem1 || !elem2){
// 		return 0;
//     }
//     if(*(int*)elem1 > *(int*)elem2){
//         return 1;
//     }
//     if(*(int*)elem1 < *(int*)elem2){
//         return -1;
//     }
//     return 0;
// }

int comparador(void* a, void* b) {
    struct pokemon* poke_a = (struct pokemon*)a;
    struct pokemon* poke_b = (struct pokemon*)b;
    
    return strcmp(poke_a->nombre, poke_b->nombre);
}

void CrearABBRetornaAlgoNoNULL()
{
	abb_t *abb = abb_crear(comparador);
	pa2m_afirmar(abb != NULL, "El abb devolvio algo no nulo");
	abb_destruir(abb);
}

void CrearABBRetornaNULLSiComparadorEsNULL()
{
	abb_t *abb = abb_crear(NULL);
	pa2m_afirmar(abb == NULL, "El abb devolvio NULL");
	abb_destruir(abb);
}

void LaCantidadDeElementosInicialesEnABBNoNulaEs0()
{
	abb_t *abb = abb_crear(comparador);
	pa2m_afirmar(abb_cantidad(abb) == 0,
		     "La cantidad inicial de una lista es 0");
	abb_destruir(abb);
}

void LaCantidadDeElementosInicialesEnABBNulaEs0()
{
	abb_t *abb = NULL;
	pa2m_afirmar(abb_cantidad(abb) == 0,
		     "La cantidad inicial de una lista Nula es 0");
	abb_destruir(abb);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de agregar

void AgregarUnPokemonEnABBVacioRetornaTrue()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };

	pa2m_afirmar(abb_insertar(abb,&pikachu),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_cantidad(abb) == 1,
		     "La cantidad de elementos en el ABB es correctamente 1");
	abb_destruir(abb);
}

void AgregarVariosPokemonesEnABBVacioRetornaTrue()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	pa2m_afirmar(abb_insertar(abb,&pikachu),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb,&charizard),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb,&venusaur),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_cantidad(abb) == 3,
		     "La cantidad de elementos en el ABB es correctamente 3");
	abb_destruir(abb);
}

void AgregarVariosPokemonesIgualesEnABBVacioRetornaTrue()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	pa2m_afirmar(abb_insertar(abb,&pikachu),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb,&charizard),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb,&venusaur),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb,&pikachu),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb,&charizard),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_cantidad(abb) == 5,
		     "La cantidad de elementos en el ABB es correctamente 5");
	abb_destruir(abb);
}


void AgregarPokemonesYElementoNULLEnABBVacioRetornaFalse()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	abb_insertar(abb,&pikachu);
	abb_insertar(abb,&charizard);
	abb_insertar(abb,&venusaur);
	pa2m_afirmar(!abb_insertar(abb,NULL),
		     "El elemento NULL es agregado al ABB correctamente");
	pa2m_afirmar(abb_cantidad(abb) == 3,
		     "La cantidad de elementos en el ABB es 3 si intento agregar un elemento/pokemon NULL");
	abb_destruir(abb);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de buscar 

void ObtenerElementoEnABBVaciaDevuelveFalse()
{
	abb_t *abb = abb_crear(comparador);

	void *elemento_encontrado = NULL;

	pa2m_afirmar(
		abb_obtener(abb,&elemento_encontrado) == NULL,
		"Intentar obtener un elemento de un ABB vacía devuelve NULL");

	abb_destruir(abb);
}

void ObtenerElementoConPunteroNuloNoModificaNada()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	abb_insertar(abb,&pikachu);

	pa2m_afirmar(
		abb_obtener(abb,NULL) == NULL,
		"Obtener un elemento con puntero nulo devuelve NULL, pero no lo guarda");

	abb_destruir(abb);
}

void BuscarPrimerPokemonDevuelveStatsDelPokemonBuscado()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	abb_insertar(abb,&pikachu);
	abb_insertar(abb,&charizard);
	abb_insertar(abb,&venusaur);

	struct pokemon *elemento_guardado = &pikachu;
	
	pa2m_afirmar(abb_obtener(abb,elemento_guardado) != NULL,
		     "El pokemon buscado esta en el ABB y no es NULL");
	pa2m_afirmar(strcmp(elemento_guardado->nombre,"Pikachu") == 0,
		     "Lo retornado tiene el mismo nombre que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->tipo == 'E',
		     "Lo retornado tiene el mismo tipo que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->fuerza == 55,
		     "Lo retornado tiene la misma fuerza que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->destreza == 40,
			"Lo retornado tiene la misma destreza que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->resistencia == 50,
			"Lo retornado tiene la misma resistencia que el pokemon buscado");
	abb_destruir(abb);
}

void BuscarMedioPokemonDevuelveStatsDelPokemonBuscado()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	abb_insertar(abb,&pikachu);
	abb_insertar(abb,&charizard);
	abb_insertar(abb,&venusaur);

	struct pokemon *elemento_guardado = &charizard;
	
	pa2m_afirmar(abb_obtener(abb,elemento_guardado) != NULL,
		     "El pokemon buscado esta en el ABB y no es NULL");
	pa2m_afirmar(strcmp(elemento_guardado->nombre,"Charizard") == 0,
		     "Lo retornado tiene el mismo nombre que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->tipo == 'F',
		     "Lo retornado tiene el mismo tipo que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->fuerza == 100,
		     "Lo retornado tiene la misma fuerza que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->destreza == 143,
			"Lo retornado tiene la misma destreza que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->resistencia == 239,
			"Lo retornado tiene la misma resistencia que el pokemon buscado");
	abb_destruir(abb);
}


void BuscarUltimoPokemonDevuelveStatsDelPokemonBuscado()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	abb_insertar(abb,&pikachu);
	abb_insertar(abb,&charizard);
	abb_insertar(abb,&venusaur);

	struct pokemon *elemento_guardado = &venusaur;

	pa2m_afirmar(abb_obtener(abb,elemento_guardado) != NULL,
		     "El pokemon buscado esta en el ABB y no es NULL");
	pa2m_afirmar(strcmp(elemento_guardado->nombre,"Venusaur") == 0,
		     "Lo retornado tiene el mismo nombre que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->tipo == 'P',
		     "Lo retornado tiene el mismo tipo que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->fuerza == 89,
		     "Lo retornado tiene la misma fuerza que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->destreza == 109,
			"Lo retornado tiene el mismo tipo que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->resistencia == 301,
			"Lo retornado tiene la misma resistencia que el pokemon buscado");
	abb_destruir(abb);
}

void BuscarPokemonInexistenteDevuelveNULL()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb,&pikachu);
	abb_insertar(abb,&charizard);
	abb_insertar(abb,&venusaur);

	struct pokemon *elemento_guardado = &blastoise;

	pa2m_afirmar(abb_obtener(abb,elemento_guardado) == NULL,
		     "Devuelve NULL si el pokemon que busco no existe en el ABB");
	abb_destruir(abb);
}

void BuscarPokemonInexistenteEnABBVaciaDevuelveNULL()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon *elemento_guardado = &pikachu;

	pa2m_afirmar(abb_obtener(abb,elemento_guardado) == NULL,
		     "Devuelve NULL si el pokemon que busco no existe porque el ABB esta vacio");
	abb_destruir(abb);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de iterar inorder

void IterarInorderConPtrsNULLSDevuelveCantidad0()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb,&pikachu);
	abb_insertar(abb,&charizard);
	abb_insertar(abb,&venusaur);
	abb_insertar(abb,&blastoise);
	pa2m_afirmar(abb_iterar_inorden(NULL,NULL,NULL) == 0,
			"Devuelve NULL si el pokemon que busco no existe porque el ABB esta vacio");


	abb_destruir(abb);
}

void IterarInorderDevuelveCantidadCorrectamente()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb,&pikachu);
	abb_insertar(abb,&charizard);
	abb_insertar(abb,&venusaur);
	abb_insertar(abb,&blastoise);

	pa2m_afirmar(abb_iterar_inorden(abb,continuar_iteracion,NULL) == 4,
			"Iterar Inorder en un ABB con 4 pokemones devuelve 4");
	abb_destruir(abb);
}

void IterarInorderEnABBVacioDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	pa2m_afirmar(abb_iterar_inorden(abb,continuar_iteracion,NULL) == 0,
			"Iterar Inorder en un ABB vacio devuelve 0, o sea no itera");
	abb_destruir(abb);
}


int main()
{
	pa2m_nuevo_grupo("Pruebas de crear ABB");
	CrearABBRetornaAlgoNoNULL();
	CrearABBRetornaNULLSiComparadorEsNULL();
	LaCantidadDeElementosInicialesEnABBNoNulaEs0();
	LaCantidadDeElementosInicialesEnABBNulaEs0();

	pa2m_nuevo_grupo("Pruebas de agregar al ABB");
	AgregarUnPokemonEnABBVacioRetornaTrue();
	AgregarVariosPokemonesEnABBVacioRetornaTrue();
	AgregarVariosPokemonesIgualesEnABBVacioRetornaTrue();
	AgregarPokemonesYElementoNULLEnABBVacioRetornaFalse();

	pa2m_nuevo_grupo("Pruebas de buscar al ABB");
	ObtenerElementoEnABBVaciaDevuelveFalse();
	ObtenerElementoConPunteroNuloNoModificaNada();
	BuscarPrimerPokemonDevuelveStatsDelPokemonBuscado();
	BuscarUltimoPokemonDevuelveStatsDelPokemonBuscado();
	BuscarPokemonInexistenteDevuelveNULL();
	BuscarPokemonInexistenteEnABBVaciaDevuelveNULL();

	pa2m_nuevo_grupo("Pruebas de Iterar");
	IterarInorderConPtrsNULLSDevuelveCantidad0();
	IterarInorderDevuelveCantidadCorrectamente();
 	IterarInorderEnABBVacioDevuelve0();


	return pa2m_mostrar_reporte();
}
