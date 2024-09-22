<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA LISTA


## Alumno: Joaquin Ezequiel Mendez Archerrizo - 111767 - jmendeza@fi.uba.ar.

- Para compilar:

```bash
make pruebas_alumno
make tp-lista
```

- Para ejecutar:

```bash
./pruebas_alumno 
./tp_lista ejemplos/pokedex.csv
```

- Para ejecutar con valgrind:
```bash
make valgrind-alumno
make valgrind-tp-lista
```

- Para compilación y ejeccución con valgrind:
```bash
make correr-pruebas
make correr-tp
```

---

##  Funcionamiento

Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluír **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
1) ¿Qué es una lista/pila/cola? Explicar con diagramas.

Una lista, es una secuencia en la cual guardamos datos del mismo tipo con un cierto orden(como un array) PERO a diferencia del array, este puede tener varias implementaciones, como las listas simplemente enlazadas, doblemente enlazadas y las circulares doblemente enlazadas. Además, no permite como en los arreglos decir "mostrarme el elemento en la posición 5" sino que acá deberíamos recorrer la lista hasta llegar al elemento 5. 

Entonces, la diferencia radical es como se manejan las listas a diferencia de los arrays, estos últimos pueden ser estáticos o dinámicos, pero las listas, como vimos, no manejas así la memoria. En general, vamos reservando espacio para un nodo que contiene un elemento y un puntero al siguiente (o anterior en el caso de las doblemente enlazadas) nodo, lo cual elimina la desventaja de los arreglos dinamicos,no necesitan de memoria contigua, sino que, al trabajar con nodos, estos "saltan" en cuanto al espacio necesario sin que estén, necesariamente, pegados en las direcciones de memoria. Por ejemplo, el primer nodo está en la dirección 00 y el siguiente nodo puede estar en la 04 y el siguiente en al 07 y así, en los vectores dinámicos, deberíamos tener el primer elemento en la posición 00, la siguiente en 01 y así. 
Además, tenemos ciertas operaciones, algunas iguales a las que haríamos en un vector dinámico, pero tiene ventajas en cuanto a la complejidad computacional. Por ejemplo, en las listas tenemos crear, agregar/insertar, destruir, eliminar en X posición y ver X elemento. A diferencia del vector dinámico, que la mayoría de estas operaciones son O(n) (insertar, eliminar y buscar X posición), en las listas se puede reducir el impacto en cuanto complejidad, por ejemplo, insertar al inicio en un vector dinámico si está lleno este debe hacer realloc y pedir más espacio contemplando esa inserción en la primera posición (y mover todo una posición más adelante) en una lista enlazada es O(1) xq solo debemos reajustar el puntero al nodo inicial y como se relaciona el nodo agregado con el que le sigue. O si tenemos una lista doblemente enlazada, la eliminación al final sería O(1). Aunque en general tienden a ser similares en cuanto complejidad computacional, aunque las listas enlazadas terminarían ganando en casos muy puntuales y siempre relacionados con el inicio o el fin de la lista.

Para expandir más, hablemos un poco sobre los enlazados dobles. Como vimos los enlazados simples sirven para eliminaciones o inserciones al inicio, pero los doblemente enlazados, son extremadamente útiles para eliminaciones al final o si queremos acceder a un elemento previo al último nodo o queremos recorrer la lista al revés de la convencional. De hecho también es muy útil si deseamos mantener un cierto orden, un ejemplo (mas allá de los que vimos en clase como el de adelantar o ir para atrás en Netflix o YouTube), algo que me ocurrió en mi tp, concretamente en la implementación de eliminar en la pila, y es que yo la pensaba como un array donde ibas apilando de izquierda a derecha y claro, ¿Como hacías para que desapilar sea O(1)?, costo entender que no debíamos apilar así sino en el orden invertido, así al desapilar eliminas al primero nodo y así sucesivamente, si hubiéramos tenido una lista doblemente enlazada, es probable que pudiera apilar como lo hacía originalmente, y para desapilar, seria guárdate el ultimo nodo en un nodo auxiliar, moverte al nodo anterior al último nodo y ahí eliminas, y ahí mantener un cierto orden. 

(meter diagrama de lista)

