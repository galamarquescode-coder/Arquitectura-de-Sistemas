# Makefile - Etapa 4: lectura de un bloque de fichero
# Compilar:  make        Ejecutar:  ./main        Limpiar:  make clean

CC = gcc
CFLAGS = -Wall -g

main: main.o input.o wificollector.o
	$(CC) $(CFLAGS) -o main main.o input.o wificollector.o

test_input: test_input.o input.o
	$(CC) $(CFLAGS) -o test_input test_input.o input.o

test_cell_print: test_cell_print.o cell.o
	$(CC) $(CFLAGS) -o test_cell_print test_cell_print.o cell.o

test_cell_read: test_cell_read.o cell.o
	$(CC) $(CFLAGS) -o test_cell_read test_cell_read.o cell.o

main.o: main.c input.h wificollector.h
	$(CC) $(CFLAGS) -c main.c

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

wificollector.o: wificollector.c wificollector.h input.h
	$(CC) $(CFLAGS) -c wificollector.c

test_input.o: test_input.c input.h
	$(CC) $(CFLAGS) -c test_input.c

test_cell_print.o: test_cell_print.c cell.h
	$(CC) $(CFLAGS) -c test_cell_print.c

cell.o: cell.c cell.h
	$(CC) $(CFLAGS) -c cell.c

test_cell_read.o: test_cell_read.c cell.h
	$(CC) $(CFLAGS) -c test_cell_read.c

clean:
	rm -f *.o main test_input test_cell_print test_cell_read

.PHONY: clean
