<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP 2

## Repositorio de Joaquin Ezequiel Mendez Archerrizo - 111767 - jmendeza@fi.uba.ar.

- Para compilar:

```bash
make pruebas_alumno
make tp2
```

- Para ejecutar:

```bash
./pruebas_alumno 
./tp2 datos/pokedex.csv
```

- Para ejecutar con valgrind:
```bash
make valgrind-alumno
make valgrind-tp2
```
- Para compilación y ejeccución con valgrind (version rapida):
```bash
make correr-pruebas
make correr-tp
```

---
##  Funcionamiento

El funcionamiento general del juego es el siguiente: tenemos un menú con 4 opciones (por defecto) y, dependiendo de la entrada, se ejecuta la función asociada a dicha entrada. Luego, tienes que jugar atrapando pokemones, es decir, hacer coincidir las posiciones del pokemon y del jugador. Si lo atrapas, se te suma el puntaje asociado al pokemon y tienes la posibilidad de iniciar una racha, que aumenta el multiplicador de tu puntaje si capturas otro pokemon con el mismo color que el último que atrapaste, o si tienen la misma primera letra. Y se tienen 60 segundos para jugar. Una vez acabado el tiempo, se muestra una outro que te muestra el puntaje obtenido, el máximo multiplicador alcanzado y la racha más larga lograda (sin contar el primer pokemon que capturaste al empezar la racha). Además, se muestran los pokemones de la racha más larga y una "calificacion" que depende de un promedio entre cantidad de pokemones en racha maxima, multiplicador maximo y puntos obtenidos.

## Respuestas a las preguntas teóricas

Bueno, para este tp se usaron 3 TDAS y el resto de la logica del juego se hizo en el main; asi que vamos con el primero de todos.

### TDA MENU

Este TDA estaba cantado, digo, creo que desde el inicio de la cursada ya se venía cocinando porque mencionaban que siempre había problemas porque no sabían cómo hacer un TDA de Menú (y también porque hay una sección concreta en el enunciado :O).
Así que para este TDA decidimos usar un TDA Hash, más que nada porque está bueno para hacer búsquedas rápidamente, y sumale que hay de 4 a 8 opciones iniciales, salís ganando porque la búsqueda para las opciones es muy rápida. Y viene bien porque la gracia del menú es que vos ingresas una opción y solo la tenés que buscar, en este caso.
En nuestro caso fue fácil eso, pero lo difícil fue cómo podíamos hacer para que vos seleccionaras una opción y que directamente ejecutara una función. Es decir, que el Hash tendría como clave la opción y como valor una función. Tuvimos bastantes problemas porque nosotros metíamos directamente la función como valor, y se tendía a romper. Así que decidí meter un struct que adentro tuviera la función y un ctx que el usuario quisiera pasarle a la función; medio inútil guardarlo el ctx en el struct de opciones, porque no lo terminé usando, pero nunca está de más.
Ahora bien, podemos ver que la gracia del TDA Menú está en dos funciones concretas:

1) **menu_agregar_opciones**
2) **menu_ejecutar_entrada**

La primera es más que nada para cargar la opción junto con la función que quieras asociar a esa entrada, junto con un ctx que se usaría más que nada para poder ejecutar dicha función, manteniendo genérica la función que le pasas para almacenar en el hash. Claro que internamente, la pasamos a un string, agregándole un 0 al final y así podemos almacenar la clave.

La segunda función es muy útil, ya que recibimos una opción, buscamos dicha opción en el menú y, una vez que la encontramos, ejecutaríamos la función asociada a la clave. Intentamos acceder al campo del struct que contiene la función y se ejecuta. Realmente fue a prueba y error esta parte, porque la parte más difícil es que se ejecutara la función una vez que buscabas la opción en el menú. Pero considero que termina siendo funcional para lo que se necesita.

Luego tenemos funciones extra, como eliminar una opción y obtener la función asociada, o más bien, que se ejecute la misma. No las usamos, pero tampoco están de más.

También, un problema que tuve fue al destruir, porque quería liberar el valor que guardó en el hash, pero necesitas el destructor y no me parecía que el usuario debiera hacerle free a eso. Entonces, de nuevo, probando, terminé pasándole a la función de destruir todo del hash, como función destructora, free. Funcionó, así que nada, quería comentar eso nomás.

