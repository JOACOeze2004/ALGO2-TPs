#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"
#include <string.h>

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};
//eliminar nodo y iterador
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
    pa2m_afirmar(lista_cantidad_elementos(lista) == 0 ,"La cantidad inicial de una lista es 0");
	void *elemento = (int*) 4;
	bool se_agrega = lista_agregar_elemento(lista,0,elemento);
	pa2m_afirmar(se_agrega ,"Se puede agregar un primer elemento");

	pa2m_afirmar(lista_cantidad_elementos(lista) == 1 ,"La cantidad de una lista se aumenta a 1");
	
	
	void *elemento2 = (int*) 12;
	bool se_agrega_segundo = lista_agregar_elemento(lista,1,elemento2);
	pa2m_afirmar(se_agrega_segundo ,"Se puede agregar un segundo elemento (al final)");


	pa2m_afirmar(lista_cantidad_elementos(lista) == 2 ,"La cantidad de una lista se aumenta a 2");

	void *elemento2_de_nuevo = (int*) 20;
	bool se_agrega_segundo_de_nuevo = lista_agregar_elemento(lista,2,elemento2_de_nuevo);
	pa2m_afirmar(se_agrega_segundo_de_nuevo ,"Se puede agregar un tercer elemento (al final)");

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
	
    struct pokemon *elemento_guardado = NULL;
	pa2m_afirmar(lista_cantidad_elementos(lista) == 4 ,"La cantidad de una lista es 4 ");
	pa2m_afirmar(lista_quitar_elemento(lista, 0, (void**)&elemento_guardado), "Se puede eliminar posicion 0");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 3 ,"La cantidad de una lista se reduce a 3 si elimino un pokemon");
	pa2m_afirmar(elemento_guardado->fuerza == 55 , "El elemento se guardo exitosamente (la fuerza es igual a la del elemento borrado)");

    lista_destruir(lista);
}

void EliminarUltimoPokemonRetoraTrueYCantidadValida()
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
	
    struct pokemon *elemento_guardado = NULL;
	pa2m_afirmar(lista_cantidad_elementos(lista) == 4 ,"La cantidad de una lista es 4 ");
	pa2m_afirmar(lista_quitar_elemento(lista, 4, (void**)&elemento_guardado), "Se puede eliminar posicion 2");
	pa2m_afirmar(lista_cantidad_elementos(lista) == 3 ,"La cantidad de una lista se reduce a 3 si elimino un pokemon");
	pa2m_afirmar(elemento_guardado->fuerza == 25 , "El elemento se guardo exitosamente (la fuerza es igual a la del elemento borrado)");

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

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Pruebas de Cola

void CrearColaRetornaAlgoNoNULL(){
	Cola *cola = cola_crear();
	pa2m_afirmar(cola != NULL,"La cola devolvio algo no nulo");
	pa2m_afirmar(cola_esta_vacía(cola), "La cantidad de elementos en la cola es 0 si esta esta vacia");
	cola_destruir(cola);
}
void CrearColaVaciaRetornaFrenteNULL(){
	Cola *cola = cola_crear();
	pa2m_afirmar(cola_esta_vacía(cola), "La cantidad de elementos en la cola es 0 si esta esta vacia");
	pa2m_afirmar(cola_frente(cola) == NULL, "El frente de la cola es NULL si esta esta vacia");
	cola_destruir(cola);
}

//pruebas de encolar

void EncolarCorrectamenteDevuelveTrue(){
	Cola *cola = cola_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 100, 143, 239};

    pa2m_afirmar(cola_encolar(cola,&pikachu), "Se puedo encolar a Picachu");
	pa2m_afirmar(cola_cantidad(cola) == 1, "La cantidad de elementos en la cola es 1 si agrego 1 elemento correctamente");
	pa2m_afirmar(cola_encolar(cola,&charizard), "Se puedo encolar a Charizard");
	pa2m_afirmar(cola_cantidad(cola) == 2, "La cantidad de elementos en la cola es 2 si agrego 1 elemento correctamente");

	cola_destruir(cola);
}

void EncolarNULLDevuelveFalse(){
	Cola *cola = cola_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    cola_encolar(cola,&pikachu);

	pa2m_afirmar(!cola_encolar(cola,NULL), "No se puedo encolar con puntero NULL");
	pa2m_afirmar(cola_cantidad(cola) == 1, "La cantidad de elementos en la cola sigue siendo 1 si intento agregar un elemento NULL");

	cola_destruir(cola);
}

void EncolarElementosRepetidos(){
    Cola *cola = cola_crear();
    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 100, 143, 239};

    cola_encolar(cola, &pikachu);
    cola_encolar(cola, &charizard);
    cola_encolar(cola, &pikachu); 

    size_t cantidad = cola_cantidad(cola);

    pa2m_afirmar(cantidad == 3, "La cantidad de elementos en la cola es correcta después de encolar elementos repetidos");

    cola_destruir(cola);
}

