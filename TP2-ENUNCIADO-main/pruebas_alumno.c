#include "pa2m.h"
#include "src/menu.h"
#include "src/pokedex.h"
#include <string.h>
#include <time.h>

void liberar_pokemon(void *elemento)
{
	struct pokemon *pokemon = elemento;
	if (pokemon != NULL) {
		free(pokemon->nombre);
		free(pokemon->color);
		free(pokemon->patron_movimientos);
		free(pokemon);
	}
}

void funcion_random(void *ctx[]) {
    printf("Hola Mundo, probamos funcion random\n"); 
}

void funcion_random2(void *ctx[]) {
    printf("Adios Mundo, probamos otra funcion random\n"); 
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

bool imprimir_pokemon(void *elemento, void *ctx)
{
	struct pokemon *poke = elemento;
	printf("Nombre: %s, puntaje: %i, color: %s, patron: %s\n",
	       poke->nombre, poke->puntaje, poke->color, poke->patron_movimientos);
	return true;
}


void CrearMenuDevuelveMenu(){
	menu_t *menu = menu_crear();
	pa2m_afirmar(menu != NULL,"Se crear exitosamente un menu");
	menu_destruir(menu);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de agregar y ejecutar opcion

void AgregarOpcionDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'a',funcion_random,NULL), "agregamos una opcion al menu");
	menu_destruir(menu);
}

void AgregarVariasOpcionesAlMenuDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random,NULL), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random,NULL), "agregamos la p como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'J',funcion_random,NULL), "agregamos la J como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'j',funcion_random,NULL), "agregamos la j como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'S',funcion_random,NULL), "agregamos la S como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'s',funcion_random,NULL), "agregamos la s como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'Q',funcion_random,NULL), "agregamos la Q como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'q',funcion_random,NULL), "agregamos la q como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 8, "agregamos en total 8 opciones al menu");

	menu_destruir(menu);
}

void AgregarEnMenuNULLDevuelveFalse(){
	menu_t *menu = NULL;

	pa2m_afirmar(!menu_agregar_opciones(menu,'P',funcion_random,NULL), "No agregamos la P como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'p',funcion_random,NULL), "No agregamos la p como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'J',funcion_random,NULL), "No agregamos la J como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 0, "agregamos en total 0 opciones al menu NULL");

	
	menu_destruir(menu);
}

void AgregarEnMenuConFuncionNULLDevuelveFalse(){
	menu_t *menu = NULL;

	pa2m_afirmar(!menu_agregar_opciones(menu,'P',NULL,NULL), "No agregamos la P como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'p',NULL,NULL), "No agregamos la p como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'J',NULL,NULL), "No agregamos la J como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 0, "agregamos en total 0 opciones (con funcion NULL) al menu");

	
	menu_destruir(menu);
}

void EjecutarAccionLlamaCorrectameneteAfuncion(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random,NULL), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random,NULL), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 2, "agregamos en total 2 opciones al menu");

	pa2m_afirmar(menu_ejecutar_entrada(menu,'P',NULL), "Se pudo ejecutra la funcion guardada.");

	menu_destruir(menu);
}

void AgregarDosVecesMismaOpcionDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random,NULL), "agregamos la P como opcion al menu");

	pa2m_afirmar(menu_ejecutar_entrada(menu,'P',NULL), "Se pudo ejecutra la funcion guardada.");

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random2,NULL), "agregamos la P pero con otra funcion");

	pa2m_afirmar(menu_ejecutar_entrada(menu,'P',NULL), "Se pudo ejecutra la nueva funcion guardada.");

	menu_destruir(menu);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de eliminar

void EliminarOpcionDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random,NULL), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random,NULL), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu,'P'), "pudimos eliminar la opcion P");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 1, "al quitar 1 opcion, solo queda 1 opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu,'p'), "pudimos eliminar la opcion P");
	pa2m_afirmar(menu_cantidad_opciones(menu) == 0, "al quitar 1 opcion, no queda opciones en el  menu");

	menu_destruir(menu);
}

void EliminarOpcionInexistenteDevuelveFalse(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random,NULL), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random,NULL), "agregamos la p como opcion al menu");

	pa2m_afirmar(!menu_eliminar_opcion(menu,'K'), "No podemos eliminar una opcion inexistente");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 2, "La cantidad se mantiene si inentamos eliminar una  opcion inexistente");

	menu_destruir(menu);
}

void EliminarOpcionYReinsertarlaDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random,NULL), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random,NULL), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu,'P'), "pudimos eliminar la opcion P");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 1, "al quitar 1 opcion, solo queda 1 opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random,NULL), "Volvemos a agregar la p como opcion al menu");
	pa2m_afirmar(menu_cantidad_opciones(menu) == 2, "La cantidad de opciones aumento correctamente");
	pa2m_afirmar(menu_ejecutar_entrada(menu,'P',NULL), "Se pudo ejecutra la funcion guardada en la opcion P, luego de haberla eliminado y vuelto a insertar");

	menu_destruir(menu);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de obtener funcion
void BuscarFuncionDeOpcionExistenteDevuelveNoNULL(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random,NULL), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random,NULL), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_obtener_funcion_opcion(menu,'P') != NULL, "Se pudo encontrar la funcion asociada a la opcion P (proque es distinto de NULL)");

	menu_destruir(menu);
}

void BuscarFuncionDeOpcionInexistenteDevuelveNULL(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random,NULL), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random,NULL), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_obtener_funcion_opcion(menu,'A') == NULL, "No se pudo encontrar la funcion asociada a la opcion A que no existe ");

	menu_destruir(menu);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de crear
void CrearPokedexConComparadorValidoDevuelePokedex(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	pa2m_afirmar(pokedex != NULL,"Se crear exitosamente una pokedex");
	pokedex_destruir(pokedex);
}

void CrearPokedexConComparadorNULLDevueleNULL(){
	pokedex_t *pokedex = pokedex_crear(NULL);
	pa2m_afirmar(pokedex == NULL,"No Se crear la pokedex porque el comparador es NULL");
	pokedex_destruir(pokedex);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de insertar
void InsertarEnPokedexUnPokemonValidoDevuelveTrue(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pa2m_afirmar(pokedex_agregar_pokemon(pokedex,&pikachu),"Se Pudo Agregar Correctamente a Pikachu");
	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 1,"La cantidad de pokemones en la pokedex es 1 luego de agregar 1 pokemon");

	pokedex_destruir(pokedex);
}

void InsertarEnPokedexUnPokemonNULLDevuelveFalse(){
	pokedex_t *pokedex = pokedex_crear(comparador);

	pa2m_afirmar(!pokedex_agregar_pokemon(pokedex,NULL),"No se Pudo Agregar a un pokemon NULL");
	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 0,"La cantidad de pokemones en la pokedex es 0 luego de inentar insertar un pokemon NULL");

	pokedex_destruir(pokedex);
}

void InsertarEnPokedexVAriosPokemonesDevuelveTrue(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	struct pokemon charizard = { "Charizard", 50, "ROJO", "JIN" };
	struct pokemon venusaur = { "Venusaur", 40, "VERDE","JJIIN"};
	struct pokemon blastoise = { "Blastoise", 45, "AZUL" , "RJINR"};
	struct pokemon mewtwo = { "Mewtwo", 100, "MAGENTA","RRRRRRIIR" };

	pokedex_agregar_pokemon(pokedex,&pikachu);
	pokedex_agregar_pokemon(pokedex,&charizard);
	pokedex_agregar_pokemon(pokedex,&venusaur);
	pokedex_agregar_pokemon(pokedex,&blastoise);
	pokedex_agregar_pokemon(pokedex,&mewtwo);

	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 5,"La cantidad de pokemones en la pokedex es 5 luego de agregar 5 pokemon");
	pokedex_destruir(pokedex);
}

void InsertarVariasVecesAlMismoPokemonDevuelveTrue(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	for (size_t i = 0; i < 5; i++){
		pa2m_afirmar(pokedex_agregar_pokemon(pokedex,&pikachu),"Pudismo agregar a pikachu a la pokedex (metidos:%zu)",i);
	}
	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 5,"La cantidad de pokemones en la pokedex es 5 luego de agregar 5 veces a pikachu");
	pokedex_destruir(pokedex);
}

void InsertarVariosPokemonesNULLDevuelvefalse(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	for (size_t i = 0; i < 5; i++){
		pa2m_afirmar(!pokedex_agregar_pokemon(pokedex,NULL),"No Pudimos agregar a un pokemon null repetidamente (intentos:%zu)",i);
	}
	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 0,"La cantidad de pokemones en la pokedex se mantiene en 0");
	pokedex_destruir(pokedex);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de eliminar
