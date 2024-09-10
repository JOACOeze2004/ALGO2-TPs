<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP1


## Alumno: Joaquin Ezequiel Mendez Archerrizo - 111767 - jmendeza@fi.uba.ar.

- Para compilar:

```bash
make ejemplo
make pruebas_alumno
make tp1
```

- Para ejecutar:

```bash
./ejemplo
./pruebas_alumno
./tp1 ejemplos/pokedex.csv
```

- Para ejecutar con valgrind:
```bash
make valgrind-ejemplo
make valgrind-alumno
valgrind-tp1 ( o probar esto: valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes ./tp1 ejemplos/pokedex.csv )
```

---

##  Funcionamiento General
El TP consta de dos archivos .h ,pokedex.h y csv.h, y un main donde se controla el flujo del programa. La idea general es que las funciones que hay en csv.h, recibir un archivo csv, donde se espera algo como: Nombre Pokémon; Tipo; Fuerza; Destreza; Resistencia; y un separado (como el ";"), e irlo leyendo línea a línea y casteando/parseando cada elemento que haya en la línea, por ejemplo, el primer elemento se castea a un string, el segundo a una letra, y los demás a enteros. 

Una vez procesada la línea, con las funciones de pokedex.h se van procesando esos datos, y se van colocando los pokemones que haya en el archivo que le pasamos, siempre que sean validos (más adelante explicare que significa), a la pokedex. Una vez llegado al final del archivo, imprimimos lo que procesamos, como que se metan lo pasado al archivo, pero ordenando, alfabéticamente ascendente, a los pokemones, se muestran cuantos pokemones hay en al pokedex, cuantos hay de cada tipo y las estadísticas más altas que se encontraron, quedando algo de este estilo:

<div align="center">
<img width="70%" src="img/EjemploMain.png">
</div>

## Funcionamiento Mas al detalle:

Para hacerlo más ordenado, voy a ir contando que hacen los .c porque decidí hacer X cosa, y porque decidí poner Y campos en los structs, lo más detallado posible y al final de la explicación dejo una diagramita. Empecemos por el de la pokedex.

#### Pokedex.c

Vamos por lo primero, ¿Qué campos elegí para el struct de pokedex? ¿Por qué? El más "obvio" seria el puntero a Pokémon, pensé en poner un puntero a Pokémon porque así podíamos tener de alguna forma sin tener que recurrir a pasarle siempre el struct pokemones, además yo lo pensé como que pokedex es un array gigante donde cada Pokémon "ocupa" una casilla y adentro de esa casilla están todos los datos del Pokémon (nombre, tipo, etc.). 
Por último, tenemos los campos "capacidad" y "cantidad", estos sirven principalmente para manejar, al agregar un Pokémon, el espacio que hay en la pokedex; volviendo a lo que pensé que era la pokedex que es un array, con capacidad decís básicamente hasta cuanto espacio Tenes para meter pokemones y al igualarlo o superarlo pedís más espacio para meter más pokemones, y con cantidad vas midiendo en tiempo de ejecución, cuantos pokemones hay y vas verificando que la capacidad nunca sea menor o igual a la cantidad de pokemones que hay. Una observación que podrías hacerme es, ¿Por qué usas dos campos si podrías hacerlo con uno? si bien podríamos sacar capacidad y dejar cantidad que sería lo más lógico, el costo a pagar, al menos desde mi poca experiencia, es que vivirías haciendo realloc o tendrías que hacer un mecanismo tal que, si por ejemplo cantidad es múltiplo de 5 por ejemplo, hagas realloc del puntero viejo y pidas 5 espacios más. Pero preferí agregar ese campo más que nada por comodidad, y no abusar del realloc ya que es una operación bastante costosa

```c
struct pokedex {
	struct pokemon *pokemones;
	size_t capacidad;
	size_t cantidad;
};
```


