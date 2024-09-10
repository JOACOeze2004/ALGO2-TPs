#include "src/csv.h"
#include "src/pokedex.h"
#include <stdio.h>
#include <string.h>

bool son_argumentos_validos(int argc, const char *argv[])
{
	if (argc < 2) {
		printf("%s <archivo>", argv[0]);
		return false;
	}
	return true;
}

//pre:	asumimos que el puntero al struct pokemones  no es NULL, y que los campos e cada pokemon fuern completados exitosamente.
//post:	devolvemos true si pudimos pudimos imprimir cada campo correctamente.
bool imprimir_pokemon(struct pokemon *pokemon, void *ctx)
{
	printf("Nombre: %s, ", pokemon->nombre);
	printf("Tipo: %c, ", pokemon->tipo);
	printf("Fuerza: %i, ", pokemon->fuerza);
	printf("Destreza: %i, ", pokemon->destreza);
	printf("Resistencia: %i\n", pokemon->resistencia);
	return true;
}

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

//pre:	asumimos que le pasamos un tipo de pokemon valido, y que se inicializo correctamente el vector de contador_tipos.
//post:	le aumentamos en uno al contador dependiendo del tipo que sea el pokemon, llendo del 0 al 7 ( tipo agua = 0, fuego = 1, planta = 2, roca = 3, electrico = 4, normal = 5, lucha = 6)
void actualizar_contadores(char tipo, size_t *contador_tipos)
{
	switch (tipo) {
	case TIPO_AGUA:
		contador_tipos[0]++;
		break;
	case TIPO_FUEGO:
		contador_tipos[1]++;
		break;
	case TIPO_PLANTA:
		contador_tipos[2]++;
		break;
	case TIPO_ROCA:
		contador_tipos[3]++;
		break;
	case TIPO_ELECTRICO:
		contador_tipos[4]++;
		break;
	case TIPO_NORMAL:
		contador_tipos[5]++;
		break;
	case TIPO_LUCHA:
		contador_tipos[6]++;
		break;
	}
}

//pre:	Se debe haber inicializado la fuerza maxima en el main. Ademas de que la fuerza del pokemon a eveluar sea valida.
//post:	Devuelve la maxima_fuerza si y solo si la fuerza del pokemon actual es mayor a la que fue registada.
int mayor_fuerza_registrada(int maxima_fuerza, int fuerza_pokemon_actual)
{
	return (fuerza_pokemon_actual > maxima_fuerza) ? fuerza_pokemon_actual :
							 maxima_fuerza;
}

//pre:	Se debe haber inicializado la destreza maxima en el main. Ademas de que la destreza del pokemon a eveluar sea valida.
//post:	Devuelve la maxima_destreza si y solo si la destreza del pokemon actual es mayor a la que fue registada.
int mayor_destreza_registrada(int maxima_destreza, int destreza_pokemon_actual)
{
	return (destreza_pokemon_actual > maxima_destreza) ?
		       destreza_pokemon_actual :
		       maxima_destreza;
}

//pre:	Se debe haber inicializado la resistencia maxima en el main. Ademas de que la resistencia del pokemon a eveluar sea valida.
//post:	Devuelve la maxima_resistencia si y solo si la resistencia del pokemon actual es mayor a la que fue registada.
int mayor_resistencia_registrada(int maxima_resistencia,
				 int resistencia_pokemon_actual)
{
	return (resistencia_pokemon_actual > maxima_resistencia) ?
		       resistencia_pokemon_actual :
		       maxima_resistencia;
}

bool son_funciones_invalidas(size_t columnas,
			     bool (*funciones[])(const char *, void *))
{
	size_t i = 0;
	bool es_invalida = false;
	while (i < columnas && !es_invalida) {
		if (funciones[i] == NULL) {
			es_invalida = true;
		}
		i++;
	}
	return es_invalida;
}

//pre:	El puntero al struct pokedex, deberia ser valido, ademas de que debe funcionar correctamente la funcion de pokedex_cantidad_pokemones.
//post:	sacamos la cantidad total de pokemones en la pokedex.
void impirmir_cantidad_total_pokemones(struct pokedex *nueva_pokedex)
{
	size_t cantidad_total_pokemones =
		pokedex_cantidad_pokemones(nueva_pokedex);
	printf("Total de pokémones en la Pokédex: %zu\n",
	       cantidad_total_pokemones);
}

