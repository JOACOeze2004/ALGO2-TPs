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

bool continuar_iteracion_cortada(void *elemento, void *ctx)
{
	struct pokemon *p = (struct pokemon *)elemento;

	if (p) {
		pa2m_afirmar(p != NULL,
			     "Se itera correctamente sobre un pokemon");
		if (strcmp(p->nombre, "Mewtwo") == 0) {
			printf("Cortando la iteración en Mewtwo\n");
			return false;
		}
	}
	printf("Iterando por: %s\n", p->nombre);
	return true;
}

int comparador(void *a, void *b)
{
	if (a == NULL && b == NULL) {
		return 0;
	}
	if (a == NULL) {
		return -1;
	}
	if (b == NULL) {
		return 1;
	}
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

	pa2m_afirmar(abb_obtener(abb, elemento_guardado) != NULL,
		     "El pokemon buscado esta en el ABB y no es NULL");
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

void BuscarMedioPokemonDevuelveStatsDelPokemonBuscad2()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon cacnea = { "Cacnea", 'P', 11, 12, 14 };

	struct pokemon joltik = { "Joltik", 'E', 8, 10, 5 };
	struct pokemon magcargo = { "Magcargo", 'F', 22, 20, 22 };
	struct pokemon dedenne = { "Dedenne", 'F', 15, 5, 33 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);

	abb_insertar(abb, &cacnea);
	abb_insertar(abb, &joltik);
	abb_insertar(abb, &magcargo);
	abb_insertar(abb, &dedenne);

	struct pokemon *elemento_guardado = &charizard;
	pa2m_afirmar(abb_obtener(abb, elemento_guardado) != NULL,
		     "El pokemon Charizard esta en el ABB y no es NULL");
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

	struct pokemon *elemento_guardado2 = &magcargo;
	pa2m_afirmar(abb_obtener(abb, elemento_guardado2) != NULL,
		     "El pokemon Charizard esta en el ABB y no es NULL");
	pa2m_afirmar(
		strcmp(elemento_guardado2->nombre, "Magcargo") == 0,
		"Lo retornado tiene el mismo nombre que el pokemon buscado");
	pa2m_afirmar(elemento_guardado2->tipo == 'F',
		     "Lo retornado tiene el mismo tipo que el pokemon buscado");
	pa2m_afirmar(
		elemento_guardado2->fuerza == 22,
		"Lo retornado tiene la misma fuerza que el pokemon buscado");
	pa2m_afirmar(
		elemento_guardado2->destreza == 20,
		"Lo retornado tiene la misma destreza que el pokemon buscado");
	pa2m_afirmar(
		elemento_guardado2->resistencia == 22,
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
//pruebas de eliminar con 0 o 1 hijo
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

	pa2m_afirmar(!abb_quitar(abb, NULL, &encontrado),
		     "Intentar quitar un pokemon inexistente devuelve false");
	pa2m_afirmar(
		encontrado == NULL,
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

	struct pokemon *encontrado = NULL;

	pa2m_afirmar(abb_cantidad(abb) == 3, "La canidad de pokemones es 3");
	pa2m_afirmar(abb_obtener(abb, &mewtwo) == NULL, "No existe Mewtwo");
	pa2m_afirmar(!abb_quitar(abb, &mewtwo, (void *)&encontrado),
		     "Intentar quitar un pokemon que no existe devuelve false");
	pa2m_afirmar(
		encontrado == NULL,
		"El elemento eliminado es NULL (porque no lo puedo eliminar)");
	pa2m_afirmar(
		abb_cantidad(abb) == 3,
		"La canidad de pokemones sigue siendo 3 si intento eliminar un pokemon inexistente");
	abb_destruir(abb);
}

void EliminarElementoUnicoDevuelveTrue()
{
	abb_t *abb = abb_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	abb_insertar(abb, &pikachu);
	struct pokemon *encontrado = NULL;

	pa2m_afirmar(abb_obtener(abb, &pikachu) != NULL,
		     "Pikachu existe en el ABB");
	pa2m_afirmar(abb_quitar(abb, &pikachu, (void *)&encontrado),
		     "Quitar Pikachu devuelve true");
	pa2m_afirmar(encontrado != NULL,
		     "El elemento eliminado no es NULL (debería ser Pikachu)");
	pa2m_afirmar(
		strcmp(encontrado->nombre, "Pikachu") == 0,
		"El elemento quitado tiene el mismo nombre que el pokemon que queriamos quitamos (de pikachu)");
	pa2m_afirmar(
		encontrado->tipo == 'E',
		"El elemento quitado tiene el mismo tipo que el pokemon que queriamos quitamos (de pikachu)");
	pa2m_afirmar(
		encontrado->fuerza == 55,
		"El elemento quitado tiene la misma fuerza que el pokemon que queriamos quitamos (de pikachu)");
	pa2m_afirmar(
		encontrado->destreza == 40,
		"El elemento quitado tiene la misma destreza que el pokemon que queriamos quitamos (de pikachu)");
	pa2m_afirmar(
		encontrado->resistencia == 50,
		"El elemento quitado tiene la misma resistencia que el pokemon que queriamos quitamos (de pikachu)");
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

	pa2m_afirmar(abb_quitar(abb, &blastoise, &encontrado),
		     "Quitar A Blastoise devuelve true");
	pa2m_afirmar(
		encontrado != NULL,
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

	pa2m_afirmar(abb_quitar(abb, &blastoise, &encontrado),
		     "Quitar a Blastoise devuelve true");
	pa2m_afirmar(abb_insertar(abb, &blastoise),
		     "Puedo agregar a Blastoise de nuevo y devuelve true");
	pa2m_afirmar(abb_quitar(abb, &venusaur, &encontrado),
		     "Quitar a venusaur devuelve true");
	pa2m_afirmar(abb_insertar(abb, &venusaur),
		     "Puedo agregar a Venusaur de nuevo y devuelve true");
	abb_destruir(abb);
}

void EliminarRaizYVuelvoAInsertarOtraRaizDevulveTrue()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };

	abb_insertar(abb, &pikachu);

	void *encontrado = NULL;

	pa2m_afirmar(abb_quitar(abb, &pikachu, &encontrado),
		     "Quitar a pikachu (raiz) devuelve true");
	abb_insertar(abb, &pikachu);
	pa2m_afirmar(abb_obtener(abb, &pikachu) != NULL,
		     "Obtengo la raiz de nuevo");
	abb_destruir(abb);
}

void EliminarElementoConUnHijoDevuelveTrue()
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
	struct pokemon *encontrado = NULL;

	pa2m_afirmar(
		abb_quitar(abb, &charizard, (void *)&encontrado),
		"Quitar a Charizard (que tiene como hijo a Blastoise) devuelve true");
	pa2m_afirmar(
		strcmp(encontrado->nombre, "Charizard") == 0,
		"El elemento quitado tiene el mismo nombre que el pokemon que queriamos quitamos (de Charizard)");
	pa2m_afirmar(
		encontrado->tipo == 'F',
		"El elemento quitado tiene el mismo tipo que el pokemon que queriamos quitamos (de Charizard)");
	pa2m_afirmar(
		encontrado->fuerza == 100,
		"El elemento quitado tiene la misma fuerza que el pokemon que queriamos quitamos (de Charizard)");
	pa2m_afirmar(
		encontrado->destreza == 143,
		"El elemento quitado tiene la misma destreza que el pokemon que queriamos quitamos (de Charizard)");
	pa2m_afirmar(
		encontrado->resistencia == 239,
		"El elemento quitado tiene la misma resistencia que el pokemon que queriamos quitamos (de Charizard)");
	abb_destruir(abb);
}

