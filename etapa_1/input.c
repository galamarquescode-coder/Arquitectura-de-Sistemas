#include <stdio.h>
#include <string.h>
#include "input.h"

/* Tamaño máximo de una línea leída del teclado (incluye el '\0' final) */
#define INP_MAX_LINE 80

/*
 * input_read_line()
 * Lee una línea del teclado y la guarda en "line" sin el salto de línea.
 * Si el usuario escribe más de "size - 1" caracteres, el resto se descarta
 * para que no contamine la siguiente lectura.
 * Devuelve 1 si se leyó una línea y 0 si se acabó la entrada (EOF).
 */
int input_read_line(char line[], int size)
{
	int length; 
	int character;

	if (fgets(line, size, stdin) == NULL)
	{
		return 0;
	}

	length = strlen(line);
	if (length > 0 && line[length - 1] == '\n') //chequea qué valor es la penúltima posición, si es un \n, lo cambia por un 0. Elimina
	{
		line[length - 1] = '\0'; 
	}
	else
	{
		/* La línea no cabía entera: se tira lo que sobra hasta el '\n' */
		character = getchar(); //inicializamos. 
		while (character != '\n' && character != EOF) //limpiar el buffer para que solo tengamos la info que le ponemos nosotros. 
		{
			character = getchar(); //guarda los valores antes de eliminarlos
		}
	}

	return 1;
}

/*
 * input_ask_number()
 * Muestra "question" y pide un número entero entre "min" y "max" (incluidos).
 * Repite la pregunta hasta que la línea contiene un único número válido.
 * Devuelve el número, o INP_EOF si se acaba la entrada (por eso "min" debe
 * ser mayor o igual que 0).
 */
int input_ask_number(const char question[], int min, int max)
{
	char line[INP_MAX_LINE]; //el tamaño máximo de un array es el 80. 
	char extra; //tipos de dato: char, lo llamamos extra
	int number; //tipo de dato: int, lo llamamos number

	while (1) //poner un 1 es como poner un "true". NO NOS DEJAN PONER BOOLEANOS. 
	//LOCKIN: En C, no podemos poner datos booleanos. Solo si ponemos 
	{
		printf("%s", question); //Esto imprime la pregunta en la pantalla. 
		if (!input_read_line(line, INP_MAX_LINE)) //lee la pregunta, la guarda en "line" que es un arreglo de caractéres tal y como lo hemos puesto. Siempre y cuando no exceda el limite de char. 
		{
			return INP_EOF; //si no se puede leer/excede límite. 
		}

		/* sscanf devuelve 1 solo si hay un número y nada más detrás */
		if (sscanf(line, "%d %c", &number, &extra) == 1 //sscanf: lee el número
			&& number >= min && number <= max)
		{ //recordar: a parte de leer el input que le metas, también te va a contar 
			return number;
		}

		printf("Error: debe escribir un número entero entre %d y %d.\n",
			min, max);
	}
}

/*
 * input_ask_yes_no()
 * Muestra "question" y espera "s" (sí) o "N" (no). También se aceptan "S" y
 * "n". Repite la pregunta hasta recibir una respuesta válida.
 * Devuelve INP_YES o INP_NO. Si se acaba la entrada, devuelve INP_NO.
 */
int input_ask_yes_no(const char question[])
{
	char line[INP_MAX_LINE]; 

	while (1)
	{
		printf("%s", question);
		if (!input_read_line(line, INP_MAX_LINE))
		{
			return INP_NO;
		}

		if (strlen(line) == 1 && (line[0] == 's' || line[0] == 'S'))
		{
			return INP_YES;
		}
		if (strlen(line) == 1 && (line[0] == 'n' || line[0] == 'N'))
		{
			return INP_NO;
		}

		printf("Error: responda \"s\" o \"N\".\n");
	}
}
