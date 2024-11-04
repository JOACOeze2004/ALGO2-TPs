#include "pa2m.h"
#include "src/hash.h"


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
int main()
{
	pa2m_nuevo_grupo("Pruebas de crear Hash");
	CrearHashRetornaAlgoNoNULL();
	CrearHashRetornaNULLSiCantidadInicial0RetornaNULL();
	LaCantidadDeElementosInicialesEnhashNoNulaEs0();
	LaCantidadDeElementosInicialesEnhashNulaEs0();
	
	pa2m_nuevo_grupo("Pruebas de insertar Hash");


	return pa2m_mostrar_reporte();
}
