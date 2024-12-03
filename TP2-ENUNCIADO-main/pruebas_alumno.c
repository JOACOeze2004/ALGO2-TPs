#include "pa2m.h"
#include "src/menu.h"
#include "src/pokedex.h"
#include "src/racha.h"
#include <string.h>
#include <time.h>

void liberar_pokemon(void *elemento)
{
	pokemon_t *pokemon = elemento;
	if (pokemon != NULL) {
		free(pokemon->nombre);
		free(pokemon->color);
		free(pokemon->patron_movimientos);
		free(pokemon);
	}
}

bool verificar_color_amarillo(void *poke, void *ctx)
{
	pokemon_t *pokemon = poke;
	char *color_buscado = ctx;
	return strcmp(pokemon->color, color_buscado) == 0;
}

void funcion_random(void *ctx[])
{
	printf("Hola Mundo, probamos funcion random\n");
}

void funcion_random2(void *ctx[])
{
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
	pokemon_t *poke_a = a;
	pokemon_t *poke_b = b;
	return strcmp(poke_a->nombre, poke_b->nombre);
}

bool imprimir_pokemon(void *elemento, void *ctx)
{
	pokemon_t *poke = elemento;
	printf("Nombre: %s, puntaje: %i, color: %s, patron: %s\n", poke->nombre,
	       poke->puntaje, poke->color, poke->patron_movimientos);
	return true;
}

void CrearMenuDevuelveMenu()
{
	menu_t *menu = menu_crear();
	pa2m_afirmar(menu != NULL, "Se crear exitosamente un menu");
	menu_destruir(menu);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de agregar y ejecutar opcion

void AgregarOpcionDevuelveTrue()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu, 'a', funcion_random, NULL),
		     "agregamos una opcion al menu");
	menu_destruir(menu);
}

void AgregarVariasOpcionesAlMenuDevuelveTrue()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu, 'P', funcion_random, NULL),
		     "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'p', funcion_random, NULL),
		     "agregamos la p como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'J', funcion_random, NULL),
		     "agregamos la J como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'j', funcion_random, NULL),
		     "agregamos la j como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'S', funcion_random, NULL),
		     "agregamos la S como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 's', funcion_random, NULL),
		     "agregamos la s como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'Q', funcion_random, NULL),
		     "agregamos la Q como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'q', funcion_random, NULL),
		     "agregamos la q como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 8,
		     "agregamos en total 8 opciones al menu");

	menu_destruir(menu);
}

void AgregarEnMenuNULLDevuelveFalse()
{
	menu_t *menu = NULL;

	pa2m_afirmar(!menu_agregar_opciones(menu, 'P', funcion_random, NULL),
		     "No agregamos la P como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu, 'p', funcion_random, NULL),
		     "No agregamos la p como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu, 'J', funcion_random, NULL),
		     "No agregamos la J como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 0,
		     "No agregamos ninguna opcion al menu NULL");
}

void AgregarEnMenuConFuncionNULLDevuelveFalse()
{
	menu_t *menu = NULL;

	pa2m_afirmar(!menu_agregar_opciones(menu, 'P', NULL, NULL),
		     "No agregamos la P como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu, 'p', NULL, NULL),
		     "No agregamos la p como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu, 'J', NULL, NULL),
		     "No agregamos la J como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 0,
		     "No agregamos ninguna opcion (con funcion NULL) al menu");
}

void EjecutarAccionLlamaCorrectameneteAfuncion()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu, 'P', funcion_random, NULL),
		     "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'p', funcion_random, NULL),
		     "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 2,
		     "agregamos en total 2 opciones al menu");

	pa2m_afirmar(menu_ejecutar_entrada(menu, 'P', NULL),
		     "Se pudo ejecutra la funcion guardada.");

	menu_destruir(menu);
}

void AgregarDosVecesMismaOpcionDevuelveTrue()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu, 'P', funcion_random, NULL),
		     "agregamos la P como opcion al menu");

	pa2m_afirmar(menu_ejecutar_entrada(menu, 'P', NULL),
		     "Se pudo ejecutra la funcion guardada.");

	pa2m_afirmar(menu_agregar_opciones(menu, 'P', funcion_random2, NULL),
		     "agregamos la P pero con otra funcion");

	pa2m_afirmar(menu_ejecutar_entrada(menu, 'P', NULL),
		     "Se pudo ejecutra la nueva funcion guardada.");

	menu_destruir(menu);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de eliminar

void EliminarOpcionDevuelveTrue()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu, 'P', funcion_random, NULL),
		     "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'p', funcion_random, NULL),
		     "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu, 'P'),
		     "pudimos eliminar la opcion P");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 1,
		     "al quitar 1 opcion, solo queda 1 opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu, 'p'),
		     "pudimos eliminar la opcion P");
	pa2m_afirmar(menu_cantidad_opciones(menu) == 0,
		     "al quitar 1 opcion, no queda opciones en el  menu");

	menu_destruir(menu);
}

