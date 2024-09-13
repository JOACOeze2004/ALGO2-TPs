#include "csv.h"
#include <stdio.h>
#include <string.h>

struct archivo_csv {
	FILE *nombre_archivo;
	size_t columnas;
	char **string;
	char separador;
};

//pre:  Asumimos q recibimos un valido, que el puntero a letra actual se pasa correctamente y que el str es valida tambien. Ademas de que el str termina en '\0' (ya sea vacio o no).
//post: devuelve la longitud que tenga una palabra hatsa que llege al delimitador o al final de la misma. Al pasarle por referencai letra_actual, se "mantiene" el orden en caso de encontrar un delimitador por ejemplo.
size_t calcular_longitud_subpalabra(const char *str, char separador,
				    size_t *letra_actual)
{
	size_t longitud = 0;
	while (str[*letra_actual] != separador && str[*letra_actual] != '\0') {
		longitud++;
		(*letra_actual)++;
	}
	return longitud;
}

//pre:  asumimos que todos los paramatros son validos.
//post: copiamos la subcadena al campo string de Partes
void escribir_subcadena(const char *string, size_t long_subcadena,
			size_t letra_actual, size_t i,
			struct archivo_csv *archivo)
{
	for (size_t j = 0; j < long_subcadena; j++) {
		archivo->string[i][j] =
			string[letra_actual - long_subcadena + j];
	}
	archivo->string[i][long_subcadena] = '\0';
}

//pre:  Asumimos que la cantidad asignada es valida y que el struc Partes tambien.
//post: Libera toda la memoria pedida, usada principalmente en caso de que falle alguna asignacion de memoria al pedirle memoria para cada subcadena.
void liberar_memoria_en_substr(struct archivo_csv *archivo,
			       size_t cantidad_asignada)
{
	for (size_t i = 0; i < cantidad_asignada; i++) {
		free(archivo->string[i]);
	}
	free(archivo->string);
	free(archivo);
}

//pre:  Asumimos que los parametros pasados son validos.
//post: escribimos en el campo string, la nueva subcadena dividida por el separador. En caso de fallo al asiganr memoria para cada substring, corta el while y llama a la funcion de liberar memoria.
void escribir_palabras(const char *string, char separador,
		       struct archivo_csv *archivo)
{
	size_t i = 0;
	size_t letra_actual = 0;
	int error = 0;
	while (i < archivo->columnas && !error) {
		size_t long_subcadena = calcular_longitud_subpalabra(
			string, separador, &letra_actual);
		archivo->string[i] = malloc(long_subcadena + 1);
		if (archivo->string[i] == NULL) {
			error = 1;
		}
		escribir_subcadena(string, long_subcadena, letra_actual, i,
				   archivo);
		i++;
		if (string[letra_actual] == separador) {
			letra_actual++;
		}
	}
	if (error) {
		liberar_memoria_en_substr(archivo, i);
	}
}

struct archivo_csv *dividir_string(struct archivo_csv *archivo,
				   const char *string)
{
	if (archivo->columnas == 0 || string == NULL) {
		return NULL;
	}

	char **str_temp =
		realloc(archivo->string, sizeof(char *) * archivo->columnas);
	if (str_temp == NULL) {
		free(archivo);
		return NULL;
	}
	archivo->string = str_temp;
	escribir_palabras(string, archivo->separador, archivo);
	return archivo;
}

void liberar_todo(struct archivo_csv *archivo)
{
	free(archivo->string);
	fclose(archivo->nombre_archivo);
	free(archivo);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pre:	Se asume que el puntero al struct es valido.
//post:	Inicializa los distintos campos del struct archvios.
void inicializar_campos(struct archivo_csv *archivo, char separador)
{
	archivo->columnas = 0;
	archivo->string = NULL;
	archivo->separador = separador;
}

//pre:	Se supone que el  puntero al struct archivos y el puntero al nombre del archivo son validos o ya fueron validados de antemano.
//post:	Devuelve true si el archivo existe y se pudo abriri, fase en caso de que el nombre del archivo es null.
bool es_archivo_valido(struct archivo_csv *archivo, const char *nombre_archivo)
{
	archivo->nombre_archivo = fopen(nombre_archivo, "r");
	if (archivo->nombre_archivo == NULL) {
		return false;
	}
	return true;
}

struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo,
				      char separador)
{
	struct archivo_csv *archivo = malloc(sizeof(struct archivo_csv));
	if (archivo == NULL) {
		return NULL;
	}
	if (!es_archivo_valido(archivo, nombre_archivo)) {
		free(archivo);
		return NULL;
	}
	inicializar_campos(archivo, separador);
	return archivo;
}

//pre:	Asumimos que el puntero al struct archivo_csv no es null y que se fue reservando memoria para cada elemento del string a castear.
//post:	Libera la memoria reservada para los elementos del vector  de strings hechos por la funcion de dividir_str.
void liberar_substr_al_procesar_linea(struct archivo_csv *archivo)
{
	for (size_t i = 0; i < archivo->columnas; i++) {
		free(archivo->string[i]);
	}
}

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
	if (archivo == NULL || funciones == NULL || ctx == NULL) {
		return 0;
	}
	char texto[1000];
	size_t contador_lineas_casteadas = 0;
	size_t i = 0;
	archivo->columnas = columnas;
	if (fgets(texto, sizeof(texto), archivo->nombre_archivo) == NULL) {
		return contador_lineas_casteadas;
	}
	if (dividir_string(archivo, texto) == NULL) {
		return 0;
	}
	while (i < archivo->columnas) {
		if (funciones[i] != NULL) {
			if (funciones[i](archivo->string[i],
					 ctx ? ctx[i] : NULL)) {
				contador_lineas_casteadas++;
			}
		}
		i++;
	}
	liberar_substr_al_procesar_linea(archivo);
	return contador_lineas_casteadas;
}

void cerrar_archivo_csv(struct archivo_csv *archivo)
{
	if (archivo != NULL) {
		liberar_todo(archivo);
	}
}