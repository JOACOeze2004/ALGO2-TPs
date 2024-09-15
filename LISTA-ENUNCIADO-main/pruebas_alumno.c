#include "pa2m.h"
#include "src/lista.h"
#include <string.h>
struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};

typedef struct nodo{
    void* elemento;
    struct nodo* siguiente;
}nodo;

typedef struct lista_iterador {
    nodo* nodo_actual_iterador;
    Lista *lista;
}lista_iterador;


int comparar_nombre_pokemon(void *_p1, void *_p2)
{
	struct pokemon *p1 = _p1;
	struct pokemon *p2 = _p2;

	return strcmp(p1->nombre, p2->nombre);
}

void prueba_simple()
{
	int i = 5;
	int j = 5;
	pa2m_afirmar(i == j, "i es igual a j (%d == %d)", i, j);
	pa2m_afirmar(2*i == 10, "2*i es igual a 2 (%d)", 2*i);
}

void CrearListaRetornaAlgoNoNULL(){
	Lista *lista = lista_crear();
	pa2m_afirmar(lista != NULL,"La lista devolvio algo no nulo");
	lista_destruir(lista);
}


void LaCantidadDeElementosInicialesEnListaNoNulaEs0()
{
	Lista *lista = lista_crear();
	size_t cantidad_de_elementos = lista_cantidad_elementos(lista);
	pa2m_afirmar(cantidad_de_elementos == 0 ,"La cantidad inicial de una lista es 0");
	lista_destruir(lista);
}

void LaCantidadDeElementosInicialesEnListaNulaEs0(){
	Lista *lista = NULL;
	size_t cantidad_de_elementos = lista_cantidad_elementos(lista);
	pa2m_afirmar(cantidad_de_elementos == 0 ,"La cantidad inicial de una lista Nula es 0");
	lista_destruir(lista);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de agregar 

void AgregarMasAllaDeCantidadDevuelveFalse()
{
	Lista *lista = lista_crear();
	void *elemento = (int*) 4;
	bool se_agrega = lista_agregar_elemento(lista,1,elemento);
	bool se_agrega_redux = lista_agregar_elemento(lista,0,NULL);
	pa2m_afirmar(!se_agrega ,"No puedo agregar mas alla de la cantidad de elementos que haya");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0 ,"La cantidad inicial de una lista se mantiene en 0");
	pa2m_afirmar(!se_agrega_redux ,"No puedo agregar si el cosa* es NULL");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0 ,"La cantidad inicial de una lista se mantiene en 0");
	
	lista_destruir(lista);
}

void AgregarCorrectamenteAlgoDevuelveTrue()
{
	Lista *lista = lista_crear();
	void *elemento = (int*) 4;
	bool se_agrega = lista_agregar_elemento(lista,0,elemento);
	pa2m_afirmar(se_agrega ,"Se puede agregar un primer elemento");

	pa2m_afirmar(lista_cantidad_elementos(lista) == 1 ,"La cantidad inicial de una lista se aumenta a 1");
	
	
	void *elemento2 = (int*) 12;
	bool se_agrega_segundo = lista_agregar_elemento(lista,1,elemento2);
	pa2m_afirmar(se_agrega_segundo ,"Se puede agregar un segundo elemento");


	pa2m_afirmar(lista_cantidad_elementos(lista) == 2 ,"La cantidad de una lista se aumenta a 2");

	void *elemento2_de_nuevo = (int*) 20;
	bool se_agrega_segundo_de_nuevo = lista_agregar_elemento(lista,1,elemento2_de_nuevo);
	pa2m_afirmar(se_agrega_segundo_de_nuevo ,"Se puede agregar un segundo elemento");

	pa2m_afirmar(lista_cantidad_elementos(lista) == 3 ,"La cantidad de una lista se aumenta a 3");

	lista_destruir(lista);
}

void AgregarAlFinalAlgoDevuelveTrue()
{
	Lista *lista = lista_crear();
	void *elemento = (int*) 4;
	bool se_agrega = lista_agregar_al_final(lista,elemento);
	pa2m_afirmar(se_agrega ,"Se puede agregar un primer elemento");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 1 ,"La cantidad inicial de una lista se aumenta a 1");
	
	
	void *elemento2 = (int*) 12;
	bool se_agrega_segundo = lista_agregar_al_final(lista,elemento2);
	pa2m_afirmar(se_agrega_segundo ,"Se puede agregar un segundo elemento");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 2 ,"La cantidad de una lista se aumenta a 2");

	void *elemento2_de_nuevo = (int*) 20;
	bool se_agrega_segundo_de_nuevo = lista_agregar_al_final(lista,elemento2_de_nuevo);
	pa2m_afirmar(se_agrega_segundo_de_nuevo ,"Se puede agregar un segundo elemento");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 3 ,"La cantidad de una lista se aumenta a 3");
	lista_destruir(lista);
}


