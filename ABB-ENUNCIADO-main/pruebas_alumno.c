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

int comparador(void *a, void *b)
{
	struct pokemon *poke_a = (struct pokemon *)a;
	struct pokemon *poke_b = (struct pokemon *)b;
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

	pa2m_afirmar(abb_insertar(abb, &pikachu),
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

	pa2m_afirmar(abb_insertar(abb, &pikachu),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb, &charizard),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb, &venusaur),
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

	pa2m_afirmar(abb_insertar(abb, &pikachu),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb, &charizard),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb, &venusaur),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb, &pikachu),
		     "El pokemon es agregado al ABB correctamente");
	pa2m_afirmar(abb_insertar(abb, &charizard),
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

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	pa2m_afirmar(!abb_insertar(abb, NULL),
		     "El elemento NULL es agregado al ABB correctamente");
	pa2m_afirmar(
		abb_cantidad(abb) == 3,
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
		abb_obtener(abb, &elemento_encontrado) == NULL,
		"Intentar obtener un elemento de un ABB vacía devuelve NULL");

	abb_destruir(abb);
}

void ObtenerElementoConPunteroNuloNoModificaNada()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	abb_insertar(abb, &pikachu);

	pa2m_afirmar(
		abb_obtener(abb, NULL) == NULL,
		"Obtener un elemento con puntero nulo devuelve NULL, pero no lo guarda");

	abb_destruir(abb);
}

void BuscarPrimerPokemonDevuelveStatsDelPokemonBuscado()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);

	struct pokemon *elemento_guardado = &pikachu;

	pa2m_afirmar(
		abb_obtener(abb, elemento_guardado) != NULL,
		"El pokemon buscado (en la raiz) esta en el ABB y no es NULL");
	pa2m_afirmar(
		strcmp(elemento_guardado->nombre, "Pikachu") == 0,
		"Lo retornado tiene el mismo nombre que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->tipo == 'E',
		     "Lo retornado tiene el mismo tipo que el pokemon buscado");
	pa2m_afirmar(
		elemento_guardado->fuerza == 55,
		"Lo retornado tiene la misma fuerza que el pokemon buscado");
	pa2m_afirmar(
		elemento_guardado->destreza == 40,
		"Lo retornado tiene la misma destreza que el pokemon buscado");
	pa2m_afirmar(
		elemento_guardado->resistencia == 50,
		"Lo retornado tiene la misma resistencia que el pokemon buscado");
	abb_destruir(abb);
}

void BuscarMedioPokemonDevuelveStatsDelPokemonBuscado()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);

	struct pokemon *elemento_guardado = &charizard;

	pa2m_afirmar(
		abb_obtener(abb, elemento_guardado) != NULL,
		"El pokemon buscado (en alguna parte) esta en el ABB y no es NULL");
	pa2m_afirmar(
		strcmp(elemento_guardado->nombre, "Charizard") == 0,
		"Lo retornado tiene el mismo nombre que el pokemon buscado");
	pa2m_afirmar(elemento_guardado->tipo == 'F',
		     "Lo retornado tiene el mismo tipo que el pokemon buscado");
	pa2m_afirmar(
		elemento_guardado->fuerza == 100,
		"Lo retornado tiene la misma fuerza que el pokemon buscado");
	pa2m_afirmar(
		elemento_guardado->destreza == 143,
		"Lo retornado tiene la misma destreza que el pokemon buscado");
	pa2m_afirmar(
		elemento_guardado->resistencia == 239,
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

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);

	struct pokemon *elemento_guardado = &blastoise;

	pa2m_afirmar(
		abb_obtener(abb, elemento_guardado) == NULL,
		"Devuelve NULL si el pokemon que busco no existe en el ABB");
	abb_destruir(abb);
}