void EliminarElementoConUnHijoYAgregarOtraVezDevuelveTrue()
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

	pa2m_afirmar(
		abb_quitar(abb, &charizard, &encontrado),
		"Quitar a Charizard (que tiene como hijo a Blastoise) devuelve true");
	pa2m_afirmar(abb_cantidad(abb) == 3,
		     "Tenemos 3 elementos luego de eliminar a Charizard");
	pa2m_afirmar(abb_insertar(abb, &charizard),
		     "Agregamos a charizard correctamente");
	pa2m_afirmar(
		abb_cantidad(abb) == 4,
		"Tenemos 4 elementos luego de agregar nuevamente a Charizard");
	abb_destruir(abb);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de eliminar con 2 hijos

void EliminarElementoConDosHijosDevuelveTrue()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon bulbasur = { "Bulbasur", 'P', 59, 24, 71 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &bulbasur);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	void *encontrado = NULL;

	pa2m_afirmar(
		abb_quitar(abb, &bulbasur, &encontrado),
		"Quitar a Bulbasur (que tiene como hijo a Blastoise y Charizard) devuelve true");
	pa2m_afirmar(abb_cantidad(abb) == 4,
		     "Tenemos 4 elementos luego de eliminar a Bulbasur");
	abb_destruir(abb);
}

