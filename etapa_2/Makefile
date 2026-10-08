# Makefile - Etapa 2: menú principal y wificollector_quit
# Compilar:  make        Ejecutar:  ./main        Limpiar:  make clean

CC = gcc
CFLAGS = -Wall -g

main: main.o input.o wificollector.o
	$(CC) $(CFLAGS) -o main main.o input.o wificollector.o

test_input: test_input.o input.o
	$(CC) $(CFLAGS) -o test_input test_input.o input.o

main.o: main.c input.h wificollector.h
	$(CC) $(CFLAGS) -c main.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

wificollector.o: wificollector.c wificollector.h input.h
	$(CC) $(CFLAGS) -c wificollector.c

test_input.o: test_input.c input.h
	$(CC) $(CFLAGS) -c test_input.c

clean:
	rm -f *.o main test_input

.PHONY: clean
