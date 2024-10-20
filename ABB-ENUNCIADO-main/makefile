VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CC = gcc
CLANG_FORMAT = clang-format

all: clean valgrind-alumno

valgrind-alumno: pruebas_alumno
	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

pruebas_alumno: src/*.c pruebas_alumno.c
	$(CC) $(CFLAGS) src/*.c pruebas_alumno.c -o pruebas_alumno
	
correr-pruebas:
	$(CC) $(CFLAGS) src/*.c pruebas_alumno.c -o pruebas_alumno && valgrind $(VALGRIND_FLAGS) ./pruebas_alumno
	
	
tp-abb: src/*.c tp_abb.c
	$(CC) $(CFLAGS) src/*.c tp_abb.c -o tp_abb
	
valgrind-tp-abb: tp_abb
	valgrind $(VALGRIND_FLAGS) ./tp_abb ejemplos/pokedex.csv

valgrind-ejemplo: ejemplo
	valgrind $(VALGRIND_FLAGS) ./ejemplo

ejemplo: src/*.c ejemplo.c
	$(CC) $(CFLAGS) src/*.c ejemplo.c -o ejemplo

clean:
	rm -f pruebas_alumno ejemplo tp_ab
	
formatear-pruebas:
	$(CLANG_FORMAT) -i -style=file pruebas_alumno.c
	
formatear-abb:
	$(CLANG_FORMAT) -i -style=file src/abb.c
	
formatear-tp:
	$(CLANG_FORMAT) -i -style=file tp_abb.c
	
correr-tp:
	$(CC) $(CFLAGS) src/*.c tp_abb.c -o tp_abb && valgrind $(VALGRIND_FLAGS) ./tp_abb ejemplos/pokedex.csv
	
	
zipear:
	cd ../ && zip -r ABB-ENUNCIADO-main.zip ABB-ENUNCIADO-main
	