Ahora pasando a la pila y la cola, estos son casos particulares de la lista ya que netamente son lo mismo pero cada uno sigue un "principio" o una restricción a diferencia de la lista. Vamos primero a la cola, esta tiene la característica FIFO, o sea si voy agregando elementos en la cola, el primero que debería eliminar o "irse" es el que primero metí, y luego se iría el segundo y así hasta que se quede vacía y para agregar, se van poniendo al final, como la cola del supermercado. En la lista no había estas restricciones, pero como hicimos en la implementación de la pila y la cola , se pueden readaptar las funciones de la lista para la pila y la cola, por ejemplo, en la cola podes apilar, llamando a una función de lista que agregue al final, y para eliminar, podes tener una función que elimine el primer elemento así respetarías la restricción de FIFO. 

(meter diagrama de cola)

Para Pila, la restricción seria LIFO, que quiere decir que el ultimo que agregue es el primero en irse, como una pila de hojas, no sacas del final directamente, sino que apilas y cuando desapilas sacas el papel de más arriba y así con los que siguen. Aunque a diferencia de la cola, capaz acá si importa como lo veas, porque acá medio que importaría el orden si quieres que tus funciones primitivas sean O(1), como me paso a mí, es más conveniente ir apilando de forma tal que el último elemento que agregaste sea el primero así al eliminarlo, esa operación es O(1). 

(meter diagrama de pila)

2) Explica y analiza las diferencias de complejidad entre las implementaciones de lista simplemente enlazada, doblemente enlazada y vector dinámico para las operaciones:
Insertar/obtener/eliminar al inicio
Insertar/obtener/eliminar al final
Insertar/obtener/eliminar al medio

Vamos con las operaciones al inicio, las LSE (lista simplemente enlazada), insertar al inicio tienen una complejidad computacional de O(1), más que nada porque al nodo nuevo/ nodo a agregar, té creas un nodo nuevo, haces que el nodo siguiente a ese apunte a lo que apuntaba el inicio de la lista , llámese nodo_inicio o el nombre que tenga, y luego el nodo inicio apunta al nodo que vamos a agregar. Para obtener elemento al inicio, seria O(1) más que nada porque no es un problema de tamaño variable, es decir, no necesitamos recorrer toda la lista con N elementos, solo devolver el primer elemento. Y para eliminar es más de lo mismo, al eliminar el primero, es O(1) porque si quieres eliminar el primero, es guardarse en un nodo auxiliar, lo que apuntaba al inicio de la lista (un nodo básicamente),y que ese inicio ahora apunte al siguiente del nodo auxiliar, y después liberas el nodo Aux, todas operaciones que no dependen de recorrer una lista, o sea son problemas que no dependen de un problema de tamaño N, sino que son instrucciones básicas. 
Para las LDE (doblemente enlazada) el proceso seria el mismo, para agrégale el paso que al reajustar el puntero a siguiente debemos ajustar el puntero a anterior. Para obtener al inicio es lo mismo que en las LSE y para eliminar es la misma idea solo que deberíamos ajustar el puntero "anterior" del nodo.  
Y para los vectores dinámicos la cosa es distinta, insertar al inicio es O(n) porque debe mover todos los espacios anteriores a ese una posición después. Para obtener al inicio es O(1) porque simplemente podes acceder al índice que quieras haciendo vector[1], y para elimina al inicio también seria O(n) porque debe mover todos los elementos una posición para la izquierda. (aunque también podríamos mover ese elemento al final, restar el tope y mover el resto a la izquierda).

Ahora vamos con las operaciones del medio. Para las LSE y LDE son O(n) más que anda porque ambas DEBEN recorrer la lista hasta que lleguen a la posición a insertar, y después agregan como mencionamos arriba (lo de crear un nodo y sestear los nodos siguiente y anterior) pero para encontrar donde deben si o si recorrer la lista. Lo mismo ocurre para eliminar y obtener elemento, ambos también deben recorrer la lista para obtener la posición del elemento a obtener o eliminar, por lo que termina cayendo en un problema de tamaño variable porque la lista puede tener 1,5,80 o 1000 nodos con sus elementos. Buscar recorre y te devuelve el elemento en esa posición , y eliminar, te guardas el nodo en un nodo Aux, haces que el siguiente al nodo previo al eliminar apunte al siguiente del nodo a eliminar y luego haces free del auxiliar.
Para los vectores dinámicos, la cosa no es tan distinta, salvo que acá trackeas la posición a agregar, y noves todos los elementos previos una posición más adelante, por lo que vuelve a caer en una operación de O(n) porque debemos recorrer el vector intercambiando las operaciones, y eso termina siendo un problema de tamaño N ya que el vector puede tener 1, 100 o 1000 elementos. Lo mismo pasaría con eliminar, es mover ese elemento al final y ahí restar el tope. Y devolver en el medio, por suerte, es O(1) porque podemos hacer vector[i] donde i es el elemento que buscamos.