void EliminarOpcionInexistenteDevuelveFalse()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu, 'P', funcion_random, NULL),
		     "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'p', funcion_random, NULL),
		     "agregamos la p como opcion al menu");

	pa2m_afirmar(!menu_eliminar_opcion(menu, 'K'),
		     "No podemos eliminar una opcion inexistente");

	pa2m_afirmar(
		menu_cantidad_opciones(menu) == 2,
		"La cantidad se mantiene si inentamos eliminar una  opcion inexistente");

	menu_destruir(menu);
}

void EliminarOpcionYReinsertarlaDevuelveTrue()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu, 'P', funcion_random, NULL),
		     "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'p', funcion_random, NULL),
		     "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu, 'P'),
		     "pudimos eliminar la opcion P");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 1,
		     "al quitar 1 opcion, solo queda 1 opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'P', funcion_random, NULL),
		     "Volvemos a agregar la p como opcion al menu");
	pa2m_afirmar(menu_cantidad_opciones(menu) == 2,
		     "La cantidad de opciones aumento correctamente");
	pa2m_afirmar(
		menu_ejecutar_entrada(menu, 'P', NULL),
		"Se pudo ejecutra la funcion guardada en la opcion P, luego de haberla eliminado y vuelto a insertar");

	menu_destruir(menu);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de obtener funcion
void BuscarFuncionDeOpcionExistenteDevuelveNoNULL()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu, 'P', funcion_random, NULL),
		     "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'p', funcion_random, NULL),
		     "agregamos la p como opcion al menu");

	pa2m_afirmar(
		menu_obtener_funcion_opcion(menu, 'P') != NULL,
		"Se pudo encontrar la funcion asociada a la opcion P (porque es distinta de NULL)");

	menu_destruir(menu);
}

void BuscarFuncionDeOpcionInexistenteDevuelveNULL()
{
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu, 'P', funcion_random, NULL),
		     "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu, 'p', funcion_random, NULL),
		     "agregamos la p como opcion al menu");

	pa2m_afirmar(
		menu_obtener_funcion_opcion(menu, 'A') == NULL,
		"No se pudo encontrar la funcion asociada a la opcion 'A' ya que no existe como opcion en el menu");

	menu_destruir(menu);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de crear
void CrearPokedexConComparadorValidoDevuelePokedex()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pa2m_afirmar(pokedex != NULL,
		     "Se pudo crear exitosamente una pokedex no NULL");
	pokedex_destruir(pokedex);
}

void CrearPokedexConComparadorNULLDevueleNULL()
{
	pokedex_t *pokedex = pokedex_crear(NULL);
	pa2m_afirmar(
		pokedex == NULL,
		"No Se pudo crear la pokedex porque el comparador es NULL");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de insertar
void InsertarEnPokedexUnPokemonValidoDevuelveTrue()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pa2m_afirmar(pokedex_agregar_pokemon(pokedex, &pikachu),
		     "Se Pudo Agregar Correctamente a Pikachu");
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 1,
		"La cantidad de pokemones en la pokedex es 1 luego de agregar 1 pokemon");

	pokedex_destruir(pokedex);
}

void InsertarEnPokedexUnPokemonNULLDevuelveFalse()
{
	pokedex_t *pokedex = pokedex_crear(comparador);

	pa2m_afirmar(!pokedex_agregar_pokemon(pokedex, NULL),
		     "No se Pudo Agregar a un pokemon NULL");
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 0,
		"La cantidad de pokemones en la pokedex es 0 luego de inentar insertar un pokemon NULL");

	pokedex_destruir(pokedex);
}

void InsertarEnPokedexVAriosPokemonesDevuelveTrue()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };
	pokemon_t venusaur = { "Venusaur", 40, "VERDE", "JJIIN" };
	pokemon_t blastoise = { "Blastoise", 45, "AZUL", "RJINR" };
	pokemon_t mewtwo = { "Mewtwo", 100, "MAGENTA", "RRRRRRIIR" };

	pokedex_agregar_pokemon(pokedex, &pikachu);
	pokedex_agregar_pokemon(pokedex, &charizard);
	pokedex_agregar_pokemon(pokedex, &venusaur);
	pokedex_agregar_pokemon(pokedex, &blastoise);
	pokedex_agregar_pokemon(pokedex, &mewtwo);

	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 5,
		"La cantidad de pokemones en la pokedex es 5 luego de agregar 5 pokemon");
	pokedex_destruir(pokedex);
}

void InsertarVariasVecesAlMismoPokemonDevuelveTrue()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	for (size_t i = 0; i < 5; i++) {
		pokedex_agregar_pokemon(pokedex, &pikachu);
	}
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 5,
		"La cantidad de pokemones en la pokedex es 5 luego de agregar 5 veces a pikachu");
	pokedex_destruir(pokedex);
}

