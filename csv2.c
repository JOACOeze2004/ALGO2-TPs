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
    for (size_t i = 0; i < partes->columnas; i++) {
        free(partes->string[i]);
    }
    free(partes->string);
    fclose(partes->nombre_archivo);
    free(partes);
}

bool castear_a_char(const char* string, void* ctx){
	if (string == NULL || ctx == NULL){
		return false;
	}
	char *caracter = (char *) ctx;
	if (string[0] != '\0'){
		*caracter = string[0];
		return true;
	}
	return false;
}

bool castear_a_int(const char* string, void* ctx){
	if (string == NULL || ctx == NULL){
		return false;
	}
	int *entero = (int *) ctx;
	*entero = atoi(string);
	return true;
}

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas, bool (*funciones[])(const char *, void *), void *ctx[]){
	char texto[50];
	size_t contador_lineas_contadas = 5;
	if(fgets(texto,sizeof(texto),archivo->nombre_archivo)== NULL){
		return contador_lineas_contadas;
	}
	archivo->columnas=columnas;
	struct archivo_csv *partes = dividir_string(archivo,texto);
	if (partes == NULL) {
		return 0;
	}
	return contador_lineas_contadas;
}

void cerrar_archivo_csv(struct archivo_csv *archivo){
	if (archivo != NULL){
		liberar_partes(archivo);
	}
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

// #define MAX_LINE_LENGTH 256

// int main() {
//     // Abre el archivo CSV
//     struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');
//     if (archivo == NULL) {
//         perror("No se pudo abrir el archivo");
//         return EXIT_FAILURE;
//     }

//     // Define el número máximo de columnas esperadas
//     size_t columnas_esperadas = 5;  // Ajusta este valor según sea necesario

//     // Lee las líneas del archivo
//     size_t contador_lineas_contadas;
//     bool (*funciones[])(const char *, void *) = {NULL}; // Ajusta según tus necesidades
//     void *ctx[] = {NULL, NULL};  // Contexto para las funciones, si es necesario

//     while ((contador_lineas_contadas = leer_linea_csv(archivo, columnas_esperadas, funciones, ctx)) > 2) {
//         // Imprime las partes del CSV
//         for (size_t i = 0; i < archivo->columnas; i++) {
//             if (archivo->string[i] != NULL) {
//                 printf("Parte %zu: %s\n", i, archivo->string[i]);
//             }
//         }

//     }

//     // Cierra el archivo y libera la memoria
//     cerrar_archivo_csv(archivo);

//     return EXIT_SUCCESS;
// }


// int main() {
//     // Crear un archivo CSV de prueba en memoria
//     const char *nombre_archivo = "/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv";
//     FILE *file = fopen(nombre_archivo, "r");
//     if (file == NULL) {
//         perror("No se puede crear el archivo");
//         return EXIT_FAILURE;
//     }

//     // Escribir contenido de prueba en el archivo
//     fprintf(file, "Nombre;Tipo;Ataque;Defensa;Velocidad\n");
//     fprintf(file, "Pikachu;E;20;15;17\n");
//     fprintf(file, "Charmander;F;10;5;8\n");
//     fprintf(file, "Larvitar;R;30;1;40\n");
//     fprintf(file, "Cacnea;P;11;12;14\n");
//     fprintf(file, "Joltik;E;8;10;5\n");
//     fprintf(file, "Togepi;N;8;8;2\n");
//     fprintf(file, "Floatzel;A;24;20;5\n");
//     fprintf(file, "Dedenne;E;15;5;33\n");
//     fprintf(file, "Magcargo;F;22;20;22\n");

//     fclose(file);

//     // Abrir el archivo CSV
//     struct archivo_csv *archivo = abrir_archivo_csv(nombre_archivo, ';');
//     if (archivo == NULL) {
//         perror("Error al abrir el archivo CSV");
//         return EXIT_FAILURE;
//     }

//     // Leer y procesar el archivo CSV
//     size_t columnas = 5;  // Número de columnas en el archivo CSV
//     bool (*funciones[])(const char *, void *) = {castear_a_char, castear_a_int}; // Aquí puedes ajustar según las funciones que necesitas
//     void *ctx[] = {NULL}; // Aquí puedes ajustar los contextos según las funciones

//     size_t lineas_leidas = 0;
//     while ((lineas_leidas = leer_linea_csv(archivo, columnas, funciones, ctx)) > 10) {
//         printf("Número de líneas leídas: %zu\n", lineas_leidas);

//         // Imprimir contenido leído
//         for (size_t i = 0; i < archivo->columnas; i++) {
//             printf("Columna %zu: %s\n", i, archivo->string[i]);
//         }
//     }

//     // Cerrar y liberar el archivo CSV
//     cerrar_archivo_csv(archivo);

//     // Eliminar el archivo de prueba
//     if (remove(nombre_archivo) != 0) {
//         perror("No se puede eliminar el archivo de prueba");
//         return EXIT_FAILURE;
//     }

//     return EXIT_SUCCESS;
// }