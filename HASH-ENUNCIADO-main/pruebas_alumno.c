#include "pa2m.h"
#include "src/hash.h"
#include <stdlib.h>
#include <string.h>

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};

void CrearHashRetornaAlgoNoNULL()
{
	hash_t *hash = hash_crear(2);
	pa2m_afirmar(hash != NULL, "El hash devolvio algo no nulo");
	hash_destruir(hash);
}

void CrearHashRetornaNULLSiCantidadInicial0RetornaNULL()
{
	hash_t *hash = hash_crear(0);
	pa2m_afirmar(hash != NULL, "El hash devolvio algo no NULL si la cantidad inicial es 0");
	hash_destruir(hash);
}

void LaCantidadDeElementosInicialesEnhashNoNulaEs0()
{
	hash_t *hash = hash_crear(2);
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad inicial de un hash es 0");
	hash_destruir(hash);
}

void LaCantidadDeElementosInicialesEnhashNulaEs0()
{
	hash_t *hash = NULL;
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad inicial de un hash NULL es 0");
	hash_destruir(hash);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de insertar
void InsertarEnHAshNULLDevuelveFalse()
{
	hash_t *hash = hash_crear(2);
	char *clave = "noc";
	void *encontrado = NULL;

	pa2m_afirmar(!hash_insertar(NULL,clave,NULL,&encontrado),
		     "insertar en un hash NULL devuelve false");
	hash_destruir(hash);
}

void InsertarConClaveNULLDevuelveFalse()
{
	hash_t *hash = hash_crear(2);
	char *clave = NULL;
	void *encontrado = NULL;

	pa2m_afirmar(!hash_insertar(hash,clave,NULL,&encontrado),
		     "insertar con una clave NULL devuelve false");
	hash_destruir(hash);
}


void InsertarBienDevuelveTrue()
{
	hash_t *hash = hash_crear(2);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	char *clave = pikachu.nombre;
	void *valor = &(pikachu.fuerza);
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash,clave,valor,&encontrado),
		     "insertamos correctamente un elemento al diccionario");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad aumento correctemente en 1"); 			 
	pa2m_afirmar( hash_buscar(hash,clave) == valor,
		     "Encontre la clave porque es distinto de NULL");	 
	hash_destruir(hash);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de buscar
void BuscarenHashVAcioDevuelveNULL()
{
	hash_t *hash = hash_crear(2);
	char *clave = "noc";
	pa2m_afirmar(hash_buscar(hash,clave) == NULL, "buscar en un hash vacio devuelve NULL");
	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de crear Hash");
	CrearHashRetornaAlgoNoNULL();
	CrearHashRetornaNULLSiCantidadInicial0RetornaNULL();
	LaCantidadDeElementosInicialesEnhashNoNulaEs0();
	LaCantidadDeElementosInicialesEnhashNulaEs0();
	
	pa2m_nuevo_grupo("Pruebas de insertar en Hash");
	InsertarEnHAshNULLDevuelveFalse();
	InsertarConClaveNULLDevuelveFalse();
	InsertarBienDevuelveTrue();

	pa2m_nuevo_grupo("Pruebas de buscar en Hash");
	BuscarenHashVAcioDevuelveNULL();	


	return pa2m_mostrar_reporte();
}
