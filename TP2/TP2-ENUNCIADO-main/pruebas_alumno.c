#include "pa2m.h"
#include "src/menu.h"
#include "src/pokedex.h"
#include <string.h>
#include <time.h>

struct pokemon {
	char *nombre;
	char tipo;
	int fuerza;
	int destreza;
	int resistencia;
};

void funcion_random() {
    printf("Hola Mundo, probamos funcion random\n"); 
}

void funcion_random2() {
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
	printf("Nombre: %s, Tipo: %c, Fuerza: %d, Destreza: %d, Resistencia: %d\n",
	       poke->nombre, poke->tipo, poke->fuerza, poke->destreza,
	       poke->resistencia);
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

	pa2m_afirmar(menu_agregar_opciones(menu,'a',funcion_random), "agregamos una opcion al menu");
	menu_destruir(menu);
}

void AgregarVariasOpcionesAlMenuDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'J',funcion_random), "agregamos la J como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'j',funcion_random), "agregamos la j como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'S',funcion_random), "agregamos la S como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'s',funcion_random), "agregamos la s como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'Q',funcion_random), "agregamos la Q como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'q',funcion_random), "agregamos la q como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 8, "agregamos en total 8 opciones al menu");

	menu_destruir(menu);
}

void AgregarEnMenuNULLDevuelveFalse(){
	menu_t *menu = NULL;

	pa2m_afirmar(!menu_agregar_opciones(menu,'P',funcion_random), "No agregamos la P como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'p',funcion_random), "No agregamos la p como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'J',funcion_random), "No agregamos la J como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 0, "agregamos en total 0 opciones al menu NULL");

	
	menu_destruir(menu);
}

void AgregarEnMenuConFuncionNULLDevuelveFalse(){
	menu_t *menu = NULL;

	pa2m_afirmar(!menu_agregar_opciones(menu,'P',NULL), "No agregamos la P como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'p',NULL), "No agregamos la p como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'J',NULL), "No agregamos la J como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 0, "agregamos en total 0 opciones (con funcion NULL) al menu");

	
	menu_destruir(menu);
}

void EjecutarAccionLlamaCorrectameneteAfuncion(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 2, "agregamos en total 2 opciones al menu");

	pa2m_afirmar(menu_ejecutar_entrada(menu,'P'), "Se pudo ejecutra la funcion guardada.");

	menu_destruir(menu);
}

void AgregarDosVecesMismaOpcionDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");

	pa2m_afirmar(menu_ejecutar_entrada(menu,'P'), "Se pudo ejecutra la funcion guardada.");

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random2), "agregamos la P pero con otra funcion");

	pa2m_afirmar(menu_ejecutar_entrada(menu,'P'), "Se pudo ejecutra la nueva funcion guardada.");

	menu_destruir(menu);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de eliminar

void EliminarOpcionDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu,'P'), "pudimos eliminar la opcion P");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 1, "al quitar 1 opcion, solo queda 1 opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu,'p'), "pudimos eliminar la opcion P");
	pa2m_afirmar(menu_cantidad_opciones(menu) == 0, "al quitar 1 opcion, no queda opciones en el  menu");

	menu_destruir(menu);
}

void EliminarOpcionInexistenteDevuelveFalse(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(!menu_eliminar_opcion(menu,'K'), "No podemos eliminar una opcion inexistente");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 2, "La cantidad se mantiene si inentamos eliminar una  opcion inexistente");

	menu_destruir(menu);
}

void EliminarOpcionYReinsertarlaDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu,'P'), "pudimos eliminar la opcion P");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 1, "al quitar 1 opcion, solo queda 1 opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "Volvemos a agregar la p como opcion al menu");
	pa2m_afirmar(menu_cantidad_opciones(menu) == 2, "La cantidad de opciones aumento correctamente");
	pa2m_afirmar(menu_ejecutar_entrada(menu,'P'), "Se pudo ejecutra la funcion guardada en la opcion P, luego de haberla eliminado y vuelto a insertar");

	menu_destruir(menu);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de obtener funcion
void BuscarFuncionDeOpcionExistenteDevuelveNoNULL(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_obtener_funcion_opcion(menu,'P') != NULL, "Se pudo encontrar la funcion asociada a la opcion P (proque es distinto de NULL)");

	menu_destruir(menu);
}

void BuscarFuncionDeOpcionInexistenteDevuelveNULL(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

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
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };

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
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };
	struct pokemon mewtwo = { "Mewtwo", 'A', 97, 167, 220 };

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
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
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
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };

	pokedex_agregar_pokemon(pokedex,&pikachu);

	struct pokemon *eliminado = NULL;
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex,&pikachu,(void *)&eliminado),"Se Pudo eliminar Correctamente a Pikachu");
	pa2m_afirmar(strcmp(eliminado->nombre, pikachu.nombre) == 0,"El elemento eliminado tiene el mismo nombre que pikachu (porque es pikachu)");
	pa2m_afirmar(eliminado->fuerza == pikachu.fuerza,"El elemento eliminado tiene la misma fuerza que pikachu (porque es pikachu)");
	pa2m_afirmar(eliminado->destreza == pikachu.destreza,"El elemento eliminado tiene la misma destreza que pikachu (porque es pikachu)");
	pa2m_afirmar(eliminado->resistencia == pikachu.resistencia,"El elemento eliminado tiene la misma resistencia que pikachu (porque es pikachu)");

	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 0,"La cantidad de pokemones en la pokedex es 0 luego de eliminar 1 pokemon");

	pokedex_destruir(pokedex);
}