void InsertarUnPokemonValidoYEliminarloDevuelveTrue(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokedex_agregar_pokemon(pokedex,&pikachu);

	struct pokemon *eliminado = NULL;
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex,&pikachu,(void *)&eliminado),"Se Pudo eliminar Correctamente a Pikachu");
	pa2m_afirmar(strcmp(eliminado->nombre, pikachu.nombre) == 0,"El elemento eliminado tiene el mismo nombre que pikachu (porque es pikachu)");
	pa2m_afirmar(eliminado->puntaje == pikachu.puntaje,"El elemento eliminado tiene la misma puntaje que pikachu (porque es pikachu)");

	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 0,"La cantidad de pokemones en la pokedex es 0 luego de eliminar 1 pokemon");

	pokedex_destruir(pokedex);
}

void EliminarPokemonConEliminadoNULLDevuelveFalse(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	struct pokemon *eliminado = NULL;
	pa2m_afirmar(!pokedex_eliminar_pokemon(pokedex,&pikachu,NULL),"No se Pudo eliminar a un pokemon con encontrado NULL");
	pa2m_afirmar(eliminado == NULL,"El elemento eliminado se mantuvo NULL porque no se elimino a ningun pokemon");
	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 1,"La cantidad de pokemones en la pokedex se mantuvo en 0 luego de inentar eliminar con encontrado NULL");

	pokedex_destruir(pokedex);
}

void EliminarPokemonNULLDevuelveFalse(){
	pokedex_t *pokedex = pokedex_crear(comparador);

	struct pokemon *eliminado = NULL;
	pa2m_afirmar(!pokedex_eliminar_pokemon(pokedex,NULL,(void *)&eliminado),"No se Pudo eliminar a un pokemon NULL");
	pa2m_afirmar(eliminado == NULL,"El elemento eliminado se mantuvo NULL porque no se elimino a ningun pokemon");

	pokedex_destruir(pokedex);
}

void EliminarPokemonInexistenteDevuelveFalse(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	struct pokemon charizard = { "Charizard", 50, "ROJO", "JIN" };

	pokedex_agregar_pokemon(pokedex,&pikachu);

	struct pokemon *eliminado = NULL;
	pa2m_afirmar(!pokedex_eliminar_pokemon(pokedex,&charizard,(void *)&eliminado),"Se Pudo eliminar Correctamente a Pikachu");
	pa2m_afirmar(eliminado == NULL,"El elemento eliminado sigue siendo NULL al inentra borrar un pokemon inexistente ");

	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 1,"La cantidad de pokemones en la pokedex es 1 luego de inentar eliminar 1 pokemon inexistente");

	pokedex_destruir(pokedex);
}

void InsertarVariosPokemonYLosEliminoloDevuelveTrue(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	struct pokemon charizard = { "Charizard", 50, "ROJO", "JIN" };
	struct pokemon venusaur = { "Venusaur", 40, "VERDE","JJIIN"};
	struct pokemon blastoise = { "Blastoise", 45, "AZUL" , "RJINR"};
	struct pokemon mewtwo = { "Mewtwo", 100, "MAGENTA","RRRRRRIIR" };

	pokedex_agregar_pokemon(pokedex,&pikachu);
	pokedex_agregar_pokemon(pokedex,&charizard);
	pokedex_agregar_pokemon(pokedex,&venusaur);
	pokedex_agregar_pokemon(pokedex,&blastoise);
	pokedex_agregar_pokemon(pokedex,&mewtwo);

	struct pokemon *eliminado = NULL;
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex,&pikachu,(void *)&eliminado),"Se Pudo eliminar Correctamente a Pikachu");
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex,&charizard,(void *)&eliminado),"Se Pudo eliminar Correctamente a charizard");
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex,&venusaur,(void *)&eliminado),"Se Pudo eliminar Correctamente a venusaur");
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex,&blastoise,(void *)&eliminado),"Se Pudo eliminar Correctamente a blastoise");
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex,&mewtwo,(void *)&eliminado),"Se Pudo eliminar Correctamente a mewtwo");

	pa2m_afirmar(strcmp(eliminado->nombre, mewtwo.nombre) == 0,"El elemento eliminado tiene el mismo nombre que mewtwo (porque es mewtwo que fue el ultimo en ser eliminado)");
	pa2m_afirmar(eliminado->puntaje == mewtwo.puntaje,"El elemento eliminado tiene la misma puntaje que mewtwo (porque es mewtwo ultimo en ser eliminado)");

	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 0,"La cantidad de pokemones en la pokedex es 0 luego de eliminar 5 pokemon");

	pokedex_destruir(pokedex);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de Buscar
