VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
ENGINECFLAGS =-Wall -Werror -O2 -g
CC = gcc
CLANG_FORMAT = clang-format

all: clean valgrind-alumno valgrind-tp2

valgrind-alumno: pruebas_alumno
	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

pruebas_alumno: src/*.c pruebas_alumno.c engine
	$(CC) $(CFLAGS) src/*.c pruebas_alumno.c engine.o -o pruebas_alumno

valgrind-tp2: tp2
	valgrind $(VALGRIND_FLAGS) ./tp2 datos/pokedex.csv

engine:
	$(CC) $(ENGINECFLAGS) -c extra/engine.c -o engine.o

tp2: engine
	$(CC) $(CFLAGS) src/*.c tp2.c engine.o -o tp2

clean:
	rm -f pruebas_alumno tp2 engine.o
	
formatear-pruebas:
	$(CLANG_FORMAT) -i -style=file pruebas_alumno.c
	
formatear-menu:
	$(CLANG_FORMAT) -i -style=file src/menu.c
	
formatear-pokedex:
	$(CLANG_FORMAT) -i -style=file src/pokedex.c

formatear-todo:
	$(CLANG_FORMAT) -i -style=file src/menu.c && $(CLANG_FORMAT) -i -style=file src/menu.c && $(CLANG_FORMAT) -i -style=file src/pokedex.c
	
correr-pruebas:
	$(CC) $(CFLAGS) src/*.c pruebas_alumno.c -o pruebas_alumno && valgrind $(VALGRIND_FLAGS) ./pruebas_alumno