void AgregarAlMedioAlgoDevuelveTrue()
{
	Lista *lista = lista_crear();
	void *elemento = (int*) 4;
	lista_agregar_al_final(lista,elemento);	
	void *elemento2 = (int*) 12;
	lista_agregar_al_final(lista,elemento2);
	void *elemento2_de_nuevo = (int*) 20;
	lista_agregar_al_final(lista,elemento2_de_nuevo);

	void *elemento_intermedio1 = (int*) 9;
	bool se_agrega_intermedio1 = lista_agregar_elemento(lista,1,elemento_intermedio1);
	pa2m_afirmar(se_agrega_intermedio1 ,"Se puede agregar un cuarto elemento");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 4 ,"La cantidad de una lista se aumenta a 4 si agrego un elemento de por medio");
	void *elemento_intermedio2 = (int*) 10;
	bool se_agrega_intermedio2 = lista_agregar_elemento(lista,1,elemento_intermedio2);
	pa2m_afirmar(se_agrega_intermedio2 ,"Se puede agregar un quinto elemento");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 5 ,"La cantidad de una lista se aumenta a 5 si agrego un elemento en la posicion recientemente agregada");

	lista_destruir(lista);
}

void AgregarAlfinalNULLDevuelveFalse()
{
	Lista *lista = lista_crear();
	void *elemento = (int*) 4;
	lista_agregar_al_final(lista,elemento);	
	void *elemento2 = (int*) 12;
	lista_agregar_al_final(lista,elemento2);

	void *elemento_nulo = NULL;
	bool se_agrega_final = lista_agregar_al_final(lista,elemento_nulo);

	pa2m_afirmar(!se_agrega_final ,"No se puede agregar un elemento null al final");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 2 ,"La cantidad de una lista se mantiene en 2 si intento agregar un elemento nulo al final");

	lista_destruir(lista);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de buscar
void BuscarPokemonDevuelveElPokemon()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 84, 78, 78};
    struct pokemon bulbasaur = {"Bulbasaur", 'P', 49, 49, 49};

    lista_agregar_al_final(lista, &pikachu);
    lista_agregar_al_final(lista, &charizard);
    lista_agregar_al_final(lista, &bulbasaur);

    void *resultado = lista_buscar_elemento(lista, &charizard, comparar_nombre_pokemon);

    pa2m_afirmar(resultado != NULL, "El Pokémon buscado se encuentra en la lista");
    pa2m_afirmar(strcmp(((struct pokemon *)resultado)->nombre, "Charizard") == 0, "El Pokémon encontrado es Charizard");

    lista_destruir(lista);
}

void BuscarPokemonInexistenteDevuelveNull()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 84, 78, 78};

    lista_agregar_al_final(lista, &pikachu);
    lista_agregar_al_final(lista, &charizard);

    struct pokemon pokemon_inexistente = {"Ho-Oh", 'F', 106, 110, 90};
    void *resultado = lista_buscar_elemento(lista, &pokemon_inexistente, comparar_nombre_pokemon);
    pa2m_afirmar(resultado == NULL, "No se encuentra a Ho-Oh porque no existente en la lista");

    lista_destruir(lista);
}

void BuscarPokemonConFuncionNulaDevuelveNull()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 84, 78, 78};

    lista_agregar_al_final(lista, &pikachu);
    lista_agregar_al_final(lista, &charizard);

    void *resultado = lista_buscar_elemento(lista, &charizard, NULL);
    pa2m_afirmar(resultado == NULL, "No se encuentra a Charizard porque la funcion pasada es null");

    lista_destruir(lista);
}

void BuscarPokemonEnListaVaciaDevuelveNull()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};

    void *resultado = lista_buscar_elemento(lista, &pikachu, comparar_nombre_pokemon);
    pa2m_afirmar(resultado == NULL, "No se encuentra a Pikachu porque la lista es vacia");

    lista_destruir(lista);
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de eliminar
void EliminarPosicionMasAllaDeCantidadDevuelveFalse()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 84, 78, 78};

    lista_agregar_al_final(lista, &pikachu);
    lista_agregar_al_final(lista, &charizard);
	char *elemento_guardado = charizard.nombre;
    pa2m_afirmar(!lista_quitar_elemento(lista, 5, (void**)&elemento_guardado), "No se puede eliminar posicion 5 porque no existente elemento en la lista mas alla");

    lista_destruir(lista);
}