Vamos con las últimas operaciones relacionadas con el final. Para LSE, insertar al final tiene una complejidad computacional de O(1) ya que lo único que tenemos que hacer es que al siguiente del puntero que apunta al final (o sea al último nodo) apunte al nuevo nodo, que el elemento final de la lista (puntero al "nodo_final") ahora apunte al último nodo y que el siguiente de ese nuevo nodo sea NULL ( en las LDE deberíamos sestear el campo anterior al anterior nodo). Aunque claro esto ocurre si y solo si tenemos un puntero al último nodo, sino deberíamos recorrer toda la lista hasta el final. Para buscar, pasa lo mismo si tenemos un puntero al último nodo es fácil decir que devuelva el elemento de ese nodo siempre que tengamos ese puntero al final sino seria O(n). Pero en nuestro caso tenemos un puntero al final así que podemos decir que es O(1). Para terminar, tenemos la eliminación al final, acá la cosa bifurca, ya que, en las LSE, van a ser O(n) porque por más que tengamos el puntero al final, ya no vamos a safar porque no podemos eliminarlo así porque necesitamos que el siguiente del último nodo sea NULL para poder liberar todos los nodos sin problema, por lo que debemos recorrer toda la lista hasta la anteúltima posición y podemos guardarnos el nodo siguiente (el ultimo) en un nodo auxiliar y ahí operar tranquilamente. Una opción "viable" seria tener un puntero al anteúltimo, pero esto es un parche porque tendríamos el mismo problema si quieres eliminar varias veces , solo serviría si es una sola vez. 
Pero para las LDE la cosa cambia radicalmente, el problema que teníamos antes es que debemos estar en el nodo anterior al último, y ¿qué ventaja nos dan las LDE? que podemos movernos adelante y atrás, por lo que podes ir al último nodo, moverte una posición atrás y operar para eliminar (guardar el siguiente en un nodo auxiliar, el siguiente del anteúltimo seria NULL y el puntero al final apunta al anteúltimo), por lo que ahora al no depender de que tan larga sea la lista, o sea un problema de tamaño N, esta operación seria O(1).

Por ultimo tenemos las operaciones en el final de los vectores dinámicos, agregar al final a priori podría ser O(1) porque es agregar un elemento en el final, PERO (siempre hay uno), el peor caso sería que mi vector está lleno y debería agrandar mi capacidad y esa operación de mover todo a un bloque más grande es O(n) porque depende del tamaño del vector previo. Para buscar, es O(1) porque podemos hacer vector[i] y accedes a esa posición. Y para eliminar, diría que depende del caso, si hacemos realloc cada vez que agregamos y eliminamos, ahí seria O(n) por las razones iguales a porque es O(n) agregar al final. Pero si no tomamos esa estrategia, seria O(1), ya que se trata de restarle uno al tope/cantidad y ya estaría eliminado del vector. 
 
3) Explica la complejidad de las operaciones implementadas en tu trabajo para la pila y la cola.

Bueno, capaz convenia más solo de lista, pero bueno es lo que toca, vamos a ir haciendo X función de pila y cola y después pasamos a la siguiente función.
Empecemos por lo fácil, cola/pila crear, serian O(1) ya que solo son instrucciones, no tenemos un problema de tamaño variable, el peor de los casos seria que asignamos memoria para la cola, y luego para pedir memoria para el strictu lista, falle y tengamos que liberar la memoria de cola/pila.

