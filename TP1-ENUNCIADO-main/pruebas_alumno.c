#include "pa2m.h"
#include "src/csv.h"
#include "src/pokedex.h"
#include <string.h>

struct archivo_csv {
	FILE *nombre_archivo;
	size_t columnas;
	char **string;
	char separador;
};

void abrirUnArchivoInexistenteDebeRetornarNull()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("noexiste/noexiste/noexiste/no", ';');
	pa2m_afirmar(archivo == NULL, "El archivo no existe y se retorna NULL");
}

void abrirUnArchivoExistenteDebeRetornarUnPunteroValido()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv",
		';');
	pa2m_afirmar(
		archivo != NULL,
		"El archivo existente se abre correctamente y se retorna un puntero válido");
	if (archivo != NULL) {
		cerrar_archivo_csv(archivo);
	}
}

void leerLineaDeArchivoDebeDividirCorrectamente()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv",
		';');
	pa2m_afirmar(archivo != NULL,
		     "El archivo existente se abre correctamente");

	bool (*funciones[])(const char *, void *) = {
		NULL
	}; // Puedes definir funciones de prueba aquí
	void *ctx[] = { NULL }; // Puedes definir contextos si es necesario

	size_t columnas = 1; // Ajusta según el archivo CSV
	size_t columnas_leidas =
		leer_linea_csv(archivo, columnas, funciones, ctx);

	// Verifica que se hayan leído la cantidad correcta de columnas
	pa2m_afirmar(columnas_leidas == columnas,
		     "es columnas casteadas correctamente");

	cerrar_archivo_csv(archivo);
}


void leerPrimeraLineaYVerificar()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv",
		';');
	pa2m_afirmar(archivo != NULL, "El archivo se abre correctamente");

	bool (*funciones[])(const char *, void *) = { NULL };
	void *ctx[] = { NULL };

	size_t columnas =
		5; // Ajusta según el número de columnas de tu archivo CSV

	// Lee solo la primera línea del archivo CSV
	size_t columnas_leidas =
		leer_linea_csv(archivo, columnas, funciones, ctx);

	// Verifica que se han leído la cantidad correcta de columnas
	pa2m_afirmar(columnas_leidas == columnas,
		     "Son 5 columnas casteadas correctamente");

	// Verifica que cada columna tenga un valor válido (ejemplo: Pikachu;E;20;15;17)
	pa2m_afirmar(strcmp(archivo->string[0], "Pikachu") == 0,
		     "La primera columna es 'Pikachu'");
	pa2m_afirmar(strcmp(archivo->string[1], "E") == 0,
		     "La segunda columna es 'E'");
	pa2m_afirmar(strcmp(archivo->string[2], "20") == 0,
		     "La tercera columna es '20'");
	pa2m_afirmar(strcmp(archivo->string[3], "15") == 0,
		     "La cuarta columna es '15'");
	pa2m_afirmar(strcmp(archivo->string[4], "17") == 0,
		     "La quinta columna es '17'");

	// Imprime las columnas para verificar visualmente el contenido
	for (size_t i = 0; i < columnas_leidas; i++) {
		printf("Columna %zu: %s\n", i, archivo->string[i]);
	}

	cerrar_archivo_csv(archivo);
}

void leerYVerificarTodasLasLineas()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv",
		';');
	pa2m_afirmar(archivo != NULL, "El archivo se abre correctamente");

	size_t columnas =
		5; // Ajusta según el número de columnas de tu archivo CSV
	bool (*funciones[])(const char *, void *) = { NULL };
	void *ctx[] = { NULL };

	const char *valores_esperados[][5] = {
		{ "Pikachu", "E", "20", "15", "17" },
		{ "Charmander", "F", "10", "5", "8" },
		{ "Larvitar", "R", "30", "1", "40" },
		{ "Cacnea", "P", "11", "12", "14" },
		{ "Joltik", "E", "8", "10", "5" },
		{ "Togepi", "N", "8", "8", "2" },
		{ "Floatzel", "A", "24", "20", "5" },
		{ "Dedenne", "E", "15", "5", "33" },
		{ "Magcargo", "F", "22", "20", "22" }
	};

	size_t num_filas =
		sizeof(valores_esperados) / sizeof(valores_esperados[0]);

	for (size_t fila = 0; fila < num_filas; fila++) {
		size_t columnas_leidas =
			leer_linea_csv(archivo, columnas, funciones, ctx);
		pa2m_afirmar(columnas_leidas == columnas,
			     "Se han leído la cantidad correcta de columnas");

		for (size_t col = 0; col < columnas_leidas; col++) {
			pa2m_afirmar(strcmp(archivo->string[col],
					    valores_esperados[fila][col]) == 0,
				     "La columna es correcta");
			printf("Fila %zu, Columna %zu: %s (Esperado: %s)\n",
			       fila + 1, col + 1, archivo->string[col],
			       valores_esperados[fila][col]);
			free(archivo->string[col]);
		}
	}
	cerrar_archivo_csv(archivo);
}

