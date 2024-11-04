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
	
tp-hash: src/*.c tp_hash.c
	$(CC) $(CFLAGS) src/*.c tp_hash.c -o tp_hash
	
valgrind-tp-hash: tp_hash
	valgrind $(VALGRIND_FLAGS) ./tp_hash ejemplos/pokedex.csv

valgrind-ejemplo: ejemplo
	valgrind $(VALGRIND_FLAGS) ./ejemplo

ejemplo: src/*.c ejemplo.c
	$(CC) $(CFLAGS) src/*.c ejemplo.c -o ejemplo

clean:
	rm -f pruebas_alumno ejemplo
	
formatear-pruebas:
	$(CLANG_FORMAT) -i -style=file pruebas_alumno.c
	
formatear-abb:
	$(CLANG_FORMAT) -i -style=file src/hash.c
	
formatear-tp:
	$(CLANG_FORMAT) -i -style=file tp_hash.c
	
correr-tp:
	$(CC) $(CFLAGS) src/*.c tp_hash.c -o tp_hash && valgrind $(VALGRIND_FLAGS) ./tp_hash ejemplos/pokedex.csv
	
	
zipear:
	cd ../ && zip -r HASH-ENUNCIADO-main.zip HASH-ENUNCIADO-main