void InsertarVariosPokemonesNULLDevuelvefalse()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	for (size_t i = 0; i < 5; i++) {
		pokedex_agregar_pokemon(pokedex, NULL);
	}
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 0,
		"La cantidad de pokemones en la pokedex se mantiene en 0 luego de haber intentado meter 5 pokemones NULL");
	pokedex_destruir(pokedex);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de eliminar
void InsertarUnPokemonValidoYEliminarloDevuelveTrue()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokedex_agregar_pokemon(pokedex, &pikachu);

	pokemon_t *eliminado = NULL;
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex, &pikachu,
					      (void *)&eliminado),
		     "Se Pudo eliminar Correctamente a Pikachu");
	pa2m_afirmar(
		strcmp(eliminado->nombre, pikachu.nombre) == 0,
		"El elemento eliminado tiene el mismo nombre que pikachu (porque es pikachu)");
	pa2m_afirmar(
		eliminado->puntaje == pikachu.puntaje,
		"El elemento eliminado tiene la misma puntaje que pikachu (porque es pikachu)");

	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 0,
		"La cantidad de pokemones en la pokedex es 0 luego de eliminar 1 pokemon");

	pokedex_destruir(pokedex);
}

void EliminarPokemonConEliminadoNULLDevuelveFalse()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokemon_t *eliminado = NULL;
	pa2m_afirmar(!pokedex_eliminar_pokemon(pokedex, &pikachu, NULL),
		     "No se Pudo eliminar a un pokemon con encontrado NULL");
	pa2m_afirmar(
		eliminado == NULL,
		"El elemento eliminado se mantuvo NULL porque no se elimino a ningun pokemon");
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 1,
		"La cantidad de pokemones en la pokedex se mantuvo en 0 luego de inentar eliminar con encontrado NULL");

	pokedex_destruir(pokedex);
}

void EliminarPokemonNULLDevuelveFalse()
{
	pokedex_t *pokedex = pokedex_crear(comparador);

	pokemon_t *eliminado = NULL;
	pa2m_afirmar(!pokedex_eliminar_pokemon(pokedex, NULL,
					       (void *)&eliminado),
		     "No se Pudo eliminar a un pokemon NULL");
	pa2m_afirmar(
		eliminado == NULL,
		"El elemento eliminado se mantuvo NULL porque no se elimino a ningun pokemon");

	pokedex_destruir(pokedex);
}

void EliminarPokemonInexistenteDevuelveFalse()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };

	pokedex_agregar_pokemon(pokedex, &pikachu);

	pokemon_t *eliminado = NULL;
	pa2m_afirmar(!pokedex_eliminar_pokemon(pokedex, &charizard,
					       (void *)&eliminado),
		     "Se Pudo eliminar Correctamente a Charizard");
	pa2m_afirmar(
		eliminado == NULL,
		"El elemento eliminado sigue siendo NULL al inentra borrar un pokemon inexistente ");

	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 1,
		"La cantidad de pokemones en la pokedex es 1 luego de inentar eliminar 1 pokemon inexistente");

	pokedex_destruir(pokedex);
}

void InsertarVariosPokemonYLosEliminoloDevuelveTrue()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };
	pokemon_t venusaur = { "Venusaur", 40, "VERDE", "JJIIN" };
	pokemon_t blastoise = { "Blastoise", 45, "AZUL", "RJINR" };
	pokemon_t mewtwo = { "Mewtwo", 100, "MAGENTA", "RRRRRRIIR" };

	pokedex_agregar_pokemon(pokedex, &pikachu);
	pokedex_agregar_pokemon(pokedex, &charizard);
	pokedex_agregar_pokemon(pokedex, &venusaur);
	pokedex_agregar_pokemon(pokedex, &blastoise);
	pokedex_agregar_pokemon(pokedex, &mewtwo);

	pokemon_t *eliminado = NULL;
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex, &pikachu,
					      (void *)&eliminado),
		     "Se Pudo eliminar Correctamente a Pikachu");
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex, &charizard,
					      (void *)&eliminado),
		     "Se Pudo eliminar Correctamente a charizard");
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex, &venusaur,
					      (void *)&eliminado),
		     "Se Pudo eliminar Correctamente a venusaur");
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex, &blastoise,
					      (void *)&eliminado),
		     "Se Pudo eliminar Correctamente a blastoise");
	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex, &mewtwo,
					      (void *)&eliminado),
		     "Se Pudo eliminar Correctamente a mewtwo");

	pa2m_afirmar(
		strcmp(eliminado->nombre, mewtwo.nombre) == 0,
		"El elemento eliminado tiene el mismo nombre que mewtwo (porque es mewtwo que fue el ultimo en ser eliminado)");
	pa2m_afirmar(
		eliminado->puntaje == mewtwo.puntaje,
		"El elemento eliminado tiene la misma puntaje que mewtwo (porque es mewtwo ultimo en ser eliminado)");

	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 0,
		"La cantidad de pokemones en la pokedex es 0 luego de eliminar 5 pokemon");

	pokedex_destruir(pokedex);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de iterar
