#include "abb.h"
#include "abb_estructura_privada.h"

//pre:	Idealmente, el elemento no deberia ser NULL, pero puede serlo, funcionaria de igual manera.
//post:	Creo un nuevo nodo con el fin de poder agregar uno en los llamados para las funciones de agregar. Seteamos los campos del mismo y lo devolvemos inicializado y con memoria reservada.
nodo_t *crear_nuevo_nodo(void *elemento)
{
	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (nodo == NULL) {
		return NULL;
	}
	nodo->elemento = elemento;
	return nodo;
}

abb_t *abb_crear(int (*comparador)(void *, void *))
{
	if (comparador == NULL) {
		return NULL;
	}
	abb_t *abb = calloc(1, sizeof(abb_t));
	if (abb == NULL) {
		return NULL;
	}
	abb->comparador = comparador;
	return abb;
}

//pre:  Idealmente, deberia haber al menos un nodo en el ABB. Y el destructor no deberia ser NULL si sabemos que no se reservo memoria para los elementos del ABB, si
// no reservamos memoria para el elemento, pasarle NULL es lo optimo.
//post: Recursivamente, vamos recorriendo el arbol y vamos liberando los nodos. En caso de que el destructor sea distinto de NULL, le aplicamos la funcion al elemento en dicho nodo.
void destruir_nodo(nodo_t *nodo, void (*destructor)(void *))
{
	if (nodo == NULL) {
		return;
	}
	if (nodo->izq != NULL) {
		destruir_nodo(nodo->izq, destructor);
	}
	if (nodo->der != NULL) {
		destruir_nodo(nodo->der, destructor);
	}
	if (destructor != NULL) {
		destructor(nodo->elemento);
	}
	free(nodo);
}

void abb_destruir(abb_t *abb)
{
	if (abb != NULL) {
		destruir_nodo(abb->raiz, NULL);
		free(abb);
	}
}

void abb_destruir_todo(abb_t *abb, void (*destructor)(void *))
{
	if (abb != NULL) {
		destruir_nodo(abb->raiz, destructor);
		free(abb);
	}
}

//pre:  El ABB no deberia ser NULL al igual que el nodo
//post: Netamente, seteamos los punteros derecha e izquierda de la raiz como NULL ya que seria el pirmer nodo ademas de setear el campo raiz como el nodo que le
// pasamos, ademas de incrementar la cantidad de nodos/elementos en el ABB.
void insertar_raiz(abb_t *abb, nodo_t *nodo)
{
	nodo->der = NULL;
	nodo->izq = NULL;
	abb->raiz = nodo;
	abb->nodos++;
}

//pre:  Deberiamos recibir argumentos validos, y deberiamos tener al menos la raiz del ABB.
//post: En caso de que el resultado entre comparar el elemento del nodo I (el nodo_actual) y el elemento del nodo nuevo, es menor o igual que 0, vamos a recorrer el subarbol
// izquierdo hasta que el nodo izquierdo sea igual a NULL (que tendriamos via libre para agregar sin problemas). Caso contrario, hacemos lo msimo pero del lado derecho. Asi
// garantisamos que los elementos menores on iguales a la raiz van del lado izquierdo y los mayores al lado derecho
nodo_t *insertar_abb_no_vacio(nodo_t *raiz, nodo_t *nuevo_nodo,
			      int (*comparador)(void *,
						void *)) //SUJETA A DEBATE !!
{
	if (raiz == NULL || nuevo_nodo == NULL) {
		return nuevo_nodo;
	}
	int resultado_comparacion =
		comparador(nuevo_nodo->elemento, raiz->elemento);
	if (resultado_comparacion <= 0) {
		raiz->izq = insertar_abb_no_vacio(raiz->izq, nuevo_nodo,
						  comparador);
	} else {
		raiz->der = insertar_abb_no_vacio(raiz->der, nuevo_nodo,
						  comparador);
	}
	return raiz;
}

bool abb_insertar(abb_t *abb, void *elemento)
{
	if (abb == NULL) {
		return false;
	}
	nodo_t *nodo_nuevo = crear_nuevo_nodo(elemento);
	if (nodo_nuevo == NULL) {
		return false;
	}
	if (abb->raiz == NULL) {
		insertar_raiz(abb, nodo_nuevo);
		return true;
	} else {
		abb->raiz = insertar_abb_no_vacio(abb->raiz, nodo_nuevo,
						  abb->comparador);
		abb->nodos++;
	}
	return true;
}

//pre:
//post:
nodo_t *buscar_predecesor_inorden(nodo_t *nodo)
{
	nodo_t *nodo_actual = nodo->izq;
	while (nodo_actual->der != NULL) {
		nodo_actual = nodo_actual->der;
	}
	return nodo_actual;
}