void EliminarNodoConPredecesorInordenConHijoIzquierdo()
{
	abb_t *abb = abb_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon bulbasur = { "Bulbasur", 'P', 59, 24, 71 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };
	struct pokemon eevee = { "Eevee", 'N', 5, 10, 200 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &bulbasur);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	abb_insertar(abb, &eevee);

	void *encontrado = NULL;

	pa2m_afirmar(
		abb_quitar(abb, &bulbasur, &encontrado),
		"Eliminar a Bulbasur con predecesor inorden que tiene hijo izquierdo devuelve true");
	pa2m_afirmar(abb_cantidad(abb) == 5,
		     "Hay 5 elementos en el ABB después de eliminar Bulbasur");
	abb_destruir(abb);
}

void EliminarElementoConDosHijosYAgregoDeNuevoDevuelveTrue()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon bulbasur = { "Bulbasur", 'P', 59, 24, 71 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &bulbasur);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	void *encontrado = NULL;

	pa2m_afirmar(
		abb_quitar(abb, &bulbasur, &encontrado),
		"Quitar a Bulbasur (que tiene como hijo a Blastoise y Charizard) devuelve true");
	pa2m_afirmar(abb_cantidad(abb) == 4,
		     "Tenemos 4 elementos luego de eliminar a Bulbasur");
	pa2m_afirmar(abb_insertar(abb, &bulbasur),
		     "Insertamos Correctamente a Bulbasur");
	pa2m_afirmar(
		abb_cantidad(abb) == 5,
		"Tenemos 5 elementos luego de volver a agregar a Bulbasur");
	abb_destruir(abb);
}

void EliminarRaizDevuleveTrue()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon bulbasur = { "Bulbasur", 'P', 59, 24, 71 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &bulbasur);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	void *encontrado = NULL;

	pa2m_afirmar(
		abb_quitar(abb, &pikachu, &encontrado),
		"Quitar a Pikachu (que tiene como hijo a Venasur y Charizard) devuelve true sin romperse");
	pa2m_afirmar(abb_cantidad(abb) == 4,
		     "Tenemos 4 elementos luego de eliminar a Pikachu");
	abb_destruir(abb);
}

