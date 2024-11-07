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

void CrearHashRetornaAlgoNoNULL(){
	hash_t *hash = hash_crear(2);
	pa2m_afirmar(hash != NULL, "El hash devolvio algo no nulo");
	hash_destruir(hash);
}

void CrearHashRetornaNULLSiCantidadInicial0RetornaNULL(){
	hash_t *hash = hash_crear(0);
	pa2m_afirmar(hash != NULL, "El hash devolvio algo no NULL si la cantidad inicial es 0");
	hash_destruir(hash);
}

void LaCantidadDeElementosInicialesEnhashNoNulaEs0(){
	hash_t *hash = hash_crear(2);
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad inicial de un hash es 0");
	hash_destruir(hash);
}

void LaCantidadDeElementosInicialesEnhashNulaEs0(){
	hash_t *hash = NULL;
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad inicial de un hash NULL es 0");
	hash_destruir(hash);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de insertar
void InsertarEnHAshNULLDevuelveFalse(){
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


void InsertarBienDevuelveTrue(){
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

void InsertarVAriosElementosDevuelveTrue(){
	hash_t *hash = hash_crear(2);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	char *clave1 = pikachu.nombre;
	void *valor1 = &(pikachu.fuerza);

	char *clave2 = charizard.nombre;
	void *valor2 = &(charizard.fuerza);

	char *clave3 = venusaur.nombre;
	void *valor3 = &(venusaur.fuerza);

	char *clave4 = blastoise.nombre;
	void *valor4 = &(blastoise.fuerza);
	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash,clave1,valor1,&encontrado),
		     "insertamos correctamente un elemento al diccionario");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad aumento correctemente en 1"); 
	pa2m_afirmar(hash_insertar(hash,clave2,valor2,&encontrado),
		     "insertamos correctamente un elemento al diccionario");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad aumento correctemente en 2"); 
	pa2m_afirmar(hash_insertar(hash,clave3,valor3,&encontrado),
		     "insertamos correctamente un elemento al diccionario");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad aumento correctemente en 3"); 
	pa2m_afirmar(hash_insertar(hash,clave4,valor4,&encontrado),
		     "insertamos correctamente un elemento al diccionario");
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "La cantidad aumento correctemente en 4"); 			 
	pa2m_afirmar( hash_buscar(hash,clave2) == valor2,
		     "Encontre la clave porque me devolvio el tipo de fuerza esperada ");	 
	hash_destruir(hash);
}

void InsertarBienPeroConEncontradoNULLDevuelveTrue(){
	hash_t *hash = hash_crear(2);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	char *clave = pikachu.nombre;
	void *valor = &(pikachu.fuerza);
	pa2m_afirmar(hash_insertar(hash,clave,valor,NULL),
		     "insertamos correctamente un elemento al diccionario Con Encontrado como NULL");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad aumento correctemente en 1"); 			 
	pa2m_afirmar( hash_buscar(hash,clave) == valor,
		     "Encontre la clave que buscaba");	 
	hash_destruir(hash);
}

void InsertarRepetidosNoAuemntaLaCantidadYMePisaElValor(){
	hash_t *hash = hash_crear(2);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	char *clave = pikachu.nombre;
	void *valor = &(pikachu.fuerza);
	void *valor_nuevo = &(pikachu.destreza);

	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash,clave,valor,&encontrado),
		     "insertamos correctamente un elemento al diccionario");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad aumento correctemente en 1"); 
	pa2m_afirmar(encontrado == NULL,
		     "encontrado se mantiene en NULL porque no reemplazamos nada aun ");			 
	pa2m_afirmar( hash_buscar(hash,clave) == valor,
		     "Encontre la clave porque es distinto de NULL");
	pa2m_afirmar(hash_insertar(hash,clave,valor_nuevo,&encontrado),
		     "insertamos correctamente un elemento repetido al diccionario");
	pa2m_afirmar(encontrado == valor,
		     "encontrado tiene el mismo valor que antes de ser reemplazado ");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad aumento correctemente en 1");
	pa2m_afirmar( hash_buscar(hash,clave) == valor_nuevo,
		     "El valor encontrado es el mismo que el del valor nuevo"); 
	hash_destruir(hash);
}