void dividirUnaLineaDeCSVResultaEnLasPartesCorrectas()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv",
		';');

	if (!archivo) {
		printf("Error al abrir el archivo\n");
		return;
	}

	// Suponemos que el archivo tiene 5 columnas
	size_t columnas = 5;

	// Array de funciones para castear cada columna
	bool (*funciones[])(const char *, void *) = { NULL };

	// Array de punteros para almacenar los valores convertidos
	char columna1[50];
	char columna2[50];
	int columna3, columna4, columna5;

	void *ctx[] = { columna1, columna2, &columna3, &columna4, &columna5 };

	size_t cantidad_columnas_leidas =
		leer_linea_csv(archivo, columnas, funciones, ctx);

	pa2m_afirmar(cantidad_columnas_leidas == columnas,
		     "La cantidad de columnas leídas es correcta");
	pa2m_afirmar(strcmp(columna1, "Pikachu") == 0,
		     "La primera columna es Pikachu");
	pa2m_afirmar(strcmp(columna2, "E") == 0, "La segunda columna es E");
	pa2m_afirmar(columna3 == 20, "La tercera columna es 20");
	pa2m_afirmar(columna4 == 15, "La cuarta columna es 15");
	pa2m_afirmar(columna5 == 17, "La quinta columna es 17");

	cerrar_archivo_csv(archivo);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// PUREBAS POKEDEX (crear pokedex)
void crearUnaPokedexResultaEnUnaPokedexVacia()
{
	struct pokedex *pokedex = pokedex_crear();
	pa2m_afirmar(pokedex != NULL,
		     "Crear una pokedex resulta en una pokedex no nula");
	pa2m_afirmar(pokedex_cantidad_pokemones(pokedex) == 0,
		     "Una pokedex recién creada está vacía");
	pokedex_destruir(pokedex);
}

void crearUnaPokedexNullaResultaEnUnaPokedexNulla()
{
	struct pokedex *pokedex = NULL;
	pa2m_afirmar(pokedex == NULL,
		    "Crear una pokedex nula resulta en una pokedex nula");
}

//Pruebas de agregar pokemones

void agregarUnPokemonALaPokedexAumentaSuCantidad()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pikachu = { "Pikachu", TIPO_ELECTRICO, 55, 40, 35 };

	pa2m_afirmar(pokedex_agregar_pokemon(pokedex, pikachu),
		     "Se puede agregar un pokemon a la pokedex");
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 1,
		"La cantidad de pokemones en la pokedex es 1 después de agregar un pokemon");

	pokedex_destruir(pokedex);
}

void agregarUnPokemonConNombreVacioALaPokedexMantieneSuCantidad()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon_vacio = { "", TIPO_NORMAL, 55, 40, 35 };

	pa2m_afirmar(!pokedex_agregar_pokemon(pokedex, pokemon_vacio),
		     "No Se puede agregar un pokemon con nombre vacio a la pokedex");
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 0,
		"La cantidad de pokemones en la pokedex sigue siendo 0 después de intentar agregar un pokemon con nombre vacio");

	pokedex_destruir(pokedex);
}

void agregarUnPokemonConTipoInvalidoALaPokedexMantieneSuCantidad()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon_vacio = { "Juan el vago", 'V', 55, 40, 35 };

	pa2m_afirmar(!pokedex_agregar_pokemon(pokedex, pokemon_vacio),
		     "No Se puede agregar un pokemon con tipo invalido a la pokedex");
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 0,
		"La cantidad de pokemones en la pokedex sigue siendo 0 después de intentar agregar un pokemon con tipo invalido");

	pokedex_destruir(pokedex);
}

