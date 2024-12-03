#include "racha.h"
#include "lista.h"

struct racha {
	Lista *racha_almacen;
	size_t cant_combos;
};

racha_t *racha_crear()
{
	racha_t *racha = calloc(1, sizeof(racha_t));
	if (!racha) {
		return NULL;
	}
	racha->racha_almacen = lista_crear();
	if (!racha->racha_almacen) {
		free(racha);
		return NULL;
	}
	return racha;
}

bool racha_agregar(racha_t *racha, void *combo)
{
	if (!racha || !combo) {
		return false;
	}
	if (!lista_agregar_al_final(racha->racha_almacen, combo)) {
		return false;
	}
	racha->cant_combos++;
	return true;
}

bool racha_eliminar(racha_t *racha, void *combo, size_t posicion,
		    void **eliminado)
{
	if (!racha || !combo || racha->cant_combos == 0 ||
	    posicion >= racha->cant_combos) {
		return false;
	}
	if (lista_quitar_elemento(racha->racha_almacen, posicion, eliminado)) {
		racha->cant_combos--;
		return true;
	}
	return false;
}

bool racha_vaciar(racha_t *racha)
{
	if (!racha || racha->cant_combos == 0) {
		return false;
	}
	while (racha_cantidad_combos(racha) > 0) {
		lista_quitar_elemento(racha->racha_almacen, 0, NULL);
		racha->cant_combos--;
	}
	return true;
}

bool racha_iterar(racha_t *racha, bool (*f)(void *, void *), void *ctx)
{
	if (!racha || !f) {
		return false;
	}
	if (lista_iterar_elementos(racha->racha_almacen, f, ctx) > 0) {
		return true;
	}
	return false;
}

size_t racha_cantidad_combos(racha_t *racha)
{
	return racha == NULL ? 0 : racha->cant_combos;
}

//pre:	La racha debe ser valida. Y si queremos aplicarle la funcion destructora no hay que pasarle null.
//post:	Liberamos la racha aplciandole la funcion destructora.
void destruir_racha_con_destructor(racha_t *racha, void (*destructor)(void *))
{
	if (racha) {
		lista_destruir_todo(racha->racha_almacen, destructor);
		free(racha);
	}
}

void racha_destruir(racha_t *racha)
{
	if (racha) {
		destruir_racha_con_destructor(racha, NULL);
	}
}

void racha_destruir_todo(racha_t *racha, void (*destructor)(void *))
{
	if (racha) {
		destruir_racha_con_destructor(racha, destructor);
	}
}