void BuscarPokemonInexistenteEnABBVaciaDevuelveNULL()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon *elemento_guardado = &pikachu;

	pa2m_afirmar(
		abb_obtener(abb, elemento_guardado) == NULL,
		"Devuelve NULL si el pokemon que busco no existe porque el ABB esta vacio");
	abb_destruir(abb);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de eliminar

void EliminarElementoNULLDevuelveFalse()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	void *encontrado = NULL;

	pa2m_afirmar(!abb_quitar(abb, NULL ,&encontrado),
		     "Intentar quitar un pokemon inexistente devuelve false");
	pa2m_afirmar(encontrado == NULL,
		     "El elemento eliminado es NULL (porque no lo puedo eliminar)");
	abb_destruir(abb);
}

void EliminarPokemonInexistenteDevuelveFalse()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon mewtwo = { "Mewtwo", 'P', 541, 654, 320 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);

	struct pokemon *elemento_guardado = &mewtwo;

	void *encontrado = NULL;

	pa2m_afirmar(abb_obtener(abb, elemento_guardado) == NULL,
		     "No existe Mewtwo");
	pa2m_afirmar(!abb_quitar(abb, elemento_guardado ,&encontrado),
		     "Intentar quitar un pokemon NULL devuelve false");
	pa2m_afirmar(encontrado == NULL,
		     "El elemento eliminado es NULL (porque no lo puedo eliminar)");
	abb_destruir(abb);
}

void EliminarElementoUnicoDevuelveTrue()
{
	abb_t *abb = abb_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	abb_insertar(abb, &pikachu);
	void *encontrado = NULL;

	pa2m_afirmar(abb_quitar(abb, &pikachu, &encontrado),
		     "Quitar Pikachu devuelve true");
	pa2m_afirmar(encontrado != NULL,
		     "El elemento eliminado no es NULL (debería ser Pikachu)");
	pa2m_afirmar(abb_obtener(abb, &pikachu) == NULL,
		     "Pikachu ya no existe en el árbol");
	abb_destruir(abb);
}

void EliminarElementoExistenteDevuelveTrue()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	
	void *encontrado = NULL;

	pa2m_afirmar(abb_quitar(abb, &blastoise ,&encontrado),
		     "Quitar A Blastoise devuelve true");
	pa2m_afirmar(encontrado != NULL,
		     "El elemento eliminado no es NULL (posiblemente sea Blastoise)");
	abb_destruir(abb);
}

void EliminarElementoYVolverAInsertarDevulveTrue()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	
	void *encontrado = NULL;

	pa2m_afirmar(abb_quitar(abb, &blastoise ,&encontrado),
		     "Quitar a Blastoise devuelve true");
	pa2m_afirmar(abb_insertar(abb, &blastoise),
		     "Puedo agregar a Blastoise de nuevo y devuelve true");
	pa2m_afirmar(abb_quitar(abb, &venusaur ,&encontrado),
		     "Quitar a venusaur devuelve true");
	pa2m_afirmar(abb_insertar(abb, &venusaur),
		     "Puedo agregar a Venusaur de nuevo y devuelve true");
	abb_destruir(abb);
}





































































//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de iterar inorder 

void IterarInorderConPtrsNULLSDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);

	pa2m_afirmar(abb_iterar_inorden(NULL, NULL, NULL) == 0,
		     "Iterar Inorder en un ABB con parametros NULL devuelve 0");
	abb_destruir(abb);
}

void IterarInorderConFuncionNULLSDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);

	pa2m_afirmar(
		abb_iterar_inorden(abb, NULL, NULL) == 0,
		"Iterar Inorder en un ABB con funcion* igual a NULL devuelve 0");
	abb_destruir(abb);
}

void IterarInorderEnABBVacioDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	pa2m_afirmar(
		abb_iterar_inorden(abb, continuar_iteracion, NULL) == 0,
		"Iterar Inorder en un ABB vacio devuelve 0, o sea no itera");
	abb_destruir(abb);
}