Pasando a destruir pila/cola:
```c
void liberar_nodos_en_cola(Lista *lista)
{
    Nodo *nodo_actual = lista->nodo_inicio;
    while (nodo_actual != NULL) {
        Nodo *nodo_siguiente = nodo_actual->siguiente;
        free(nodo_actual);
        nodo_actual = nodo_siguiente;
    }
}

void cola_destruir(Cola *cola)
{
    if (cola != NULL) {
        liberar_nodos_en_cola(cola->lista);
        free(cola->lista);
        free(cola);
    }
}
```
tenemos que para destruir todos los nodos, debemos recorrer la pila/cola hasta llegar a que el nodo_actual sea NULL, o sea llegar al final, por lo que al vernos obligados a recorrer la pila/cola esto termina siendo un problema de tamaño N, por lo que esta función (que usa a liberar_nodos) es O(n).

Para destruir_todo, seguimos la misma lógica que antes, salvo que esta sería un poco más compleja que destruir pila/cola, debido a que también debemos ir recorriendo la lista e ir liberando los nodos uno a uno, pero tema bien vas liberando (antes que a los nodos porque si no perdemos la referencia al elemento dentro del nodo) los elementos del nodo, por lo que al tener que recorrer la pila/cola para ir liberando los elementos y después los nodos, hace que esta función, sea O(n).

Luego tenemos cola/pila cantidad:
```c
size_t cola_cantidad(Cola *cola)
{
    if (cola == NULL) {
        return 0;
    }
    return lista_cantidad_elementos(cola->lista);
}

size_t pila_cantidad(Pila *pila)
{
    if (pila == NULL) {
        return 0;
    }
    return pila->lista->cantidad;
}
```

Es claro que es O(1) ambas son O(1) porque lo único que hacen (además de validar que los punteros no sean NULL) es retornar la cantidad de elementos, me pareció interesante poner ambas versiones ya que una es la versión más clara (la de la pila) y la otra es "reutilizando" la función de cantidad de la lista.

Bueno, sigue cola frente:
void *cola_frente(Cola *cola)

```c
void *cola_frente(Cola *cola)
{
    if (cola == NULL || cola->lista->nodo_inicio == NULL ||
        cola->lista->cantidad == 0) {
        return NULL;
    }
    return cola->lista->nodo_inicio->elemento;
}
```
que lo único que hace es retornar el elemento al que apunta el inicio de la lista (o el primer nodo de la lista) por lo que es O(1).
Y después tenemos el de pila_tope:
```c
void *pila_tope(Pila *pila)
{
    if (pila == NULL || pila->lista->cantidad == 0 ||
        pila->lista->nodo_inicio == NULL) {
        return NULL;
    }
    return pila->lista->nodo_inicio->elemento;
}
```
Que sigue la misma lógica de cola_frente (de hecho son casi que un calco) pero esta devuelve el último elemento en apilarse, que sería donde apunta el nodo_inicio, así que sería O(1) también.

Ahora vamos con cola_encolar y cola_descolar:
```c
void agregar_nodo_al_final(Lista *lista, Nodo *nodo_nuevo)
{
    if (lista->nodo_final != NULL) {
        lista->nodo_final->siguiente = nodo_nuevo;
        lista->nodo_final = nodo_nuevo;
        nodo_nuevo->siguiente = NULL;
    }
}

bool lista_agregar_al_final(Lista *lista, void *cosa)
{
    if (lista == NULL || cosa == NULL) {
        return false;
    }
    Nodo *nodo_nuevo = crear_nuevo_nodo(cosa);
    if (nodo_nuevo == NULL) {
        return false;
    }
    if (lista->cantidad == 0) {
        inicializar_lista_con_nodo(lista, nodo_nuevo);
    } else {
        agregar_nodo_al_final(lista, nodo_nuevo);
    }
    (lista->cantidad)++;
    return true;
}

bool cola_encolar(Cola *cola, void *cosa)
{
    if (cola == NULL || cosa == NULL || cola->lista == NULL) {
        return false;
    }
    return lista_agregar_al_final(cola->lista, cosa);
}

void *cola_desencolar(Cola *cola)
{
    if (cola == NULL || cola->lista == NULL || cola->lista->cantidad == 0) {
        return NULL;
    }
    void *elemento_quitado = NULL;
    if (lista_quitar_elemento(cola->lista, 0, &elemento_quitado)) {
        return elemento_quitado;
    }
    return NULL;
}
```