//pre:
//post:
nodo_t *eliminar_nodo(nodo_t *nodo, void *buscado, void **encontrado,
		      int (*comparador)(void *, void *))
{
	if (nodo == NULL) {
		return NULL;
	}
	int resultado_comparacion = comparador(buscado, nodo->elemento);
	if (resultado_comparacion == 0) {
		if (*encontrado == NULL) {
			*encontrado = nodo->elemento;
		}
		if (nodo->der != NULL && nodo->izq != NULL) {
			nodo_t *nodo_inorden = buscar_predecesor_inorden(nodo);
			nodo->elemento = nodo_inorden->elemento;
			nodo->izq = eliminar_nodo(nodo->izq,
						  nodo_inorden->elemento,
						  encontrado, comparador);
			return nodo;
		}
		nodo_t *hijo_no_null = nodo->der != NULL ? nodo->der :
							   nodo->izq;
		free(nodo);
		return hijo_no_null;
	}
	if (resultado_comparacion > 0) {
		nodo->der = eliminar_nodo(nodo->der, buscado, encontrado,
					  comparador);
	} else {
		nodo->izq = eliminar_nodo(nodo->izq, buscado, encontrado,
					  comparador);
	}
	return nodo;
}

bool abb_quitar(abb_t *abb, void *buscado, void **encontrado)
{
	if (abb == NULL || buscado == NULL) {
		return false;
	}
	*encontrado = NULL;
	nodo_t *nodo_a_eliminar =
		eliminar_nodo(abb->raiz, buscado, encontrado, abb->comparador);
	if (*encontrado != NULL) {
		abb->raiz = nodo_a_eliminar;
		(abb->nodos)--;
		return true;
	}
	return false;
}

//pre:  Idealmente no deberiamos pasarle un NULL al parametro elemento.
//post: Buscamos el elemento hasta que el resultado de la comparacion entre el elemento que este en el nodo I (o nodo que estemos recorriendo)
// y el elemento que buscamos, sea igual a 0 (que seria que lo encontramos). Si es mayor, recorreriamos el lado derecho del arbol sino vamos a la izquierda.
void *abb_obtener_elemento_recursivo(nodo_t *nodo, void *elemento,
				     int (*comparador)(void *, void *))
{
	if (nodo == NULL) {
		return NULL;
	}
	int resultado_comparacion = comparador(elemento, nodo->elemento);
	if (resultado_comparacion == 0) {
		return nodo->elemento;
	}
	if (resultado_comparacion > 0) {
		return abb_obtener_elemento_recursivo(nodo->der, elemento,
						      comparador);
	} else {
		return abb_obtener_elemento_recursivo(nodo->izq, elemento,
						      comparador);
	}
}

void *abb_obtener(abb_t *abb, void *elemento)
{
	if (abb == NULL || elemento == NULL) {
		return NULL;
	}
	void *elemento_buscado = abb_obtener_elemento_recursivo(
		abb->raiz, elemento, abb->comparador);
	if (elemento_buscado != NULL) {
		return elemento_buscado;
	}
	return NULL;
}

size_t abb_cantidad(abb_t *abb)
{
	return abb == NULL ? 0 : abb->nodos;
}

//pre:  Deberiamos pasarle un nodo valido (o mejor dicho la raiz) y la funcion no puede ser NULL.
//post: Recursivamente, recorremos primero a la izquierda, sumamos todas las iteraciones siempre que el nodo donde estemos parados no sea NULL, luego le sumamos uno al contador
//  por la raiz, y luego volvemos a recorrer pero del lado derecho y vamos aumentando el contador a medida que el nodo que estamos parados no sea NULL.
size_t contar_iteraciones_inorder(nodo_t *nodo, bool (*f)(void *, void *),
				  void *ctx, bool *continua_iteracion)
{
	if (nodo == NULL || !(*continua_iteracion)) {
		return 0;
	}
	size_t cantidad = 0;
	cantidad += contar_iteraciones_inorder(nodo->izq, f, ctx,continua_iteracion);
	if (!f(nodo->elemento, ctx)) {
		*continua_iteracion = false;
		return cantidad;
	}
	cantidad++;
	cantidad += contar_iteraciones_inorder(nodo->der, f, ctx,continua_iteracion);
	return cantidad;
}

size_t abb_iterar_inorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (abb == NULL || f == NULL) {
		return 0;
	}
	bool continuar_iteracion = true;
	return contar_iteraciones_inorder(abb->raiz, f, ctx,&continuar_iteracion);
}

//pre:  Deberiamos pasarle un nodo valido (o mejor dicho la raiz) y la funcion no puede ser NULL.
//post: Recursivamente, aumentamos en uno el contador por la raiz (si la funcion devolvio true), luego recorremos a la izquierda, sumamos todas las iteraciones siempre
// que el nodo donde estemos parados no sea NULL, y por ultimo recorremos el lado derecho y vamos aumentando el contador a medida que el nodo que estamos parados no sea NULL.
size_t contar_iteraciones_preorden(nodo_t *nodo, bool (*f)(void *, void *),
				   void *ctx)
{
	if (nodo == NULL) {
		return 0;
	}
	size_t cantidad = 0;
	if (!f(nodo->elemento, ctx)) {
		return cantidad;
	}
	cantidad++;
	cantidad += contar_iteraciones_preorden(nodo->izq, f, ctx);
	cantidad += contar_iteraciones_preorden(nodo->der, f, ctx);
	return cantidad;
}