void InsertarUnvalorNULLdevuelveTrue(){
	hash_t *hash = hash_crear(2);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	char *clave = pikachu.nombre;
	void *valor = NULL;

	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash,clave,valor,&encontrado),
		     "insertamos correctamente un elemento al diccionario");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad aumento correctemente en 1"); 			 
	pa2m_afirmar( hash_buscar(hash,clave) == NULL,
		     "Encontre la clave a pesar de que el valor de la misma es NULL");
	hash_destruir(hash);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de buscar
void BuscarenHashNULLDevuelveNULL(){
	hash_t *hash = hash_crear(2);
	char *clave = "noc";
	pa2m_afirmar(hash_buscar(NULL,clave) == NULL, "buscar en un hash NULL devuelve NULL");
	hash_destruir(hash);
}

void BuscarenHashVAcioDevuelveNULL(){
	hash_t *hash = hash_crear(2);
	char *clave = "noc";
	pa2m_afirmar(hash_buscar(hash,clave) == NULL, "buscar en un hash vacio devuelve NULL");
	hash_destruir(hash);
}

void BuscarUnaClaveInexistenteDevuelveNULL(){
	hash_t *hash = hash_crear(2);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };

	char *clave = pikachu.nombre;
	void *valor = &(pikachu.fuerza);
	char *clave_inexistente = charizard.nombre;

	void *encontrado = NULL;
	pa2m_afirmar(hash_insertar(hash,clave,valor,&encontrado),
		     "insertamos correctamente un elemento al diccionario");			 
	pa2m_afirmar( hash_buscar(hash,clave_inexistente) == NULL,
		     "Devuelve NULL en caso de que busquemos una clave inexistente");
	hash_destruir(hash);
}


void BuscarVariosPokemonesDevuelveSiempreElValorBucado(){
	hash_t *hash = hash_crear(3);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };
	struct pokemon mewtwo = { "Mewtwo", 'P', 541, 654, 320 };

	char *clave1 = pikachu.nombre;
	void *valor1 = &(pikachu.fuerza);

	char *clave2 = charizard.nombre;
	void *valor2 = &(charizard.fuerza);

	char *clave3 = venusaur.nombre;
	void *valor3 = &(venusaur.fuerza);

	char *clave4 = blastoise.nombre;
	void *valor4 = &(blastoise.fuerza);

	char *clave5 = mewtwo.nombre;
	void *valor5 = &(mewtwo.fuerza);

	void *encontrado = NULL;

	hash_insertar(hash,clave1,valor1,&encontrado);
	hash_insertar(hash,clave2,valor2,&encontrado);
	hash_insertar(hash,clave3,valor3,&encontrado);
	hash_insertar(hash,clave4,valor4,&encontrado);
	hash_insertar(hash,clave5,valor5,&encontrado);

	pa2m_afirmar( hash_cantidad(hash) == 5,
		     "Hay 5 pokemones");
	pa2m_afirmar(hash_buscar(hash,clave3) == &(venusaur.fuerza),
		     "Busque la clave venusaur y me devolvio su fuerza");
	pa2m_afirmar(hash_buscar(hash,clave5) == &(mewtwo.fuerza),
		     "Busque la clave mewtwo y me devolvio su fuerza");
	pa2m_afirmar(hash_buscar(hash,clave1) == &(pikachu.fuerza),
		     "Busque la clave pikachu y me devolvio su fuerza");
	pa2m_afirmar(hash_buscar(hash,clave4) == &(blastoise.fuerza),
		     "Busque la clave blastoise y me devolvio su fuerza");
	pa2m_afirmar(hash_buscar(hash,clave2) == &(charizard.fuerza),
		     "Busque la clave charizard y me devolvio su fuerza");
	hash_destruir(hash);
}

void BuscarClaveConVAloresActualizadosDevuelveUltimoValorInsertado(){
	hash_t *hash = hash_crear(3);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	char *clave1 = pikachu.nombre;
	void *valor1 = &(pikachu.fuerza);

	char *clave2 = pikachu.nombre;
	void *valor2 = &(charizard.fuerza);

	char *clave3 = pikachu.nombre;
	void *valor3 = &(venusaur.fuerza);

	char *clave4 = pikachu.nombre;
	void *valor4 = &(blastoise.fuerza);

	void *encontrado = NULL;

	hash_insertar(hash,clave1,valor1,&encontrado);
	hash_insertar(hash,clave2,valor2,&encontrado);
	hash_insertar(hash,clave3,valor3,&encontrado);
	hash_insertar(hash,clave4,valor4,&encontrado);

	pa2m_afirmar(hash_buscar(hash,clave2) == &(blastoise.fuerza),
		    "Buscamos la clave pikachu y nos devolvio el ultimo valor actualizado (la fuerza de blastoise que es 8)");
	hash_destruir(hash);
}
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Pruebas de eliminar
void EliminarenHashNULLDevuelveNULL(){
	hash_t *hash = hash_crear(3);
	char *clave = "noc";
	pa2m_afirmar(hash_quitar(NULL,clave) == NULL, "Quitar en un hash NULL devuelve NULL");
	hash_destruir(hash);
}

