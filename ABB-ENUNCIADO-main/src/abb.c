#include "abb.h"
#include "abb_estructura_privada.h"


//pre:	Idealmente, el elemento no deberia ser NULL, pero puede serlo, funcionaria de igual manera.
//post:	Creo un nuevo nodo con el fin de poder agregar uno en los llamados para las funciones de agregar. Seteamos los campos del mismo y lo devolvemos inicializado y con memoria reservada.
nodo_t *crear_nuevo_nodo(void *elemento)
{
	nodo_t *nodo = calloc(1,sizeof(nodo_t));
	if (nodo == NULL) {
		return NULL;
	}
	nodo->elemento = elemento;
	return nodo;
}

abb_t* abb_crear(int (*comparador)(void*, void*))
{    
    if (comparador == NULL)
    {
        return NULL;
    }    
    abb_t *abb = calloc(1,sizeof(abb_t)) ;
    if (abb == NULL)
    {
        return NULL;
    }
    abb->comparador = comparador;
    return abb;
}

//pre:
//post:
void destruir_nodo(nodo_t* nodo, void (*destructor)(void*)){
    if(nodo == NULL){
        return;
    }
    if(nodo->izq){
        destruir_nodo(nodo->izq, destructor);
    }
    if(nodo->der){
        destruir_nodo(nodo->der, destructor);
    }
    if(destructor){
        destructor(nodo->elemento);
    }
   free(nodo);
}

void abb_destruir(abb_t* abb)
{   
    if (abb != NULL)
    {
        destruir_nodo(abb->raiz,NULL);
        free(abb);    
    }
}

void abb_destruir_todo(abb_t* abb, void (*destructor)(void*))
{
    if (abb != NULL)
    {
        destruir_nodo(abb->raiz,destructor);
        free(abb);    
    }
}

//pre:
//post:
void insertar_raiz(abb_t *abb,nodo_t *nodo)
{
    nodo->der = NULL;
    nodo->izq = NULL;
    abb->raiz = nodo;
    abb->nodos++;
} 

//pre:
//post:
bool insertar_abb_no_vacio(nodo_t *nodo_actual,nodo_t *nuevo_nodo, int (*comparador)(void*,void*))  //SUJETA A DEBATE !!
{
    int resultado_comparacion = comparador(nodo_actual->elemento, nuevo_nodo->elemento);
    if (resultado_comparacion >= 0)
    {
        if (nodo_actual->der == NULL)
        {
            nodo_actual->der = nuevo_nodo;
        }
        else{
            insertar_abb_no_vacio(nodo_actual->der,nuevo_nodo,comparador);
        }  
    }else
    {
        if (nodo_actual->izq == NULL)
        {
            nodo_actual->izq = nuevo_nodo;
        }else{
            insertar_abb_no_vacio(nodo_actual->izq,nuevo_nodo,comparador);
        }        
    }
    return true;
}

bool abb_insertar(abb_t *abb, void* elemento)
{
    if (abb == NULL || elemento == NULL)
    {
        return false;
    }
    nodo_t *nodo_nuevo = crear_nuevo_nodo(elemento);
    if (nodo_nuevo == NULL)
    {
        return false;
    }
    if (abb->raiz == NULL)
    {        
        insertar_raiz(abb,nodo_nuevo);
        return true;
    }else{
        insertar_abb_no_vacio(abb->raiz,nodo_nuevo,abb->comparador);
        abb->nodos++;
    }
    return true;   
}

/**
 * Quita el elemento buscado del arbol. Si lo encuentra y encontrado no es NULL,
 * almacena el puntero.
 *
 * Devuelve true si pudo quitar el elemento.
 */
//bool abb_quitar(abb_t* abb, void* buscado, void** encontrado);

//pre:
//post:
void* abb_obtener_elemento_recursivo(nodo_t *nodo, void* elemento, int (*comparador)(void*,void*))
{
    if (nodo == NULL)
    {
        return NULL;
    }
    int resultado_comparacion = comparador(nodo->elemento,elemento); 
    if (resultado_comparacion == 0)
    {
        return nodo;
    }
    if(resultado_comparacion > 0)
    {
        return abb_obtener_elemento_recursivo(nodo->der,elemento,comparador);
    }
    else{
        return abb_obtener_elemento_recursivo(nodo->izq,elemento,comparador);
    }
}

void* abb_obtener(abb_t* abb, void* elemento)
{
    if (abb == NULL || elemento == NULL)
    {
        return NULL;
    }
    void* elemento_buscado = abb_obtener_elemento_recursivo(abb->raiz,elemento,abb->comparador);
    if (elemento_buscado != NULL)
    {
        return elemento_buscado;
    }
    return NULL;    
}

size_t abb_cantidad(abb_t* abb)
{
    return abb == NULL ? 0 : abb->nodos;    
}

/**
 * Recorre los elementos del abb en el orden específico y aplica la función f a
 * cada uno.
 *
 * Si la función f devuelve false, se deja de iterar.
 *
 * Devuelve la cantidad de veces que fue invocada la función f.
*/

size_t contar_iteraciones_inorder(nodo_t *nodo,bool (*f)(void*,void*), void* ctx)
{    
    if (nodo == NULL)
    {
        return 0;
    }    
    size_t cantidad = contar_iteraciones_inorder(nodo->izq,f,ctx);
    if (!f(nodo->elemento,ctx))
    {
        return cantidad;
    }
    return cantidad +1 +contar_iteraciones_inorder(nodo->der,f,ctx);
}

size_t abb_iterar_inorden(abb_t* abb, bool (*f)(void*,void*), void* ctx)
{
    if (abb == NULL || abb->raiz == NULL)   //Innecesaria la segunda validacion??
    {
        return 0;
    }
    return contar_iteraciones_inorder(abb->raiz,f,ctx);    
}
// size_t abb_iterar_preorden(abb_t* abb, bool (*f)(void*,void*), void* ctx);
// size_t abb_iterar_postorden(abb_t* abb, bool (*f)(void*,void*), void* ctx);

/**
 * Rellena el vector de punteros con los elementos del abb siguiendo un orden
 * dado. Tamaño indica la capacidad del vector.
 *
 * Devuelve la cantidad de elementos guardados en el vector.
 */
// size_t abb_vectorizar_inorden(abb_t* abb, void** vector, size_t tamaño);
// size_t abb_vectorizar_preorden(abb_t* abb, void** vector, size_t tamaño);
// size_t abb_vectorizar_postorden(abb_t* abb, void** vector, size_t tamaño);