size_t abb_iterar_preorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (abb == NULL || f == NULL) {
		return 0;
	}
	return contar_iteraciones_preorden(abb->raiz, f, ctx);
}

//pre:  Deberiamos pasarle un nodo valido (o mejor dicho la raiz) y la funcion no puede ser NULL.
//post: Recursivamente, primero recorremos a la izquierda, sumamos todas las iteraciones siempre que el nodo donde estemos parados no sea NULL, luego recorremos el
// lado derecho y vamos aumentando el contador a medida que el nodo que estamos parados no sea NULL y por ultimo aumentamos en uno el contador por la raiz (si la funcion devolvio true)
size_t contar_iteraciones_postorden(nodo_t *nodo, bool (*f)(void *, void *),
				    void *ctx)
{
	if (nodo == NULL) {
		return 0;
	}
	size_t cantidad = 0;
	cantidad += contar_iteraciones_postorden(nodo->izq, f, ctx);
	cantidad += contar_iteraciones_postorden(nodo->der, f, ctx);
	if (!f(nodo->elemento, ctx)) {
		return cantidad;
	}
	cantidad++;
	return cantidad;
}

size_t abb_iterar_postorden(abb_t *abb, bool (*f)(void *, void *), void *ctx)
{
	if (abb == NULL || f == NULL) {
		return 0;
	}
	return contar_iteraciones_postorden(abb->raiz, f, ctx);
}

//pre:  El elemento y el vector que le pasamos no son NULL. Y el Indice o I, deberia haverse inicializado con 0.
//post: Agregamos al vector nuevo, con el elemento que le pasamos en la posicion que le pasamos, y aumentamos en 1 el indice I.
void agregar_elemento_al_vector(void *elemento, size_t *i, void **vector)
{
	vector[*i] = elemento;
	(*i)++;
}

//pre:
//post:	Los elementos del ABB se guardan, recursivamente y recorremos inorden, en el vector que le pasamos hasta llenar el vector o hasta que se recorre todo el ABB.
void rellenar_vector_inorden_recu(nodo_t *nodo, void **vector, size_t tamaño,
				  size_t *i)
{
	if (*i == tamaño || nodo == NULL) {
		return;
	}
	if (nodo->izq != NULL) {
		rellenar_vector_inorden_recu(nodo->izq, vector, tamaño, i);
	}
	if (*i < tamaño) {
		agregar_elemento_al_vector(nodo->elemento, i, vector);
	}
	if (nodo->der != NULL) {
		rellenar_vector_inorden_recu(nodo->der, vector, tamaño, i);
	}
}

size_t abb_vectorizar_inorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (abb == NULL || vector == NULL) {
		return 0;
	}
	size_t i = 0;
	rellenar_vector_inorden_recu(abb->raiz, vector, tamaño, &i);
	return i;
}

//pre:
//post:	Los elementos del ABB se guardan, recursivamente y recorremos preorden, en el vector que le pasamos hasta llenar el vector o hasta que se recorre todo el ABB.
void rellenar_vector_preorden_recu(nodo_t *nodo, void **vector, size_t tamaño,
				   size_t *i)
{
	if (*i == tamaño || nodo == NULL) {
		return;
	}
	if (*i < tamaño) {
		agregar_elemento_al_vector(nodo->elemento, i, vector);
	}
	if (nodo->izq != NULL) {
		rellenar_vector_preorden_recu(nodo->izq, vector, tamaño, i);
	}
	if (nodo->der != NULL) {
		rellenar_vector_preorden_recu(nodo->der, vector, tamaño, i);
	}
}

size_t abb_vectorizar_preorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (abb == NULL || vector == NULL) {
		return 0;
	}
	size_t i = 0;
	rellenar_vector_preorden_recu(abb->raiz, vector, tamaño, &i);
	return i;
}

//pre:
//post:	Los elementos del ABB se guardan, recursivamente y recorremos postorden, en el vector que le pasamos hasta llenar el vector o hasta que se recorre todo el ABB.
void rellenar_vector_postorden_recu(nodo_t *nodo, void **vector, size_t tamaño,
				    size_t *i)
{
	if (*i == tamaño || nodo == NULL) {
		return;
	}
	if (nodo->izq != NULL) {
		rellenar_vector_postorden_recu(nodo->izq, vector, tamaño, i);
	}
	if (nodo->der != NULL) {
		rellenar_vector_postorden_recu(nodo->der, vector, tamaño, i);
	}
	if (*i < tamaño) {
		agregar_elemento_al_vector(nodo->elemento, i, vector);
	}
}

size_t abb_vectorizar_postorden(abb_t *abb, void **vector, size_t tamaño)
{
	if (abb == NULL || vector == NULL) {
		return 0;
	}
	size_t i = 0;
	rellenar_vector_postorden_recu(abb->raiz, vector, tamaño, &i);
	return i;
}