void EncolarCorrectamenteDevuelveTrueYFrenteCorrecto(){
	Cola *cola = cola_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 100, 143, 239};
    cola_encolar(cola,&pikachu);
    cola_encolar(cola,&charizard);

	pa2m_afirmar(cola_cantidad(cola) == 2, "La cantidad de elementos en la cola es 2 si agrego 1 elemento correctamente");

    struct pokemon *primer_elemento = cola_frente(cola);
    pa2m_afirmar(primer_elemento != NULL, "El frente de la cola no es NULL después de encolar al menos un elemento (aca fueron dos)");
    pa2m_afirmar(primer_elemento == &pikachu, "El primer elemento en la cola debe ser Pikachu (si encole primero a Pichachu)");

	cola_destruir(cola);
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de desencolar

void DesencolarCorrectamenteDevuelveElElementoQuitado(){
	Cola *cola = cola_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 100, 143, 239};
    struct pokemon venusaur = {"Venusaur", 'P', 89, 142, 278};
    struct pokemon blastoise = {"Blastoise", 'A', 97, 167, 220};
    cola_encolar(cola,&pikachu);
    cola_encolar(cola,&charizard);
    cola_encolar(cola,&venusaur);
    cola_encolar(cola,&blastoise);

    size_t cantidad_luego_agregar2 = cola_cantidad(cola);

	pa2m_afirmar(cantidad_luego_agregar2 == 4, "La cantidad de elementos en la cola es 4 si agrego 4 elementos correctamente");
    struct pokemon *elemento_quitado = cola_desencolar(cola);
    pa2m_afirmar(elemento_quitado == &pikachu, "El elemento quitado es pichachu ya que este fue el primer que fue encolado");
	pa2m_afirmar(cola_cantidad(cola) == 3, "La cantidad de elementos en la cola es 3 si descole correctamente");

	cola_destruir(cola);
}

void DesencolarUnaColaVaciaRetornaNuLL(){
	Cola *cola = cola_crear();

	pa2m_afirmar(cola_esta_vacía(cola), "La cantidad de elementos en la cola es 0");
    struct pokemon *elemento_quitado = cola_desencolar(cola);
    pa2m_afirmar(elemento_quitado == NULL, "Retorna NULL si intento descolar en una cola vacia ");
	pa2m_afirmar(cola_esta_vacía(cola) , "La cantidad de elementos en la cola sigue siendo de 0 si intento descolar una cola vacia");

	cola_destruir(cola);
}

void DesencolarCorrectamenteDevuelveElElementoQuitadoPeroEnColaConUnElemento(){
	Cola *cola = cola_crear();
    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    cola_encolar(cola,&pikachu);
    size_t cantidad_luego_agregar2 = cola_cantidad(cola);

	pa2m_afirmar(cantidad_luego_agregar2 == 1, "La cantidad de elementos en la cola es 1");
    struct pokemon *elemento_quitado = cola_desencolar(cola);
    pa2m_afirmar(elemento_quitado == &pikachu, "El elemento quitado es pichachu ya que este fue el primer que fue encolado");
	pa2m_afirmar(cola_esta_vacía(cola), "La cantidad de elementos en la cola seria 0 si descolo el uncio elemento en la cola");

	cola_destruir(cola);
}

void DescolarVariasVecesEnListaConUnElementoDevuelveNULL(){
	Cola *cola = cola_crear();
    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    cola_encolar(cola,&pikachu);
    size_t cantidad_luego_agregar2 = cola_cantidad(cola);

	pa2m_afirmar(cantidad_luego_agregar2 == 1, "La cantidad de elementos en la cola es 1");
    struct pokemon *elemento_quitado = cola_desencolar(cola);
    pa2m_afirmar(elemento_quitado == &pikachu, "El elemento quitado es pichachu ya que este fue el primer que fue encolado");
    struct pokemon *elemento_quitado2 = cola_desencolar(cola);
    pa2m_afirmar(elemento_quitado2 == NULL, "Devuelve NULL si ya no puedo descolar porque ya no hay elementos");

	cola_destruir(cola);
}