void IterarInorderDevuelveCantidadCorrectamenteSiABBTiene1Elemento()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };

	abb_insertar(abb, &pikachu);

	pa2m_afirmar(abb_iterar_inorden(abb, continuar_iteracion, NULL) == 1,
		     "Iterar Inorder en un ABB con 1 pokemon devuelve 1");
	abb_destruir(abb);
}

void IterarInorderDevuelveCantidadCorrectamente()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	pa2m_afirmar(abb_iterar_inorden(abb, continuar_iteracion, NULL) == 4,
		     "Iterar Inorder en un ABB con 4 pokemones devuelve 4");
	abb_destruir(abb);
}

void IterarInorderConPokemonesRepetidosDevuelveLACantidadCorrecta()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	pa2m_afirmar(abb_iterar_inorden(abb, continuar_iteracion, NULL) == 8,
		     "Iterar Inorder en un ABB con 8 pokemones devuelve 8");
	abb_destruir(abb);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de iterar preorder
void IterarPreorderConPtrsNULLSDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);

	pa2m_afirmar(abb_iterar_preorden(NULL, NULL, NULL) == 0,
		     "Iterar Preorder en un ABB con parametros NULL devuelve 0");
	abb_destruir(abb);
}

void IterarPreorderConFuncionNULLSDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);

	pa2m_afirmar(
		abb_iterar_preorden(abb, NULL, NULL) == 0,
		"Iterar Preorden en un ABB con funcion* igual a NULL devuelve 0");
	abb_destruir(abb);
}

void IterarPreorderEnABBVacioDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	pa2m_afirmar(
		abb_iterar_preorden(abb, continuar_iteracion, NULL) == 0,
		"Iterar Preorder en un ABB vacio devuelve 0, o sea no itera");
	abb_destruir(abb);
}

void IterarPreorderDevuelveCantidadCorrectamenteSiABBTiene1Elemento()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };

	abb_insertar(abb, &pikachu);

	pa2m_afirmar(abb_iterar_preorden(abb, continuar_iteracion, NULL) == 1,
		     "Iterar Preorder en un ABB con 1 pokemon devuelve 1");
	abb_destruir(abb);
}

void IterarPreorderDevuelveCantidadCorrectamente()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	pa2m_afirmar(abb_iterar_preorden(abb, continuar_iteracion, NULL) == 4,
		     "Iterar Preorder en un ABB con 4 pokemones devuelve 4");
	abb_destruir(abb);
}

void IterarPreorderConPokemonesRepetidosDevuelveLACantidadCorrecta()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	pa2m_afirmar(abb_iterar_preorden(abb, continuar_iteracion, NULL) == 8,
		     "Iterar Preorder en un ABB con 8 pokemones devuelve 8");
	abb_destruir(abb);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de iterar postorder

void IterarPostorderConPtrsNULLSDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);

	pa2m_afirmar(abb_iterar_postorden(NULL, NULL, NULL) == 0,
		     "Iterar Postorder en un ABB con parametros NULL devuelve 0");
	abb_destruir(abb);
}

void IterarPostorderConFuncionNULLSDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);

	pa2m_afirmar(
		abb_iterar_postorden(abb, NULL, NULL) == 0,
		"Iterar Postorden en un ABB con funcion* igual a NULL devuelve 0");
	abb_destruir(abb);
}

void IterarPostorderEnABBVacioDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	pa2m_afirmar(
		abb_iterar_postorden(abb, continuar_iteracion, NULL) == 0,
		"Iterar Postorden en un ABB vacio devuelve 0, o sea no itera");
	abb_destruir(abb);
}

void IterarPostorderDevuelveCantidadCorrectamenteSiABBTiene1Elemento()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };

	abb_insertar(abb, &pikachu);

	pa2m_afirmar(abb_iterar_postorden(abb, continuar_iteracion, NULL) == 1,
		     "Iterar Postorder en un ABB con 1 pokemon devuelve 1");
	abb_destruir(abb);
}

