#include "pa2m.h"
#include "src/csv.h"
#include "src/pokedex.h"
#include <string.h>

struct archivo_csv {
	FILE* nombre_archivo;
	size_t columnas;
	char** string;
	char separador;
};

void abrirUnArchivoInexistenteDebeRetornarNull()
{
	struct archivo_csv *archivo =
		abrir_archivo_csv("noexiste/noexiste/noexiste/no", ';');
	pa2m_afirmar(archivo == NULL, "El archivo no existe y se retorna NULL");
}

void abrirUnArchivoExistenteDebeRetornarUnPunteroValido() {
    struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');
    pa2m_afirmar(archivo != NULL, "El archivo existente se abre correctamente y se retorna un puntero válido");
	    if (archivo != NULL) {
        cerrar_archivo_csv(archivo);  
    }
}

void leerLineaDeArchivoDebeDividirCorrectamente() {
    struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');
    pa2m_afirmar(archivo != NULL, "El archivo existente se abre correctamente");

    bool (*funciones[])(const char *, void *) = {NULL}; // Puedes definir funciones de prueba aquí
    void *ctx[] = {NULL}; // Puedes definir contextos si es necesario

    size_t columnas = 1; // Ajusta según el archivo CSV
    size_t columnas_leidas = leer_linea_csv(archivo, columnas, funciones, ctx);

    // Verifica que se hayan leído la cantidad correcta de columnas
    pa2m_afirmar(columnas_leidas == columnas, "es columnas casteadas correctamente");

    cerrar_archivo_csv(archivo);
}

void liberarRecursosCorrectamente() {
    struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');
    pa2m_afirmar(archivo != NULL, "El archivo existente se abre correctamente y se libera correctamente");

    // Verifica la liberación de recursos
    cerrar_archivo_csv(archivo);

    // Aquí podrías añadir más validaciones si es necesario
}

void leerPrimeraLineaYVerificar() {
    struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');
    pa2m_afirmar(archivo != NULL, "El archivo se abre correctamente");

    bool (*funciones[])(const char *, void *) = { NULL };
    void *ctx[] = { NULL };

    size_t columnas = 5; // Ajusta según el número de columnas de tu archivo CSV

    // Lee solo la primera línea del archivo CSV
    size_t columnas_leidas = leer_linea_csv(archivo, columnas, funciones, ctx);

    // Verifica que se han leído la cantidad correcta de columnas
    pa2m_afirmar(columnas_leidas == columnas, "Son 5 columnas casteadas correctamente");

    // Verifica que cada columna tenga un valor válido (ejemplo: Pikachu;E;20;15;17)
    pa2m_afirmar(strcmp(archivo->string[0], "Pikachu") == 0, "La primera columna es 'Pikachu'");
    pa2m_afirmar(strcmp(archivo->string[1], "E") == 0, "La segunda columna es 'E'");
    pa2m_afirmar(strcmp(archivo->string[2], "20") == 0, "La tercera columna es '20'");
    pa2m_afirmar(strcmp(archivo->string[3], "15") == 0, "La cuarta columna es '15'");
    pa2m_afirmar(strcmp(archivo->string[4], "17") == 0, "La quinta columna es '17'");
    
    // Imprime las columnas para verificar visualmente el contenido
    for (size_t i = 0; i < columnas_leidas; i++) {
        printf("Columna %zu: %s\n", i, archivo->string[i]);
    }

    cerrar_archivo_csv(archivo);
}

void leerYVerificarTodasLasLineas() {
    struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');
    pa2m_afirmar(archivo != NULL, "El archivo se abre correctamente");

    size_t columnas = 5; // Ajusta según el número de columnas de tu archivo CSV
    bool (*funciones[])(const char *, void *) = { NULL };
    void *ctx[] = { NULL };

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

    for (size_t fila = 0; fila < num_filas; fila++) {
        size_t columnas_leidas = leer_linea_csv(archivo, columnas, funciones, ctx);
        pa2m_afirmar(columnas_leidas == columnas, "Se han leído la cantidad correcta de columnas");

        for (size_t col = 0; col < columnas_leidas; col++) {
            pa2m_afirmar(strcmp(archivo->string[col], valores_esperados[fila][col]) == 0,
                         "La columna es correcta");
            printf("Fila %zu, Columna %zu: %s (Esperado: %s)\n", fila + 1, col + 1, archivo->string[col], valores_esperados[fila][col]);
            free(archivo->string[col]);
        }
    }
    cerrar_archivo_csv(archivo);
}