void EliminarenHashVacioDevuelveNULL(){
	hash_t *hash = hash_crear(3);
	char *clave = "noc";
	pa2m_afirmar(hash_quitar(hash,clave) == NULL, "Quitar en un hash vacio devuelve NULL");
	hash_destruir(hash);
}

void EliminarUnSoloElementoDevulveSuClave(){
	hash_t *hash = hash_crear(3);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	char *clave = pikachu.nombre;
	void *valor = &(pikachu.fuerza);
	void *encontrado = NULL;
	
	hash_insertar(hash,clave,valor,&encontrado);
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad aumento correctemente en 1"); 			 
	pa2m_afirmar( hash_quitar(hash,clave) == valor,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad se decremento correctemente en 1 (el hash esta vacio)");	 
	hash_destruir(hash);
}

void InsertarVariosPokemonesYeliminarlosExitosamente(){
	hash_t *hash = hash_crear(3);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	char *clave1 = pikachu.nombre;
	void *valor1 = &(pikachu.fuerza);

	char *clave2 = charizard.nombre;
	void *valor2 = &(charizard.fuerza);

	char *clave3 = venusaur.nombre;
	void *valor3 = &(venusaur.fuerza);

	char *clave4 = blastoise.nombre;
	void *valor4 = &(blastoise.fuerza);

	void *encontrado = NULL;

	hash_insertar(hash,clave1,valor1,&encontrado);
	hash_insertar(hash,clave2,valor2,&encontrado);
	hash_insertar(hash,clave3,valor3,&encontrado);
	hash_insertar(hash,clave4,valor4,&encontrado);

	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "Hay 4 pokemones");
	pa2m_afirmar( hash_quitar(hash,clave1) == valor1,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad se decremento correctemente en 1 (hay 3 pokemones)");
	pa2m_afirmar( hash_quitar(hash,clave2) == valor2,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad se decremento correctemente en 1 (hay 2 pokemones)");
	pa2m_afirmar( hash_quitar(hash,clave3) == valor3,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad se decremento correctemente en 1 (hay 1 pokemon)");
	pa2m_afirmar( hash_quitar(hash,clave4) == valor4,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad se decremento correctemente en 1 (hash vacio)");
	hash_destruir(hash);
}

void InsertarVariosPokemones(){
	hash_t *hash = hash_crear(3);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	char *clave1 = pikachu.nombre;
	void *valor1 = &(pikachu.fuerza);

	char *clave2 = charizard.nombre;
	void *valor2 = &(charizard.fuerza);

	char *clave3 = venusaur.nombre;
	void *valor3 = &(venusaur.fuerza);

	char *clave4 = blastoise.nombre;
	void *valor4 = &(blastoise.fuerza);

	void *encontrado = NULL;

	hash_insertar(hash,clave1,valor1,&encontrado);
	hash_insertar(hash,clave2,valor2,&encontrado);
	hash_insertar(hash,clave3,valor3,&encontrado);
	hash_insertar(hash,clave4,valor4,&encontrado);

	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "Hay 4 pokemones");
	pa2m_afirmar( hash_quitar(hash,clave1) == valor1,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad se decremento correctemente en 1 (hay 3 pokemones)");
	pa2m_afirmar( hash_quitar(hash,clave1) == valor1,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar( hash_buscar(hash,clave1) == NULL,
		     "Buscar una clave que ya no existe devuelve NULL");
	for (int i = 0; i < 3; i++){
		pa2m_afirmar( hash_quitar(hash,clave1) == NULL,
		    "Intentar eliminar de nuevo una clave que ya no existe devuelve NULL");
	}
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad se mantuvo (hay 3 pokemones)");
	hash_destruir(hash);
}

void EliminoTodosLosPokemonesAgreggodeNuevoYEliminoFuncionaBien(){
	hash_t *hash = hash_crear(3);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	char *clave1 = pikachu.nombre;
	void *valor1 = &(pikachu.fuerza);

	char *clave2 = charizard.nombre;
	void *valor2 = &(charizard.fuerza);

	char *clave3 = venusaur.nombre;
	void *valor3 = &(venusaur.fuerza);

	char *clave4 = blastoise.nombre;
	void *valor4 = &(blastoise.fuerza);

	void *encontrado = NULL;

	hash_insertar(hash,clave1,valor1,&encontrado);
	hash_insertar(hash,clave2,valor2,&encontrado);
	hash_insertar(hash,clave3,valor3,&encontrado);
	hash_insertar(hash,clave4,valor4,&encontrado);

	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "Hay 4 pokemones");
	pa2m_afirmar( hash_quitar(hash,clave1) == valor1,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "La cantidad se decremento correctemente en 1 (hay 3 pokemones)");
	pa2m_afirmar( hash_quitar(hash,clave2) == valor2,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar(hash_cantidad(hash) == 2,
		     "La cantidad se decremento correctemente en 1 (hay 2 pokemones)");
	pa2m_afirmar( hash_quitar(hash,clave3) == valor3,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "La cantidad se decremento correctemente en 1 (hay 1 pokemon)");
	pa2m_afirmar( hash_quitar(hash,clave4) == valor4,
		     "Se devolvio el valor de la clave del elemento eliminado");
	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "La cantidad se decremento correctemente en 1 (hash vacio)");

	hash_insertar(hash,clave1,valor1,&encontrado);
	hash_insertar(hash,clave2,valor2,&encontrado);
	hash_insertar(hash,clave3,valor3,&encontrado);
	hash_insertar(hash,clave4,valor4,&encontrado);
	pa2m_afirmar(hash_cantidad(hash) == 4,
		     "La cantidad de pokemones es 4 luego de haber eliminado todo el hash y volver a insertar");
	hash_destruir(hash);
}



// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Pruebas de iterar
bool continuar_iteracion(char *clave, void *valor, void *ctx){
	struct pokemon *p = (struct pokemon *)valor;
	if (p) {
		pa2m_afirmar(p != NULL,
			     "Se itera correctamente sobre un pokemon");
		if (strcmp(clave, "Mewtwo") == 0) {
			return false;
		}
	}
	return true;
}

void IterarConHashNULLDevuelve0(){
	hash_t *hash = hash_crear(2);

	size_t elementos_iterados =
		hash_iterar(NULL, continuar_iteracion, NULL);

	pa2m_afirmar(elementos_iterados == 0,
		     "Con un HAsh NULL, itero 0 elementos");
	hash_destruir(hash);
}

void IterarConFuncionNULLDevuelve0(){
	hash_t *hash = hash_crear(2);

	size_t elementos_iterados =
		hash_iterar(hash, NULL, NULL);

	pa2m_afirmar(elementos_iterados == 0,
		     "Con funcion NULL, iteramos 0 eleemntos");
	hash_destruir(hash);
}


void IterarSinElementosDevuelve0(){
	hash_t *hash = hash_crear(2);

	size_t elementos_iterados =
		hash_iterar(hash, continuar_iteracion, NULL);

	pa2m_afirmar(elementos_iterados == 0,
		     "Sin elementos/pokemones en la hash, no se itera");
	hash_destruir(hash);
}

void Iterar3PokemonesDevuelve3ElementosIterados(){
	hash_t *hash = hash_crear(3);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };
	struct pokemon mewtwo = { "Mewtwo", 'P', 541, 654, 320 };

	char *clave1 = pikachu.nombre;
	void *valor1 = &(pikachu.fuerza);

	char *clave2 = charizard.nombre;
	void *valor2 = &(charizard.fuerza);

	char *clave3 = venusaur.nombre;
	void *valor3 = &(venusaur.fuerza);

	char *clave4 = blastoise.nombre;
	void *valor4 = &(blastoise.fuerza);

	char *clave5 = mewtwo.nombre;
	void *valor5 = &(mewtwo.fuerza);

	void *encontrado = NULL;

	hash_insertar(hash,clave5,valor5,&encontrado);
	hash_insertar(hash,clave1,valor1,&encontrado);
	hash_insertar(hash,clave2,valor2,&encontrado);
	hash_insertar(hash,clave3,valor3,&encontrado);
	hash_insertar(hash,clave4,valor4,&encontrado);

	size_t elementos_iterados =
		hash_iterar(hash, continuar_iteracion, NULL);
	pa2m_afirmar(elementos_iterados == 3,
		     "Se iteran correctamente los 3 Pokémon de la hash ya que freno en Mewtwo ");

	hash_destruir(hash);
}

void IterarSinFrenadoDevuelveTodosLosPokemonesEnElHash(){
	hash_t *hash = hash_crear(3);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	char *clave1 = pikachu.nombre;
	void *valor1 = &(pikachu.fuerza);

	char *clave2 = charizard.nombre;
	void *valor2 = &(charizard.fuerza);

	char *clave3 = venusaur.nombre;
	void *valor3 = &(venusaur.fuerza);

	char *clave4 = blastoise.nombre;
	void *valor4 = &(blastoise.fuerza);

	void *encontrado = NULL;

	hash_insertar(hash,clave1,valor1,&encontrado);
	hash_insertar(hash,clave2,valor2,&encontrado);
	hash_insertar(hash,clave3,valor3,&encontrado);
	hash_insertar(hash,clave4,valor4,&encontrado);

	size_t elementos_iterados =
		hash_iterar(hash, continuar_iteracion, NULL);
	pa2m_afirmar(elementos_iterados == 4,
		     "Se iteran correctamente los 4 Pokémon de la hash ya que no hay condicion de frenado en la iteracion (no esta mewtwo)");

	hash_destruir(hash);
}

void IterarConInserccionConMismaClaveDevuelve1(){
	hash_t *hash = hash_crear(3);

	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 8, 167, 220 };

	char *clave1 = pikachu.nombre;
	void *valor1 = &(pikachu.fuerza);

	char *clave2 = pikachu.nombre;
	void *valor2 = &(charizard.fuerza);

	char *clave3 = pikachu.nombre;
	void *valor3 = &(venusaur.fuerza);

	char *clave4 = pikachu.nombre;
	void *valor4 = &(blastoise.fuerza);

	void *encontrado = NULL;

	hash_insertar(hash,clave1,valor1,&encontrado);
	hash_insertar(hash,clave2,valor2,&encontrado);
	hash_insertar(hash,clave3,valor3,&encontrado);
	hash_insertar(hash,clave4,valor4,&encontrado);

	size_t elementos_iterados =
		hash_iterar(hash, continuar_iteracion, NULL);
	pa2m_afirmar(elementos_iterados == 1,
		     "Se iteran correctamente el uncio pokemon en el hash ");

	hash_destruir(hash);
}


int main(){
	pa2m_nuevo_grupo("Pruebas de crear Hash");
	CrearHashRetornaAlgoNoNULL();
	CrearHashRetornaNULLSiCantidadInicial0RetornaNULL();
	LaCantidadDeElementosInicialesEnhashNoNulaEs0();
	LaCantidadDeElementosInicialesEnhashNulaEs0();
	
	pa2m_nuevo_grupo("Pruebas de insertar en Hash");
	InsertarEnHAshNULLDevuelveFalse();
	InsertarConClaveNULLDevuelveFalse();
	InsertarBienDevuelveTrue();
	InsertarVAriosElementosDevuelveTrue();
	InsertarRepetidosNoAuemntaLaCantidadYMePisaElValor();
	InsertarBienPeroConEncontradoNULLDevuelveTrue();
	InsertarUnvalorNULLdevuelveTrue();

	pa2m_nuevo_grupo("Pruebas de buscar en Hash");
	BuscarenHashNULLDevuelveNULL();
	BuscarenHashVAcioDevuelveNULL();	
	BuscarUnaClaveInexistenteDevuelveNULL();
	BuscarVariosPokemonesDevuelveSiempreElValorBucado();
	BuscarClaveConVAloresActualizadosDevuelveUltimoValorInsertado();

	pa2m_nuevo_grupo("Pruebas de eliminar");
	EliminarenHashNULLDevuelveNULL();
	EliminarenHashVacioDevuelveNULL();
	EliminarUnSoloElementoDevulveSuClave();
	InsertarVariosPokemonesYeliminarlosExitosamente();
	EliminoTodosLosPokemonesAgreggodeNuevoYEliminoFuncionaBien();

	pa2m_nuevo_grupo("Pruebas de Iterar en Hash");
	IterarConHashNULLDevuelve0();
	IterarConFuncionNULLDevuelve0();
	IterarSinElementosDevuelve0();
	Iterar3PokemonesDevuelve3ElementosIterados();
	IterarSinFrenadoDevuelveTodosLosPokemonesEnElHash();
	IterarConInserccionConMismaClaveDevuelve1();

	return pa2m_mostrar_reporte();
}