Luego tenemos la función de "pokedex_crear", no hay mucho que decir acá, inicializamos los campos que mencionamos antes, y hacemos malloc del tamaño que tenga el struct pokedex, más que nada para poder hacer dinámica el proceso de agregar pokemones.

Después tenemos "pokedex_agregar_pokemon", acá hay cosas que no decía el enunciado, pero prefería agregar yo, que tiene que ver con "estándares" que debería tener el archivo, por ejemplo, estas 3 funciones:

```c
bool es_pokemon_repetido(struct pokedex *pokedex, struct pokemon pokemon)
{
	bool esta_repetido = false;
	for (size_t i = 0; i < pokedex->cantidad; i++) {
		if (strcmp(pokedex->pokemones[i].nombre, pokemon.nombre) == 0) {
			if (pokedex->pokemones[i].fuerza == pokemon.fuerza &&
			    pokedex->pokemones[i].destreza ==
				    pokemon.destreza &&
			    pokedex->pokemones[i].resistencia ==
				    pokemon.resistencia) {
				esta_repetido = true;
			}
		}
	}
	return esta_repetido;
}

bool es_tipo_esperado(struct pokemon pokemon)
{
	return (pokemon.tipo == TIPO_AGUA || pokemon.tipo == TIPO_FUEGO ||
		pokemon.tipo == TIPO_ELECTRICO || pokemon.tipo == TIPO_LUCHA ||
		pokemon.tipo == TIPO_NORMAL || pokemon.tipo == TIPO_PLANTA ||
		pokemon.tipo == TIPO_ROCA);
}

bool es_entrada_adecuada(struct pokemon pokemon)
{
	return (strcmp(pokemon.nombre, "") != 0 && es_tipo_esperado(pokemon) &&
		pokemon.fuerza >= 0 && pokemon.destreza >= 0 &&
		pokemon.resistencia >= 0);
}
```

Donde validamos cosas como que el nombre del Pokémon y las estadísticas no esté en la pokedex, porque no queremos que se agreguen pokemones repetidos. Técnicamente la pokedex sirve para registrar un Pokémon atrapado, y no permite volver a meter un Pokémon que ya estaba registrado, pero metí esto más que nada para hacer una validación de entrada, y no lo especifica el enunciado por lo que puede estar mal agregarlo si no lo piden. Después el resto son cosas como validar que el tipo de Pokémon sea válido y que las stats sean mayores o iguales a 0. 

Pero volviendo a lo que propiamente se pidió de la función de agregar, básicamente pedimos memoria para guardar el nombre del Pokémon + 1 para ponerle el 0 al final del string, lo vemos en esta función:
```c
bool asignar_memoria_pokemon(struct pokedex *pokedex, struct pokemon pokemon)
{
	pokedex->pokemones[pokedex->cantidad].nombre =
		malloc(strlen(pokemon.nombre) + 1);
	if (pokedex->pokemones[pokedex->cantidad].nombre == NULL) {
		return false;
	}
	return true;
}

bool redimensionar_pokedex(struct pokedex *pokedex)
{
	size_t nueva_capacidad_pokedex =
		(pokedex->capacidad == 0) ?
			CAPACIDAD_INICIAL :
			pokedex->capacidad * FACTOR_DE_CRECIMIENTO;
	struct pokemon *pokemones_redimensionados =
		realloc(pokedex->pokemones,
			nueva_capacidad_pokedex * sizeof(struct pokemon));
	if (pokemones_redimensionados == NULL) {
		return false;
	}
	pokedex->pokemones = pokemones_redimensionados;
	pokedex->capacidad = nueva_capacidad_pokedex;
	return true;
}
```
Y luego entran los campos de capacidad y cantidad, al principio seteamos ambos a 0 porque la pokedex empieza vacía por lo que de entrada terminaríamos pidiendo espacio para 10 pokemones, con la operación del realloc, aunque nos guardamos el resultado del realloc en pokemon_redimensionados por si llegara a fallar no perder el puntero original. En caso de que la cantidad fuera mayor o igual pedimos la capacidad actual multiplicada por 2. Aunque podría ser ineficiente si tuviéramos 11 pokemones por ejemplo hay que quedan ahí 9 espacios sin usar, pero eso supongo que lo veremos más adelante (o no) temas de eficiencia y optimización, pero supongo que para empezar está bien.