### TDA POKEDEX

Para este TDA, decidimos usar un ABB, más que nada porque en una de las opciones, que es apretar la "P", debes mostrar los pokemones en orden alfabético. En todos los TP que hicimos, solo dos se mostraban en orden alfabético: el del TP1, donde usábamos un vector dinámico, así que quedaba descartado, y el ABB, que si lo recorriéramos inorden sería lo que necesitábamos. Así que la elección era obvia. Tenemos las funciones de agregar, eliminar y buscar. Pero las más destacables serían:

1) **pokedex_mostrar_ordenados**
2) **pokedex_devolver_pokemon_aleatorio**
3) **pokedex_cargar_pokemones_desde_csv**
4) **pokedex_iterar**
5) **pokedex_agregar_monstruo**
6) **pokedex_eliminar_monstruo**


Vamos por partes. La primera función sirve más que nada para hacer esto que pide el menú: si apretas la "P", te muestra los pokemones que hay en la pokedex, pero los recorre en orden inorden, así se imprimen alfabéticamente ordenados.

La segunda es más compleja, ya que nosotros creamos un número al azar con rand (que no exceda la cantidad de pokemones en la pokedex), armamos un ctx, con un índice aleatorio y un puntero a pokemon. Después, nosotros iteramos postorden (más que nada porque sería el más "aleatorio") y vamos avanzando en el índice hasta que este sea igual al número que nos generamos aleatoriamente. Nos quedamos con el pokemon que había en ese nodo en el que estábamos iterando. Lo que sí, lo caótico fue esta línea:
```c
pokemon_t **resultado = ((pokemon_t ***)ctx)[2];
```
Realmente fue costoso lleagr a esto ya que siempre tendia a romperse o no me generaba bien el pokemon y me devolvia cualquier cosa, o se me quejaba el compilador, entones probando y probando llegue a esto y funciono, asi que nada, lo comento por arriba eso.

Luego tenemos pokedex_cargar_pokemones_desde_csv, que lo que hace es muy similar a lo que hacíamos en otros TP, donde leemos el CSV que nos pasan como parámetro. Pero acá tomé quizás una decisión polémica, y es no hacerlo tan genérico, ya que internamente nosotros usamos como ctx los campos/secciones que tendría el archivo, es decir, el nombre, color, puntaje, etc. Es decir, no le damos la libertad al usuario de elegir cómo va a estar dispuesto el pokemon que vamos a setear, y quedaría fijo a un tipo de archivo CSV con el formato: nombre, puntaje, color, patrón. Y no se podría sacar o agregar nada más. Aunque bueno, suponiendo que se charló de antemano con el usuario y pidiera hacer cambios, no sería tan complicado cambiarlo, aunque probablemente hubiera sido mejor haberlo hecho más genérico.

Aunque lo que me trajo problemas es que debemos pedir memoria y copiar los strings que nos pasen en los respectivos campos. El problema es que yo necesitaba liberar esa memoria, así que tomé la decisión de relegarle al usuario la responsabilidad de liberarlo. Es decir, que use destruir_todo y le pase a la función lo que haya reservado de memoria, y que libere el nombre, color y patrón del pokemon. Es polémico porque se me hace raro que el usuario deba liberar memoria que tú pediste, pero fue la única solución que se me ocurrió para que así el usuario tenga la capacidad de, si quiere, pedir memoria para algún elemento más del pokemon que lo requiera. De esta manera, puede meter en su función destructora todo lo que quiera liberar, más lo que le pido que libere. Porque si no, le saco la capacidad de liberar otros campos si quiere reservar memoria para alguna otra cosa.

Después, las siguientes tres funciones sirven más para el juego. Por ejemplo, la de pokedex_iterar sirve para ir iterando la pokedex en preorden, más que nada para iterar de forma más ordenada los pokemones que tienes en el árbol.

Las funciones agregar_monstruo y eliminar_monstruo son para agregar y eliminar los pokemones que usamos en el terreno de juego (no se usan para el menú), y sirven más que nada para el juego esas funciones.