void IterarSobrePokedexConFiltroDeColorDevuelveTrue()
{
	pokedex_t *pokedex = pokedex_crear(comparador);

	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charmander = { "Charmander", 10, "ROJO", "J" };
	pokemon_t lapras = { "Lapras", 15, "AZUL", "NRORSRER" };

	pokedex_agregar_pokemon(pokedex, &pikachu);
	pokedex_agregar_pokemon(pokedex, &charmander);
	pokedex_agregar_pokemon(pokedex, &lapras);

	char *color_buscado = "AMARILLO";

	pa2m_afirmar(pokedex_iterar(pokedex, verificar_color_amarillo,
				    color_buscado),
		     "Se encontró al menos un Pokémon de color AMARILLO.");
	pokedex_destruir(pokedex);
}

void IterarSobrepokedexVaciaDevuelveFalse()
{
	pokedex_t *pokedex = pokedex_crear(comparador);

	char *color_buscado = "ROJO";

	pa2m_afirmar(!pokedex_iterar(pokedex, verificar_color_amarillo,
				     color_buscado),
		     "No se encontró ningún Pokémon en una racha vacía.");
	pokedex_destruir(pokedex);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de Buscar
void BuscarUnPokemonValidoDevuelveAlPokemon()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokedex_agregar_pokemon(pokedex, &pikachu);

	pokemon_t *elemento_guardado = &pikachu;

	pa2m_afirmar(pokedex_buscar_pokemon(pokedex, elemento_guardado) != NULL,
		     "Se Pudo encontrar Correctamente a Pikachu");
	pa2m_afirmar(strcmp(elemento_guardado->nombre, pikachu.nombre) == 0,
		     "El nombre del encontrado es el mismo que el de pikachu");
	pa2m_afirmar(elemento_guardado->puntaje == pikachu.puntaje,
		     "La puntaje del encontrado es el mismo que el de pikachu");

	pokedex_destruir(pokedex);
}

void BuscarUnPokemoninexistenteDevuelveNULL()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };

	pokedex_agregar_pokemon(pokedex, &pikachu);

	pokemon_t *elemento_guardado = &charizard;

	pa2m_afirmar(
		pokedex_buscar_pokemon(pokedex, elemento_guardado) == NULL,
		"No se Pudo encontrar a Charizard porque no esta en la pokedex");
	pokedex_destruir(pokedex);
}

void BuscarUnPokemonEliminadoDevuelveNULL()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokedex_agregar_pokemon(pokedex, &pikachu);

	pokemon_t *elemento_guardado = &pikachu;
	pokemon_t *eliminado = NULL;

	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex, &pikachu,
					      (void *)&eliminado),
		     "Eliminamos a Pikachu de la pokedex");
	pa2m_afirmar(
		pokedex_buscar_pokemon(pokedex, elemento_guardado) == NULL,
		"No se Pudo encontrar a Pikachu porque ya no esta en la pokedex");

	pokedex_destruir(pokedex);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de mostrar ordenados
void MostrarPokemonesOrdenadosImprimeEnOrden()
{
	pokedex_t *pokedex = pokedex_crear(comparador);

	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };
	pokemon_t venusaur = { "Venusaur", 40, "VERDE", "JJIIN" };

	pokedex_agregar_pokemon(pokedex, &pikachu);
	pokedex_agregar_pokemon(pokedex, &charizard);
	pokedex_agregar_pokemon(pokedex, &venusaur);

	pa2m_afirmar(pokedex_mostrar_ordenados(pokedex, imprimir_pokemon, NULL),
		     "Se muestran los Pokémon en orden alfabético");
	pokedex_destruir(pokedex);
}

void MostrarPokemonesOrdenadosSegunEjemploImprimeEnOrden()
{
	pokedex_t *pokedex = pokedex_crear(comparador);

	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charmander = { "Charmander", 10, "ROJO", "J" };
	pokemon_t lapras = { "Lapras", 15, "AZUL", "NRORSRER" };
	pokemon_t mew = { "Mew", 27, "MAGENTA", "R" };
	pokemon_t lotad = { "Lotad", 5, "VERDE", "NNEENESSESONOSO" };
	pokemon_t magikarp = { "Magikarp", 5, "ROJO", "EEEROOOR" };
	pokemon_t cacnea = { "Cacnea", 12, "VERDE", "NNNRSSSR" };
	pokemon_t pachirisu = { "Pachirisu", 7, "AZUL", "JRRI" };
	pokemon_t gengar = { "Gengar", 22, "MAGENTA", "RJRI" };
	pokemon_t galvantula = { "Galvantula", 20, "AMARILLO", "IJJRIR" };

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
void ObtenerUnPokemonRandomDevuelvePokemonRandom()
{
	pokedex_t *pokedex = pokedex_crear(comparador);

	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };
	pokemon_t venusaur = { "Venusaur", 40, "VERDE", "JJIIN" };

	pokedex_agregar_pokemon(pokedex, &pikachu);
	pokedex_agregar_pokemon(pokedex, &charizard);
	pokedex_agregar_pokemon(pokedex, &venusaur);
	pokemon_t *pokemon_aleatorio =
		pokedex_devolver_pokemon_aleatorio(pokedex);
	pa2m_afirmar(pokemon_aleatorio != NULL,
		     "El Pokemon es distinto de NULL");
	printf("el nombre del pokemon aleatorio es:%s\n",
	       pokemon_aleatorio->nombre);
	pokedex_destruir(pokedex);
}