Entonces al llegar a la función pokedex_agregar_pokemon, validamos que el puntero pokedex no sea null, verificamos que la cantidad no supere o iguale a la capacidad, en caso de serlo llamamos a redimensionar y si este devolvió false porque fallo, devolvemos false en la función. Después verificamos que la entrada sea válida para agregar y si seteamos correctamente los atributos pasados (nombre, tipo, etc.) devolvemos true.


Luego tenemos la función de pokedex_cantidad_pokemones, que lo único que hace es validar que el puntero pokedex, no sea null y devuelve lo que haya en el campo cantidad en la pokedex. 


Luego tenemos la función de pokedex_buscar_pokemon, las únicas dos cosas interesantes serian, la condición para que retorno null, ya que validamos que pokedex y nombre no sean null y después si la cantidad es menor o igual a 0 o si el nombre del Pokémon a buscar es 0, retorna null, esas dos últimas son más que nada para que no tire segmentation porque se rompía obviamente si buscaba un nombre vacío, o si no había nada en la pokedex. Lo otro interesante es que buscamos el Pokémon por búsqueda binaria. Honestamente, elegí búsqueda binaria porque en el discord preguntaron y alguien dijo que había hecho búsqueda binaria, entonces recordé que al llamar a esta función ya ordena la pokedex por orden alfabético y lo cambie a búsqueda binara ya que es más eficiente y no era una búsqueda lineal (que es como originalmente lo pensé).



Por ultimo tenemos la función de iterar, primero que todo debemos ir ordenando a medida que ordenamos, por lo que si la cantidad de pokemones es mayor a 1 (porque no voy a ordenar 1 elemento porque ya lo estaría) y lo vamos ordenando con el método de ordenamiento por burbujeo, porque es el único que me acuerdo siempre, y la verdad entre selección, inserción y burbujeo, es mejor burbujeo solo porque es el más usado para incitantes, (total creo que son todos O(n^n)). Y luego iteramos hasta que lleguemos a la cantidad de pokemones o hasta que el puntero a funciones devuelva false, y devolvemos la cantidad de iteraciones hechas.
```c
void ordenar_pokemones(struct pokedex *pokedex)
{
	for (size_t i = 0; i < pokedex->cantidad - 1; i++) {
		for (size_t j = 0; j < pokedex->cantidad - i - 1; j++) {
			if (strcmp(pokedex->pokemones[j].nombre,
				   pokedex->pokemones[j + 1].nombre) > 0) {
				intercambiar_pokemones(
					&pokedex->pokemones[j],
					&pokedex->pokemones[j + 1]);
			}
		}
	}
}

size_t pokedex_iterar_pokemones(struct pokedex *pokedex,
				bool (*funcion)(struct pokemon *, void *),
				void *ctx)
{
	if (pokedex == NULL) {
		return 0;
	}
	if (pokedex->cantidad > 1) {
		ordenar_pokemones(pokedex);
	}
	size_t cant_iterada = 0;
	size_t i = 0;
	bool finalizar_iteracion = false;
	while (i < pokedex->cantidad && !finalizar_iteracion) {
		bool continuar_iteracion = funcion(&pokedex->pokemones[i], ctx);
		if (!continuar_iteracion) {
			finalizar_iteracion = true;
		}
		cant_iterada++;
		i++;
	}
	return cant_iterada;
}
```
Capaz algo que te llame la atención es la variable finalizar iteración, y que está dentro del while, es más que nada para no meter un return dentro del while, sino que cortarlo de forma menos artificial.

Por ultimo tenemos la función de destruir_pokedex, no hay mucho misterio en esta función, solo liberamos lo pedido en memoria para los nombres de los pokemones que fuimos agregando, del puntero a pokemones, y del struct pokedex.  