### TDA RACHA

Este TDA me puso las cosas complicadas. Pero primero, ¿qué se supone que hace este TDA y para qué sirve? La idea detrás de este TDA es abstraer el tema de las rachas de la lógica del main, utilizando el TDA lista que ya habíamos creado. Más que nada, esto se hace porque en un ABB no se podía implementar de manera eficiente (ya veremos por qué), y en un hash era difícil hacerlo. Así que me quedó la lista como opción para el descarte. Pero, ¿realmente es necesario abstraer algo así? La respuesta no fue tan fácil, ya que una racha es, relativamente abstracta, pero no lo suficiente.

Lo que más me impulsó a crear este TDA fue que no quería que en el main aparecieran las funciones de la lista. Es decir, quería encapsular todo el TDA lista dentro del TDA racha. Además, necesitaba una función particular que era la de racha_vaciar, que quería usar para hacer más eficiente un problema que tenía en el "prototipo" de la racha que se encontraba en el main.

Contando un poco más, originalmente mi racha vivía en el main (tanto la lógica como todas las funciones necesarias). Era un ABB, principalmente porque me empeciné en reutilizar las funciones que teníamos, como la de pokedex_crear. Lo que hacíamos era que, si se superaba el multiplicador máximo, agregábamos al Pokémon al ABB y luego lo iterábamos en la otra lista. Sin embargo, obviamente estaba mal porque, primero, no garantizaba que los pokemones estuvieran en el orden en que fueron atrapados, y segundo, solo agregaba cuando se superaba el multiplicador máximo.

Entonces, como nos dieron más tiempo, decidí arreglarlo. Traje la idea de la lista y empecé a probar distintas formas de hacerlo. En clase, se sugirió usar dos listas: una para guardar la racha actual y otra para guardar la racha máxima registrada. Entonces probé y llegué a una solución rudimentaria pero funcional: la idea era crear la lista para la racha actual, llenarla hasta que se rompiera la racha, y si no existía una racha máxima, creaba una lista para la misma y movía todos los elementos de la lista de racha actual a la lista de racha máxima. Luego destruía la racha actual y la volvía a crear. Si en algún momento la racha máxima se superaba, destruía la lista de la racha máxima, creaba una nueva lista y movía los elementos de la racha actual a esa nueva lista.

Obviamente, esta era una solución muy ineficiente tanto en términos de asignación de memoria como en el uso de la misma. Así que pensé en algo como una lista_vaciar pero para las rachas. Y como también quería encapsular todo lo relacionado con la lista que no estuviera disponible en el main, decidí crear este TDA.

Una vez creado el TDA, llegué a la solución que tenemos en actualizar_multiplicador_y_racha, donde, en lugar de destruir y crear una lista, vaciamos las listas dependiendo del caso. Esto termina siendo mucho más eficiente, ya que siempre usamos las mismas dos listas. Luego, dependiendo del caso, iteramos sobre una lista u otra.

De todas formas, la estructura de este TDA es similar a la de la pokedex: tiene funciones para insertar, eliminar, iterar, y la función "estrella" es la de vaciar, que básicamente elimina el primer elemento de la racha hasta que no quede ningún elemento. No incluí una función de "buscar" porque no veía la necesidad de buscar un elemento dentro de la racha, aunque podría haber sido programada si fuera necesario.

### Juego/main ¿Posible TDA?

El juego, que por suerte, hicimos una parte en clase, y otra parte ya la pensé/sufrí cuando tuvimos que hacer otro juego en Algo1/Fundamentos. De hecho, hay funciones que se terminaron reciclando de ese TP (pocas porque ahí usábamos vectores estáticos) y muchas cosas de la lógica en general fueron pensadas en base a esa "experiencia pasada", por ejemplo que para setear los pokemones, imprimirlos, eliminarlos, hacer que se muevan, etc. Todo debías iterar, el problema es que antes eran vectores o a lo sumo un vector dinámico. Que podés hacerlo todo con uno o varios for. Pero acá no podés usar vectores sino los 3 TDAs que hicimos en la cursada.