void ObtenerUnPokemonRandomEnPokedexVaciaDevuelveNULL()
{
	pokedex_t *pokedex = pokedex_crear(comparador);

	pokemon_t *pokemon_aleatorio =
		pokedex_devolver_pokemon_aleatorio(pokedex);
	pa2m_afirmar(
		pokemon_aleatorio == NULL,
		"El Pokemon es igual a NULL porque no hay pokemones en al pokedex");
	pokedex_destruir(pokedex);
}

void ObtenerPokemonRandomYEliminoUnPokemonMeDevuelvenDistintosPokemones()
{
	pokedex_t *pokedex = pokedex_crear(comparador);

	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };
	pokemon_t venusaur = { "Venusaur", 40, "VERDE", "JJIIN" };

	pokedex_agregar_pokemon(pokedex, &pikachu);
	pokedex_agregar_pokemon(pokedex, &charizard);
	pokedex_agregar_pokemon(pokedex, &venusaur);

	pokemon_t *eliminado = NULL;

	pokemon_t *pokemon_aleatorio =
		pokedex_devolver_pokemon_aleatorio(pokedex);
	pa2m_afirmar(pokemon_aleatorio != NULL,
		     "El Pokemon es distinto de NULL");
	printf("el nombre del pokemon aleatorio es:%s\n",
	       pokemon_aleatorio->nombre);
	printf("el puntaje del pokemon aleatorio es:%i\n",
	       pokemon_aleatorio->puntaje);
	printf("el color del pokemon aleatorio es:%s\n",
	       pokemon_aleatorio->color);
	printf("el patron del pokemon aleatorio es:%s\n",
	       pokemon_aleatorio->patron_movimientos);

	pa2m_afirmar(pokedex_eliminar_pokemon(pokedex, &venusaur,
					      (void *)&eliminado),
		     "Eliminamos a venusaur");
	pa2m_afirmar(pokemon_aleatorio != NULL,
		     "El Pokemon random nuevo es distinto de NULL");
	pokemon_aleatorio = pokedex_devolver_pokemon_aleatorio(pokedex);
	printf("el nombre del pokemon aleatorio es:%s\n",
	       pokemon_aleatorio->nombre);
	pokedex_destruir(pokedex);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de lectura del csv en pokedex
void LeerCSVDevuelveTrue()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	const char *argv[] = { NULL, "datos/pokedex.csv" };
	pa2m_afirmar(pokedex_cargar_pokemones_desde_csv(pokedex, argv, ',', 4),
		     "Leer archivo CSV devuelve true y no pierde memoria");

	pokemon_t *pokemon_aleatorio =
		pokedex_devolver_pokemon_aleatorio(pokedex);
	pa2m_afirmar(
		pokemon_aleatorio != NULL,
		"El Pokemon aleatorio no es NULL, por lo que fue generado exitosamente");
	pokedex_destruir_todo(pokedex, liberar_pokemon);
}

void LeerCSVConPrametrosNULLDevuelveFalse()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	const char *argv[] = { NULL, "datos/pokedex.csv" };
	pa2m_afirmar(!pokedex_cargar_pokemones_desde_csv(NULL, argv, ',', 4),
		     "Leer archivo CSV devuelve false");
	pokedex_destruir_todo(pokedex, liberar_pokemon);
}

void LeerCSVConNombreIncorrectoDevuelveFalse()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	const char *argv[] = { NULL, "datos/Pokedex.csv" };
	pa2m_afirmar(!pokedex_cargar_pokemones_desde_csv(pokedex, argv, ',', 4),
		     "Leer archivo CSV inexistente devuelve false");
	pokedex_destruir_todo(pokedex, liberar_pokemon);
}

