#include "csv.h"
#include <stdio.h>
#include <string.h>

struct archivo_csv {
	FILE* nombre_archivo;
	size_t numero_columnas;
	char separador;
};




struct archivo_csv *abrir_archivo_csv(const char *nombre_archivo, char separador){
	if (nombre_archivo == NULL){
		return NULL;
	}
	FILE *archivo = fopen(nombre_archivo,"r");
	if (archivo == NULL){
		return NULL;
	}
	struct archivo_csv *archivo_csv = malloc(sizeof(struct archivo_csv));
	if (archivo_csv == NULL){
		fclose(archivo);
		return NULL;
	}
	archivo_csv->nombre_archivo = archivo;
	archivo_csv->separador = separador;
	archivo_csv->numero_columnas = 0;	

	return archivo_csv;
}

size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas, bool (*funciones[])(const char *, void *), void *ctx[]){
		char texto[100];
		if(fgets(texto,sizeof(texto),archivo->nombre_archivo) == NULL){
			return 0;
		}
	
	return columnas;
}

void cerrar_archivo_csv(struct archivo_csv *archivo){
	if (archivo->nombre_archivo != NULL){
		fclose(archivo->nombre_archivo);
	}
	free(archivo);
}