void EliminarTodoElABBDevulveTrue()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon bulbasur = { "Bulbasur", 'P', 59, 24, 71 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &bulbasur);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	void *encontrado = NULL;

	pa2m_afirmar(
		abb_quitar(abb, &charizard, &encontrado),
		"Quitar a Charizard (que tiene como hijo a Blastoise) devuelve true sin romperse");
	pa2m_afirmar(abb_cantidad(abb) == 4,
		     "Tenemos 4 elementos luego de eliminar a Charizard");
	pa2m_afirmar(abb_quitar(abb, &bulbasur, &encontrado),
		     "Quitar a Bulbasur devuelve true sin romperse");
	pa2m_afirmar(abb_cantidad(abb) == 3,
		     "Tenemos 3 elementos luego de eliminar a Bulbasur");
	pa2m_afirmar(abb_quitar(abb, &blastoise, &encontrado),
		     "Quitar a Blastoise devuelve true sin romperse");
	pa2m_afirmar(abb_cantidad(abb) == 2,
		     "Tenemos 2 elementos luego de eliminar a Blastoise");
	pa2m_afirmar(abb_quitar(abb, &pikachu, &encontrado),
		     "Quitar a Pikachu (la raiz) devuelve true sin romperse");
	pa2m_afirmar(abb_cantidad(abb) == 1,
		     "Tenemos 1 elemento luego de eliminar a Pikachu");
	pa2m_afirmar(abb_quitar(abb, &venusaur, &encontrado),
		     "Quitar a Venusaur devuelve true sin romperse");
	pa2m_afirmar(abb_cantidad(abb) == 0, "El ABB se vacio completamente");
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

	pa2m_afirmar(
		abb_iterar_preorden(NULL, NULL, NULL) == 0,
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

	pa2m_afirmar(
		abb_iterar_postorden(NULL, NULL, NULL) == 0,
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

	pa2m_afirmar(abb_vectorizar_inorden(abb, (void **)vector, 4) == 4,
		     "Vectorizar Inorder en un ABB con 4 pokemones devuelve 4");
	pa2m_afirmar(
		vector[0]->tipo == 'A',
		"El primer elemento del vector tiene tipo esperado (de Blastoise)");
	pa2m_afirmar(
		vector[1]->tipo == 'F',
		"El segundo elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(
		vector[2]->tipo == 'E',
		"El tercer elemento del vector tiene tipo esperado (de Pikachu)");
	pa2m_afirmar(
		vector[3]->tipo == 'P',
		"El cuarto elemento del vector tiene tipo esperado (de Venusaur)");
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

	pa2m_afirmar(
		abb_vectorizar_inorden(abb, (void **)vector, 5) == 4,
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

	pa2m_afirmar(abb_cantidad(abb) == 4, "La cantidad de pokemones es 4");
	pa2m_afirmar(
		abb_vectorizar_inorden(abb, (void **)vector, 2) == 2,
		"Vectorizar Inorder en un ABB con 4 pokemones cuando le paso un tamaño inferiro a la cantidad de pokemones en el ABB devuelvo la capacidad que le pasamos a la funcion (2 en este caso)");
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

	pa2m_afirmar(
		abb_vectorizar_preorden(abb, (void **)vector, 4) == 4,
		"Vectorizar Preorden en un ABB con 4 pokemones devuelve 4");
	pa2m_afirmar(
		vector[0]->tipo == 'E',
		"El primer elemento del vector tiene tipo esperado (de Pikachu)");
	pa2m_afirmar(
		vector[1]->tipo == 'F',
		"El segundo elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(
		vector[2]->tipo == 'A',
		"El tercer elemento del vector tiene tipo esperado (de Blastoise)");
	pa2m_afirmar(
		vector[3]->tipo == 'P',
		"El cuarto elemento del vector tiene tipo esperado (de Venusaur)");
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

	pa2m_afirmar(
		abb_vectorizar_preorden(abb, NULL, 4) == 0,
		"Vectorizar Preorder en un ABB con vector NULL devuelve 0");
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

	pa2m_afirmar(
		abb_vectorizar_preorden(abb, (void **)vector, 5) == 4,
		"Vectorizar Preorder en un ABB con 4 pokemones cuando le paso un tamaño que exdece el vector devuelvo la cantidad de pokemones que habia en el ABB");
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

	pa2m_afirmar(
		abb_vectorizar_preorden(abb, (void **)vector, 2) == 2,
		"Vectorizar Preorder en un ABB con 4 pokemones cuando le paso un tamaño inferiro a la cantidad de pokemones en el ABB devuelvo la capacidad que le pasamos a la funcion (2 en este caso)");
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

	pa2m_afirmar(
		abb_vectorizar_postorden(abb, (void **)vector, 4) == 4,
		"Vectorizar Postorder en un ABB con 4 pokemones devuelve 4");
	pa2m_afirmar(
		vector[0]->tipo == 'A',
		"El primer elemento del vector tiene tipo esperado (de Blastoise)");
	pa2m_afirmar(
		vector[1]->tipo == 'F',
		"El segundo elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(
		vector[2]->tipo == 'P',
		"El tercer elemento del vector tiene tipo esperado (de Venusaur)");
	pa2m_afirmar(
		vector[3]->tipo == 'E',
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

	pa2m_afirmar(
		abb_vectorizar_postorden(abb, NULL, 4) == 0,
		"Vectorizar Postorder en un ABB con vector NULL devuelve 0");
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

	pa2m_afirmar(
		abb_vectorizar_postorden(abb, (void **)vector, 5) == 4,
		"Vectorizar Postorder en un ABB con 4 pokemones cuando le paso un tamaño que exdece el vector devuelvo la cantidad de pokemones que habia en el ABB");
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

	pa2m_afirmar(
		abb_vectorizar_postorden(abb, (void **)vector, 2) == 2,
		"Vectorizar Postorder en un ABB con 4 pokemones cuando le paso un tamaño inferiro a la cantidad de pokemones en el ABB devuelvo la capacidad que le pasamos a la funcion (2 en este caso)");
	abb_destruir(abb);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Pruebas combinadas

void VectorizarPirmeroPostordenLuegoPreordenYLuegoInorderTerminaConLosElementosDelVectorInorder()
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

	pa2m_afirmar(
		abb_vectorizar_postorden(abb, (void **)vector, 4) == 4,
		"Vectorizar Postorder en un ABB con 4 pokemones devuelve 4");
	pa2m_afirmar(
		vector[0]->tipo == 'A',
		"El primer elemento del vector tiene tipo esperado (de Blastoise)");
	pa2m_afirmar(
		vector[1]->tipo == 'F',
		"El segundo elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(
		vector[2]->tipo == 'P',
		"El tercer elemento del vector tiene tipo esperado (de Venusaur)");
	pa2m_afirmar(
		vector[3]->tipo == 'E',
		"El cuarto elemento del vector tiene tipo esperado (de Pikachu)");
	pa2m_afirmar(
		abb_vectorizar_preorden(abb, (void **)vector, 4) == 4,
		"Vectorizar Preorden en un ABB con 4 pokemones devuelve 4");
	pa2m_afirmar(
		vector[0]->tipo == 'E',
		"El primer elemento del vector tiene tipo esperado (de Pikachu)");
	pa2m_afirmar(
		vector[1]->tipo == 'F',
		"El segundo elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(
		vector[2]->tipo == 'A',
		"El tercer elemento del vector tiene tipo esperado (de Blastoise)");
	pa2m_afirmar(
		vector[3]->tipo == 'P',
		"El cuarto elemento del vector tiene tipo esperado (de venusaur)");
	pa2m_afirmar(
		abb_vectorizar_inorden(abb, (void **)vector, 4) == 4,
		"Vectorizar Inorder en un ABB con 4 pokemones devuelve 4 ");
	pa2m_afirmar(
		vector[0]->tipo == 'A',
		"El primer elemento del vector tiene tipo esperado (de Blastoise)");
	pa2m_afirmar(
		vector[1]->tipo == 'F',
		"El segundo elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(
		vector[2]->tipo == 'E',
		"El tercer elemento del vector tiene tipo esperado (de Pikachu)");
	pa2m_afirmar(
		vector[3]->tipo == 'P',
		"El cuarto elemento del vector tiene tipo esperado (de Venusaur)");
	abb_destruir(abb);
}

void VectorizarInorderYLuegoEliminarAlgunElementoDevuelveTrue()
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
	void *encontrado = NULL;

	pa2m_afirmar(abb_vectorizar_inorden(abb, (void **)vector, 4) == 4,
		     "Vectorizar Inorder en un ABB con 4 pokemones devuelve 4");
	pa2m_afirmar(
		vector[0]->tipo == 'A',
		"El primer elemento del vector tiene tipo esperado (de Blastoise)");
	pa2m_afirmar(
		vector[1]->tipo == 'F',
		"El segundo elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(
		vector[2]->tipo == 'E',
		"El tercer elemento del vector tiene tipo esperado (de Pikachu)");
	pa2m_afirmar(
		vector[3]->tipo == 'P',
		"El cuarto elemento del vector tiene tipo esperado (de Venusaur)");
	pa2m_afirmar(
		abb_quitar(abb, &charizard, &encontrado),
		"Quitar a Charizard (que tiene como hijo a Blastoise) devuelve true");
	pa2m_afirmar(
		abb_vectorizar_inorden(abb, (void **)vector, 4) == 3,
		"Vectorizar Inorder en un ABB con 3 pokemones (eliminando a Charizard) devuelve 3");
	pa2m_afirmar(
		vector[0]->tipo == 'A',
		"El primer elemento del vector tiene tipo esperado (de Blastoise)");
	pa2m_afirmar(
		vector[1]->tipo == 'E',
		"El segundo elemento del vector tiene tipo esperado (de Pikachu)");
	pa2m_afirmar(
		vector[2]->tipo == 'P',
		"El tercer elemento del vector tiene tipo esperado (de Venusaur)");
	pa2m_afirmar(abb_obtener(abb, &blastoise) != NULL,
		     "Encontre al ultimo elemento del vector (Blastoise)");
	abb_destruir(abb);
}

void VectorizarInorderYLuegoEliminarTodoElArbolNoDevuelveNada()
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
	void *encontrado = NULL;

	pa2m_afirmar(abb_vectorizar_inorden(abb, (void **)vector, 4) == 4,
		     "Vectorizar Inorder en un ABB con 4 pokemones devuelve 4");
	pa2m_afirmar(
		vector[0]->tipo == 'A',
		"El primer elemento del vector tiene tipo esperado (de Blastoise)");
	pa2m_afirmar(
		vector[1]->tipo == 'F',
		"El segundo elemento del vector tiene tipo esperado (de Charizard)");
	pa2m_afirmar(
		vector[2]->tipo == 'E',
		"El tercer elemento del vector tiene tipo esperado (de Pikachu)");
	pa2m_afirmar(
		vector[3]->tipo == 'P',
		"El cuarto elemento del vector tiene tipo esperado (de Venusaur)");
	pa2m_afirmar(
		abb_quitar(abb, &charizard, &encontrado),
		"Quitar a Charizard (que tiene como hijo a Blastoise) devuelve true");
	pa2m_afirmar(
		abb_quitar(abb, &blastoise, &encontrado),
		"Quitar a Blastoise (que tiene como hijo a Blastoise) devuelve true");
	pa2m_afirmar(
		abb_quitar(abb, &venusaur, &encontrado),
		"Quitar a venusaur (que tiene como hijo a Blastoise) devuelve true");
	pa2m_afirmar(
		abb_quitar(abb, &pikachu, &encontrado),
		"Quitar a pikachu (que tiene como hijo a Blastoise) devuelve true");
	pa2m_afirmar(abb_vectorizar_inorden(abb, (void **)vector, 4) == 0,
		     "Vectorizar Inorder en un ABB con 0 pokemones devuelve 0");
	pa2m_afirmar(abb_obtener(abb, &blastoise) == NULL,
		     "No encontre a Blastoise dentro del ABB");
	pa2m_afirmar(abb_obtener(abb, &pikachu) == NULL,
		     "No encontre a Pikachu dentro del ABB");
	pa2m_afirmar(abb_obtener(abb, &charizard) == NULL,
		     "No encontre a Charizard dentro del ABB");
	pa2m_afirmar(abb_obtener(abb, &venusaur) == NULL,
		     "No encontre a Venusaur dentro del ABB");
	pa2m_afirmar(abb_cantidad(abb) == 0, "No hay elementos en el ABB");
	abb_destruir(abb);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Pruebas Extras

void EliminarRaizDevuleveLaRaiz()
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
	struct pokemon *encontrado = NULL;

	pa2m_afirmar(abb_obtener(abb, &pikachu) != NULL,
		     "Pikachu existe en el ABB");
	pa2m_afirmar(abb_quitar(abb, &pikachu, (void *)&encontrado),
		     "Quitar Pikachu devuelve true");
	pa2m_afirmar(encontrado != NULL,
		     "El elemento eliminado no es NULL (debería ser Pikachu)");
	pa2m_afirmar(
		strcmp(encontrado->nombre, "Pikachu") == 0,
		"El elemento quitado tiene el mismo nombre que el pokemon que queriamos quitamos (de pikachu)");
	pa2m_afirmar(
		encontrado->tipo == 'E',
		"El elemento quitado tiene el mismo tipo que el pokemon que queriamos quitamos (de pikachu)");
	pa2m_afirmar(
		encontrado->fuerza == 55,
		"El elemento quitado tiene la misma fuerza que el pokemon que queriamos quitamos (de pikachu)");
	pa2m_afirmar(
		encontrado->destreza == 40,
		"El elemento quitado tiene la misma destreza que el pokemon que queriamos quitamos (de pikachu)");
	pa2m_afirmar(
		encontrado->resistencia == 50,
		"El elemento quitado tiene la misma resistencia que el pokemon que queriamos quitamos (de pikachu)");
	pa2m_afirmar(abb_obtener(abb, &pikachu) == NULL,
		     "Pikachu ya no existe en el árbol");

	pa2m_afirmar(abb_quitar(abb, &charizard, (void *)&encontrado),
		     "Quitar Charizard devuelve true");
	pa2m_afirmar(
		strcmp(encontrado->nombre, "Charizard") == 0,
		"El elemento quitado tiene el mismo nombre que el pokemon que queriamos quitamos (de Charizard)");
	pa2m_afirmar(abb_quitar(abb, &blastoise, (void *)&encontrado),
		     "Quitar Blastoise devuelve true");
	pa2m_afirmar(
		strcmp(encontrado->nombre, "Blastoise") == 0,
		"El elemento quitado tiene el mismo nombre que el pokemon que queriamos quitamos (de Blastoise)");
	pa2m_afirmar(abb_quitar(abb, &venusaur, (void *)&encontrado),
		     "Quitar Venusaur devuelve true");
	pa2m_afirmar(
		strcmp(encontrado->nombre, "Venusaur") == 0,
		"El elemento quitado tiene el mismo nombre que el pokemon que queriamos quitamos (de Venusaur)");
	abb_destruir(abb);
}

void IterarYCortarPrematuramenteDevulveCantidadCorrecta()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };
	struct pokemon mewtwo = { "Mewtwo", 'A', 97, 167, 220 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	abb_insertar(abb, &mewtwo);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);
	abb_insertar(abb, &blastoise);
	pa2m_afirmar(
		abb_iterar_inorden(abb, continuar_iteracion_cortada, NULL) == 4,
		"Iterar Inorder en un ABB con 8 pokemones y detener en mewtwo (pokemon numero 5) devuelve 4");

	abb_destruir(abb);
}

