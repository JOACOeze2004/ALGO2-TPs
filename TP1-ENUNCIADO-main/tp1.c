#include "src/csv.h"
#include "src/pokedex.h"
#include <stdio.h>
#include <string.h>

struct archivo_csv {
	FILE *nombre_archivo;
	size_t columnas;
	char **string;
	char separador;
};
//pre:
//post:
bool son_cant_argumentos_validos(int argc)
{
	return argc == 2;
}

//pre:
//post:
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

//pre:
//post:
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

//pre:
//post:
int mayor_fuerza_registrada(int maxima_fuerza, int fuerza_pokemon_actual) {
    return (fuerza_pokemon_actual > maxima_fuerza) ? fuerza_pokemon_actual : maxima_fuerza;
}

int mayor_destreza_registrada(int maxima_destreza, int destreza_pokemon_actual) {
    return (destreza_pokemon_actual > maxima_destreza) ? destreza_pokemon_actual : maxima_destreza;
}

int mayor_resistencia_registrada(int maxima_resistencia, int resistencia_pokemon_actual) {
    return (resistencia_pokemon_actual > maxima_resistencia) ? resistencia_pokemon_actual : maxima_resistencia;
}

//pre:
//post:
void liberar_partes_restantes(struct archivo_csv *archivo)
{
	for (size_t i = 0; i < archivo->columnas; i++) {
		free(archivo->string[i]);
	}
}

//pre:
//post:
void impirmir_cantidad_total_pokemones(struct pokedex *nueva_pokedex)
{
	size_t cantidad_total_pokemones =
		pokedex_cantidad_pokemones(nueva_pokedex);
	printf("\n");
	printf("Total de pokémones en la Pokédex: %zu\n",
	    cantidad_total_pokemones);
}

//pre:
//post:
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

//pre:
//post:
void imprimir_resultados(struct pokedex *nueva_pokedex, size_t *contador_tipos)
{
	printf("\n");
	printf("Bienvenido ash, aqui encontaras todos los pokemones que cargaste, las estdisticas de los mismos, ademas de la cantidad que hay de cada tipo y quien se el mejor en cada estaditsica que me pasaste\n\n");
	printf("Pokémones en la Pokédex:\n");
	pokedex_iterar_pokemones(nueva_pokedex, imprimir_pokemon, NULL);
	printf("\n");

	impirmir_cantidad_total_pokemones(nueva_pokedex);

	imprimir_cant_tipos_pokemones(contador_tipos);
	printf("\n");
}


int main(int argc, char const *argv[])
{
	if (!son_cant_argumentos_validos(argc)) {
		printf("%s <archivo>", argv[0]);
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
					castear_a_int,	    castear_a_int,
					castear_a_int,	    NULL };
	void *ctx[] = { &nombre_pokemon, &tipo, &stat1, &stat2, &stat3 };
	size_t columnas_a_leer = 5;
	while (leer_linea_csv(archivo, columnas_a_leer, funciones, ctx) == 5) {
		pokemon.nombre = nombre_pokemon;
		pokemon.tipo = tipo;
		pokemon.fuerza = stat1;
		pokemon.destreza = stat2;
		pokemon.resistencia = stat3;
		if (!pokedex_agregar_pokemon(nueva_pokedex, pokemon)) {
			printf("Error al agregar al Pokémon %s a la Pokédex, es posible que ya este en la pokedex, hayas metido un nombre vacio, un tipo invalido o una estadistica negativa.\n ",
			       pokemon.nombre);
		}else{
			actualizar_contadores(pokemon.tipo, contador_tipos);
			fuerza_maxima = mayor_fuerza_registrada(fuerza_maxima,pokemon.fuerza);
			destreza_maxima = mayor_destreza_registrada(destreza_maxima, pokemon.destreza);
			resistencia_maxima = mayor_resistencia_registrada(resistencia_maxima, pokemon.resistencia);
		}
		liberar_partes_restantes(archivo);
		free(nombre_pokemon);
	}
	cerrar_archivo_csv(archivo);
	imprimir_resultados(nueva_pokedex, contador_tipos);
	printf("La fuerza maxima es de: %i.\n",fuerza_maxima);
	printf("La destreza maxima es de: %i.\n",destreza_maxima);
	printf("La resistencia maxima es de: %i.\n",resistencia_maxima);

	pokedex_destruir(nueva_pokedex);
	return 0;
}