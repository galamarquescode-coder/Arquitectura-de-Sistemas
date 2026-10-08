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
	if (length > 0 && line[length - 1] == '\n')
	{
		line[length - 1] = '\0';
	}
	else
	{
		/* La línea no cabía entera: se tira lo que sobra hasta el '\n' */
		character = getchar();
		while (character != '\n' && character != EOF)
		{
			character = getchar();
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
	char line[INP_MAX_LINE];
	char extra;
	int number;

	while (1)
	{
		printf("%s", question);
		if (!input_read_line(line, INP_MAX_LINE))
		{
			return INP_EOF;
		}

		/* sscanf devuelve 1 solo si hay un número y nada más detrás */
		if (sscanf(line, "%d %c", &number, &extra) == 1
			&& number >= min && number <= max)
		{
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
