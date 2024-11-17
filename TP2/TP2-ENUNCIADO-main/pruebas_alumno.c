#include "pa2m.h"
#include "src/menu.h"
#include "src/hash.h"


void funcion_random() {
    printf("Hola Mundo, probamos funcion random\n"); 
}

void funcion_random2() {
    printf("Adios Mundo, probamos otra funcion random\n"); 
}


void CrearMenuDevuelveMenu(){
	menu_t *menu = menu_crear();
	pa2m_afirmar(menu != NULL,"Se crear exitosamente un menu");
	menu_destruir(menu);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de agregar y ejecutar opcion

void AgregarOpcionDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'a',funcion_random), "agregamos una opcion al menu");
	menu_destruir(menu);
}

void AgregarVariasOpcionesAlMenuDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'J',funcion_random), "agregamos la J como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'j',funcion_random), "agregamos la j como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'S',funcion_random), "agregamos la S como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'s',funcion_random), "agregamos la s como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'Q',funcion_random), "agregamos la Q como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'q',funcion_random), "agregamos la q como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 8, "agregamos en total 8 opciones al menu");

	menu_destruir(menu);
}

void AgregarEnMenuNULLDevuelveFalse(){
	menu_t *menu = NULL;

	pa2m_afirmar(!menu_agregar_opciones(menu,'P',funcion_random), "No agregamos la P como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'p',funcion_random), "No agregamos la p como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'J',funcion_random), "No agregamos la J como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 0, "agregamos en total 0 opciones al menu NULL");

	
	menu_destruir(menu);
}

void AgregarEnMenuConFuncionNULLDevuelveFalse(){
	menu_t *menu = NULL;

	pa2m_afirmar(!menu_agregar_opciones(menu,'P',NULL), "No agregamos la P como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'p',NULL), "No agregamos la p como opcion al menu");
	pa2m_afirmar(!menu_agregar_opciones(menu,'J',NULL), "No agregamos la J como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 0, "agregamos en total 0 opciones (con funcion NULL) al menu");

	
	menu_destruir(menu);
}

void EjecutarAccionLlamaCorrectameneteAfuncion(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 2, "agregamos en total 2 opciones al menu");

	pa2m_afirmar(menu_ejecutar_entrada(menu,'P'), "Se pudo ejecutra la funcion guardada.");

	menu_destruir(menu);
}

void AgregarDosVecesMismaOpcionDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");

	pa2m_afirmar(menu_ejecutar_entrada(menu,'P'), "Se pudo ejecutra la funcion guardada.");

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random2), "agregamos la P pero con otra funcion");

	pa2m_afirmar(menu_ejecutar_entrada(menu,'P'), "Se pudo ejecutra la funcion guardada.");



	menu_destruir(menu);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//pruebas de eliminar

void EliminarOpcionDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu,'P'), "pudimos eliminar la opcion P");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 1, "al quitar 1 opcion, solo queda 1 opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu,'p'), "pudimos eliminar la opcion P");
	pa2m_afirmar(menu_cantidad_opciones(menu) == 0, "al quitar 1 opcion, no queda opciones en el  menu");

	menu_destruir(menu);
}

void EliminarOpcionInexistenteDevuelveFalse(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(!menu_eliminar_opcion(menu,'K'), "No podemos eliminar una opcion inexistente");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 2, "La cantidad se mantiene si inentamos eliminar una  opcion inexistente");

	menu_destruir(menu);
}

void EliminarOpcionYReinsertarlaDevuelveTrue(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_eliminar_opcion(menu,'P'), "pudimos eliminar la opcion P");

	pa2m_afirmar(menu_cantidad_opciones(menu) == 1, "al quitar 1 opcion, solo queda 1 opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "Volvemos a agregar la p como opcion al menu");
	pa2m_afirmar(menu_cantidad_opciones(menu) == 2, "La cantidad de opciones aumento correctamente");
	pa2m_afirmar(menu_ejecutar_entrada(menu,'P'), "Se pudo ejecutra la funcion guardada en la opcion P, luego de haberla eliminado y vuelto a insertar");

	menu_destruir(menu);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Pruebas de obtener funcion
void BuscarFuncionDeOpcionExistenteDevuelveNoNULL(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_obtener_funcion_opcion(menu,'P') != NULL, "Se pudo encontrar la funcion asociada a la opcion P (proque es distinto de NULL)");

	menu_destruir(menu);
}

void BuscarFuncionDeOpcionInexistenteDevuelveNULL(){
	menu_t *menu = menu_crear();

	pa2m_afirmar(menu_agregar_opciones(menu,'P',funcion_random), "agregamos la P como opcion al menu");
	pa2m_afirmar(menu_agregar_opciones(menu,'p',funcion_random), "agregamos la p como opcion al menu");

	pa2m_afirmar(menu_obtener_funcion_opcion(menu,'A') == NULL, "No se pudo encontrar la funcion asociada a la opcion A que no existe ");

	menu_destruir(menu);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de TDA Menu");
	CrearMenuDevuelveMenu();
	pa2m_nuevo_grupo("Pruebas de Agregar y ejecutar opcion (TDA Menu)");
	AgregarOpcionDevuelveTrue();
	AgregarVariasOpcionesAlMenuDevuelveTrue();
	AgregarEnMenuNULLDevuelveFalse();
	AgregarEnMenuConFuncionNULLDevuelveFalse();
	EjecutarAccionLlamaCorrectameneteAfuncion();
	AgregarDosVecesMismaOpcionDevuelveTrue();
	
	
	pa2m_nuevo_grupo("Pruebas de eliminar (TDA Menu)");
	EliminarOpcionDevuelveTrue();
	EliminarOpcionInexistenteDevuelveFalse();
	EliminarOpcionYReinsertarlaDevuelveTrue();

	BuscarFuncionDeOpcionExistenteDevuelveNoNULL();
	BuscarFuncionDeOpcionInexistenteDevuelveNULL();


	
	return pa2m_mostrar_reporte();
}