(meter diagrama de pokedex)
<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

#### Csv.c
Vamos a omitir la explicación de la primera parte ya que es parte del tp0, y ya había hecho una explicación del mismo.

Vamos por partes, en el siguiente struct vemos 4 campos, uno sirve para guardar el nombre del archivo, otro para guardar el separador que le vamos a usar para hacer el Split, y los otros dos restantes son los equivalentes a partes y strign del tp0. 

```c
struct archivo_csv {
	FILE *nombre_archivo;
	size_t columnas;
	char **string;
	char separador;
};
```

Es verdad que string y columnas podrían estar de más, pero como tuve problemas al intentar importar lo usado para el tp0, no funcionaba y decidí traer todo e irlo modificando según lo que tenía, y por eso están los campos string (para ir copiando el nuevo string separado por el delimitador) y columnas que vendría a ser el equivalente a partes porque ya sabes que, si te pasan 5 como columnas, vas a tener 5 espacios en string para almacenar las palabras. Pero si no hubiera tenido problemas con la importación de lo hecho en el tp0, con el nombre del archivo (porque necesitas cerrarlo y no tenes "nombre archivo" en cerrar archivo) y el separador, porque en leer_linea no tenes el separador como tenías en abrir, por lo que es obligatorio tenerlo en un campo para pasárselo a dividir string.

En abrir_archivo, no hay nada interesante mas allá de inicializar los campos del struct, el fopen del archivo en lectura, pedir memoria para el struct archivo_csv y verificar que el puntero al nombre del archivo no sea NULL ni que el malloc falle, aunque en caso de que el archivo fuera null, libero lo pedido para el struct 

Lo más interesante está en leer_linea_csv, donde tenemos un contador de líneas casteadas a modo de que, si salió bien el casteo, aumenta ese contador, además de que en caso de que el fgets devolviera null (que sería cuando se llegó al final del archivo o la línea o algo salió mal) devuelve el contador de líneas casteadas. Luego llamamos a dividir string, en caso de que algo haya salido mal, devolvemos 0, sino me dividí el string y sigue ejecutándose la función. Por ultimo debemos recorrer el puntero a funciones, en caso de que alguna función fuera null, cortaría la ejecución porque la variable es_funcion_invalida hace que sea true, entonces corta el while, libera y retorna el contador de líneas. Si eso no ocurre, o sea que la función es válida, le pasamos el n elemento que tengamos guardado de string (o sea un string separado por el delimitador) y el n elemento del arreglo de ctx y aumentamos el contador de líneas. 

```c
size_t leer_linea_csv(struct archivo_csv *archivo, size_t columnas,
		      bool (*funciones[])(const char *, void *), void *ctx[])
{
    // lo mas relevante
	while (!es_funcion_invalida && i < archivo->columnas) {
		if (funciones[i] == NULL){
			es_funcion_invalida = true;
		}		
		else if (funciones[i](archivo->string[i], ctx[i])) {
			contador_lineas_casteadas++;
		}		
		i++;
	}
	liberar_substr_al_procesar_linea(archivo);
	return contador_lineas_casteadas;
}
```

Por último, llamamos a liberar_substr_al_procesar_linea, que una vez procesados los strings divididos por el separador, liberamos esa memoria pedida, que sería la cantidad exacta de "partes" o columnas que el pasamos. En resumen, si le pasan 5 como la cantidad de columnas a leer, nosotros en las funciones del tp0 pedimos espacio para 5 strings separados por el delimitador, y acá liberamos esos espacios pedidos. 
```c
void liberar_substr_al_procesar_linea(struct archivo_csv *archivo)
{
	for (size_t i = 0; i < archivo->columnas; i++) {
		free(archivo->string[i]);
	}
}
```

Por último, tenemos cerrar archivo que libera lo pedido para el campo string, el struct y cierra el archivo. 
<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
1) Explicar con diagramas cómo quedan dispuestas las estructuras y elementos en memoria.


