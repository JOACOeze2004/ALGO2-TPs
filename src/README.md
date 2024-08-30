**DOCUMENTACIÓN**

En este README, voy a explicar brevemente cómo funciona el código y la lógica detrás del mismo. Sin embargo, también se puede ver más a fondo el código, donde están las "pre y postcondiciones" de cada función (no sé si aún es necesario hacerlo, pero para mantener buenas prácticas lo hago de todas formas).

**FUNCIONAMIENTO GENERAL**

Como bien dice el enunciado y el título del TP0, el objetivo era hacer la función .split() de Python, pero en C, ya que no existe una función que separe el string en varios "substrings" o elementos de un vector de strings delimitados por un separador que se le pasa a la función.

Eso es lo que hace una de las dos funciones "principales", que es dividir_string. Le pasamos un string y un delimitador para que haga el split. Dentro de esta función, podemos dividirla en 3 funciones auxiliares.

**FUNCIONAMIENTO Y LÓGICA DE LAS FUNCIONES**

La primera es la de inicializar el struct de Partes. Dentro de ella, vamos a empezar pidiendo memoria para el struct. Vi necesario hacerlo ya que, al no pasarlo a la función general como un puntero, no sobreviviría nada de la inicialización una vez que se termine de ejecutar la función. Luego inicializamos los otros dos campos. Algo que probablemente te llame la atención es por qué inicializo el campo cantidad en 0, y tiene una explicación. Podemos ver que más abajo en la función principal existe una función que cuenta la cantidad de delimitadores, así sabríamos cuántas subcadenas vamos a tener. Esto es en caso de que el string pasado a la función principal fuera NULL, y si en el campo cantidad llamáramos a la función, lanzaría un segmentation fault. Así que, para no repetir código y evitar errores, preferí inicializarla como 0 y, si el string no es NULL, ahora sí ir a la función de contar delimitadores.

Luego tenemos la función de contar delimitadores, que recorre el string pasado a la función y, si la letra de la palabra es un delimitador, aumenta en 1 el contador de separadores. Al llamarla en la función principal, aumentamos en 1 ya que así tendríamos la cantidad correcta de partes, o sea, de subcadenas del string. Un ejemplo más claro sería que, si tienes esta línea: "Hola, mundo, ¿cómo estás?" y el delimitador fuera la ",", nosotros contaríamos 2 comas, pero ¿qué ocurre con "¿cómo estás?"? No la estaríamos contabilizando como parte porque el conteo llegaría hasta "mundo". Es más que nada por eso que se aumenta en 1 el valor; tal vez podríamos mover esta lógica a su respectiva función.

Luego pedimos memoria para el campo string con realloc (solo para aprovechar que lo seteamos como NULL, entonces funciona como un malloc). Eso sí, no estoy seguro de que sea correcto usar una variable auxiliar para hacer realloc y, en caso de fallo, liberarla, y si no falla, setear el campo string como esa variable.

Por último, tenemos la función más extensa (y la más difícil), escribir_palabras. Básicamente, esta función se encarga de ir reservando memoria para cada substring (o elemento con las palabras separadas). Pedimos espacio de longitud de string +1, y vamos por partes: el +1 sirve para agregar al final el "\0", y la longitud de palabra es una variable que llama a la función calcular_longitud_subpalabra, que recibe el string y un puntero a un iterador o un índice que usamos para recorrer la palabra. Contamos siempre que la letra no sea el separador y no haya finalizado el string. Así es como conseguiríamos la longitud del substring o de la cadena nueva sin el separador.

¿Por qué por referencia? Sencillo, necesitamos que el valor del iterador se mantenga al finalizar la función porque, si no, podríamos cortar prematuramente la palabra ya que calcularíamos mal la longitud de la misma y no copiaríamos todo.

Volviendo a escribir_palabras, llamamos a escribir_subcadena, que, como su nombre indica, usa otro índice para ir copiando la nueva cadena. Al finalizar la iteración, le agregamos el '\0' para marcar que es un string. (Podríamos usar la función strcpy, pero como hicimos una versión casera en clase, decidí usarla acá también porque se podía readaptar a esta situación). En caso de que la letra sea un separador, aumentamos en uno el índice letra_actual. Es cierto que puede ser un poco confuso tener varios iteradores, uno que es i (el principal, que marca la posición en el string) y letra_actual, que sirve más que nada para los casos donde la letra es un separador. Opté por hacerlo así, pero tal vez podríamos simplificar las cosas.

Por último, en caso de que malloc falle al asignar memoria para el substring, cortamos el while (porque error sería igual a 1) y manejamos el error liberando toda la memoria previamente asignada, primero la de string y luego la de Partes, EN ESE ORDEN (porque si no, se perdería alguna asignación y no podríamos recuperar esa memoria).

Y una vez pasadas esas 3 funciones, retornamos el struct Partes y pasamos a la otra función principal, que sería para liberar toda la memoria pedida.

**APRECIACIÓN FINAL**

Pido disculpas de antemano si no cumplo con la documentación adecuada, es la primera vez que tenemos que hacer algo así, y estaría bueno que me corrigieran sobre cómo se hace una buena documentación. Capaz fui muy extenso al explicar mis funciones, capaz no se entendió nada porque no fui claro, o tal vez no expliqué con suficiente detalle qué hace cada función, etc. Así que, nada, cualquier feedback sobre documentación (o una forma de hacer X función más modular, eficiente o replanteamientos de las mismas) se agradece :D.