Yo decidí usar árboles para la parte de almacenar al monstruo (o al pokemon que es jugable, no el pokemon de que está para el menú), y de ahí hacer todo lo que necesito, ¿necesito imprimirlos? Puedo usar iterar_pokedex, ¿necesito moverlos? Uso iterar_pokedex, y así con las otras partes que mencioné.

Lo que sí puede ser raro es que usamos 3 árboles. ¿Por qué tantos? La respuesta es que 2 son vitales y uno es de "respaldo", por así decirlo. En uno de los árboles importantes guardamos los pokemones que leímos del CSV, y en el otro me voy guardando el monstruo/pokemon que usamos en el juego, que en sí contiene los datos del pokemon que estaba en el CSV (nombre, color, patrón, etc.), pero le agregamos un campo posición, otro campo color (capaz redundante, pero sino no se seteaba bien el color del pokemon) y un campo letra para poder identificarlo en el tablero.

Después, el último sirve para ir guardando los pokemones que voy eliminando, porque me ocurría un problema: si quería eliminar el pokemon en sí del ABB que tiene a los pokemones del juego, me tiraba un "invalid read" por querer usar el pokemon para mostrar el último eliminado y verificar lo del multiplicador. Y si no lo liberaba, no me tiraba el "invalid read", pero sí perdía memoria. Así que se me ocurrió la idea de meterlos en un árbol auxiliar, y cuando terminaba el juego, lo destruía así no tenés ni invalid read ni pérdida de memoria. Es verdad que no es lo más eficiente, porque tener que usar más memoria para un árbol que en sí no sirve para nada más que para no tener errores en valgrind, pero como acá no nos preocupamos tanto por el uso de memoria (que creo que sería complejidad espacial), fue la mejor solución que se me ocurrió. Sacrificamos espacio para poder liberar todo correctamente y no tener invalid read.

Ahora bien, ¿por qué elegí ABBs para el juego? La respuesta es "fácil": ya tenías la función de crear la pokedex, y podías reutilizarla fácilmente sin tener que crear las mismas funciones para una lista, que aparentemente muchos eligieron.

Sin embargo, tuve un problema donde, estando en la misma posición del pokemon, no se lo capturaba. Es decir, no te sumaba puntos ni aumentaba la racha. Incluso el último pokemon (el último en ser eliminado) marcaba el texto de "no capturaste a ningún pokemon aún", lo que indicaba que el puntero doble que pasábamos a la función de eliminación se quedaba en NULL. Esto significaba que no encontraba a dicho pokemon, y como la lógica del juego dependía de que la eliminación devolviera True para aumentar el puntaje, el hecho de que devolviera False rompía esa parte del sistema.

Probé de todo hasta que teoricé que el problema podía estar en el comparador, porque me fijaba que los parámetros no fueran NULL y pedía imprimir algo si la función de eliminar_pokemon y como no se imprimía nada, entonces la función estaba devolviendo false y como el último pokemon se seteaba como NULL, quería decir que el pokemon que quería eliminar, no estaba siendo encontrado. Originalmente, usábamos como parámetro de comparación el nombre, pero podía ocurrir (y era bastante frecuente) que se eliminaran varios pokemones con el mismo nombre. Esto sucedía debido al orden de inserción: por ejemplo, si teníamos dos Charmander y capturabas uno, podía pasar que en el ABB estuviera primero el que no debías capturar, entonces lo eliminaba, pero como seguías compartiendo posición con otro pokemon, iba y recién ahí eliminaba al correcto.

Decidí entonces cambiar el criterio de comparación a posición, ya que tenía más sentido que usar el nombre. Sin embargo, el problema persistía: al no encontrar correctamente al pokemon, el puntero al último eliminado quedaba en NULL, y esto podía arruinar un combo sin que fuera responsabilidad del jugador.

Finalmente, se me ocurrió asignarle a cada pokemon un ID único generado aleatoriamente. Modifiqué el comparador para que utilizara el ID como primer parámetro, y en el caso extremadamente improbable de que dos IDs coincidieran, que comparara por posición. Esto solucionó el problema, ya que ahora el ABB podía distinguir correctamente entre pokemones con el mismo nombre y asegurarse de eliminar al correcto. Y parece que anda bien, o sea, mejor que antes seguro, porque ahora no te puede pasar que tenías una racha de 4 y capturabas un pokemon que aumentara a 5 la racha y, por alguna razón, se acabe tu racha y aparezca que no se habían capturado pokemones aún, sino que ahora se comporta más estable.

