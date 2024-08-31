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
		//free(texto_editado);
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
		// if (string[letra_actual] == '\0'){
		// 	liberar_memoria_en_substr(texto_editado, i);
		// }
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

bool castear_a_int(const char* string, void* ctx){
	char *caracter = (char *) ctx;
	if (string[0] != '\0'){
		*caracter = string[0];
		return true;
	}
	
	return false;
}

bool castear_a_char(const char* string, void* ctx){
	int *entero = (int *) ctx;
	*entero = atoi(string);
	return true;
}

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas, bool (*funciones[])(const char *, void *), void *ctx[]){
	char texto[50];
	if(fgets(texto,sizeof(texto),archivo->nombre_archivo)== NULL){
		return 0;
	}
	archivo->columnas = columnas;
	char **str_temp = realloc(archivo->string, sizeof(char *) * archivo->columnas);
	if (str_temp == NULL) {
		free(archivo);
		return 0;
	}
	archivo->string = str_temp;
	escribir_palabras(texto, archivo->separador, archivo);
	return 5;
}

void cerrar_archivo_csv(struct archivo_csv *archivo){
	if (archivo != NULL){
		fclose(archivo->nombre_archivo);
		for (size_t i = 0; i < archivo->columnas; i++) {
			free(archivo->string[i]);
		}
		free(archivo->string);
	}
	free(archivo);
}


// int main() {
//     //Leer archivo CSV
//     struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');
//     if (!archivo) {
//         printf("Error al abrir el archivo.\n");
//         return 1;
//     }

//     printf("Leyendo lineas del archivo...\n");
//     char texto[1000];
//     while (fgets(texto, sizeof(texto), archivo->nombre_archivo) != NULL) {
//         printf("\nLinea leída: %s\n", texto);
        
//         //Dividir la línea leída en partes
//         struct archivo_csv partes;
//         partes.string = NULL;
//         partes.separador = archivo->separador;
// 		size_t columnas = 5;
//         struct archivo_csv *resultado = escribir_palabras(texto, archivo->separador, &partes);
//         if (resultado != NULL) {
//             for (size_t i = 0; i < columnas && resultado->string[i] != NULL; i++) {
//                 printf("Parte %zu: %s\n", i, resultado->string[i]);
//             }

//             liberar_memoria_en_substr(&partes, columnas);
//         }
//     }

//     printf("Fin de archivo\n");

//     cerrar_archivo_csv(archivo);

//     return 0;
// }