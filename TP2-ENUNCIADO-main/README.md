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
./tp_hash datos/pokedex.csv
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

El funcionamiento general del juego es el siguiente: tenemos un menú con 4 opciones (por defecto) y, dependiendo de la entrada, se ejecuta la función asociada a dicha entrada. Luego, tienes que jugar atrapando pokemones, es decir, hacer coincidir las posiciones del pokemon y del jugador. Si lo atrapas, se te suma el puntaje asociado al pokemon y tienes la posibilidad de iniciar una racha, que aumenta el multiplicador de tu puntaje si capturas otro pokemon con el mismo color que el último que atrapaste, o si tienen la misma primera letra. Y se tienen 60 segundos para jugar. Una vez acabado el tiempo, se muestra una outro que te muestra el puntaje obtenido, el máximo multiplicador alcanzado y la racha más larga lograda (sin contar el primer pokemon que capturaste). Además, se muestran los pokemones de la racha más larga y una "calificacion" que depende de un promedio entre cantidad de pokemones en racha maxima, multiplicador maximo y puntos obtenidos.

## Respuestas a las preguntas teóricas

Bueno, para este tp se usaron 2 TDAS y el resto de la logica del juego se hizo en el main; asi que vamos con el primero de todos.

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

### Juego/main ¿Posible TDA?

El juego, por suerte, lo hicimos en parte en clase, y otra parte ya la pensé/sufrí cuando tuvimos que hacer otro juego en Algo1/Fundamentos. De hecho, hay funciones que se terminaron reciclando de ese TP (pocas porque ahí usábamos vectores estáticos). Lo que sí puede ser raro es que usamos 4 árboles. ¿Por qué tantos? La respuesta es que 2 son vitales y los otros dos no son extremadamente necesarios. En uno de los árboles importantes guardamos los pokemones que leímos del CSV, y en el otro me voy guardando el monstruo/pokemon que usamos en el tablero, que en sí contiene los datos del pokemon que estaba en el CSV (nombre, color, patrón, etc.), pero le agregamos un campo posición, otro campo color y un campo letra para poder identificarlo en el tablero.

Uno de los árboles es para guardar los pokemones del combo máximo, y después el último sirve para ir guardando los pokemones que voy eliminando, porque me ocurría un problema: si quería eliminar el pokemon en sí del ABB, me tiraba un "invalid read" por querer usar el pokemon para mostrar el último eliminado y lo del multiplicador. Y si no lo liberaba, no me tiraba el "invalid read", pero sí perdía memoria. Terminé definiéndolo así, capaz no es lo más eficiente por el uso de memoria, pero bueno, si guardas todos los pokemones eliminados y después llamas a destruir todo, no pierdes memoria y Valgrind no se te queja.

Ahora bien, ¿por qué elegí ABBs para el juego? Es "fácil", y es que, ya que tenías la función de crear la pokedex, podías reutilizarla fácilmente sin tener que crear las mismas funciones para la lista, que aparentemente muchos eligieron. Aunque algo "grave" que noté es que a veces no elimina bien, o mejor dicho, no elimina un pokemon aunque estés en la misma posición. Quizá haber elegido un ABB para las eliminaciones me jugó en contra. Realmente desconozco por qué no lo elimina, pero ocurre en ciertos momentos, y podría arruinarte un combo, por ejemplo. Si ocurre esto de que no se elimina bien, se bugea y pierde un poco de memoria. Francamente, no sé por qué es. Muy irónicamente, algo similar me pasó en Algo1, que cuando eliminabas un objeto (bombas en ese caso), a mí me pasaba que por algún motivo la bomba tenía un timer de -1, y entonces no explotaba y no perdías vida. Así que, nada, lo comento.

Más allá de ese problema, quizás algo más a cuestionar es por qué lo metí todo en el main. Bien podríamos haber hecho un TDA Juego. La razón por la que no lo hice es que no me parecía que fuera realmente necesario hacer un TDA, ya que no tendrías algo como juego_buscar, juego_agregar, etc. Sino que directamente todo lo que se hace en el juego va en la función de lógica, ya provista, entonces no me parecía netamente necesario. Es decir, si vemos la función de lógica, haces todo el juego: imprimir, mover cosas, la interacción que tienen los objetos, etc. Pero no hay que descartar que quizás hubiese sido más prolijo o incluso correcto el haberlo hecho un TDA, aunque, de nuevo, sería como un TDA con 2-3 funciones, quizás: una función para inicializar campos, otra para la lógica del juego y otra para la impresión. Pero, de nuevo, todo esto se puede hacer en la función de lógica en el main, así que no se me hacía tan necesario hacer un TDA con 2-3 funciones cuando podías hacerlo en el main.

Volviendo al problema que tengo con al eliminacion, tenga que ver con que no encuentra al pokemon al eliminar, porque sino no tiene explicacion el porque no se elimina correctamente, pero no lo pude solucionar. Probablemente no debe estar encontrando el pokemon a eliminar. Posiblemente hubiera ameritado mas una lista, por el hecho de que la a la hora de eliminar no pasas por un comparador, pero no lo se. Yo lo plantee con aeboles porque me gustan mas y nada, ya tenias funciones del TDA pokedex para usar en un ABB.

## ¿ Y Como y en que usamos los TDAS ?

Bueno, ya vimos que la Lista no la use, posiblemnete hubiera sido conveniente haberla usado. Vimos que el TDA Hash, lo usamos solo para guardar la entrada y la funcion asociada al menu. Y vimos que el ABB fue el que mas use, ya que teniamos uno para almacenar los pokemones que se leian del csv, otro para ir almacenando los pokemones que se mostarran en el tablero, otro para almacenar la racha mas larga asi depsues podemos imrpmir los pokemones de dicha racha. Y por ultimo teniamos uno que era para almacenar los pokemones eliminados y al finalizar el programa, los podemos destruir sin tener invalid read o peridadas de memoria. Este es mas que nada, porque si queria eliminar al pokemon que corresponde, no liberaba nunca lo pedido para almacenar al pokemon en el ABB, y si hacia free, en el loop de logca, intentaban usar el puntero a pokemon_eliminado en lo del multiplicador y para imprmir abajo lo del ultimo pokemon atrapado, asi que probe haciendo un nuevo arbol e ir alamcenando los pokemones asi cuando se terminaba el programa, podrias destruir y liberar todo sin tener perdida de memoria ni invalid reads. (Auqnue cabe resaltar que a veces cuando no elimina bien tinde a no lberar algun pokemon, pero como no lo pude arreglar, lo comento por las dudas.).
