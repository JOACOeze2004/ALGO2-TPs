VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CC = gcc
CLANG_FORMAT = clang-format

all: clean valgrind-alumno

valgrind-alumno: pruebas_alumno
	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

pruebas_alumno: src/*.c pruebas_alumno.c
	$(CC) $(CFLAGS) src/*.c pruebas_alumno.c -o pruebas_alumno

valgrind-ejemplo: ejemplo
	valgrind $(VALGRIND_FLAGS) ./ejemplo

clean:
	rm -f pruebas_alumno ejemplo
		
formatear-pruebas:
	$(CLANG_FORMAT) -i -style=file pruebas_alumno.c
	
formatear-lista:
	$(CLANG_FORMAT) -i -style=file src/lista.c
	
formatear-pila:
	$(CLANG_FORMAT) -i -style=file src/pila.c
	
formatear-cola:
	$(CLANG_FORMAT) -i -style=file src/cola.c
	
formatear-tp:
	$(CLANG_FORMAT) -i -style=file tp_lista.c
	
tp-lista: src/*.c tp_lista.c
	$(CC) $(CFLAGS) src/*.c tp_lista.c -o tp_lista
	
valgrind-tp-lista: tp_lista
	valgrind $(VALGRIND_FLAGS) ./tp_lista ejemplos/pokedex.csv
	
correr-tp:
	$(CC) $(CFLAGS) src/*.c tp_lista.c -o tp_lista && valgrind $(VALGRIND_FLAGS) ./tp_lista ejemplos/pokedex.csv