void EliminarAlMismoPokemonDevuelveTrueYDespuesFalse()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);

	struct pokemon *encontrado = NULL;

	pa2m_afirmar(abb_cantidad(abb) == 3, "La canidad de pokemones es 4");
	pa2m_afirmar(abb_quitar(abb, &pikachu, (void *)&encontrado),
		     "Intentar quitar un pokemon que existe devuelve true");
	pa2m_afirmar(encontrado != NULL,
		     "El elemento eliminado es distinto de NULL");
	pa2m_afirmar(abb_cantidad(abb) == 2,
		     "La canidad de pokemones baja a 2 si elimino a Pikachu");
	pa2m_afirmar(!abb_quitar(abb, &pikachu, (void *)&encontrado),
		     "Intentar quitar a Pikachu de nuevo  devuelve true");
	pa2m_afirmar(encontrado == NULL,
		     "El elemento eliminado es distinto de NULL");
	pa2m_afirmar(
		abb_cantidad(abb) == 2,
		"La canidad de pokemones sigue siendo 2 si intento eliminar un pokemon que ya no existe");
	abb_destruir(abb);
}

void EliminarNodoConElementoNull()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);

	struct pokemon *elemento_null = NULL;
	abb_insertar(abb, elemento_null);

	struct pokemon *encontrado = NULL;

	pa2m_afirmar(abb_cantidad(abb) == 4, "La cantidad de pokemones es 4");

	pa2m_afirmar(
		abb_quitar(abb, elemento_null, (void *)&encontrado),
		"Intentar quitar un pokemon con elemento NULL devuelve true");

	pa2m_afirmar(encontrado == NULL,
		     "El elemento eliminado es NULL (porque era NULL)");

	// Verificar que la cantidad de nodos ha disminuido
	pa2m_afirmar(
		abb_cantidad(abb) == 3,
		"La cantidad de pokemones baja a 3 si elimino el nodo con elemento NULL");

	// Intentar quitar a Pikachu nuevamente para asegurar que sigue estando
	pa2m_afirmar(abb_quitar(abb, &pikachu, (void *)&encontrado),
		     "Intentar quitar a Pikachu devuelve true");
	pa2m_afirmar(encontrado != NULL,
		     "El elemento eliminado es distinto de NULL");

	pa2m_afirmar(abb_cantidad(abb) == 2,
		     "La cantidad de pokemones baja a 2 si elimino a Pikachu");

	// Intentar quitar a Pikachu nuevamente para confirmar que ya no está
	pa2m_afirmar(!abb_quitar(abb, &pikachu, (void *)&encontrado),
		     "Intentar quitar a Pikachu de nuevo devuelve false");

	pa2m_afirmar(
		encontrado == NULL,
		"El elemento eliminado es NULL (porque no se pudo eliminar)");

	pa2m_afirmar(
		abb_cantidad(abb) == 2,
		"La cantidad de pokemones sigue siendo 2 si intento eliminar un pokemon que ya no existe");

	// Limpiar el ABB
	abb_destruir(abb);
}