void LeerCSVConseparadorIncorrectoDevuelveFalse()
{
	pokedex_t *pokedex = pokedex_crear(comparador);
	const char *argv[] = { NULL, "datos/Pokedex.csv" };
	pa2m_afirmar(
		!pokedex_cargar_pokemones_desde_csv(pokedex, argv, ';', 4),
		"Leer archivo CSV con separador incorrecto devuelve false");
	pokedex_destruir_todo(pokedex, liberar_pokemon);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de crear
void CrearRachaDevuelveRacha()
{
	racha_t *racha = racha_crear();
	pa2m_afirmar(racha != NULL,
		     "Se pudo crear exitosamente una racha no NULL");
	pa2m_afirmar(racha_cantidad_combos(racha) == 0,
		     "La cantidad de combos es 0");

	racha_destruir(racha);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de agregar
void AgregarUnPokemonALaRachaDevuelveTrue()
{
	racha_t *racha = racha_crear();
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pa2m_afirmar(racha_agregar(racha, &pikachu),
		     "se pudo agregar a un pokemon a la racha");
	pa2m_afirmar(racha_cantidad_combos(racha) == 1,
		     "La cantidad de combos de la racha es 1");

	racha_destruir(racha);
}

void AgregarVAriosPokemonEsALaRachaDevuelveTrue()
{
	racha_t *racha = racha_crear();
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };
	pokemon_t venusaur = { "Venusaur", 40, "VERDE", "JJIIN" };
	pokemon_t blastoise = { "Blastoise", 45, "AZUL", "RJINR" };

	pa2m_afirmar(racha_agregar(racha, &pikachu),
		     "se pudo agregar a un pokemon a la racha");
	pa2m_afirmar(racha_agregar(racha, &charizard),
		     "se pudo agregar a un pokemon a la racha");
	pa2m_afirmar(racha_agregar(racha, &venusaur),
		     "se pudo agregar a un pokemon a la racha");
	pa2m_afirmar(racha_agregar(racha, &blastoise),
		     "se pudo agregar a un pokemon a la racha");
	pa2m_afirmar(racha_cantidad_combos(racha) == 4,
		     "La cantidad de combos de la racha es 4");

	racha_destruir(racha);
}

void AgregarVAriosVecesAlMismoPokemonALaRachaDevuelveTrue()
{
	racha_t *racha = racha_crear();
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	for (int i = 0; i < 5; i++) {
		racha_agregar(racha, &pikachu);
	}

	pa2m_afirmar(
		racha_cantidad_combos(racha) == 5,
		"La cantidad de combos de la racha es 5 si agregamos al mismo pokemon 5 veces");

	racha_destruir(racha);
}

void AgregarPokemonNULLALaRachaDevuelveFalse()
{
	racha_t *racha = racha_crear();

	pa2m_afirmar(!racha_agregar(racha, NULL),
		     "No se pudo agregar a un pokemon NULL a la racha");
	pa2m_afirmar(racha_cantidad_combos(racha) == 0,
		     "La cantidad de combos de la racha se mantuvo en 0");

	racha_destruir(racha);
}

void AgregarEnRachaNULLDevuelveFalse()
{
	racha_t *racha = NULL;
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pa2m_afirmar(
		!racha_agregar(racha, &pikachu),
		"No se pudo agregar a un pokemon a la racha si esta es NULL");
	pa2m_afirmar(racha_cantidad_combos(racha) == 0,
		     "La cantidad de combos de la racha se mantuvo en 0");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de eliminar

void EliminarAUnPokemonDeLaRachaDevuelveTrue()
{
	racha_t *racha = racha_crear();
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokemon_t *eliminado = NULL;
	racha_agregar(racha, &pikachu);
	pa2m_afirmar(racha_eliminar(racha, &pikachu, 0, (void *)&eliminado),
		     "Se pudo eliminar a Pikachu");
	pa2m_afirmar(
		strcmp(pikachu.nombre, eliminado->nombre) == 0,
		"El elemnto eliminado tiene el mismo nombre que pikachu (porque es pikachu)");

	pa2m_afirmar(racha_cantidad_combos(racha) == 0,
		     "La cantidad de combos de la racha se bajo a 0");

	racha_destruir(racha);
}

void EliminarAvAriosPokemonesDeLaRachaDevuelveTrue()
{
	racha_t *racha = racha_crear();
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };
	pokemon_t venusaur = { "Venusaur", 40, "VERDE", "JJIIN" };
	pokemon_t blastoise = { "Blastoise", 45, "AZUL", "RJINR" };

	pokemon_t *eliminado = NULL;
	racha_agregar(racha, &pikachu);
	racha_agregar(racha, &charizard);
	racha_agregar(racha, &venusaur);
	racha_agregar(racha, &blastoise);
	pa2m_afirmar(racha_cantidad_combos(racha) == 4,
		     "La cantidad de combos de la racha es 4");

	pa2m_afirmar(racha_eliminar(racha, &pikachu, 0, (void *)&eliminado),
		     "Se pudo eliminar a Pikachu");
	pa2m_afirmar(racha_eliminar(racha, &charizard, 0, (void *)&eliminado),
		     "Se pudo eliminar a charizard");
	pa2m_afirmar(racha_eliminar(racha, &venusaur, 0, (void *)&eliminado),
		     "Se pudo eliminar a venusaur");

	pa2m_afirmar(
		strcmp(venusaur.nombre, eliminado->nombre) == 0,
		"El elemnto eliminado tiene el mismo nombre que pikachu (porque es pikachu)");
	pa2m_afirmar(
		racha_cantidad_combos(racha) == 1,
		"La cantidad de combos de la racha se bajo a 1 si eliminamos a 3 pokemones ");

	racha_destruir(racha);
}

void EliminarAUnPokemonDeLaRachaConIndiceIncorrectoDevuelveFalse()
{
	racha_t *racha = racha_crear();
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokemon_t *eliminado = NULL;
	racha_agregar(racha, &pikachu);
	pa2m_afirmar(
		!racha_eliminar(racha, &pikachu, 5, (void *)&eliminado),
		"No Se pudo eliminar a Pikachu porque lepasamos mal la posicion");

	pa2m_afirmar(racha_cantidad_combos(racha) == 1,
		     "La cantidad de combos de la racha se mantuvo en 1");

	racha_destruir(racha);
}

void EliminarAUnPokemonDeLaRachaConEliminadoNULLDevuelveTruePeroNoSeGuardaEliminado()
{
	racha_t *racha = racha_crear();
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokemon_t **eliminado = NULL;
	racha_agregar(racha, &pikachu);
	pa2m_afirmar(
		racha_eliminar(racha, &pikachu, 0, (void *)eliminado),
		"Se pudo eliminar a Pikachu porque aun con eliminado igual a NULL");
	pa2m_afirmar(eliminado == NULL, "Eliminado sigue siendo NULL");

	pa2m_afirmar(racha_cantidad_combos(racha) == 0,
		     "La cantidad de combos de la racha se bajo a 0");

	racha_destruir(racha);
}

void EliminarAUnPokemonConRachaNULLDevuelveFalse()
{
	racha_t *racha = NULL;
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };

	pokemon_t *eliminado = NULL;
	racha_agregar(racha, &pikachu);
	pa2m_afirmar(!racha_eliminar(racha, &pikachu, 0, (void *)&eliminado),
		     "No Se pudo eliminar a Pikachu porquela racha es NULL");
	pa2m_afirmar(eliminado == NULL, "Eliminado sigue siendo NULL");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de vaciar racha
void VaciarRachaConVAriosPokemonesDevuelveTrue()
{
	racha_t *racha = racha_crear();
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };
	pokemon_t venusaur = { "Venusaur", 40, "VERDE", "JJIIN" };
	pokemon_t blastoise = { "Blastoise", 45, "AZUL", "RJINR" };

	racha_agregar(racha, &pikachu);
	racha_agregar(racha, &charizard);
	racha_agregar(racha, &venusaur);
	racha_agregar(racha, &blastoise);
	pa2m_afirmar(racha_cantidad_combos(racha) == 4,
		     "La cantidad de combos de la racha es 4");

	pa2m_afirmar(racha_vaciar(racha),
		     "se pudo vaciar la racha exitosamente");
	pa2m_afirmar(
		racha_cantidad_combos(racha) == 0,
		"La cantidad de combos de la racha es 0 (esta vacia ahora)");

	racha_destruir(racha);
}

