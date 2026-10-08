#include <stdio.h>
#include "input.h"

/*
 * main()
 * Programa de prueba del módulo input: pide un número y una respuesta sí/no.
 */
int main(void)
{
	int number;
	int answer;

	number = input_ask_number("Escriba un número entre 1 y 21: ", 1, 21);
	if (number == INP_EOF)
	{
		printf("\nSe acabó la entrada de datos.\n");
		return 0;
	}
	printf("Ha escrito el número %d\n", number);

	answer = input_ask_yes_no("¿Le gusta programar en C? [s/N]: ");
	if (answer == INP_YES)
	{
		printf("¡Estupendo!\n");
	}
	else
	{
		printf("Ya le gustará.\n");
	}

	return 0;
}
