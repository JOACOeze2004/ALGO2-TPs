#include "csv.h"
#include <stdio.h>
#include <string.h>

struct archivo_csv {
	FILE* nombre_archivo;
	size_t columnas;
	char** string;
	char separador;
};

//pre:  Asumimos q recibimos un valido, que el puntero a letra actual se pasa correctamente y que el str es valida tambien. Ademas de que el str termina en '\0' (ya sea vacio o no).
//post: devuelve la longitud que tenga una palabra hatsa que llege al delimitador o al final de la misma. Al pasarle por referencai letra_actual, se "mantiene" el orden en caso de encontrar un delimitador por ejemplo.
size_t calcular_longitud_subpalabra(const char *str, char separador,
				    size_t *letra_actual)
{
	size_t longitud = 0;
	while (str[*letra_actual] != separador && str[*letra_actual] != '\0' && str[*letra_actual] != '\n') {
		longitud++;
		(*letra_actual)++;
	}
	return longitud;
}

//pre:  asumimos que todos los paramatros son validos.
//post: copiamos la subcadena al campo string de Partes
void escribir_subcadena(const char *string, size_t long_subcadena,
			size_t letra_actual, size_t i,
			struct archivo_csv *texto_editado)
{
	for (size_t j = 0; j < long_subcadena; j++) {
		texto_editado->string[i][j] =
			string[letra_actual - long_subcadena + j];
	}
	texto_editado->string[i][long_subcadena] = '\0';
}

//pre:  Asumimos que la cantidad asignada es valida y que el struc Partes tambien.
//post: Libera toda la memoria pedida, usada principalmente en caso de que falle alguna asignacion de memoria al pedirle memoria para cada subcadena.
void liberar_memoria_en_substr(struct archivo_csv *texto_editado,
			       size_t cantidad_asignada)
{
	for (size_t i = 0; i < cantidad_asignada; i++) {
		free(texto_editado->string[i]);
	}
	free(texto_editado->string);
	free(texto_editado);
}

//pre:  Asumimos que los parametros pasados son validos.
//post: escribimos en el campo string, la nueva subcadena dividida por el separador. En caso de fallo al asiganr memoria para cada substring, corta el while y llama a la funcion de liberar memoria.
void escribir_palabras(const char *string, char separador,
		       struct archivo_csv *texto_editado)
{
	size_t i = 0;
	size_t letra_actual = 0;
	int error = 0;
	while (i < texto_editado->columnas && !error) {
		size_t long_subcadena = calcular_longitud_subpalabra(
			string, separador, &letra_actual);
		texto_editado->string[i] = malloc(long_subcadena + 1);
		if (texto_editado->string[i] == NULL) {
			error = 1;
		}
		escribir_subcadena(string, long_subcadena, letra_actual, i,
				   texto_editado);
		i++;
		if (string[letra_actual] == separador) {
			letra_actual++;
		}		
	}
	if (error) {
		liberar_memoria_en_substr(texto_editado, i);
	}
}

struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo, char separador){
	struct archivo_csv *archivo = malloc(sizeof(struct archivo_csv));
	if (archivo == NULL){
		return NULL;
	}
	archivo->nombre_archivo = fopen(nombre_archivo,"r");
	if (archivo->nombre_archivo == NULL){
		free(archivo);
		return NULL;
	}
	archivo->columnas = 0;
	archivo->string = NULL;
	archivo->separador = separador;
	return archivo;
}

struct archivo_csv *dividir_string(struct archivo_csv* archivo ,const char *string)
{
	char **str_temp = realloc(archivo->string,
				  sizeof(char *) * archivo->columnas);
	if (str_temp == NULL) {
		free(archivo);
		return NULL;
	}
	archivo->string = str_temp;
	escribir_palabras(string, archivo->separador, archivo);
	return archivo;
}

void liberar_partes(struct archivo_csv *partes) {
    free(partes->string);
    fclose(partes->nombre_archivo);
    free(partes);
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

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas, bool (*funciones[])(const char *, void *), void *ctx[]){
	char texto[50];
	size_t contador_lineas_casteadas = 0;
	size_t i = 0;
	if(fgets(texto,sizeof(texto),archivo->nombre_archivo)== NULL){
		return contador_lineas_casteadas;
	}
	archivo->columnas = columnas;
	struct archivo_csv *partes = dividir_string(archivo,texto);
	if (partes == NULL) {
		return 0;
	}
	while (funciones[i] != NULL && i < archivo->columnas){
		if (funciones[i](archivo->string[i],ctx[i])){
			contador_lineas_casteadas++;
		}
		i++;
	}
	return contador_lineas_casteadas;
}

void cerrar_archivo_csv(struct archivo_csv *archivo){
	if (archivo != NULL){
		liberar_partes(archivo);
	}
}

// MAIN