void EliminarElementoNoEncontradoDevuelveFalse()
{
	abb_t *abb = abb_crear(comparador);

	// Creación de un Pokémon que será insertado
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };

	// Insertar solo Pikachu en el ABB
	abb_insertar(abb, &pikachu);

	struct pokemon *elemento_eliminado = NULL;

	// Intentar eliminar un Pokémon que no está en el ABB (Charizard)
	pa2m_afirmar(
		!abb_quitar(abb, &charizard, (void **)&elemento_eliminado),
		"Intentar eliminar un Pokémon que no se encuentra en el ABB devuelve false.");
	pa2m_afirmar(
		elemento_eliminado == NULL,
		"El elemento eliminado es NULL porque no se encontró en el ABB.");

	// Afirmar que la cantidad de Pokémon sigue siendo 1
	pa2m_afirmar(
		abb_cantidad(abb) == 1,
		"La cantidad de Pokémon sigue siendo 1 tras intentar eliminar un Pokémon no encontrado.");

	// Limpiar recursos
	abb_destruir(abb);
}

void EliminarElementoNuloDevuelveFalse()
{
	abb_t *abb = abb_crear(comparador);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

	abb_insertar(abb, &pikachu);
	abb_insertar(abb, &charizard);
	abb_insertar(abb, &venusaur);

	struct pokemon *encontrado = NULL;

	// Afirmamos que el árbol tiene 3 elementos al inicio
	pa2m_afirmar(abb_cantidad(abb) == 3, "La cantidad de pokemones es 3");

	// Intentamos quitar un elemento NULL
	pa2m_afirmar(!abb_quitar(abb, NULL, (void *)&encontrado),
		     "Intentar quitar un elemento NULL devuelve false");

	// Afirmamos que el elemento encontrado es NULL
	pa2m_afirmar(
		encontrado == NULL,
		"El elemento eliminado es NULL (porque no puedo eliminar NULL)");

	// La cantidad de pokemones debe seguir siendo 3
	pa2m_afirmar(
		abb_cantidad(abb) == 3,
		"La cantidad de pokemones sigue siendo 3 si intento eliminar un elemento NULL");

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

	pa2m_nuevo_grupo("Pruebas de buscar en el ABB");
	ObtenerElementoEnABBVaciaDevuelveFalse();
	ObtenerElementoConPunteroNuloNoModificaNada();
	BuscarPrimerPokemonDevuelveStatsDelPokemonBuscado();
	BuscarMedioPokemonDevuelveStatsDelPokemonBuscad2();
	BuscarPokemonInexistenteDevuelveNULL();
	BuscarPokemonInexistenteEnABBVaciaDevuelveNULL();

	pa2m_nuevo_grupo("Pruebas de Eliminar/quitar con 0 o 1 hijo");
	EliminarElementoNULLDevuelveFalse();
	EliminarPokemonInexistenteDevuelveFalse();
	EliminarElementoNULLDevuelveFalse();
	EliminarElementoUnicoDevuelveTrue();
	EliminarElementoExistenteDevuelveTrue();
	EliminarElementoYVolverAInsertarDevulveTrue();
	EliminarRaizYVuelvoAInsertarOtraRaizDevulveTrue();
	EliminarElementoConUnHijoDevuelveTrue();
	EliminarElementoConUnHijoYAgregarOtraVezDevuelveTrue();

	pa2m_nuevo_grupo("Pruebas de Eliminar/quitar con 2 hijos");
	EliminarElementoConDosHijosDevuelveTrue();
	EliminarElementoConDosHijosYAgregoDeNuevoDevuelveTrue();
	EliminarNodoConPredecesorInordenConHijoIzquierdo();
	EliminarRaizDevuleveTrue();
	EliminarTodoElABBDevulveTrue();

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

	pa2m_nuevo_grupo("Pruebas de funciones combinadas");
	VectorizarPirmeroPostordenLuegoPreordenYLuegoInorderTerminaConLosElementosDelVectorInorder();
	VectorizarInorderYLuegoEliminarAlgunElementoDevuelveTrue();
	VectorizarInorderYLuegoEliminarTodoElArbolNoDevuelveNada();

	pa2m_nuevo_grupo("Pruebas Extra");
	EliminarRaizDevuleveLaRaiz();
	IterarYCortarPrematuramenteDevulveCantidadCorrecta();
	//EliminarAlMismoPokemonDevuelveTrueYDespuesFalse();
	//EliminarNodoConElementoNull();
	// EliminarElementoNoEncontradoDevuelveFalse();
	// EliminarElementoNuloDevuelveFalse();

	return pa2m_mostrar_reporte();
}