void EliminarConNingunElementoDevuelveFalse()
{
	struct pokemon charizard = {"Charizard", 'F', 84, 78, 78};
    Lista *lista = lista_crear();
	char *elemento_guardado = charizard.nombre;
    pa2m_afirmar(!lista_quitar_elemento(lista, 0, (void**)&elemento_guardado), "No se puede eliminar porque no existente elemento alguno");
    lista_destruir(lista);
}



void EliminarPokemonRetoraTrueYCantidadValida()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 84, 78, 78};
    struct pokemon squirle = {"Squirle", 'A', 20, 51, 71};
    struct pokemon cartepie = {"Cartepie", 'P', 25, 80, 11};

    lista_agregar_al_final(lista, &pikachu);
    lista_agregar_al_final(lista, &charizard);
	lista_agregar_al_final(lista, &squirle);
    lista_agregar_al_final(lista, &cartepie);
	
	char *elemento_guardado = charizard.nombre;
	pa2m_afirmar(lista_cantidad_elementos(lista) == 4 ,"La cantidad de una lista es 4 ");
	pa2m_afirmar(lista_quitar_elemento(lista, 0, (void**)&elemento_guardado), "Se puede eliminar posicion 2");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 3 ,"La cantidad de una lista se reduce a 3 si elimino un pokemon");
	pa2m_afirmar(elemento_guardado != NULL , "El elemento se guardo exitosamente");

    lista_destruir(lista);
}


void EliminarPokemonConElementoGuardadoNuloDevuelveTruePeroNoGuardaElemento()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 84, 78, 78};
    struct pokemon squirle = {"Squirle", 'A', 20, 51, 71};
    struct pokemon cartepie = {"Cartepie", 'P', 25, 80, 11};

    lista_agregar_al_final(lista, &pikachu);
    lista_agregar_al_final(lista, &charizard);
	lista_agregar_al_final(lista, &squirle);
    lista_agregar_al_final(lista, &cartepie);
	void **elemento_a_guardar = NULL;
    pa2m_afirmar(lista_quitar_elemento(lista, 2, elemento_a_guardar), "Se puede eliminar posicion 3");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 3 ,"La cantidad de una lista se reduce a 3 si elimino un pokemon");
	pa2m_afirmar(elemento_a_guardar == NULL , "El elemento no se guardo porque este es null");

    lista_destruir(lista);
}

void EliminarUltimoPokemonDevuelveTrue()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};

    lista_agregar_al_final(lista, &pikachu);	
	char *elemento_guardado = pikachu.nombre;
	pa2m_afirmar(lista_quitar_elemento(lista, 0, (void**)&elemento_guardado), "Se puede eliminar posicion 2");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 0 ,"La cantidad de la lista es 0 (queda vacia)");
	pa2m_afirmar(elemento_guardado != NULL , "El elemento se guardo exitosamente");
    lista_destruir(lista);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de obtener elemento

void ObtenerElementoEnPosicionInvalidaDevuelveFalse()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};

    lista_agregar_al_final(lista, &pikachu);	
	char *elemento_guardado = pikachu.nombre;
	pa2m_afirmar(!lista_obtener_elemento(lista,5,(void**)&elemento_guardado) ,"no se puede obtener el elemento porque la cantidad de elementos es menor al elmento buscado");
	pa2m_afirmar(elemento_guardado == pikachu.nombre , "El elemento no se guardo o modifica");
    lista_destruir(lista);
}

void ObtenerElementoEnListaVaciaDevuelveFalse()
{
    Lista *lista = lista_crear();

    void *elemento_encontrado = NULL;

    pa2m_afirmar(!lista_obtener_elemento(lista, 0, &elemento_encontrado), "Intentar obtener un elemento de una lista vacía devuelve false");
    
    lista_destruir(lista);
}

void ObtenerElementoConPunteroNuloNoModificaNada()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    lista_agregar_al_final(lista, &pikachu);

    pa2m_afirmar(lista_obtener_elemento(lista, 0, NULL), "Obtener un elemento con puntero nulo devuelve true, pero no lo guarda");

    lista_destruir(lista);
}