void BuscarUnPokemonValidoDevuelveAlPokemon(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokedex_agregar_pokemon(pokedex,&pikachu);

	struct pokemon *elemento_guardado = &pikachu;

	pa2m_afirmar(pokedex_buscar_pokemon(pokedex,elemento_guardado) != NULL,"Se Pudo encontrar Correctamente a Pikachu");
	pa2m_afirmar(strcmp(elemento_guardado->nombre, pikachu.nombre) == 0,"El nombre del encontrado es el misma que la de pikachu");
	pa2m_afirmar(elemento_guardado->puntaje == pikachu.puntaje,"La puntaje del encontrado es el misma que la de pikachu");

	pokedex_destruir(pokedex);
}

void BuscarUnPokemoninexistenteDevuelveNULL(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	struct pokemon charizard = { "Charizard", 50, "ROJO", "JIN" };


	pokedex_agregar_pokemon(pokedex,&pikachu);

	struct pokemon *elemento_guardado = &charizard;

	pa2m_afirmar(pokedex_buscar_pokemon(pokedex,elemento_guardado) == NULL,"No se Pudo encontrar a Charizard porque no esta en la pokedex");

	pokedex_destruir(pokedex);
}

void BuscarUnPokemonEliminadoDevuelveNULL(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokedex_agregar_pokemon(pokedex,&pikachu);

	struct pokemon *elemento_guardado = &pikachu;
	struct pokemon *eliminado = NULL;

	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex,&pikachu,(void*)&eliminado),"Eliminamos a Pikachu de la pokedex");
	pa2m_afirmar(pokedex_buscar_pokemon(pokedex,elemento_guardado) == NULL,"No se Pudo encontrar a Pikachu porque ya no esta en la pokedex");

	pokedex_destruir(pokedex);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de mostrar ordenados
void MostrarPokemonesOrdenadosImprimeEnOrden() {
    pokedex_t *pokedex = pokedex_crear(comparador);

    struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };
    struct pokemon charizard = { "Charizard", 50, "ROJO", "JIN" };
    struct pokemon venusaur = { "Venusaur", 40, "VERDE","JJIIN"};

    pokedex_agregar_pokemon(pokedex, &pikachu);
    pokedex_agregar_pokemon(pokedex, &charizard);
    pokedex_agregar_pokemon(pokedex, &venusaur);

    pa2m_afirmar(pokedex_mostrar_ordenados(pokedex, imprimir_pokemon, NULL),
                 "Se muestran los Pokémon en orden alfabético");
    pokedex_destruir(pokedex);
}

void MostrarPokemonesOrdenadosSegunEjemploImprimeEnOrden() {
    pokedex_t *pokedex = pokedex_crear(comparador);

    struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };
    struct pokemon charmander = { "Charmander", 10, "ROJO","J" };
    struct pokemon lapras = { "Lapras", 15, "AZUL","NRORSRER" };
    struct pokemon mew = { "Mew", 27, "MAGENTA","R" };
    struct pokemon lotad = { "Lotad", 5,"VERDE","NNEENESSESONOSO" };
    struct pokemon magikarp = { "Magikarp", 5,"ROJO", "EEEROOOR"};
    struct pokemon cacnea = { "Cacnea", 12, "VERDE","NNNRSSSR" };
    struct pokemon pachirisu = { "Pachirisu",7,"AZUL","JRRI" };
    struct pokemon gengar = { "Gengar", 22,"MAGENTA","RJRI" };
    struct pokemon galvantula = { "Galvantula", 20,"AMARILLO","IJJRIR" };

    pokedex_agregar_pokemon(pokedex, &pikachu);
    pokedex_agregar_pokemon(pokedex, &charmander);
    pokedex_agregar_pokemon(pokedex, &lapras);
    pokedex_agregar_pokemon(pokedex, &mew);
    pokedex_agregar_pokemon(pokedex, &lotad);
    pokedex_agregar_pokemon(pokedex, &magikarp);
    pokedex_agregar_pokemon(pokedex, &cacnea);
    pokedex_agregar_pokemon(pokedex, &pachirisu);
    pokedex_agregar_pokemon(pokedex, &gengar);
    pokedex_agregar_pokemon(pokedex, &galvantula);

    pa2m_afirmar(pokedex_mostrar_ordenados(pokedex, imprimir_pokemon, NULL),
                 "Se muestran los Pokémon en orden alfabético ");
    pokedex_destruir(pokedex);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de obtener pokemon random