void agregarUnPokemonConStatInvalidaALaPokedexMantieneSuCantidad()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon_vacio = { "Vicente Viloni", TIPO_LUCHA, -1, 40, 35 };

	pa2m_afirmar(!pokedex_agregar_pokemon(pokedex, pokemon_vacio),
		     "No Se puede agregar un pokemon con stats negativas a la pokedex");
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 0,
		"La cantidad de pokemones en la pokedex sigue siendo 0 después de intentar agregar un pokemon con stats negativas");

	pokedex_destruir(pokedex);
}

void agregarUnPokemonALaPokedexRepetidoNoTeDeja()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pikachu = { "Pikachu", TIPO_ELECTRICO, 55, 40, 35 };

	pa2m_afirmar(pokedex_agregar_pokemon(pokedex, pikachu),
		     "Se puede agregar un pokemon a la pokedex");
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 1,
		"La cantidad de pokemones en la pokedex es 1 después de agregar un pokemon");
	pa2m_afirmar(
		!pokedex_agregar_pokemon(pokedex, pikachu),
		"No se puede agregar un pokemon que a estaba en la pokedex");
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 1,
		"La cantidad de pokemones en la pokedex se mantiene en 1 después de intentar agregar un pokemon");

	pokedex_destruir(pokedex);
}

//Pruebas de Buscar pokemones

void buscarUnPokemonEnLaPokedexDevuelveElPokemonCorrecto()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon charmander = { "Charmander", TIPO_FUEGO, 52, 43, 39 };
	pokedex_agregar_pokemon(pokedex, charmander);

	const struct pokemon *encontrado =
		pokedex_buscar_pokemon(pokedex, "Charmander");
	pa2m_afirmar(encontrado != NULL,
		     "Buscar un pokemon existente devuelve un puntero no nulo");
	pa2m_afirmar(strcmp(encontrado->nombre, "Charmander") == 0,
		     "El nombre del pokemon encontrado es 'Charmander'");

	pokedex_destruir(pokedex);
}

void buscarUnPokemonConNombreVacioDevuelveNull()
{
    struct pokedex *pokedex = pokedex_crear();
    struct pokemon charmander = { "Charmander", TIPO_FUEGO, 52, 43, 39 };
    pokedex_agregar_pokemon(pokedex, charmander);

    const struct pokemon *encontrado =
        pokedex_buscar_pokemon(pokedex, "");
    pa2m_afirmar(encontrado == NULL,
                 "Buscar un pokemon con nombre vacío devuelve NULL");

    pokedex_destruir(pokedex);
}

void buscarUnPokemonNulloEnLaPokedexDevuelveNull()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon charmander = { "Charmander", TIPO_FUEGO, 52, 43, 39 };
	pokedex_agregar_pokemon(pokedex, charmander);

    char *pokemon_buscado = NULL;
	const struct pokemon *encontrado =
		pokedex_buscar_pokemon(pokedex, pokemon_buscado);
	pa2m_afirmar(encontrado == NULL,
		     "Buscar un pokemon nulo devuelve un puntero nulo");
	pokedex_destruir(pokedex);
}

void buscarUnPokemonInexistenteEnLaPokedexDevuelveNull()
{
	struct pokedex *pokedex = pokedex_crear();
	const struct pokemon *encontrado =
		pokedex_buscar_pokemon(pokedex, "Bulbasaur");

	pa2m_afirmar(encontrado == NULL,
		     "Buscar un pokemon inexistente devuelve NULL");

	pokedex_destruir(pokedex);
}

