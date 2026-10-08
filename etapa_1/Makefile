# Makefile - Etapa 1: entrada de datos (módulo input)
# Compilar:  make        Ejecutar:  ./main        Limpiar:  make clean

CC = gcc
CFLAGS = -Wall -g

test_input: test_input.o input.o
	$(CC) $(CFLAGS) -o test_input test_input.o input.o

test_input.o: test_input.c input.h
	$(CC) $(CFLAGS) -c test_input.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

clean:
	rm -f *.o test_input

.PHONY: clean