void DescolarYEncolarPoneAlMismoElemento(){
	Cola *cola = cola_crear();
    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    cola_encolar(cola,&pikachu);
    struct pokemon *primer_elemento = cola_frente(cola);
    pa2m_afirmar(primer_elemento == &pikachu, "El primer elemento en la cola debe ser Pikachu (si encole primero a Pichachu)");

    struct pokemon *elemento_quitado = cola_desencolar(cola);
    pa2m_afirmar(elemento_quitado == &pikachu, "El elemento quitado es pichachu ya que este fue el primer que fue encolado");
    pa2m_afirmar(cola_esta_vacía(cola), "La cola esta vacia ahora");

    pa2m_afirmar(cola_encolar(cola,elemento_quitado), "La cola tiene 1 elemento ahora");

    struct pokemon *primer_elemento_de_nuevo = cola_frente(cola);
    pa2m_afirmar(primer_elemento_de_nuevo == &pikachu, "El primer elemento en la cola vuelve a ser Pikachu");


	cola_destruir(cola);
}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de pila

void CrearpilaRetornaAlgoNoNULL(){
	Pila *pila = pila_crear();
	pa2m_afirmar(pila != NULL,"La pila devolvio algo no nulo");
	pa2m_afirmar(pila_esta_vacía(pila), "La cantidad de elementos en la pila es 0 si esta esta vacia");
	pila_destruir(pila);
}

void CrearpilaVaciaRetornaTopeNULL(){
	Pila *pila = pila_crear();
	pa2m_afirmar(pila_esta_vacía(pila), "La cantidad de elementos en la pila es 0 si esta esta vacia");
	pa2m_afirmar(pila_tope(pila) == NULL, "El tope de la pila es NULL si esta esta vacia");
	pila_destruir(pila);
}


// pruebas de apilar
void ApilarCorrectamenteDevuelveTrue(){
	Pila *pila = pila_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 100, 143, 239};

    pa2m_afirmar(pila_apilar(pila,&pikachu), "Se puedo apilar a Picachu");
	pa2m_afirmar(pila_cantidad(pila ) == 1, "La cantidad de elementos en la pila es 1 si agrego 1 elemento correctamente");
	pa2m_afirmar(pila_apilar(pila,&charizard), "Se puedo apilar a Charizard");
	pa2m_afirmar(pila_cantidad(pila) == 2, "La cantidad de elementos en la pila es 2 si agrego 1 elemento correctamente");

	pila_destruir(pila);
}

void ApilarNULLDevuelveFalse(){
	Pila *pila = pila_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    pila_apilar(pila,&pikachu);

	pa2m_afirmar(!pila_apilar(pila,NULL), "No se puedo apilar con puntero NULL");
	pa2m_afirmar(pila_cantidad(pila) == 1, "La cantidad de elementos en la pila sigue siendo 1 si intento agregar un elemento NULL");

	pila_destruir(pila);
}

void ApilararCorrectamenteDevuelveTrueYTopeCorrecto(){
	Pila *pila = pila_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 100, 143, 239};
    pila_apilar(pila,&pikachu);
    pila_apilar(pila,&charizard);

	pa2m_afirmar(pila_cantidad(pila) == 2, "La cantidad de elementos en la pila es 2 si agrego 1 elemento correctamente");

    struct pokemon *ultimo_elemento = pila_tope(pila);
    pa2m_afirmar(ultimo_elemento != NULL, "El tope de la pila no es NULL después de apilar al menos un elemento (aca fueron dos)");
    pa2m_afirmar(ultimo_elemento == &charizard, "El tope en la pila debe ser Charizard (si apile primero a Pichachu y despues a Charizard)");

	pila_destruir(pila);
}

// pruebas de desapilar :C

void DesapilararCorrectamenteDevuelveElElementoQuitado(){
	Pila *pila = pila_crear();

    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    struct pokemon charizard = {"Charizard", 'F', 100, 143, 239};
    struct pokemon venusaur = {"Venusaur", 'P', 89, 142, 278};
    struct pokemon blastoise = {"Blastoise", 'A', 97, 167, 220};
    pila_apilar(pila,&pikachu);
    pila_apilar(pila,&charizard);
    pila_apilar(pila,&venusaur);
    pila_apilar(pila,&blastoise);


	pa2m_afirmar(pila_cantidad(pila) == 4, "La cantidad de elementos en la pila es 4 si agrego 4 elementos correctamente");
    struct pokemon *elemento_quitado = pila_desapilar(pila);
    pa2m_afirmar(elemento_quitado == &blastoise, "El elemento quitado es Blastoise ya que este fue el ultimo en apilarse");
	pa2m_afirmar(pila_cantidad(pila) == 3, "La cantidad de elementos en la pila es 3 si desapile correctamente");

	pila_destruir(pila);
}

void DesapilararUnapilaVaciaRetornaNuLL(){
	Pila *pila = pila_crear();

	pa2m_afirmar(pila_esta_vacía(pila), "La cantidad de elementos en la pila es 0");
    struct pokemon *elemento_quitado = pila_desapilar(pila);
    pa2m_afirmar(elemento_quitado == NULL, "Retorna NULL si intento desapilar en una pila vacia");
	pa2m_afirmar(pila_esta_vacía(pila) , "La cantidad de elementos en la pila sigue siendo de 0 si intento desapilar una pila vacia");

	pila_destruir(pila);
}