//pre:	El vector de contadores debe estar inicializado y deberia haberse aumentado con la funcion de aumentar_contadores.
//post:	Imprimimos las cantidades de cada tipo de los pokemones en la pokedex.
void imprimir_cant_tipos_pokemones(size_t *contador_tipos)
{
	printf("\nCantidad de Pokemones de cada tipo:\n");
	printf("Tipo Agua: %zu\n", contador_tipos[0]);
	printf("Tipo Fuego: %zu\n", contador_tipos[1]);
	printf("Tipo Planta: %zu\n", contador_tipos[2]);
	printf("Tipo Roca: %zu\n", contador_tipos[3]);
	printf("Tipo Eléctrico: %zu\n", contador_tipos[4]);
	printf("Tipo Normal: %zu\n", contador_tipos[5]);
	printf("Tipo Lucha: %zu\n", contador_tipos[6]);
}

//pre:	el puntero al struct pokedex y el vector de contador no son NULL.
//post:	imrpimimos los resultados obtenidos de los contadores. Ayudandonos de la funcion de iterar que venia en el .h.
void imprimir_resultados(struct pokedex *nueva_pokedex, size_t *contador_tipos)
{
	printf("\n");
	printf("Bienvenido Ash, aqui estan todos los pokemones que cargaste, las estadisticas de los mismos, la cantidad que hay de cada tipo.\n\n");
	printf("Pokémones en la Pokédex:\n");
	pokedex_iterar_pokemones(nueva_pokedex, imprimir_pokemon, NULL);
	printf("\n");

	impirmir_cantidad_total_pokemones(nueva_pokedex);

	imprimir_cant_tipos_pokemones(contador_tipos);
	printf("\n");
}
void imprimir_stats(int fuerza_maxima, int destreza_maxima,
		    int resistencia_maxima)
{
	printf("La fuerza maxima es de: %i.\n", fuerza_maxima);
	printf("La destreza maxima es de: %i.\n", destreza_maxima);
	printf("La resistencia maxima es de: %i.\n", resistencia_maxima);
	printf("\n");
}

int main(int argc, char const *argv[])
{
	if (!son_argumentos_validos(argc, argv)) {
		return -1;
	}
	const char *nombre_archivo = argv[1];
	struct pokedex *nueva_pokedex = pokedex_crear();
	struct pokemon pokemon;
	struct archivo_csv *archivo = abrir_archivo_csv(nombre_archivo, ';');
	size_t contador_tipos[7] = { 0 };
	int fuerza_maxima = 0;
	int destreza_maxima = 0;
	int resistencia_maxima = 0;

	char *nombre_pokemon = NULL;
	char tipo;
	int stat1, stat2, stat3;

	bool (*funciones[])(const char *,
			    void *) = { crear_string_nuevo, castear_a_char,
					castear_a_int, castear_a_int,
					castear_a_int };
	void *ctx[] = { &nombre_pokemon, &tipo, &stat1, &stat2, &stat3 };
	size_t columnas = 5;
	while (leer_linea_csv(archivo, columnas, funciones, ctx) == 5) {
		pokemon.nombre = nombre_pokemon;
		pokemon.tipo = tipo;
		pokemon.fuerza = stat1;
		pokemon.destreza = stat2;
		pokemon.resistencia = stat3;
		if (!pokedex_agregar_pokemon(nueva_pokedex, pokemon) ||
		    funciones == NULL) {
			printf("\nError al agregar al Pokémon %s a la Pokédex, es posible que ya este en la pokedex, hayas metido un nombre vacio, un tipo invalido o una estadistica negativa.\n ",
			       pokemon.nombre);
		} else {
			actualizar_contadores(pokemon.tipo, contador_tipos);
			fuerza_maxima = mayor_fuerza_registrada(fuerza_maxima,
								pokemon.fuerza);
			destreza_maxima = mayor_destreza_registrada(
				destreza_maxima, pokemon.destreza);
			resistencia_maxima = mayor_resistencia_registrada(
				resistencia_maxima, pokemon.resistencia);
		}
		free(nombre_pokemon);
	}
	if (son_funciones_invalidas(columnas, funciones)) {
		free(nombre_pokemon);
	}
	cerrar_archivo_csv(archivo);
	imprimir_resultados(nueva_pokedex, contador_tipos);
	imprimir_stats(fuerza_maxima, destreza_maxima, resistencia_maxima);
	pokedex_destruir(nueva_pokedex);
	return 0;
}