void VaciarRachaSinPokemonesDevuelveFalse()
{
	racha_t *racha = racha_crear();

	pa2m_afirmar(!racha_vaciar(racha),
		     "No se pudo vaciar la racha si no hay elementos");

	racha_destruir(racha);
}

void VaciarConRachaNULLDevuelveFalse()
{
	racha_t *racha = NULL;
	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charizard = { "Charizard", 50, "ROJO", "JIN" };
	pokemon_t venusaur = { "Venusaur", 40, "VERDE", "JJIIN" };
	pokemon_t blastoise = { "Blastoise", 45, "AZUL", "RJINR" };

	racha_agregar(racha, &pikachu);
	racha_agregar(racha, &charizard);
	racha_agregar(racha, &venusaur);
	racha_agregar(racha, &blastoise);

	pa2m_afirmar(!racha_vaciar(racha),
		     "No se pudo vaciar la racha si esta es NULL");
}

void VaciarRachaConMuchosPokemonesDevuelveTrue()
{
	racha_t *racha = racha_crear();

	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charmander = { "Charmander", 10, "ROJO", "J" };
	pokemon_t lapras = { "Lapras", 15, "AZUL", "NRORSRER" };
	pokemon_t mew = { "Mew", 27, "MAGENTA", "R" };
	pokemon_t lotad = { "Lotad", 5, "VERDE", "NNEENESSESONOSO" };
	pokemon_t magikarp = { "Magikarp", 5, "ROJO", "EEEROOOR" };
	pokemon_t cacnea = { "Cacnea", 12, "VERDE", "NNNRSSSR" };
	pokemon_t pachirisu = { "Pachirisu", 7, "AZUL", "JRRI" };
	pokemon_t gengar = { "Gengar", 22, "MAGENTA", "RJRI" };
	pokemon_t galvantula = { "Galvantula", 20, "AMARILLO", "IJJRIR" };

	racha_agregar(racha, &pikachu);
	racha_agregar(racha, &charmander);
	racha_agregar(racha, &lapras);
	racha_agregar(racha, &mew);
	racha_agregar(racha, &lotad);
	racha_agregar(racha, &magikarp);
	racha_agregar(racha, &cacnea);
	racha_agregar(racha, &pachirisu);
	racha_agregar(racha, &gengar);
	racha_agregar(racha, &galvantula);

	pa2m_afirmar(racha_cantidad_combos(racha) == 10,
		     "La cantidad de combos de la racha es 10");
	pa2m_afirmar(racha_vaciar(racha),
		     "Se pudo vaciar la racha si no hay elementos");
	pa2m_afirmar(
		racha_cantidad_combos(racha) == 0,
		"La cantidad de combos de la racha es 0 (ahora esta vacia ahora)");

	racha_destruir(racha);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de vaciar racha

void IterarSobreRachaConFiltroDeColorDevuelveTrue()
{
	racha_t *racha = racha_crear();

	pokemon_t pikachu = { "Pikachu", 15, "AMARILLO", "I" };
	pokemon_t charmander = { "Charmander", 10, "ROJO", "J" };
	pokemon_t lapras = { "Lapras", 15, "AZUL", "NRORSRER" };

	racha_agregar(racha, &pikachu);
	racha_agregar(racha, &charmander);
	racha_agregar(racha, &lapras);

	char *color_buscado = "AMARILLO";

	pa2m_afirmar(racha_iterar(racha, verificar_color_amarillo,
				  color_buscado),
		     "Se encontró al menos un Pokémon de color AMARILLO.");
	racha_destruir(racha);
}

void IterarSobreRachaVaciaDevuelveFalse()
{
	racha_t *racha = racha_crear();

	char *color_buscado = "ROJO";

	pa2m_afirmar(!racha_iterar(racha, verificar_color_amarillo,
				   color_buscado),
		     "No se encontró ningún Pokémon en una racha vacía.");
	racha_destruir(racha);
}

int main()
{
	srand((unsigned int)time(NULL));
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

	pa2m_nuevo_grupo("Pruebas de iterar (TDA Pokedex)");
	IterarSobrePokedexConFiltroDeColorDevuelveTrue();
	IterarSobrepokedexVaciaDevuelveFalse();

	pa2m_nuevo_grupo("Pruebas de buscar (TDA Pokedex)");
	BuscarUnPokemonValidoDevuelveAlPokemon();
	BuscarUnPokemoninexistenteDevuelveNULL();
	BuscarUnPokemonEliminadoDevuelveNULL();

	pa2m_nuevo_grupo(
		"Pruebas de mostrar pokemones ordenados (TDA Pokedex)");
	MostrarPokemonesOrdenadosImprimeEnOrden();
	MostrarPokemonesOrdenadosSegunEjemploImprimeEnOrden();

	pa2m_nuevo_grupo("Pruebas de obtener pokemon random (TDA Pokedex)");
	ObtenerUnPokemonRandomDevuelvePokemonRandom();
	ObtenerPokemonRandomYEliminoUnPokemonMeDevuelvenDistintosPokemones();
	ObtenerUnPokemonRandomEnPokedexVaciaDevuelveNULL();

	pa2m_nuevo_grupo("Pruebas de leer csv (TDA Pokedex)");
	LeerCSVDevuelveTrue();
	LeerCSVConPrametrosNULLDevuelveFalse();
	LeerCSVConNombreIncorrectoDevuelveFalse();
	LeerCSVConseparadorIncorrectoDevuelveFalse();

	pa2m_nuevo_grupo("Pruebas de crear (TDA Racha)");
	CrearRachaDevuelveRacha();

	pa2m_nuevo_grupo("Pruebas de agregar (TDA Racha)");
	AgregarUnPokemonALaRachaDevuelveTrue();
	AgregarVAriosPokemonEsALaRachaDevuelveTrue();
	AgregarPokemonNULLALaRachaDevuelveFalse();
	AgregarEnRachaNULLDevuelveFalse();
	AgregarVAriosVecesAlMismoPokemonALaRachaDevuelveTrue();

	pa2m_nuevo_grupo("Pruebas de eliminar (TDA Racha)");
	EliminarAUnPokemonDeLaRachaDevuelveTrue();
	EliminarAvAriosPokemonesDeLaRachaDevuelveTrue();
	EliminarAUnPokemonDeLaRachaConIndiceIncorrectoDevuelveFalse();
	EliminarAUnPokemonDeLaRachaConEliminadoNULLDevuelveTruePeroNoSeGuardaEliminado();
	EliminarAUnPokemonConRachaNULLDevuelveFalse();

	pa2m_nuevo_grupo("Pruebas de vaciar racha (TDA Racha)");
	VaciarRachaConVAriosPokemonesDevuelveTrue();
	VaciarRachaSinPokemonesDevuelveFalse();
	VaciarConRachaNULLDevuelveFalse();
	VaciarRachaConMuchosPokemonesDevuelveTrue();

	pa2m_nuevo_grupo("Pruebas de iterar racha (TDA Racha)");
	IterarSobreRachaConFiltroDeColorDevuelveTrue();
	IterarSobreRachaVaciaDevuelveFalse();

	return pa2m_mostrar_reporte();
}