void IterarPostorderDevuelveCantidadCorrectamente()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	pa2m_afirmar(abb_iterar_postorden(abb, continuar_iteracion, NULL) == 4,
		     "Iterar Postorder en un ABB con 4 pokemones devuelve 4");
	abb_destruir(abb);
}

void IterarPostorderConPokemonesRepetidosDevuelveLACantidadCorrecta()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	pa2m_afirmar(abb_iterar_postorden(abb, continuar_iteracion, NULL) == 8,
		     "Iterar Postorder en un ABB con 8 pokemones devuelve 8");
	abb_destruir(abb);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de vectorisar inorder

void VectorizarInorderDevuelveCantidadCorrectamente()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };
	
	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	size_t capacidad = abb_cantidad(abb);
	struct pokemon *vector[capacidad];

	pa2m_afirmar(abb_vectorizar_inorden(abb, (void**)vector, 4) == 4,
		     "Vectorizar Inorder en un ABB con 4 pokemones devuelve 4");


	for (size_t i = 0; i < 4; i++)
	{
		printf("nombre inorden:%s\n",vector[i]->nombre);
	}
	
	pa2m_afirmar(vector[0]->tipo == 'P',
		     "El primer elemento del vector tiene tipo esperado (de Venusaur)");
	pa2m_afirmar(vector[1]->tipo == 'E',
		     "El segundo elemento del vector tiene tipo esperado (de Pikachu)");
	pa2m_afirmar(vector[2]->tipo == 'F',
		     "El tercer elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(vector[3]->tipo == 'A',
		     "El cuarto elemento del vector tiene tipo esperado (de Blastoise)");
	abb_destruir(abb);
}

void VectorizarConVectorNULLDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	pa2m_afirmar(abb_vectorizar_inorden(abb, NULL, 4) == 0,
		     "Vectorizar Inorder en un ABB con vector NULL devuelve 0");
	abb_destruir(abb);
}

void VectorizarConTamañoExcedidoDevuelveLaCantidadDeAgregados()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	
	size_t capacidad = abb_cantidad(abb);
	struct pokemon *vector[capacidad];

	pa2m_afirmar(abb_vectorizar_inorden(abb, (void**)vector, 5) == 4,
		     "Vectorizar Inorder en un ABB con 4 pokemones cuando le paso un tamaño que exdece el vector devuelvo la cantidad de pokemones que habia en el ABB");
	abb_destruir(abb);
}

void VectorizarConTAmañoInvalidoDevuelveLaCantidadDeAgregados()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };
		
	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	size_t capacidad = abb_cantidad(abb);
	struct pokemon *vector[capacidad];

	pa2m_afirmar(abb_vectorizar_inorden(abb, (void**)vector, 2) == 2,
		     "Vectorizar Inorder en un ABB con 4 pokemones cuando le paso un tamaño que exdece el vector devuelvo la cantidad de pokemones que habia en el ABB");
	abb_destruir(abb);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de vectorisar preorder

void VectorizarPreorderDevuelveCantidadCorrectamente()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };
	
	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	size_t capacidad = abb_cantidad(abb);
	struct pokemon *vector[capacidad];

	pa2m_afirmar(abb_vectorizar_preorden(abb, (void**)vector, 4) == 4,
		     "Vectorizar Inorder en un ABB con 4 pokemones devuelve 4");
	pa2m_afirmar(vector[0]->tipo == 'E',
		     "El primer elemento del vector tiene tipo esperado (de Pikachu)");
	pa2m_afirmar(vector[1]->tipo == 'P',
		     "El segundo elemento del vector tiene tipo esperado (de venusaur)");
	pa2m_afirmar(vector[2]->tipo == 'F',
		     "El tercer elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(vector[3]->tipo == 'A',
		     "El cuarto elemento del vector tiene tipo esperado (de Blastoise)");
	abb_destruir(abb);
}

void VectorizarPreorderConVectorNULLDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	pa2m_afirmar(abb_vectorizar_preorden(abb, NULL, 4) == 0,
		     "Vectorizar Inorder en un ABB con vector NULL devuelve 0");
	abb_destruir(abb);
}

void VectorizarPreorderConTamañoExcedidoDevuelveLaCantidadDeAgregados()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	
	size_t capacidad = abb_cantidad(abb);
	struct pokemon *vector[capacidad];

	pa2m_afirmar(abb_vectorizar_preorden(abb, (void**)vector, 5) == 4,
		     "Vectorizar Inorder en un ABB con 4 pokemones cuando le paso un tamaño que exdece el vector devuelvo la cantidad de pokemones que habia en el ABB");
	abb_destruir(abb);
}

void VectorizarPreorderConTAmañoInvalidoDevuelveLaCantidadDeAgregados()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };
		
	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	size_t capacidad = abb_cantidad(abb);
	struct pokemon *vector[capacidad];

	pa2m_afirmar(abb_vectorizar_preorden(abb, (void**)vector, 2) == 2,
		     "Vectorizar Inorder en un ABB con 4 pokemones cuando le paso un tamaño que exdece el vector devuelvo la cantidad de pokemones que habia en el ABB");
	abb_destruir(abb);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de vectorisar Postorder

void VectorizarPostorderDevuelveCantidadCorrectamente()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };
	
	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	size_t capacidad = abb_cantidad(abb);
	struct pokemon *vector[capacidad];

	pa2m_afirmar(abb_vectorizar_postorden(abb, (void**)vector, 4) == 4,
		     "Vectorizar Inorder en un ABB con 4 pokemones devuelve 4");
	pa2m_afirmar(vector[0]->tipo == 'P',
		     "El primer elemento del vector tiene tipo esperado (de Venusaur)");
	pa2m_afirmar(vector[1]->tipo == 'A',
		     "El segundo elemento del vector tiene tipo esperado (de Blastoise)");
	pa2m_afirmar(vector[2]->tipo == 'F',
		     "El tercer elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(vector[3]->tipo == 'E',
		     "El cuarto elemento del vector tiene tipo esperado (de Pikachu)");
	abb_destruir(abb);
}

void VectorizarPostorderConVectorNULLDevuelve0()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	pa2m_afirmar(abb_vectorizar_postorden(abb, NULL, 4) == 0,
		     "Vectorizar Inorder en un ABB con vector NULL devuelve 0");
	abb_destruir(abb);
}

void VectorizarPostorderConTamañoExcedidoDevuelveLaCantidadDeAgregados()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	
	size_t capacidad = abb_cantidad(abb);
	struct pokemon *vector[capacidad];

	pa2m_afirmar(abb_vectorizar_postorden(abb, (void**)vector, 5) == 4,
		     "Vectorizar Inorder en un ABB con 4 pokemones cuando le paso un tamaño que exdece el vector devuelvo la cantidad de pokemones que habia en el ABB");
	abb_destruir(abb);
}