void DesapilarCorrectamenteDevuelveElElementoQuitadoPeroEnpilaConUnElemento(){
	Pila *pila = pila_crear();
    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    pila_apilar(pila,&pikachu);

	pa2m_afirmar(pila_cantidad(pila) == 1, "La cantidad de elementos en la pila es 1");
    struct pokemon *elemento_quitado = pila_desapilar(pila);
    pa2m_afirmar(elemento_quitado == &pikachu, "El elemento quitado es pichachu ya que este fue el ultimo en ser apilado");
	pa2m_afirmar(pila_esta_vacía(pila), "La cantidad de elementos en la pila seria 0 si desapilo el uncio elemento en la pila");
	
    pila_destruir(pila);
}

void DesapilarVariasVecesEnPilaConUnElementoDevuelveNULL(){
	Pila *pila = pila_crear();
    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    pila_apilar(pila,&pikachu);

	pa2m_afirmar(pila_cantidad(pila) == 1, "La cantidad de elementos en la pila es 1");
    struct pokemon *elemento_quitado = pila_desapilar(pila);
    pa2m_afirmar(elemento_quitado == &pikachu, "El elemento quitado es pichachu ya que este fue el primer que fue encolado");
    struct pokemon *elemento_quitado2 = pila_desapilar(pila);
    pa2m_afirmar(elemento_quitado2 == NULL, "Devuelve NULL si ya no puedo descolar porque ya no hay elementos");

	pila_destruir(pila);
}

void DesapilarYEncolarPoneAlMismoElemento(){
	Pila *pila = pila_crear();
    struct pokemon pikachu = {"Pikachu", 'E', 55, 40, 50};
    pila_apilar(pila,&pikachu);
    struct pokemon *primer_elemento = pila_tope(pila);
    pa2m_afirmar(primer_elemento == &pikachu, "El primer elemento en la cola debe ser Pikachu (si encole primero a Pichachu)");

    struct pokemon *elemento_quitado = pila_desapilar(pila);
    pa2m_afirmar(elemento_quitado == &pikachu, "El elemento quitado es pichachu ya que este fue el primer que fue encolado");
    pa2m_afirmar(pila_esta_vacía(pila), "La cola esta vacia ahora");

    pa2m_afirmar(pila_apilar(pila,elemento_quitado), "La cola tiene 1 elemento ahora");

    struct pokemon *primer_elemento_de_nuevo = pila_tope(pila);
    pa2m_afirmar(primer_elemento_de_nuevo == &pikachu, "El primer elemento en la cola vuelve a ser Pikachu");


	pila_destruir(pila);
}


int main()
{
	pa2m_nuevo_grupo("Pruebas de Lista");
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
    EliminarUltimoPokemonRetoraTrueYCantidadValida();
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

	pa2m_nuevo_grupo("Pruebas de Cola");
    CrearColaRetornaAlgoNoNULL();
    CrearColaVaciaRetornaFrenteNULL();

	pa2m_nuevo_grupo("Pruebas de Encolar");
    EncolarCorrectamenteDevuelveTrue();
    EncolarNULLDevuelveFalse();
    EncolarElementosRepetidos();
    EncolarCorrectamenteDevuelveTrueYFrenteCorrecto();

	pa2m_nuevo_grupo("Pruebas de Desencolar");
    DesencolarCorrectamenteDevuelveElElementoQuitado();
    DesencolarUnaColaVaciaRetornaNuLL();
    DesencolarCorrectamenteDevuelveElElementoQuitadoPeroEnColaConUnElemento();
    DescolarVariasVecesEnListaConUnElementoDevuelveNULL();
    DescolarYEncolarPoneAlMismoElemento();

	pa2m_nuevo_grupo("Pruebas de Pila");
    CrearpilaRetornaAlgoNoNULL();
    CrearpilaVaciaRetornaTopeNULL();

	pa2m_nuevo_grupo("Pruebas de apilar");
    ApilarCorrectamenteDevuelveTrue();
    ApilarNULLDevuelveFalse();
    ApilararCorrectamenteDevuelveTrueYTopeCorrecto();
    //prueba_pila();
	pa2m_nuevo_grupo("Pruebas de desapilar");
    DesapilararCorrectamenteDevuelveElElementoQuitado();
    DesapilararUnapilaVaciaRetornaNuLL();
    DesapilarCorrectamenteDevuelveElElementoQuitadoPeroEnpilaConUnElemento();
    //DesapilarVariasVecesEnPilaConUnElementoDevuelveNULL();
    //DesapilarYEncolarPoneAlMismoElemento();

	return pa2m_mostrar_reporte();
}