void ObtenerUnPokemonRandomDevuelvePokemonRandom() {
    pokedex_t *pokedex = pokedex_crear(comparador);

    struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };
    struct pokemon charizard = { "Charizard", 50, "ROJO", "JIN" };
    struct pokemon venusaur = { "Venusaur", 40, "VERDE","JJIIN"};

    pokedex_agregar_pokemon(pokedex, &pikachu);
    pokedex_agregar_pokemon(pokedex, &charizard);
    pokedex_agregar_pokemon(pokedex, &venusaur);
	struct pokemon *pokemon_aleatorio = pokedex_devolver_pokemon_aleatorio(pokedex);
    pa2m_afirmar(pokemon_aleatorio != NULL,
                 "El Pokemon es distinto de NULL");
	printf("el nombre del pokemon aleatorio es:%s\n",pokemon_aleatorio->nombre);
    pokedex_destruir(pokedex);
}

void ObtenerPokemonRandomYEliminoUnPokemonMeDevuelvenDistintosPokemones() {
    pokedex_t *pokedex = pokedex_crear(comparador);

    struct pokemon pikachu = { "Pikachu", 15, "AMARILLO", "I" };
    struct pokemon charizard = { "Charizard", 50, "ROJO", "JIN" };
    struct pokemon venusaur = { "Venusaur", 40, "VERDE","JJIIN"};

    pokedex_agregar_pokemon(pokedex, &pikachu);
    pokedex_agregar_pokemon(pokedex, &charizard);
    pokedex_agregar_pokemon(pokedex, &venusaur);

	struct pokemon *eliminado = NULL;

	struct pokemon *pokemon_aleatorio = pokedex_devolver_pokemon_aleatorio(pokedex);
    pa2m_afirmar(pokemon_aleatorio != NULL,
                 "El Pokemon es distinto de NULL");
	printf("el nombre del pokemon aleatorio es:%s\n",pokemon_aleatorio->nombre);
	printf("el puntaje del pokemon aleatorio es:%i\n",pokemon_aleatorio->puntaje);
	printf("el color del pokemon aleatorio es:%s\n",pokemon_aleatorio->color);
	printf("el patron del pokemon aleatorio es:%s\n",pokemon_aleatorio->patron_movimientos);

	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex,&venusaur,(void*)&eliminado),"Eliminamos a venusaur");
	pa2m_afirmar(pokemon_aleatorio != NULL,
                 "El Pokemon random nuevo es distinto de NULL");
	pokemon_aleatorio = pokedex_devolver_pokemon_aleatorio(pokedex);
	printf("el nombre del pokemon aleatorio es:%s\n",pokemon_aleatorio->nombre);
    pokedex_destruir(pokedex);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de lectura del csv en pokedex
void LeerCSVDevuelveTrue() {
    pokedex_t *pokedex = pokedex_crear(comparador);
	const char *argv[] = { NULL, "datos/pokedex.csv" };
	pa2m_afirmar(pokedex_cargar_pokemones_desde_csv(pokedex,argv,',',4),"Leer archivo CSV devuelve true y no pierde memoria");

	struct pokemon *pokemon_aleatorio = pokedex_devolver_pokemon_aleatorio(pokedex);
    pa2m_afirmar(pokemon_aleatorio != NULL,
                 "El Pokemon aleatorio no es NULL, por lo que fue generado exitosamente");
    pokedex_destruir_todo(pokedex,liberar_pokemon);
}

void LeerCSVConPrametrosNULLDevuelveFalse() {
    pokedex_t *pokedex = pokedex_crear(comparador);
	const char *argv[] = { NULL, "datos/pokedex.csv" };
	pa2m_afirmar(!pokedex_cargar_pokemones_desde_csv(NULL,argv,',',4),"Leer archivo CSV devuelve false");
    pokedex_destruir_todo(pokedex,liberar_pokemon);
}

void LeerCSVConNombreIncorrectoDevuelveFalse() {
    pokedex_t *pokedex = pokedex_crear(comparador);
	const char *argv[] = { NULL, "datos/Pokedex.csv" };
	pa2m_afirmar(!pokedex_cargar_pokemones_desde_csv(pokedex,argv,',',4),"Leer archivo CSV inexistente devuelve false");
    pokedex_destruir_todo(pokedex,liberar_pokemon);
}

