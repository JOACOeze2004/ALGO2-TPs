struct Partes* dividir_string(const char* string, char separador) {
    // struct Partes *texto_editado = malloc(sizeof(struct Partes));
    // if (texto_editado == NULL) {
    //     return NULL;
    // }

    // texto_editado->cantidad = cant_delimitadores(string, separador) + 1;

    // texto_editado->string = malloc(texto_editado->cantidad * sizeof(char*));
    // if (texto_editado->string == NULL) {
    //     free(texto_editado);
    //     return NULL;
    // }

    size_t letra_actual = 0;
    size_t i = 0;
    while (string[letra_actual] != '\0' && i < texto_editado->cantidad) {
        size_t long_subcadena = long_palabra_hasta_separador(string, separador, &letra_actual);

        // Asignar memoria para la subcadena + '\0'
        texto_editado->string[i] = malloc((long_subcadena + 1) * sizeof(char));
        if (texto_editado->string[i] == NULL) {
            // Manejo de error: liberar memoria ya asignada
            for (size_t j = 0; j < i; j++) {
                free(texto_editado->string[j]);
            }
            free(texto_editado->string);
            free(texto_editado);
            return NULL;
        }

        // Copiar la subcadena
        strncpy(texto_editado->string[i], string + letra_actual - long_subcadena, long_subcadena);
        texto_editado->string[i][long_subcadena] = '\0';
        i++;

        if (string[letra_actual] == separador) {
            letra_actual++;
        }
    }

    return texto_editado;
}