//  -------------------------------------------------------------------------------------------------------------------------------------------------- //
void imprimir_resultados(const char *nombre_pokemon, char tipo, int stat1, int stat2, int stat3) {
    printf("Pokemon: %s\n", nombre_pokemon);
    printf("Tipo: %c\n", tipo);
    printf("Stat 1: %d\n", stat1);
    printf("Stat 2: %d\n", stat2);
    printf("Stat 3: %d\n", stat3);
}

// Prueba 1: Datos válidos
void prueba_datos_validos() {
    const char *nombre_archivo = "/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv";
    char separador = ';';

    // Crear archivo de prueba
    FILE *archivo = fopen(nombre_archivo, "r");
    fprintf(archivo, "Pikachu;E;20;15;17\n");
    fclose(archivo);

    struct archivo_csv *archivo_csv = abrir_archivo_csv(nombre_archivo, separador);
    if (!archivo_csv) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char *nombre_pokemon;
    char tipo;
    int stat1, stat2, stat3;
    //char nombre_pokemon[50];

    bool (*funciones[])(const char *, void *) = {crear_string_nuevo, castear_a_char, castear_a_int, castear_a_int, castear_a_int, NULL};
    void *ctx[] = {&nombre_pokemon, &tipo, &stat1, &stat2, &stat3};

    size_t columnas_leidas = leer_linea_csv(archivo_csv, 5, funciones, ctx);

    if (columnas_leidas == 5) {
        imprimir_resultados(nombre_pokemon, tipo, stat1, stat2, stat3);
    } else {
        printf("Error al leer las columnas. Se leyeron %zu columnas correctamente.\n", columnas_leidas);
    }
    free(nombre_pokemon);

    cerrar_archivo_csv(archivo_csv);
}

// Prueba 2: Datos con errores en columnas
void prueba_datos_con_errores() {
    const char *nombre_archivo = "/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv";
    char separador = ';';

    // Crear archivo de prueba
    FILE *archivo = fopen(nombre_archivo, "r");
    fprintf(archivo, "Pikachu;E;20;15;incorrecto\n");
    fclose(archivo);

    struct archivo_csv *archivo_csv = abrir_archivo_csv(nombre_archivo, separador);
    if (!archivo_csv) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char *nombre_pokemon;
    char tipo;
    int stat1, stat2, stat3;
    //char nombre_pokemon[50];

    bool (*funciones[])(const char *, void *) = {crear_string_nuevo, castear_a_char, castear_a_int, castear_a_int, castear_a_int, NULL};
    void *ctx[] = {&nombre_pokemon, &tipo, &stat1, &stat2, &stat3};

    size_t columnas_leidas = leer_linea_csv(archivo_csv, 5, funciones, ctx);

    if (columnas_leidas == 4) {
        imprimir_resultados(nombre_pokemon, tipo, stat1, stat2, stat3);
    } else {
        printf("Error al leer las columnas. Se leyeron %zu columnas correctamente.\n", columnas_leidas);
    }
    free(nombre_pokemon);

    cerrar_archivo_csv(archivo_csv);
}

// Prueba 3: Datos con columnas adicionales
void prueba_datos_columnas_adicionales() {
    const char *nombre_archivo = "/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv";
    char separador = ';';

    // Crear archivo de prueba
    FILE *archivo = fopen(nombre_archivo, "r");
    fprintf(archivo, "Pikachu;E;20;15;17;extra\n");
    fclose(archivo);

    struct archivo_csv *archivo_csv = abrir_archivo_csv(nombre_archivo, separador);
    if (!archivo_csv) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char *nombre_pokemon;
    char tipo;
    int stat1, stat2, stat3;
    //char nombre_pokemon[50];

    bool (*funciones[])(const char *, void *) = {crear_string_nuevo, castear_a_char, castear_a_int, castear_a_int, castear_a_int, NULL};
    void *ctx[] = {&nombre_pokemon, &tipo, &stat1, &stat2, &stat3};

    size_t columnas_leidas = leer_linea_csv(archivo_csv, 5, funciones, ctx);

    if (columnas_leidas == 5) {
        imprimir_resultados(nombre_pokemon, tipo, stat1, stat2, stat3);
    } else {
        printf("Error al leer las columnas. Se leyeron %zu columnas correctamente.\n", columnas_leidas);
    }
    free(nombre_pokemon);
    cerrar_archivo_csv(archivo_csv);
}