void buscarUnPokemonInexistenteEnUnaPokedexLlenaDevuelveNull()
{
	struct pokedex *pokedex = pokedex_crear();

	struct pokemon charmander = {
		"Charmander", TIPO_FUEGO, 50, 2, 24
	}; 
	struct pokemon pikachu = { "Picachu", TIPO_ELECTRICO, 50, 5, 20 };
	struct pokemon bulbasaur = { "Bulbasaur", TIPO_PLANTA, 49, 49, 45 };
	struct pokemon squirtle = { "Squirtle", TIPO_AGUA, 48, 65, 44 };

	pokedex_agregar_pokemon(pokedex, charmander);
	pokedex_agregar_pokemon(pokedex, squirtle);
	pokedex_agregar_pokemon(pokedex, bulbasaur);
	pokedex_agregar_pokemon(pokedex, pikachu);

	const struct pokemon *encontrado =
		pokedex_buscar_pokemon(pokedex, "Mewtwo");
	pa2m_afirmar(
		encontrado == NULL,
		"Buscar un pokemon que no existe en una Pokedex llena devuelve NULL");

	pokedex_destruir(pokedex);
}



bool mostrarPokemon(struct pokemon *p, void *ctx)
{
	if (p) {
		pa2m_afirmar(p != NULL,
			     "Se itera correctamente sobre un pokemon");
	}
	return true;
}

//Pruebas de iterar pokemones


void iterarSobreUnaPokedexVaciaNoIteraNingunPokemon()
{
    struct pokedex *pokedex = pokedex_crear();

    size_t iterados =
        pokedex_iterar_pokemones(pokedex, mostrarPokemon, NULL);
    pa2m_afirmar(iterados == 0,
                 "No se itera sobre ningún pokemon en una Pokédex vacía");

    pokedex_destruir(pokedex);
}

void iterarSobreLosPokemonesDeLaPokedexInvocaLaFuncionCorrectamente()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon bulbasaur = { "Bulbasaur", TIPO_PLANTA, 49, 49, 45 };
	struct pokemon squirtle = { "Squirtle", TIPO_AGUA, 48, 65, 44 };

	pokedex_agregar_pokemon(pokedex, bulbasaur);
	pokedex_agregar_pokemon(pokedex, squirtle);

	size_t iterados =
		pokedex_iterar_pokemones(pokedex, mostrarPokemon, NULL);
	pa2m_afirmar(iterados == 2,
		     "Se iteró sobre los dos pokemones agregados");

	pokedex_destruir(pokedex);
}