void dividirUnaLineaDeCSVResultaEnLasPartesCorrectas()
{
    struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');
    
    if (!archivo) {
        printf("Error al abrir el archivo\n");
        return;
    }

    // Suponemos que el archivo tiene 5 columnas
    size_t columnas = 5;

    // Array de funciones para castear cada columna
    bool (*funciones[])(const char *, void *) = {NULL};

    // Array de punteros para almacenar los valores convertidos
    char columna1[50];
    char columna2[50];
    int columna3, columna4, columna5;
    
    void *ctx[] = {columna1, columna2, &columna3, &columna4, &columna5};

    size_t cantidad_columnas_leidas = leer_linea_csv(archivo, columnas, funciones, ctx);

    pa2m_afirmar(cantidad_columnas_leidas == columnas, "La cantidad de columnas leídas es correcta");
    pa2m_afirmar(strcmp(columna1, "Pikachu") == 0, "La primera columna es Pikachu");
    pa2m_afirmar(strcmp(columna2, "E") == 0, "La segunda columna es E");
    pa2m_afirmar(columna3 == 20, "La tercera columna es 20");
    pa2m_afirmar(columna4 == 15, "La cuarta columna es 15");
    pa2m_afirmar(columna5 == 17, "La quinta columna es 17");

    cerrar_archivo_csv(archivo);
}

void leerYVerificarArchivoCompleto() {
    struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');
    pa2m_afirmar(archivo != NULL, "El archivo se abre correctamente (de leer y verificar todo)");

    // Aquí puedes definir funciones específicas para castear cada columna si es necesario
    bool (*funciones[])(const char *, void *) = { NULL };
    void *ctx[] = { NULL };

    size_t columnas = 5;  // Ajusta según el número de columnas de tu archivo CSV
    size_t columnas_leidas;

    // Leer línea por línea del archivo CSV
    while ((columnas_leidas = leer_linea_csv(archivo, columnas, funciones, ctx)) > 0 ) {
        // Verificar que se han leído la cantidad correcta de columnas
        pa2m_afirmar(columnas_leidas == columnas, "Son 5 columnas casteadas correctamente");

        // Verifica cada columna si es necesario, aquí un ejemplo con la primera línea
        if (strcmp(archivo->string[0], "Pikachu") == 0) {
            pa2m_afirmar(strcmp(archivo->string[1], "E") == 0, "La segunda columna es 'E'");
            pa2m_afirmar(strcmp(archivo->string[2], "20") == 0, "La tercera columna es '20'");
            pa2m_afirmar(strcmp(archivo->string[3], "15") == 0, "La cuarta columna es '15'");
            pa2m_afirmar(strcmp(archivo->string[4], "17") == 0, "La quinta columna es '17'");
        }

        // Imprime las columnas para verificar visualmente el contenido
        for (size_t i = 0; i < columnas_leidas; i++) {
            printf("Columna %zu: %s\n", i, archivo->string[i]);
        }
        printf("\n");
    }

    cerrar_archivo_csv(archivo);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de archivos CSV");
	abrirUnArchivoInexistenteDebeRetornarNull();
    //otras pruebas?
	//abrirUnArchivoExistenteDebeRetornarUnPunteroValido();
	
    //leerLineaDeArchivoDebeDividirCorrectamente();
    //leerPrimeraLineaYVerificar();
    leerYVerificarTodasLasLineas();
    //dividirUnaLineaDeCSVResultaEnLasPartesCorrectas();
    //leerYVerificarArchivoCompleto();
    liberarRecursosCorrectamente();

	return pa2m_mostrar_reporte();
}