Más allá de ese problema, quizás algo más a cuestionar es por qué lo metí todo en el main. Bien podríamos haber hecho un TDA Juego. La razón por la que no lo hice es que no me parecía que fuera realmente necesario hacer un TDA. Me explico, en los otros TDA los creabas porque eran cosas pequeñas y manejablles (exceptuando la pokedex que hacia varias cosas pero no tantas en comparacion al juego), tampoco me vi en la obligacion de encapsular alguna implementacion de otro TDA como me paso con la racha. Asi que vi senti que era mas comodo hacerlo en el main, auqnue vino con la enorme desventaja de ocuparme una cantidad bastante abrumadora de lineas. Capaz hubiese sido optimo un TDA que no se tenga las funciones de inicializar juego, logica, imprimir terreno y no se, mostar estadisticas. Pero el problema es que era muy dificil abstraer el juego ya que tenia muchas depednencias, tenes el terreno, los pokemones del juego, el jugador y estructuras y campso extras para el propio juego. Ademas como la funcion de logica ya estaba en el main, no me parecía netamente necesario. Es decir, si vemos la función de lógica, haces todo el juego: imprimir, mover cosas, la interacción que tienen los objetos, etc. Pero no hay que descartar que quizás hubiese sido más prolijo o incluso correcto el haberlo hecho un TDA. Pero bueno, es cuestion de diseños pero este partcularmente, era mas dificl de que decision tomar. 

Una pequeña cosa que quería mencionar es el uso del tipo de dato volatile, que utilizo para la outro o cuando se acaba el juego. Lo que quería hacer era un delay para que pareciera que se están procesando los datos, así que pensé en un bucle que haga muchas iteraciones para que parezca que está cargando algo. El problema fue cuando llegué a long y alcanzaba el máximo del rango de representación que tenía ese tipo de dato. Busqué en algún lado si había algo que pudiera ayudar a que el for no se procesara tan rápido, y terminé dando con este tipo de dato, que en teoría es C99, y lo que hace es básicamente decirle al compilador que no optimice el bucle for, o al menos eso entendí.

Pensándolo más fríamente, no sé por qué querrías que no se optimicen las cosas a la hora de hacer un bucle, pero como necesitaba hacer un efecto de delay, me sirve. Aunque quizás sea perjudicial en términos de rendimiento, porque estás haciendo trabajar de más al procesador al tener que hacer esas iteraciones sin optimización por parte del compilador. Probablemente exista algo en la biblioteca  en time.h (u otra) que usamos para el srand y el rand, que haga un mejor trabajo. Pero bueno, supongo que está bien hacer estos experimentos poco comunes.

Despues no creo que amerite mucho hablar de la logica, porque en general, como comente antes, parte la hicimos en clase y otra parte la pensamos con el otro juego que tuve que hacer para algo1. Y mas alla de las dificultades que mencione antes, no paso nada mas que quiera recalcar.

## ¿Como y en que usamos los TDAS hechos durante la cursada?

Bueno, vimos que en total usamos: 1 hash, que es el menú, para ir almacenando las opciones junto a una función que se ejecuta si se elige cierta entrada. Luego, 2 listas: una para almacenar la racha que está ocurriendo en ese momento, donde vamos almacenando pokemones siempre que la racha no se rompa, y la otra lista para almacenar la racha máxima alcanzada, que se va actualizando en caso de que la racha actual supere la máxima. Y por último, tuvimos 3 ABB: uno para los pokemones que leíamos del CSV y que luego usábamos para imprimir en orden alfabético si el usuario lo pedía en el menú; el otro árbol lo usábamos para almacenar el pokemon del juego junto a su posición, un ID, la inicial y el color, que nos servía para controlar el comportamiento de los pokemones en el juego; y el último árbol nos servía para almacenar los pokemones que íbamos eliminando, de forma que, una vez que se acaba el programa, podamos liberar todos esos datos sin tener pérdida de memoria ni "invalid reads".

 