Para encolar no hay ningún drama ya que llamamos a lista_agregar_al_final que es O(1) porque no tenemos que recorrer la lista gracias al puntero que apunta al último nodo, y como tenemos agregar al final de la cola, por las restricciones FIFO, es correcto este uso, por lo que es de tipo O(1) encolar.
La cosa es más "interesante" en decolar, como dijimos antes la cola tiene la restricción FIFO, o sea que el primero en salir es el primero que llego, o sea que debemos eliminar el primer elemento de la cola. PERO (en serio siempre hay uno), hay un pequeño problema con a la función de lista_quitar_elemento, veamos primero la función:

```c
Nodo *lista_quitar_nodo_en_posicion(Lista *lista, size_t posicion)
{
    Nodo *nodo_anterior = lista->nodo_inicio;
    for (size_t i = 1; i < posicion; i++) {
        nodo_anterior = nodo_anterior->siguiente;
    }
    Nodo *nodo_aux = nodo_anterior->siguiente;
    nodo_anterior->siguiente = nodo_aux->siguiente;
    return nodo_aux;
}

bool lista_quitar_elemento(Lista *lista, size_t posicion,
               void **elemento_quitado)
{
    if (lista == NULL || posicion >= lista->cantidad ||
        lista->cantidad ==
            0)
    {
        return false;
    }
    Nodo *nodo_aux;
    if (posicion == 0) {
        nodo_aux = lista->nodo_inicio;
        lista->nodo_inicio = nodo_aux->siguiente;
    } else {
        nodo_aux = lista_quitar_nodo_en_posicion(lista, posicion);
    }
    setear_elemento_quitado(elemento_quitado, nodo_aux);
    liberar_nodo_y_decrementar_cantidad(lista, nodo_aux);
    return true;
}
```
Antes de que sales diciendo que es O(n) y que no es O(1) y que la consigna dice que sea O(1), déjame explicarlo, es cierto que el peor caso de eliminar seria que estuviera en el medio o el final porque debe recorrer la lista hasta llegar a esa posicion, entonces caeríamos en O(n) porque no sabemos qué tan grande o pequeña es la lista. Pero ¿Y si te digiera que en descolar no nos interesa las demás posiciones sino EXCLUSIVAMENTE la primera? ya no sería O(n) porque nunca caería en el caso donde queremos eliminar una posicion diferente a la primera, entonces el pero caso (y el único acá) es que queramos eliminar la posicion 0, y solo por eso sería O(1), aunque si sogueras con dudas, capaz hubiera sido mejor una función el yen .h que fuera eliminar inicio y ya no tendrías este pequeño problema. 

Ahora vamos rapidamente con Pila_apilar y Pila_desapilar:
```c
bool pila_apilar(Pila *pila, void *cosa)
{
    if (pila == NULL || cosa == NULL || pila->lista == NULL) {
        return false;
    }
    return lista_agregar_elemento(pila->lista, 0, cosa);
}

void *pila_desapilar(Pila *pila)
{
    if (pila == NULL || pila->lista == NULL || pila->lista->cantidad == 0) {
        return NULL;
    }
    void *elemento_quitado = NULL;
    if (lista_quitar_elemento(pila->lista, 0, &elemento_quitado)) {
        return elemento_quitado;
    }
    return NULL;
}
```

Para apilar, pasa algo muy similar que para cola_descolar, tenemos que siempre vamos a ir apilando en la posición 0, por lo que esa operación es O(1) y nunca caeríamos en querer apilar en otra posicion, por lo que por poco es O(1) (siguiendo el mismo razonamiento de antes). Y ocurre exactamente lo mismo que antes pero para desapilar, así que como ya lo explique, saltemos con que sería O(1) por muy poco.

Para finalizar, tenemos pila/cola_esta_vacia:
```c
bool pila_esta_vacía(Pila *pila)
{
    if (pila == NULL) {
        return NULL;
    }
    return pila->lista->cantidad == 0;
}
```
Que son O(1) por el hecho de que no dependen de un tamaño variable solo retornan true si la cantidad es 0 o false en caso contrario por lo que no son un problema de tamaño variable por lo que sería valido decir que es O(1) porque solo son verificaciones e instrucciones básicas.