2) Explicar la complejidad computacional de cada una de las funciones que se piden implementar.

Bueno, empecemos por pokedex.c. La primera fucnion que teneiamos era la de "pokedex_crear", es de las familias o(1) ya que no hay fors ni whiles, ni es recursivo, ni hay dos fors, etc. Y tiene 5 instrucciones, 3 son de stear los campos, 1 de retornar y 1 del malloc. O sea seria o(1) + 5 instrucciones. 

Para la funcion pokedex_agregar_pokemon, vamos a desglozar rapidamente, la complejidad de las funciones auxiliares que tiene. 
La funcion de es_pokemon_repetido, es de la familia O(n) auqnue si desglozamos mas diria que seria o(n*m) donde N es la cantidad de pokemones (del for) y M seria la longitud del strign buscado con el strcmp, pero nos alcanza con decir que es o(n), y tiene unas 4 o 6 instrucciones. O sea o(n*m) + 4/6
Luego tenemos asignar_memoria_pokemon, tengo mis dudas porque tecnicamente todas las funciones son o(1), el problema lo tendriamos en la cantidad de asignacion porque depende de la longitud del strign que es algo que no "controlamos" o podemos anticipar, por lo que por eso podria llegar a ser o(n), por el strlen, aunque yo me inclinaria mas por el lado que es o(1) porque lo que variaria en el peor de los casos, es lo que pedimos de memoria, tiene 3 instrucciones en el caso que malloc falle (tendriamos el malloc, la condicion del if y el return). O sea que seria o(1)+3
Luego tenemos setear_atributos_pokemon, que es de tipo o(n) donde n es tamaño del nombre del pokemon a copiar, y tiene 6 instrucciones (que son los seteos, el aumento en la cantidad y el strcpy).
setear_nuevo_pokemon depende de las funciones "asignar_memoria_pokemon" y "setear_atributos_pokemon", en caso de que analisis sea correcto, esta seria o(1) + o(n) pero "prevalece" o(n) antes que o(1), asi que seria del tipo o(n) + 3 instrucciones.
es_tipo_esperado y es_entrada_adecuada son de la familia O(1), dodne la primera tendria una instruccion compleja (o 2 que serian el validar y el retornar) y la segunda tambien tendira 1 instruccion compleja. 
Por ultimo, tenemos redimensionar_pokedex, que es de tipo o(n)+6 instrucciones aprox, donde N depende de la cantidad a asignar y a mover los elementos del antuguo puntero al nuevo. 

Una vez analisadas estas funciones auxiliares, podemos definir que complejidad computacional tiene pokedex_agregar_pokemon. Por lo que para mi tendria esta forma, o(n*m) + 5 instrucciones(en el caso donde tenga que redimensionar, entra en ese if, llama a redimensionar, luego entra en el if donde es un pokemon no repetido, llama a setear al pokemon, y retorna true ), donde N es la cantiudad de pokemones y M la longitud del nombre del pokemon a agregar, Por lo que seria de las familias o(n). AUqnue en el caso donde se deban contar las instrucciones de las funciones llamadas, tendia mas instrucciones, teniendo aproximandamente, 22 instrcciones 

Por suerte, pokedex_cantidad_pokemones, es de las familias o(1)+2 instrucciones, en el caso de que el puntero sea null, es o(1) porque solo tiene seteos, validaciones y retornos. 


Para pokedex_buscar_pokemon, tenemos que analizar rapidamente las dos funciones que la acompañan; comparar_strs, seria o(n*m)+1 donde N seria la longiidu del primer string y M la longitud de la segunda, y tiene 1 instruccion compleja (o dos si contamos el strcmp y el return del valor). Depsues tenemos calcular_centro, que es o(1)+1 instruccion simple (o 2/3 si contamos el return el calculo y el seteo de centro). Ya con esto, y viedo el codigo, podmeos ver que tenemos una busqueda binaria, que tiene una complejidad computacional de O(log(n)), proque va reduciendo aun mas el problema hatsa llegar a algo absurdamente facil de resolver (que es si ese elemento es el buscado o no) pero vimos que comparar strigns es O(n*m), asi que podriamos decir que seria algo como O(log(n*h*m))  donde m y h son la longitud de los dos nombvres a comparar. Pero supongo que alcanza con decir que es de la familia O(log(n))+14 instrucciones aprox, 14 instrucciones si contamos los llamados como una instruccion. 


