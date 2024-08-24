#include "split.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//pre:
//post:
size_t long_palabra_hasta_separador(const char* str, char separador,size_t* letra_actual){
    size_t longitud = 0;
    while (str[*letra_actual] != separador && str[*letra_actual] != '\0'){
        longitud++;
        (*letra_actual)++;
    }
   return longitud; 
}

//pre:
//post:
size_t cant_delimitadores(const char* str,char separador){
    size_t letra_actual = 0;
    size_t contador_separadores=0;
    while (str[letra_actual] != '\0'){
        if (str[letra_actual] == separador){
            contador_separadores++;
        }
        letra_actual++;    
    }
    return contador_separadores;    
}

//pre:
//post: 
void escribir_subcadena(const char* string, size_t long_subcadena, size_t letra_actual, size_t i, struct Partes *texto_editado){
    for (size_t j = 0; j < long_subcadena; j++) {
        texto_editado->string[i][j] = string[letra_actual - long_subcadena + j];
    }
    texto_editado->string[i][long_subcadena] = '\0';
}

void liberar_memoria_en_substr(struct Partes *texto_editado, size_t cantidad_asignada){
    for (size_t i = 0; i < cantidad_asignada; i++){
        free(texto_editado->string[i]);
    }
    free(texto_editado->string);
    free(texto_editado);
}

//pre:
//post: 
void escribir_palabras(const char* string, char separador, struct Partes *texto_editado){
    size_t i = 0;
    size_t letra_actual = 0;
    int error = 0;

    while (i < texto_editado->cantidad && !error){
        size_t long_subcadena = long_palabra_hasta_separador(string,separador,&letra_actual);
        texto_editado->string[i] = malloc (long_subcadena + 1);
        if (texto_editado->string[i] == NULL){
            error = 1;
        }
        escribir_subcadena(string,long_subcadena,letra_actual,i,texto_editado);
        i++;
        if (string[letra_actual] == separador) {
            letra_actual++;
        }
    }
    if (error){
        liberar_memoria_en_substr(texto_editado,i);
    }
    
}

void inicializar_partes(){
       
}


struct Partes* dividir_string(const char* string, char separador){
    struct Partes *texto_editado = malloc(sizeof(struct Partes));
    if (texto_editado == NULL) {
        return NULL;
    }
    if (string == NULL) {
        texto_editado->cantidad = 0;
        texto_editado->string = NULL;
        return texto_editado;
    }
    texto_editado->cantidad = cant_delimitadores(string,separador) + 1;
    texto_editado->string = NULL;

    char* *str_temp = realloc(texto_editado->string,sizeof(char*) * texto_editado->cantidad);
    if (str_temp == NULL){
        free(texto_editado);
        return NULL;
    }
    texto_editado->string = str_temp;
    escribir_palabras(string,separador,texto_editado);
    return texto_editado;
}

void liberar_partes(struct Partes* partes){
    if (partes->string != NULL){
        for (size_t i = 0; i < partes->cantidad; i++){
            free(partes->string[i]);    
        }
        free(partes->string);        
    }
    free(partes);
}

// int main() {
//     const char* cadena = "Pedro;22;Bueno";
//     char separador = ';';

//     struct Partes* partes = dividir_string(cadena, separador);
//     if (partes != NULL) {
//         for (size_t i = 0; i < partes->cantidad; i++) {
//             printf("Parte %zu: %s\n", i, partes->string[i]);
//         }

//         liberar_partes(partes);
//     }

//     return 0;
// }