void ObtenerElementoConElementoBuscadoValidoDevuelveTrue()
{
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};

    lista_agregar_al_final(lista, &pikachu);

    struct pokemon *elemento_guardado = NULL; 
    pa2m_afirmar(lista_obtener_elemento(lista, 0, (void **)&elemento_guardado), "Se puede obtener el elemento buscado");
    pa2m_afirmar(elemento_guardado != NULL, "El elemento se guardó exitosamente");
    pa2m_afirmar(strcmp(elemento_guardado->nombre, "Pikachu") == 0, "Se obtiene correctamente el primer nombre del primer Pokémon");
	pa2m_afirmar(lista_obtener_elemento(lista, 0, (void **)&elemento_guardado) && elemento_guardado->tipo == 'E', "Se obtiene correctamente el tipo del primer Pokémon");
    pa2m_afirmar(lista_obtener_elemento(lista, 0, (void **)&elemento_guardado) && elemento_guardado->fuerza == 55, "Se obtiene correctamente la fuerza del primer Pokémon");
    pa2m_afirmar(lista_obtener_elemento(lista, 0, (void **)&elemento_guardado) && elemento_guardado->destreza == 40, "Se obtiene correctamente la destreza del primer Pokémon");
    pa2m_afirmar(lista_obtener_elemento(lista, 0, (void **)&elemento_guardado) && elemento_guardado->resistencia == 50, "Se obtiene correctamente la resistencia del primer Pokémon");

    lista_destruir(lista);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de iteracion

bool continuar_iteracion(void *elemento, void *ctx) {
    struct pokemon *p = (struct pokemon *)elemento;
    if (p) {
        pa2m_afirmar(p != NULL, "Se itera correctamente sobre un pokemon");
    }
    return true;
}

void IterarSinElementosDevuelve0() {
    Lista *lista = lista_crear();

    size_t elementos_iterados = lista_iterar_elementos(lista, continuar_iteracion, NULL);

    pa2m_afirmar(elementos_iterados == 0, "Sin elementos/pokemones en la lista, no se itera");

    lista_destruir(lista);
}

void Iterar3PokemonesDevuelve3ElementosIterados() {
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 100, 143, 239};
    struct pokemon bulbasaur = {"Bulbasaur", 'P', 49, 49, 65};

    lista_agregar_al_final(lista, &pikachu);
    lista_agregar_al_final(lista, &charizard);
    lista_agregar_al_final(lista, &bulbasaur);

    size_t elementos_iterados = lista_iterar_elementos(lista, continuar_iteracion, NULL);

    pa2m_afirmar(elementos_iterados == 3, "Se iteran correctamente los 3 Pokémon de la lista");

    lista_destruir(lista);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de iterador externo.
void IntentraCrearIteradorExternoConListaNULLDevuelveNULL() {
    Lista *lista = NULL;
	Lista_iterador *iterador_externo = lista_iterador_crear(lista);

    pa2m_afirmar( iterador_externo == NULL, "No se crea el iterador externo si la lista es NULL");
	lista_iterador_destruir(iterador_externo);
}

void CrearIteradorExternoCorrectamenteNoDevuelveNULL() {
	Lista *lista = lista_crear();
	struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    lista_agregar_al_final(lista, &pikachu);

	Lista_iterador *iterador_externo = lista_iterador_crear(lista);
    pa2m_afirmar( iterador_externo != NULL, "Se crea el iterador externo correctamente");

	lista_iterador_destruir(iterador_externo);
    lista_destruir(lista);
}

//Avanzar o ver si hay siguiente

void IteradorDevuelveFalseSiNoHaySiguienteEnListaCon1Elemento() {
    Lista *lista = lista_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    lista_agregar_al_final(lista, &pikachu);

    Lista_iterador *iterador_externo = lista_iterador_crear(lista);

    // Verifica que no haya siguiente nodo
    pa2m_afirmar(!lista_iterador_hay_siguiente(iterador_externo), "El iterador indica correctamente que no hay un siguiente elemento en una lista con 1 elemento");

    lista_iterador_destruir(iterador_externo);
    lista_destruir(lista);
}

void IteradorNoAvanzaSiNoHaySiguiente() {
    Lista *lista = lista_crear();
    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    lista_agregar_al_final(lista, &pikachu);

    Lista_iterador *iterador = lista_iterador_crear(lista);

    pa2m_afirmar(iterador->nodo_actual_iterador != NULL, "El iterador comienza apuntando al nodo inicial");
	
	pa2m_afirmar(!lista_iterador_hay_siguiente(iterador), "El primer elemento no tiene siguiente");

    lista_iterador_avanzar(iterador);
    pa2m_afirmar(iterador->nodo_actual_iterador != NULL, "El iterador no avanza más allá del último nodo, porque el rpimer no tiene mas nodos");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}

