#include "split.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

//pre:  asumimos que recibimos un str valido y que se manejo correctamente en caso de que el puntero haya sido null. Y que el separador es valido.
//post: devolvemos un contador de separadores, que en caso de que el caracter sea igual al delimitador, aumenta.
size_t contar_delimitadores(const char *str, char separador)
{
	size_t letra_actual = 0;
	size_t contador_separadores = 0;
	while (str[letra_actual] != '\0') {
		if (str[letra_actual] == separador) {
			contador_separadores++;
		}
		letra_actual++;
	}
	return contador_separadores;
}

//pre:  asumimos que todos los paramatros son validos.
//post: copiamos la subcadena al campo string de Partes
void escribir_subcadena(const char *string, size_t long_subcadena,
			size_t letra_actual, size_t i,
			struct Partes *texto_editado)
{
	for (size_t j = 0; j < long_subcadena; j++) {
		texto_editado->string[i][j] =
			string[letra_actual - long_subcadena + j];
	}
	texto_editado->string[i][long_subcadena] = '\0';
}

//pre:  Asumimos que la cantidad asignada es valida y que el struc Partes tambien.
//post: Libera toda la memoria pedida, usada principalmente en caso de que falle alguna asignacion de memoria al pedirle memoria para cada subcadena.
void liberar_memoria_en_substr(struct Partes *texto_editado,
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
		       struct Partes *texto_editado)
{
	size_t i = 0;
	size_t letra_actual = 0;
	int error = 0;
	while (i < texto_editado->cantidad && !error) {
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

//post: hacemos un malloc para reservar espacio para el struct Partes, manejando el error, y seteamos el campo string como null y la cantidad como 0.
struct Partes *inicializar_partes()
{
	struct Partes *texto_editado = malloc(sizeof(struct Partes));
	if (texto_editado == NULL) {
		return NULL;
	}
	texto_editado->cantidad = 0;
	texto_editado->string = NULL;
	return texto_editado;
}

struct Partes *dividir_string(const char *string, char separador)
{
	struct Partes *texto_editado = inicializar_partes();
	if (string == NULL) {
		return texto_editado;
	}
	texto_editado->cantidad = contar_delimitadores(string, separador) + 1;
	char **str_temp = realloc(texto_editado->string,
				  sizeof(char *) * texto_editado->cantidad);
	if (str_temp == NULL) {
		free(texto_editado);
		return NULL;
	}
	texto_editado->string = str_temp;
	escribir_palabras(string, separador, texto_editado);
	return texto_editado;
}

void liberar_partes(struct Partes *partes)
{
	if (partes->string != NULL) {
		for (size_t i = 0; i < partes->cantidad; i++) {
			free(partes->string[i]);
		}
		free(partes->string);
	}
	free(partes);	
}


// int main() {
//     const char* cadena = "Pikachu;E;20;15;17;Charmander;F;10;5;8;Larvitar;R;30;1;40";
//     char separador = ';';

//     struct Partes* partes = dividir_string(cadena, separador);
//     if (partes != NULL) {
//         for (size_t i = 0; i < partes->cantidad; i++) {
//             printf("Parte %zu: %s\n", i, partes->string[i]);
//         }

//         liberar_partes(partes);
//     }

// //     return 0;
// // }

// #define MAX_LINE_LENGTH 1024

// int main() {
//     FILE *file = fopen("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", "r");
//     if (file == NULL) {
//         perror("No se pudo abrir el archivo");
//         return EXIT_FAILURE;
//     }

//     char line[MAX_LINE_LENGTH];
//     while (fgets(line, sizeof(line), file)) {

//         struct Partes* partes = dividir_string(line, ';');
//         if (partes != NULL) {
//             for (size_t i = 0; i < partes->cantidad; i++) {
//                 printf("Parte %zu: %s\n", i, partes->string[i]);
//             }

//             liberar_partes(partes);
//         }
//     }

//     fclose(file);
//     return EXIT_SUCCESS;
// }


void leerYVerificarTodasLasLineas() {
    FILE *file = fopen("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", "r");
    if (file == NULL) {
        perror("No se pudo abrir el archivo");
        exit(EXIT_FAILURE);
    }

    const char *valores_esperados[][5] = {
        {"Pikachu", "E", "20", "15", "17"},
        {"Charmander", "F", "10", "5", "8"},
        {"Larvitar", "R", "30", "1", "40"},
        {"Cacnea", "P", "11", "12", "14"},
        {"Joltik", "E", "8", "10", "5"},
        {"Togepi", "N", "8", "8", "2"},
        {"Floatzel", "A", "24", "20", "5"},
        {"Dedenne", "E", "15", "5", "33"},
        {"Magcargo", "F", "22", "20", "22"}
    };

    size_t num_filas = sizeof(valores_esperados) / sizeof(valores_esperados[0]);
    size_t columnas = 5; // Ajusta según el número de columnas de tu archivo CSV

    char line[1024];
    size_t fila_actual = 0;

    while (fgets(line, sizeof(line), file) && fila_actual < num_filas) {
        // Elimina el salto de línea al final de cada línea
        //line[strcspn(line, "\n")] = '\0';

        struct Partes *partes = dividir_string(line, ';');
        if (partes != NULL) {
            size_t columnas_leidas = partes->cantidad;
            printf("Fila %zu:\n", fila_actual + 1);

            if (columnas_leidas == columnas) {
                for (size_t col = 0; col < columnas_leidas; col++) {
                    if (strcmp(partes->string[col], valores_esperados[fila_actual][col]) == 0) {
                        printf("Columna %zu: %s (Correcto)\n", col + 1, partes->string[col]);
                    } else {
                        printf("Columna %zu: %s (Esperado: %s)\n", col + 1, partes->string[col], valores_esperados[fila_actual][col]);
                    }
                }
            } else {
                printf("Error: Se esperaban %zu columnas, pero se leyeron %zu.\n", columnas, columnas_leidas);
            }

            liberar_partes(partes);
            fila_actual++;
        }
    }

    fclose(file);
}

int main() {
    leerYVerificarTodasLasLineas();
    return EXIT_SUCCESS;
}