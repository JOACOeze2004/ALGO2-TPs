<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TDA HASH

## Alumno: Joaquin Ezequiel Mendez Archerrizo - 111767 - jmendeza@fi.uba.ar.

- Para compilar:

```bash
make pruebas_alumno
make tp-hash
```

- Para ejecutar:

```bash
./pruebas_alumno 
./tp_hash ejemplos/pokedex.csv
```

- Para ejecutar con valgrind:
```bash
make valgrind-alumno
make valgrind-tp-hash
```

- Para compilación y ejeccución con valgrind (version rapida):
```bash
make correr-pruebas
make correr-tp
```

---
##  Funcionamiento


El TP consta en hacer algo similar a lo que se hizo para el TP de Listas y de ABB, pero acá usamos el TDA Hash, usando nodos simplemente enlazados. Lo que se pide hacer, es básicamente, leer un archivo caso, línea por línea, separar los elementos separados por el ";" o "," (depende del separador que le pasemos), irlo casteando/parseando esos datos e irlos guardando en el ABB. Y debemos darle la opción al usuario de listar los pokemones que se leyeron de ese .csv (netamente lo hecho en el tp1 y el de lista) o darle la opción de buscar X Pokémon y que aparezca por pantalla el nombre, el tipo y las estadísticas, si se lo encuentra claro. Y se imprimiría estas dos opciones:

Bueno, para estructurar un poco esta parte, podemos empezar con un diagrama de como quedan las estructuras, y luego ir comentando en general la implementacion del hash, halar de funciones concretas (como la de insertar, la funcion hash y el rehash). Empezemos entonces por como definimos nuestras estructuras y luego vamos al diagrama:

```c
struct par {
	char *clave;
	void *valor;
	par_t *siguiente;
};

struct hash {
	par_t **pares;
	size_t *contador_pares;     //Podria ser opcional
	size_t capacidad;
	size_t cantidad;
};
```
Entonces el Hash vendria a ser la estructura prinicpal, que tiene un vector de punteros par_t (que es donde vamos a ir guardando laos pares clave-valor), una cantidad para medir cuantos pares hay en el hash, una capacidad que nos sirve a la hora de medir cuando hay que hacer rehash para el vector de pares. Y por ultimo el contador_pares, este ultimo es "opcional" y mas abajo explicare bien porque lo usamos, pero a priori digamos que nos sirve para medir cuantos pares hay en una posicion del vector que usamos para ir guardando segun lo que nos devuelva la funcion de hash. Yo lo veo mas como que la cantidad y la capacidad nos sirve como "verificador horizontal" y el vector de contador_pares es mas un "verificador vertical", supongo que con el diagrama se va a entender mejor esta idea. 
Despues tenemos la estructura de par que vendria a ser un nodo donde guardamos el par clave-valor (de ahi los campos que tenemos) y un puntero a un siguiente par, entrenos es un nodo que almacena una clave en vez de solo el valor. Bien, ahora vamos con el diagrama:

<div align="center">
<img width="70%" src="img/DiagramaMemoria(convectextra).png">
</div>




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
Incluír acá las respuestas a las preguntas del enunciado (si aplica).