Para pokedex_iterar_pokemones, de nuevo tenemos que considerar a las dos funciones que la acompañan. La de intercambiar_pokemones, es o(1)+3 instrucciones, y la de ordenar_pokemones, es O(n^n), porque tiene dos fors, que dependen de la cantidad de pokemones, y como son dos, se terminarian multiplicando y por eso es n*n (cosa que pasa con la inserccion y selecion como metodos de sort).Y ademas tenemos el strcmp que depende de la longitud de las dos strigns que le pasemos, por lo que esat fucnion seria O(n^n *m*h) donde n es la cantidad de pokemones, h y  la longitud de los dos strigns pasados a strcmp. Pero supongo que alcanza con decir que es de las familias O(n^n)+2 instrucciones simples (el if y el llamado al swap). Una vez analizado estas dos funciones, podemos ver que la funcion de iterar_pokemones, seria una combinacion de las dos funciones, quedando algo de este estilo O(n^n*m*h) + O(n) +8/9 instrucciones, capaz esta mal planteado, o erroneo, asi que vamos a dezglosar de donde sale esto. LA parte de O(n^n*m*h), viene por la parte del ordenamiento, ya lo vimos, y la segudan parte viene del while que usamos para ir iterando, capaz solo nos interesa saber que seria algo como O(n^n) + O(n) + 8/9 instrucciones. 

Por ultimo, tenemos la funcion de pokedex_destruir, que es de las familias de O(n) ,por el for, donde n es la cantidad de pokemones, y tiene 3 instrucciones simples. 


Ahora vamos con CSV.C, como no se si deberia incluir el analisis de la complejidad computacional de la parte del tp0, voy a inlcuirla en el siguiente parrafo y lo mas resumidamente posible, si no es de relevancia, salteate al siguiente parrafo del que sigue.

calcular_longitud_subpalabra, O(n) + 4 instrucciones, donde n es la cantidad de letras que hay antes de llegar a un separador u el final de un strign.escribir_subcadena, O(n) + 3 instrucciones donde n es la longitud del substring calculado previamente. liberar_memoria_en_substr, o(1) + 3 instrucciones. escribir_palabras, O(n*m) + 8/9 instrucciones, con n dependiendo de las partes/columnas y m la longitud de las subcadenas. dividir_string, O(n*m) + 4 instrucciones, con n = a la cantidad de columnas/partes, y m la longitud de las substrings. liberar_todo es O(1)+3 instrucciones.

Bien, una vez sacadas esas complejidades computacionales, vamos a lo que nos compete, inicializar_campos y es_archivo_valido son O(1) porque no dependen de un problema variable (un for) con 3 y 2 instrucciones respectivamente. abrir_archivo_csv, por otro lado tambien es O(1)+ 4 instrucciones en el caso donde devolviera null es archivo valido, ya que tendria la validacion de la funcion, el free y el return, mas el malloc inicial. 

Despues en leer_linea_csv, es O(n*m) +11/12 instrucciones aprox, donde n vendria a ser la cantidad de columnas (usados para el while) y m vendria a ser la longitud del substring a dividir, para las instrucciones, tenemos 5 seteo iniciales, llamar a dividir string,1 de la validacion dentro del while lo que hay dentro del else if que serian 2 instrucciones, 1 al aumentar i, y las ultimas 2, llamar a liberar_substr_al_procesar_linea y el return del contador. 

Por ultimo tenemos cerrar_archivo que es O(1)+2 instrucciones, validar y llamar a liberar_todo