void LeerCSVConseparadorIncorrectoDevuelveFalse() {
    pokedex_t *pokedex = pokedex_crear(comparador);
	const char *argv[] = { NULL, "datos/Pokedex.csv" };
	pa2m_afirmar(!pokedex_cargar_pokemones_desde_csv(pokedex,argv,';',4),"Leer archivo CSV con separador incorrecto devuelve false");
    pokedex_destruir_todo(pokedex,liberar_pokemon);
}



int main()
{
	srand ((unsigned int)time(NULL));	//en time iria la semilla, es decir en vez de time(null) pones semilla qsy
	pa2m_nuevo_grupo("Pruebas de TDA Menu");
	pa2m_nuevo_grupo("Pruebas de Crear (TDA Menu)");
	CrearMenuDevuelveMenu();
	
	pa2m_nuevo_grupo("Pruebas de Agregar y ejecutar opcion (TDA Menu)");
	AgregarOpcionDevuelveTrue();
	AgregarVariasOpcionesAlMenuDevuelveTrue();
	AgregarEnMenuNULLDevuelveFalse();
	AgregarEnMenuConFuncionNULLDevuelveFalse();
	EjecutarAccionLlamaCorrectameneteAfuncion();
	AgregarDosVecesMismaOpcionDevuelveTrue();
	
	
	pa2m_nuevo_grupo("Pruebas de eliminar (TDA Menu)");
	EliminarOpcionDevuelveTrue();
	EliminarOpcionInexistenteDevuelveFalse();
	EliminarOpcionYReinsertarlaDevuelveTrue();

	pa2m_nuevo_grupo("Pruebas de buscar funcion (TDA Menu)");
	BuscarFuncionDeOpcionExistenteDevuelveNoNULL();
	BuscarFuncionDeOpcionInexistenteDevuelveNULL();

	pa2m_nuevo_grupo("Pruebas de TDA Pokedex");
	pa2m_nuevo_grupo("Pruebas de Crear (TDA Pokedex)");
	CrearPokedexConComparadorValidoDevuelePokedex();
	CrearPokedexConComparadorNULLDevueleNULL();

	pa2m_nuevo_grupo("Pruebas de agregar (TDA Pokedex)");
	InsertarEnPokedexUnPokemonValidoDevuelveTrue();
	InsertarEnPokedexUnPokemonNULLDevuelveFalse();
	InsertarEnPokedexVAriosPokemonesDevuelveTrue();
	InsertarVariasVecesAlMismoPokemonDevuelveTrue();
	InsertarVariosPokemonesNULLDevuelvefalse();

	pa2m_nuevo_grupo("Pruebas de eliminar (TDA Pokedex)");
	InsertarUnPokemonValidoYEliminarloDevuelveTrue();
	EliminarPokemonNULLDevuelveFalse();
	EliminarPokemonInexistenteDevuelveFalse();
	EliminarPokemonInexistenteDevuelveFalse();
	InsertarVariosPokemonYLosEliminoloDevuelveTrue();

	pa2m_nuevo_grupo("Pruebas de buscar (TDA Pokedex)");
	BuscarUnPokemonValidoDevuelveAlPokemon();
	BuscarUnPokemoninexistenteDevuelveNULL();
	BuscarUnPokemonEliminadoDevuelveNULL();

	pa2m_nuevo_grupo("Pruebas de mostrar pokemones ordenados (TDA Pokedex)");
	MostrarPokemonesOrdenadosImprimeEnOrden();
	MostrarPokemonesOrdenadosSegunEjemploImprimeEnOrden();

	pa2m_nuevo_grupo("Pruebas de obtener pokemon random (TDA Pokedex)");
	ObtenerUnPokemonRandomDevuelvePokemonRandom();
	ObtenerPokemonRandomYEliminoUnPokemonMeDevuelvenDistintosPokemones();

	pa2m_nuevo_grupo("Pruebas de leer csv (TDA Pokedex)");
	LeerCSVDevuelveTrue();
	LeerCSVConPrametrosNULLDevuelveFalse();
	LeerCSVConNombreIncorrectoDevuelveFalse();
	LeerCSVConseparadorIncorrectoDevuelveFalse();
	
	return pa2m_mostrar_reporte();
}