void EliminarPokemonConEliminadoNULLDevuelveFalse(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };

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
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };

	pokedex_agregar_pokemon(pokedex,&pikachu);

	struct pokemon *eliminado = NULL;
	pa2m_afirmar(!pokedex_eliminar_pokemon(pokedex,&charizard,(void *)&eliminado),"Se Pudo eliminar Correctamente a Pikachu");
	pa2m_afirmar(eliminado == NULL,"El elemento eliminado sigue siendo NULL al inentra borrar un pokemon inexistente ");

	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 1,"La cantidad de pokemones en la pokedex es 1 luego de inentar eliminar 1 pokemon inexistente");

	pokedex_destruir(pokedex);
}

void InsertarVariosPokemonYLosEliminoloDevuelveTrue(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
	struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };
	struct pokemon blastoise = { "Blastoise", 'A', 97, 167, 220 };
	struct pokemon mewtwo = { "Mewtwo", 'A', 97, 167, 220 };

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
	pa2m_afirmar(eliminado->fuerza == mewtwo.fuerza,"El elemento eliminado tiene la misma fuerza que mewtwo (porque es mewtwo ultimo en ser eliminado)");
	pa2m_afirmar(eliminado->destreza == mewtwo.destreza,"El elemento eliminado tiene la misma destreza que mewtwo (porque es mewtwo ultimo en ser eliminado)");
	pa2m_afirmar(eliminado->resistencia == mewtwo.resistencia,"El elemento eliminado tiene la misma resistencia que mewtwo (porque es mewtwo ultimo en ser eliminado)");

	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 0,"La cantidad de pokemones en la pokedex es 0 luego de eliminar 5 pokemon");

	pokedex_destruir(pokedex);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de Buscar
void BuscarUnPokemonValidoDevuelveAlPokemon(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };

	pokedex_agregar_pokemon(pokedex,&pikachu);

	struct pokemon *elemento_guardado = &pikachu;

	pa2m_afirmar(pokedex_buscar_pokemon(pokedex,elemento_guardado) != NULL,"Se Pudo encontrar Correctamente a Pikachu");
	pa2m_afirmar(elemento_guardado->fuerza == pikachu.fuerza,"La fuerza del encontrado es la misma que la de pikachu");
	pa2m_afirmar(elemento_guardado->destreza == pikachu.destreza,"La destreza del encontrado es la misma que la de pikachu");
	pa2m_afirmar(elemento_guardado->resistencia == pikachu.resistencia,"La resistencia del encontrado es la misma que la de pikachu");

	pokedex_destruir(pokedex);
}

void BuscarUnPokemoninexistenteDevuelveNULL(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
	struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };


	pokedex_agregar_pokemon(pokedex,&pikachu);

	struct pokemon *elemento_guardado = &charizard;

	pa2m_afirmar(pokedex_buscar_pokemon(pokedex,elemento_guardado) == NULL,"No se Pudo encontrar a Charizard porque no esta en la pokedex");

	pokedex_destruir(pokedex);
}

void BuscarUnPokemonEliminadoDevuelveNULL(){
	pokedex_t *pokedex = pokedex_crear(comparador);
	struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };

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

    struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
    struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
    struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

    pokedex_agregar_pokemon(pokedex, &pikachu);
    pokedex_agregar_pokemon(pokedex, &charizard);
    pokedex_agregar_pokemon(pokedex, &venusaur);

    pa2m_afirmar(pokedex_mostrar_ordenados(pokedex, imprimir_pokemon, NULL),
                 "Se muestran los Pokémon en orden alfabético");
    pokedex_destruir(pokedex);
}

void MostrarPokemonesOrdenadosSegunEjemploImprimeEnOrden() {
    pokedex_t *pokedex = pokedex_crear(comparador);

    struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
    struct pokemon charmander = { "Charmander", 'F', 60, 47, 23 };
    struct pokemon lapras = { "Lapras", 'P', 10, 14, 30 };
    struct pokemon mew = { "Mew", 'A', 100, 147, 300 };
    struct pokemon lotad = { "Lotad", 'L', 21, 40, 37 };
    struct pokemon magikarp = { "Magikarp", 'A', 1, 1, 3 };
    struct pokemon cacnea = { "Cacnea", 'P', 11, 23, 27 };
    struct pokemon pachirisu = { "Pachirisu", 'L', 40, 21, 38 };
    struct pokemon gengar = { "Gengar", 'E', 47, 20, 18 };
    struct pokemon galvantula = { "Galvantula", 'F', 17, 29, 52 };

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

    struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
    struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
    struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

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

    struct pokemon pikachu = { "Pikachu", 'E', 55, 40, 50 };
    struct pokemon charizard = { "Charizard", 'F', 100, 143, 239 };
    struct pokemon venusaur = { "Venusaur", 'P', 89, 109, 301 };

    pokedex_agregar_pokemon(pokedex, &pikachu);
    pokedex_agregar_pokemon(pokedex, &charizard);
    pokedex_agregar_pokemon(pokedex, &venusaur);

	struct pokemon *eliminado = NULL;

	struct pokemon *pokemon_aleatorio = pokedex_devolver_pokemon_aleatorio(pokedex);
    pa2m_afirmar(pokemon_aleatorio != NULL,
                 "El Pokemon es distinto de NULL");
	printf("el nombre del pokemon aleatorio es:%s\n",pokemon_aleatorio->nombre);
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex,&venusaur,(void*)&eliminado),"Eliminamos a venusaur");
	pa2m_afirmar(pokemon_aleatorio != NULL,
                 "El Pokemon random nuevo es distinto de NULL");
	pokemon_aleatorio = pokedex_devolver_pokemon_aleatorio(pokedex);
	printf("el nombre del pokemon aleatorio es:%s\n",pokemon_aleatorio->nombre);
    pokedex_destruir(pokedex);
}

int main()
{
	srand ((unsigned)time(NULL));
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

	return pa2m_mostrar_reporte();
}