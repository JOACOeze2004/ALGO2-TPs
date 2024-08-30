#include "pa2m.h"
#include "src/csv.h"
#include "src/pokedex.h"

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
    struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ',');
    pa2m_afirmar(archivo != NULL, "El archivo existente se abre correctamente");

    bool (*funciones[])(const char *, void *) = {NULL}; // Puedes definir funciones de prueba aquí
    void *ctx[] = {NULL}; // Puedes definir contextos si es necesario

    size_t columnas = 3; // Ajusta según el archivo CSV
    size_t columnas_leidas = leer_linea_csv(archivo, columnas, funciones, ctx);

    // Verifica que se hayan leído la cantidad correcta de columnas
    pa2m_afirmar(columnas_leidas == columnas, "Se leen correctamente las columnas");

    cerrar_archivo_csv(archivo);
}

void liberarRecursosCorrectamente() {
    struct archivo_csv *archivo = abrir_archivo_csv("/home/joacoeze/Documents/Programacion/ALGO2/TP1/TP1-ENUNCIADO-main/ejemplos/pokedex.csv", ';');
    pa2m_afirmar(archivo != NULL, "El archivo existente se abre correctamente");

    // Verifica la liberación de recursos
    cerrar_archivo_csv(archivo);

    // Aquí podrías añadir más validaciones si es necesario
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de archivos CSV");
	abrirUnArchivoInexistenteDebeRetornarNull();
	abrirUnArchivoExistenteDebeRetornarUnPunteroValido();
	//otras pruebas?
	    abrirUnArchivoExistenteDebeRetornarUnPunteroValido();
    leerLineaDeArchivoDebeDividirCorrectamente();
    liberarRecursosCorrectamente();

	return pa2m_mostrar_reporte();
}