void IteradorNoAvanzaSiNoHayNingunElemento() {
    Lista *lista = lista_crear();

    Lista_iterador *iterador = lista_iterador_crear(lista);

    pa2m_afirmar(iterador->nodo_actual_iterador == NULL, "El iterador comienza apuntando al nodo inicial");
	
	pa2m_afirmar(!lista_iterador_hay_siguiente(iterador), "No hay siguiente de una lista Vacia");

    lista_iterador_avanzar(iterador);
    pa2m_afirmar(iterador->nodo_actual_iterador == NULL, "El iterador no avanza porque no se puede avanzar en lista vacia");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}

//Pruebas de ver elemento
void AvanzarHastaCharizardYPidoEseElementooDevuelveCharizard() {
    Lista *lista = lista_crear();
    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 100, 143, 239};
    struct pokemon venusaur = {"Venusaur", 'P', 89, 109, 301};

    lista_agregar_al_final(lista, &pikachu);
    lista_agregar_al_final(lista, &charizard);
    lista_agregar_al_final(lista, &venusaur);
    Lista_iterador *iterador = lista_iterador_crear(lista);

    lista_iterador_avanzar(iterador);

	struct pokemon *elemento_actual = (struct pokemon *)lista_iterador_obtener_elemento_actual(iterador);

    pa2m_afirmar(elemento_actual != NULL, "El iterador no es NULL en una lista completa");
    pa2m_afirmar(strcmp(elemento_actual->nombre, "Charizard") == 0, "El iterador devuelve correctamente el elemento Charizard");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}

void IntentarAvanzarYPidoElementooDevuelveNULL() {
    Lista *lista = lista_crear();
    Lista_iterador *iterador = lista_iterador_crear(lista);

    lista_iterador_avanzar(iterador);

	struct pokemon *elemento_actual = (struct pokemon *)lista_iterador_obtener_elemento_actual(iterador);

    pa2m_afirmar(elemento_actual == NULL, "El iterador es NULL en una lista vacia");

    lista_iterador_destruir(iterador);
    lista_destruir(lista);
}


int main()
{
	pa2m_nuevo_grupo("Pruebas iniciales Lista");
	prueba_simple();
	CrearListaRetornaAlgoNoNULL();
	LaCantidadDeElementosInicialesEnListaNoNulaEs0();
	LaCantidadDeElementosInicialesEnListaNulaEs0();

	pa2m_nuevo_grupo("Pruebas de agregar");

	AgregarMasAllaDeCantidadDevuelveFalse();
	AgregarCorrectamenteAlgoDevuelveTrue();
	AgregarAlFinalAlgoDevuelveTrue();
	AgregarAlMedioAlgoDevuelveTrue();
	AgregarAlfinalNULLDevuelveFalse();
	
	pa2m_nuevo_grupo("Pruebas de buscar");
	BuscarPokemonDevuelveElPokemon();
	BuscarPokemonInexistenteDevuelveNull();
	BuscarPokemonConFuncionNulaDevuelveNull();
	BuscarPokemonEnListaVaciaDevuelveNull();
	
	pa2m_nuevo_grupo("Pruebas de eliminar");
	EliminarPosicionMasAllaDeCantidadDevuelveFalse();
	EliminarConNingunElementoDevuelveFalse();
	EliminarPokemonRetoraTrueYCantidadValida();
	EliminarPokemonConElementoGuardadoNuloDevuelveTruePeroNoGuardaElemento();
	EliminarUltimoPokemonDevuelveTrue();
	
	pa2m_nuevo_grupo("Pruebas de obtener elemento");
	ObtenerElementoEnPosicionInvalidaDevuelveFalse();
	ObtenerElementoEnListaVaciaDevuelveFalse();
	ObtenerElementoConPunteroNuloNoModificaNada();
	ObtenerElementoConElementoBuscadoValidoDevuelveTrue();

	pa2m_nuevo_grupo("Pruebas de iterar lista");
	IterarSinElementosDevuelve0();
	Iterar3PokemonesDevuelve3ElementosIterados();
	
	pa2m_nuevo_grupo("Pruebas de iterador externo");
	IntentraCrearIteradorExternoConListaNULLDevuelveNULL();
	CrearIteradorExternoCorrectamenteNoDevuelveNULL();

	IteradorDevuelveFalseSiNoHaySiguienteEnListaCon1Elemento();
	IteradorNoAvanzaSiNoHaySiguiente();
	IteradorNoAvanzaSiNoHayNingunElemento();
	AvanzarHastaCharizardYPidoEseElementooDevuelveCharizard();
	IntentarAvanzarYPidoElementooDevuelveNULL();

	return pa2m_mostrar_reporte();
}