void VectorizarPostorderConTAmañoInvalidoDevuelveLaCantidadDeAgregados()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };
		
	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);

	size_t capacidad = abb_cantidad(abb);
	struct pokemon *vector[capacidad];

	pa2m_afirmar(abb_vectorizar_postorden(abb, (void**)vector, 2) == 2,
		     "Vectorizar Inorder en un ABB con 4 pokemones cuando le paso un tamaño que exdece el vector devuelvo la cantidad de pokemones que habia en el ABB");
	abb_destruir(abb);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de crear el ABB");
	CrearABBRetornaAlgoNoNULL();
	CrearABBRetornaNULLSiComparadorEsNULL();
	LaCantidadDeElementosInicialesEnABBNoNulaEs0();
	LaCantidadDeElementosInicialesEnABBNulaEs0();

	pa2m_nuevo_grupo("Pruebas de agregar en el ABB");
	AgregarUnPokemonEnABBVacioRetornaTrue();
	AgregarVariosPokemonesEnABBVacioRetornaTrue();
	AgregarVariosPokemonesIgualesEnABBVacioRetornaTrue();
	AgregarPokemonesYElementoNULLEnABBVacioRetornaFalse();

	pa2m_nuevo_grupo("Pruebas de buscar en el ABB");
	ObtenerElementoEnABBVaciaDevuelveFalse();
	ObtenerElementoConPunteroNuloNoModificaNada();
	BuscarPrimerPokemonDevuelveStatsDelPokemonBuscado();
	BuscarPokemonInexistenteDevuelveNULL();
	BuscarPokemonInexistenteEnABBVaciaDevuelveNULL();

	pa2m_nuevo_grupo("Pruebas de quitar en el ABB");


	pa2m_nuevo_grupo("Pruebas de Iterar Inorder");
	IterarInorderConPtrsNULLSDevuelve0();
	IterarInorderConFuncionNULLSDevuelve0();
	IterarInorderEnABBVacioDevuelve0();
	IterarInorderDevuelveCantidadCorrectamenteSiABBTiene1Elemento();
	IterarInorderDevuelveCantidadCorrectamente();
	IterarInorderConPokemonesRepetidosDevuelveLACantidadCorrecta();

	pa2m_nuevo_grupo("Pruebas de Iterar Preorden");
	IterarPreorderConPtrsNULLSDevuelve0();
	IterarPreorderConFuncionNULLSDevuelve0();
	IterarPreorderEnABBVacioDevuelve0();
	IterarPreorderDevuelveCantidadCorrectamenteSiABBTiene1Elemento();
	IterarPreorderDevuelveCantidadCorrectamente();
	IterarPreorderConPokemonesRepetidosDevuelveLACantidadCorrecta();

	pa2m_nuevo_grupo("Pruebas de Iterar Postorden");
	IterarPostorderConPtrsNULLSDevuelve0();
	IterarPostorderConFuncionNULLSDevuelve0();
	IterarPostorderEnABBVacioDevuelve0();
	IterarPostorderDevuelveCantidadCorrectamenteSiABBTiene1Elemento();
	IterarPostorderDevuelveCantidadCorrectamente();
	IterarPostorderConPokemonesRepetidosDevuelveLACantidadCorrecta();

	pa2m_nuevo_grupo("Pruebas de vectorizar Inorden");
	VectorizarInorderDevuelveCantidadCorrectamente();
	VectorizarConVectorNULLDevuelve0();
	VectorizarConTamañoExcedidoDevuelveLaCantidadDeAgregados();
	VectorizarConTAmañoInvalidoDevuelveLaCantidadDeAgregados();

	pa2m_nuevo_grupo("Pruebas de vectorizar Preorder");
 	VectorizarPreorderDevuelveCantidadCorrectamente();
	VectorizarPreorderConVectorNULLDevuelve0();
	VectorizarPreorderConTamañoExcedidoDevuelveLaCantidadDeAgregados();
	VectorizarPreorderConTAmañoInvalidoDevuelveLaCantidadDeAgregados();

	pa2m_nuevo_grupo("Pruebas de vectorizar Postorder");
	VectorizarPostorderDevuelveCantidadCorrectamente();
	VectorizarPostorderConVectorNULLDevuelve0();
	VectorizarPostorderConTamañoExcedidoDevuelveLaCantidadDeAgregados();
	VectorizarPostorderConTAmañoInvalidoDevuelveLaCantidadDeAgregados();


	pa2m_nuevo_grupo("Pruebas de Eliminar");
	EliminarElementoNULLDevuelveFalse();
	EliminarPokemonInexistenteDevuelveFalse();
	EliminarElementoNULLDevuelveFalse();
	EliminarElementoUnicoDevuelveTrue();
	EliminarElementoExistenteDevuelveTrue();
	EliminarElementoYVolverAInsertarDevulveTrue();

	return pa2m_mostrar_reporte();
}
