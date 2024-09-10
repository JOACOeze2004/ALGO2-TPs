#include "pa2m.h"
#include "src/csv.h"
#include "src/pokedex.h"
#include <string.h>

bool castear_a_int(const char *str, void *ctx)
{
	return sscanf(str, "%d", (int *)ctx) == 1;
}

bool crear_string_nuevo(const char *str, void *ctx)
{
	char *nuevo = malloc(strlen(str) + 1);
	if (nuevo == NULL)
		return false;
	strcpy(nuevo, str);
	*(char **)ctx = nuevo;
	return true;
}

bool castear_a_char(const char *str, void *ctx)
{
	*(char *)ctx = *(char *)str;
	return true;
}

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

void LeerLineaCSVExito()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv",
		';');

	char *nombre;
	char tipo;
	int fuerza, destreza, resistencia;

	void *contextos[] = { &nombre, &tipo, &fuerza, &destreza,
			      &resistencia };
	bool (*funciones[])(const char *,
			    void *) = { crear_string_nuevo, castear_a_char,
					castear_a_int, castear_a_int,
					castear_a_int };

	size_t columnas_leidas =
		leer_linea_csv(archivo, 5, funciones, contextos);

	pa2m_afirmar(columnas_leidas == 5,
		     "Se leen y castean correctamente las 5 columnas.");
	pa2m_afirmar(strcmp(nombre, "Pikachu") == 0,
		     "El nombre se castean correctamente como 'Pikachu'.");
	pa2m_afirmar(tipo == 'E', "El tipo se castean correctamente como 'E'.");
	pa2m_afirmar(fuerza == 20,
		     "La fuerza se castean correctamente como 20.");
	pa2m_afirmar(destreza == 15,
		     "La destreza se castean correctamente como 15.");
	pa2m_afirmar(resistencia == 17,
		     "La resistencia se castean correctamente como 17.");
	free(nombre);
	cerrar_archivo_csv(archivo);
}

void LeerLineaCSVLineaIncompleta()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex_menos_cols.csv",
		';');

	char *nombre;
	char tipo;
	int fuerza, destreza, resistencia;

	void *contextos[] = { &nombre, &tipo, &fuerza, &destreza,
			      &resistencia };
	bool (*funciones[])(const char *,
			    void *) = { crear_string_nuevo, castear_a_char,
					castear_a_int, castear_a_int,
					castear_a_int };

	size_t columnas_leidas =
		leer_linea_csv(archivo, 5, funciones, contextos);

	pa2m_afirmar(
		columnas_leidas < 5,
		"No se leen todas las columnas porque faltan datos en el archivo.");

	if (columnas_leidas >= 1) {
		free(nombre);
	}
	cerrar_archivo_csv(archivo);
}

void LeerLineaCSVValorInvalido()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex_cols_invalidas.csv",
		';');

	char *nombre;
	char tipo;
	int fuerza, destreza, resistencia;

	void *contextos[] = { &nombre, &tipo, &fuerza, &destreza,
			      &resistencia };
	bool (*funciones[])(const char *,
			    void *) = { crear_string_nuevo, castear_a_char,
					castear_a_int, castear_a_int,
					castear_a_int };

	size_t columnas_leidas =
		leer_linea_csv(archivo, 5, funciones, contextos);

	pa2m_afirmar(
		columnas_leidas < 5,
		"No se leen todas las columnas debido a un valor inválido.");

	if (columnas_leidas >= 1) {
		free(nombre);
	}

	cerrar_archivo_csv(archivo);
}

void LeerLineaCSVVAcio()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex_Vacia.csv",
		';');

	char *nombre;
	char tipo;
	int fuerza, destreza, resistencia;

	void *contextos[] = { &nombre, &tipo, &fuerza, &destreza,
			      &resistencia };
	bool (*funciones[])(const char *,
			    void *) = { crear_string_nuevo, castear_a_char,
					castear_a_int, castear_a_int,
					castear_a_int };

	size_t columnas_leidas =
		leer_linea_csv(archivo, 5, funciones, contextos);

	pa2m_afirmar(
		columnas_leidas == 0,
		"No se leen las columnas debido a que el archivo esta vacio.");

	if (columnas_leidas >= 1) {
		free(nombre);
	}

	cerrar_archivo_csv(archivo);
}

void LeerLineaCSVConNullEnFuncionesDevuelveLaCantidadDeColumnasLeidas()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv",
		';');

	char *nombre;
	char tipo;
	int fuerza, destreza, resistencia;

	void *contextos[] = { &nombre, &tipo, &fuerza, &destreza,
			      &resistencia };
	bool (*funciones[])(const char *,
			    void *) = { crear_string_nuevo, castear_a_char,
					NULL, castear_a_int, castear_a_int };

	size_t columnas_leidas =
		leer_linea_csv(archivo, 5, funciones, contextos);

	pa2m_afirmar(
		columnas_leidas == 2,
		"Solo lee la primera y segunda columna si le pasamos un null al vector de funciones.");

	if (columnas_leidas >= 1) {
		free(nombre);
	}
	cerrar_archivo_csv(archivo);
}