// Prueba 4: Línea vacía
void prueba_linea_vacia() {
    const char *nombre_archivo = "/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv";
    char separador = ';';

    // Crear archivo de prueba
    FILE *archivo = fopen(nombre_archivo, "r");
    fprintf(archivo, "\n");
    fclose(archivo);

    struct archivo_csv *archivo_csv = abrir_archivo_csv(nombre_archivo, separador);
    if (!archivo_csv) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char *nombre_pokemon;
    char tipo;
    int stat1, stat2, stat3;
    //char nombre_pokemon[50];

    bool (*funciones[])(const char *, void *) = {crear_string_nuevo, castear_a_char, castear_a_int, castear_a_int, castear_a_int, NULL};
    void *ctx[] = {&nombre_pokemon, &tipo, &stat1, &stat2, &stat3};

    size_t columnas_leidas = leer_linea_csv(archivo_csv, 5, funciones, ctx);

    if (columnas_leidas == 0) {
        printf("Línea vacía leída correctamente.\n");
    } else {
        printf("Error al leer la línea vacía. Se leyeron %zu columnas correctamente.\n", columnas_leidas);
    }
    free(nombre_pokemon);
    cerrar_archivo_csv(archivo_csv);
}


void prueba_datos_validos2() {
    const char *nombre_archivo = "/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv";
    char separador = ';';

    struct archivo_csv *archivo_csv = abrir_archivo_csv(nombre_archivo, separador);
    if (!archivo_csv) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char *nombre_pokemon;
    char tipo;
    int stat1, stat2, stat3;
    //char nombre_pokemon[50];

    bool (*funciones[])(const char *, void *) = {crear_string_nuevo, castear_a_char, castear_a_int, castear_a_int, castear_a_int, NULL};
    void *ctx[] = {&nombre_pokemon, &tipo, &stat1, &stat2, &stat3};


    // Leer línea por línea hasta el final del archivo
    while (true) {
        size_t columnas_leidas = leer_linea_csv(archivo_csv, 5, funciones, ctx);
        if (columnas_leidas == 0) {
            // Si no se leen columnas, el archivo está vacío o ocurrió un error
            break;
        }
        if (columnas_leidas == 5) {
            imprimir_resultados(nombre_pokemon, tipo, stat1, stat2, stat3);
        } else {
            printf("Error al leer las columnas. Se leyeron %zu columnas correctamente.\n", columnas_leidas);
        }
        for (size_t i = 0; i < archivo_csv->columnas; i++){
            free(archivo_csv->string[i]);
        }
        free(nombre_pokemon);
    }

    cerrar_archivo_csv(archivo_csv);
}

// int main() {
//     //prueba_datos_validos();
//    	//prueba_datos_con_errores(); 
//     //prueba_datos_columnas_adicionales();
//     //prueba_linea_vacia();
// 	prueba_datos_validos2();
//     return 0;
// }

int main()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');

	bool (*funciones[3])(const char *, void *) = { crear_string_nuevo,
						       castear_a_char,
						       castear_a_int };
	int entero;
	char caracter;
	char *string = NULL;
	void *punteros[3] = { &string, &caracter, &entero };
    
	printf("Leyendo lineas...\n");

	while (leer_linea_csv(archivo, 3, funciones, punteros) == 3) {
		printf("Entero: %d, String: %s, Caracter: %c\n", entero, string,
		       caracter);
        for (size_t i = 0; i < archivo->columnas; i++){
            free(archivo->string[i]);
        }
		free(string);
	}

	printf("Fin de archivo\n");

	cerrar_archivo_csv(archivo);

	return 0;
}


// int main()
// {
//     const char *nombre_archivo = "/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv";
//     char separador = ';';

//     struct archivo_csv *archivo_csv = abrir_archivo_csv(nombre_archivo, separador);
//     if (!archivo_csv) {
//         printf("Error al abrir el archivo.\n");
//         return 1; // Error al abrir el archivo
//     }

//     char *nombre_pokemon = NULL;
//     char tipo;
//     int stat1, stat2, stat3;

//     // Definir las funciones para procesar cada columna y los punteros a los contextos
//     bool (*funciones[])(const char *, void *) = {crear_string_nuevo, castear_a_char, castear_a_int, castear_a_int, castear_a_int};
//     void *ctx[] = {&nombre_pokemon, &tipo, &stat1, &stat2, &stat3};

//     printf("Leyendo líneas...\n");

//     while (true) {
//         size_t columnas_leidas = leer_linea_csv(archivo_csv, 5, funciones, ctx);
//         if (columnas_leidas == 0) {
//             // Si no se leen columnas, el archivo está vacío o ocurrió un error
//             break;
//         }
//         if (columnas_leidas == 5) {
//             imprimir_resultados(nombre_pokemon, tipo, stat1, stat2, stat3);
//         } else {
//             printf("Error al leer las columnas. Se leyeron %zu columnas correctamente.\n", columnas_leidas);
//         }
//         for (size_t i = 0; i < archivo_csv->columnas; i++){
//             free(archivo_csv->string[i]);
//         }
//         free(nombre_pokemon); // Liberar la memoria del nombre del Pokémon
//         nombre_pokemon = NULL; // Resetear el puntero para evitar accesos no deseados
//     }

//     printf("Fin de archivo\n");

//     cerrar_archivo_csv(archivo_csv);

//     return 0;
// }