void iterarSobreTodosLosPokemonesDeLaPokedexInvocaLaFuncionCorrectamente()
{
	struct pokedex *pokedex = pokedex_crear();

	struct pokemon pikachu = { "Pikachu", TIPO_ELECTRICO, 20, 15, 17 };
	struct pokemon charmander = { "Charmander", TIPO_FUEGO, 10, 5, 8 };
	struct pokemon larvitar = { "Larvitar", TIPO_ROCA, 30, 1, 40 };
	struct pokemon cacnea = { "Cacnea", TIPO_PLANTA, 11, 12, 14 };
	struct pokemon joltik = { "Joltik", TIPO_ELECTRICO, 8, 10, 5 };
	struct pokemon togepi = { "Togepi", TIPO_NORMAL, 8, 8, 2 };
	struct pokemon floatzel = { "Floatzel", TIPO_AGUA, 24, 20, 5 };
	struct pokemon dedenne = { "Dedenne", TIPO_ELECTRICO, 15, 5, 33 };
	struct pokemon magcargo = { "Magcargo", TIPO_FUEGO, 22, 20, 22 };

	pokedex_agregar_pokemon(pokedex, pikachu);
	pokedex_agregar_pokemon(pokedex, charmander);
	pokedex_agregar_pokemon(pokedex, larvitar);
	pokedex_agregar_pokemon(pokedex, cacnea);
	pokedex_agregar_pokemon(pokedex, joltik);
	pokedex_agregar_pokemon(pokedex, togepi);
	pokedex_agregar_pokemon(pokedex, floatzel);
	pokedex_agregar_pokemon(pokedex, dedenne);
	pokedex_agregar_pokemon(pokedex, magcargo);

	size_t iterados =
		pokedex_iterar_pokemones(pokedex, mostrarPokemon, NULL);
	pa2m_afirmar(iterados == 9,
		     "Se iteró sobre los nueve pokemones agregados");

	const struct pokemon *encontrado =
		pokedex_buscar_pokemon(pokedex, "Pikachu");
	pa2m_afirmar(encontrado != NULL &&
			     strcmp(encontrado->nombre, "Pikachu") == 0,
		     "Pikachu está en la pokedex");

	encontrado = pokedex_buscar_pokemon(pokedex, "Charmander");
	pa2m_afirmar(encontrado != NULL &&
			     strcmp(encontrado->nombre, "Charmander") == 0,
		     "Charmander está en la pokedex");

	encontrado = pokedex_buscar_pokemon(pokedex, "Larvitar");
	pa2m_afirmar(encontrado != NULL &&
			     strcmp(encontrado->nombre, "Larvitar") == 0,
		     "Larvitar está en la pokedex");

	encontrado = pokedex_buscar_pokemon(pokedex, "Cacnea");
	pa2m_afirmar(encontrado != NULL &&
			     strcmp(encontrado->nombre, "Cacnea") == 0,
		     "Cacnea está en la pokedex");

	encontrado = pokedex_buscar_pokemon(pokedex, "Joltik");
	pa2m_afirmar(encontrado != NULL &&
			     strcmp(encontrado->nombre, "Joltik") == 0,
		     "Joltik está en la pokedex");

	encontrado = pokedex_buscar_pokemon(pokedex, "Togepi");
	pa2m_afirmar(encontrado != NULL &&
			     strcmp(encontrado->nombre, "Togepi") == 0,
		     "Togepi está en la pokedex");

	encontrado = pokedex_buscar_pokemon(pokedex, "Floatzel");
	pa2m_afirmar(encontrado != NULL &&
			     strcmp(encontrado->nombre, "Floatzel") == 0,
		     "Floatzel está en la pokedex");

	encontrado = pokedex_buscar_pokemon(pokedex, "Dedenne");
	pa2m_afirmar(encontrado != NULL &&
			     strcmp(encontrado->nombre, "Dedenne") == 0,
		     "Dedenne está en la pokedex");

	encontrado = pokedex_buscar_pokemon(pokedex, "Magcargo");
	pa2m_afirmar(encontrado != NULL &&
			     strcmp(encontrado->nombre, "Magcargo") == 0,
		     "Magcargo está en la pokedex");

	pokedex_destruir(pokedex);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de archivos CSV");
	abrirUnArchivoInexistenteDebeRetornarNull();
	abrirUnArchivoExistenteDebeRetornarUnPunteroValido();

	//leerLineaDeArchivoDebeDividirCorrectamente();
	//leerPrimeraLineaYVerificar();
	//leerYVerificarTodasLasLineas();
	//dividirUnaLineaDeCSVResultaEnLasPartesCorrectas();
	//leerYVerificarArchivoCompleto();
	//liberarRecursosCorrectamente();

	pa2m_nuevo_grupo("Pruebas de pokedex");

	crearUnaPokedexResultaEnUnaPokedexVacia();
    crearUnaPokedexNullaResultaEnUnaPokedexNulla();

	pa2m_nuevo_grupo("Pruebas de agregar a la Pokedex");

	agregarUnPokemonALaPokedexAumentaSuCantidad();
	agregarUnPokemonALaPokedexRepetidoNoTeDeja();
	agregarUnPokemonConNombreVacioALaPokedexMantieneSuCantidad();
	agregarUnPokemonConTipoInvalidoALaPokedexMantieneSuCantidad();
	agregarUnPokemonConStatInvalidaALaPokedexMantieneSuCantidad();

	pa2m_nuevo_grupo("Pruebas de buscar en la Pokedex");

	buscarUnPokemonEnLaPokedexDevuelveElPokemonCorrecto();
    buscarUnPokemonNulloEnLaPokedexDevuelveNull();
    buscarUnPokemonConNombreVacioDevuelveNull();
	buscarUnPokemonInexistenteEnLaPokedexDevuelveNull();
	buscarUnPokemonInexistenteEnUnaPokedexLlenaDevuelveNull();

	pa2m_nuevo_grupo("Pruebas de iteracion en la Pokedex");
    iterarSobreUnaPokedexVaciaNoIteraNingunPokemon();
	iterarSobreLosPokemonesDeLaPokedexInvocaLaFuncionCorrectamente();
	iterarSobreTodosLosPokemonesDeLaPokedexInvocaLaFuncionCorrectamente();

	return pa2m_mostrar_reporte();
}