void LeerLineaCSVConNullEnctxDevuelveLaCantidadDeColumnasLeidas()
{
	struct archivo_csv *archivo = abrir_archivo_csv(
		"/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv",
		';');

	char *nombre;
	char tipo;
	int destreza, resistencia;

	void *contextos[] = { &nombre, &tipo, NULL, &destreza, &resistencia };
	bool (*funciones[])(const char *,
			    void *) = { crear_string_nuevo, castear_a_char,
					castear_a_int, castear_a_int,
					castear_a_int };

	size_t columnas_leidas =
		leer_linea_csv(archivo, 5, funciones, contextos);

	pa2m_afirmar(
		columnas_leidas == 2,
		"Solo lee la primera y segunda columna si le pasamos un null al vector de contexto.");

	if (columnas_leidas >= 1) {
		free(nombre);
	}
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

	pa2m_afirmar(
		!pokedex_agregar_pokemon(pokedex, pokemon_vacio),
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

	pa2m_afirmar(
		!pokedex_agregar_pokemon(pokedex, pokemon_vacio),
		"No Se puede agregar un pokemon con tipo invalido a la pokedex");
	pa2m_afirmar(
		pokedex_cantidad_pokemones(pokedex) == 0,
		"La cantidad de pokemones en la pokedex sigue siendo 0 después de intentar agregar un pokemon con tipo invalido");

	pokedex_destruir(pokedex);
}

void agregarUnPokemonConStatInvalidaALaPokedexMantieneSuCantidad()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pokemon_vacio = { "Vicente Viloni", TIPO_LUCHA, -1, 40,
					 35 };

	pa2m_afirmar(
		!pokedex_agregar_pokemon(pokedex, pokemon_vacio),
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

	const struct pokemon *encontrado = pokedex_buscar_pokemon(pokedex, "");
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

	struct pokemon charmander = { "Charmander", TIPO_FUEGO, 50, 2, 24 };
	struct pokemon pikachu = { "Picachu", TIPO_ELECTRICO, 50, 5, 20 };

	pokedex_agregar_pokemon(pokedex, charmander);
	pokedex_agregar_pokemon(pokedex, pikachu);

	const struct pokemon *encontrado =
		pokedex_buscar_pokemon(pokedex, "Mewtwo");
	pa2m_afirmar(
		encontrado == NULL,
		"Buscar un pokemon que no existe en una Pokedex llena devuelve NULL");

	pokedex_destruir(pokedex);
}

void buscarUnPokemonQueNoEstaDevuelveNULL()
{
	struct pokedex *pokedex = pokedex_crear();
	struct pokemon pikachu = { "Pikachu", TIPO_ELECTRICO, 55, 40, 35 };
	//struct pokemon charmander = { "Charmander", TIPO_FUEGO, 39, 52, 43 };

	// Agregamos un Pokémon a la pokédex
	pa2m_afirmar(pokedex_agregar_pokemon(pokedex, pikachu),
		     "Se puede agregar un Pokémon a la pokédex");

	// Buscamos un Pokémon que no está en la pokédex
	pa2m_afirmar(
		pokedex_buscar_pokemon(pokedex, "Charmander") == NULL,
		"Buscar un Pokémon que no está en la pokédex devuelve NULL");

	// Destruimos la pokédex para liberar memoria
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

void iterarSobreTodosLosPokemonesDeLaPokedexInvocaLaFuncionCorrectamente()
{
	struct pokedex *pokedex = pokedex_crear();

	struct pokemon pikachu = { "Pikachu", TIPO_ELECTRICO, 20, 15, 17 };
	struct pokemon charmander = { "Charmander", TIPO_FUEGO, 10, 5, 8 };
	struct pokemon larvitar = { "Larvitar", TIPO_ROCA, 30, 1, 40 };
	struct pokemon cacnea = { "Cacnea", TIPO_PLANTA, 11, 12, 14 };
	struct pokemon joltik = { "Joltik", TIPO_ELECTRICO, 8, 10, 5 };

	pokedex_agregar_pokemon(pokedex, pikachu);
	pokedex_agregar_pokemon(pokedex, charmander);
	pokedex_agregar_pokemon(pokedex, larvitar);
	pokedex_agregar_pokemon(pokedex, cacnea);
	pokedex_agregar_pokemon(pokedex, joltik);

	size_t iterados =
		pokedex_iterar_pokemones(pokedex, mostrarPokemon, NULL);
	pa2m_afirmar(iterados == 5,
		     "Se iteró sobre los cinco pokemones agregados");

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
	pokedex_destruir(pokedex);
}

//ELIMINAR
// --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void LeerLineaCSVConPunterosNulos()
{
    struct archivo_csv *archivo = abrir_archivo_csv(
        "/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex_menos_cols.csv",
        ';');

    // Punteros de contexto nulos
    void *contextos[] = { NULL, NULL, NULL, NULL, NULL };
    bool (*funciones[])(const char *, void *) = { NULL, NULL, NULL, NULL, NULL };

    size_t columnas_leidas =
        leer_linea_csv(archivo, 5, funciones, contextos);

    // La cantidad de columnas leídas debería ser 3 cuando los punteros son nulos
    pa2m_afirmar(
        columnas_leidas == 3,
        "Leer línea del archivo de ejemplo devuelve 3 columnas cuando los punteros son nulos (y la función de parseo no los usa).");

    cerrar_archivo_csv(archivo);
}

void LeerLineaCSVConLineasLargas()
{
    struct archivo_csv *archivo = abrir_archivo_csv(
        "/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex_15_cols.csv",
        ';');

    // Asume que el archivo tiene al menos una línea con 15 campos
    char *campos[15];
    for (int i = 0; i < 15; i++) {
        campos[i] = NULL; // Inicializa los punteros
    }

    void *contextos[15];
    for (int i = 0; i < 15; i++) {
        contextos[i] = &campos[i];
    }

    bool (*funciones[15])(const char *, void *);
    for (int i = 0; i < 15; i++) {
        funciones[i] = crear_string_nuevo; // Asume que todos los campos se tratan como cadenas
    }

    size_t columnas_leidas =
        leer_linea_csv(archivo, 15, funciones, contextos);

    pa2m_afirmar(
        columnas_leidas == 15,
        "Se deberían leer 15 columnas cuando el archivo contiene una línea con 15 campos.");

    // Libera los campos leídos
    for (int i = 0; i < 15; i++) {
        if (campos[i] != NULL) {
            free(campos[i]);
        }
    }

    cerrar_archivo_csv(archivo);
}

void LeerLineaCSVLineaIncompleta2()
{
    // Abre el archivo CSV
    struct archivo_csv *archivo = abrir_archivo_csv(
        "/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex_menos_cols.csv",
        ';');

    // Variables para almacenar los datos leídos
    char *nombre = NULL;
    char tipo = '\0';
    int fuerza = 0, destreza = 0, resistencia = 0;

    // Contextos y funciones para la lectura
    void *contextos[] = { &nombre, &tipo, &fuerza, &destreza, &resistencia };
    bool (*funciones[])(const char *, void *) = { crear_string_nuevo, castear_a_char,
                                                  castear_a_int, castear_a_int,
                                                  castear_a_int };

    // Lee la línea del archivo CSV
    size_t columnas_leidas = leer_linea_csv(archivo, 5, funciones, contextos);

    // Verifica que no se lean todas las columnas debido a datos incompletos
    pa2m_afirmar(
        columnas_leidas < 5,
        "No se leen todas las columnas porque faltan datos en el archivo.");

    // Si se leyeron columnas, libera la memoria asignada
    if (columnas_leidas >= 1 && nombre != NULL) {
        free(nombre);
    }

    // Cierra el archivo CSV
    cerrar_archivo_csv(archivo);
}



int main()
{
	pa2m_nuevo_grupo("Pruebas de archivos CSV");
	abrirUnArchivoInexistenteDebeRetornarNull();
	abrirUnArchivoExistenteDebeRetornarUnPunteroValido();
	LeerLineaCSVExito();
	LeerLineaCSVLineaIncompleta();
	LeerLineaCSVValorInvalido();
	LeerLineaCSVVAcio();
	LeerLineaCSVConNullEnFuncionesDevuelveLaCantidadDeColumnasLeidas();
	LeerLineaCSVConNullEnctxDevuelveLaCantidadDeColumnasLeidas();

	pa2m_nuevo_grupo("Pruebas de pokedex");

	crearUnaPokedexResultaEnUnaPokedexVacia();
	crearUnaPokedexNullaResultaEnUnaPokedexNulla();

	pa2m_nuevo_grupo("Pruebas de agregar a la Pokedex");

	agregarUnPokemonALaPokedexAumentaSuCantidad();
	//agregarUnPokemonALaPokedexRepetidoNoTeDeja();
	agregarUnPokemonConNombreVacioALaPokedexMantieneSuCantidad();
	agregarUnPokemonConTipoInvalidoALaPokedexMantieneSuCantidad();
	agregarUnPokemonConStatInvalidaALaPokedexMantieneSuCantidad();

	pa2m_nuevo_grupo("Pruebas de buscar en la Pokedex");

	buscarUnPokemonEnLaPokedexDevuelveElPokemonCorrecto();
	buscarUnPokemonNulloEnLaPokedexDevuelveNull();
	buscarUnPokemonConNombreVacioDevuelveNull();
	buscarUnPokemonInexistenteEnLaPokedexDevuelveNull();
	buscarUnPokemonInexistenteEnUnaPokedexLlenaDevuelveNull();
	buscarUnPokemonQueNoEstaDevuelveNULL();

	pa2m_nuevo_grupo("Pruebas de iteracion en la Pokedex");
	iterarSobreUnaPokedexVaciaNoIteraNingunPokemon();
	iterarSobreTodosLosPokemonesDeLaPokedexInvocaLaFuncionCorrectamente();


	LeerLineaCSVConLineasLargas();
	LeerLineaCSVConPunterosNulos();
	LeerLineaCSVLineaIncompleta2();
	
	return pa2m_mostrar_reporte();
}