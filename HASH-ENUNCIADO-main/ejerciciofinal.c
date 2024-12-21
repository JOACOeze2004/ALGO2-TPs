#include <stdio.h>
#include <string.h>
#include "src/hash.h"

char * primer_string_repetido(char **vector, size_t tope, hash_t *hash){
    if (vector == NULL || tope == 0 || hash == NULL){
        return NULL;
    }
    for (size_t i = 0; i < tope; i++){
        void *elemento_repetido = hash_buscar(hash,vector[i]);
        if (elemento_repetido != NULL){
            return vector[i];
        }        
        if(!hash_insertar(hash,vector[i],(void*)i,NULL)){
            return NULL;
        }
    }
    return NULL;    
}

int main() {
    hash_t *hash = hash_crear(50);

    char *vector[] = {
        "manzana",
        "plátano",
        "cereza",
        "manzana",
        "uva"
    };
    size_t tope = sizeof(vector) / sizeof(vector[0]);

    char *resultado = primer_string_repetido(vector, tope, hash);
    
    if (resultado != NULL) {
        printf("El primer string repetido es: %s\n", resultado);
    } else {
        printf("No se encontró ningún string repetido.\n");
    }

    hash_destruir(hash);
    return 0;
}