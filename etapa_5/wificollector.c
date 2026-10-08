#include <stdio.h>
#include "wificollector.h"
#include "cell.h"
#include "input.h"

/* Número de celda mínimo: corresponde al fichero info_cell_1.txt */
#define WFC_MIN_CELL_ID 1

/* Número de celda máximo: corresponde al fichero info_cell_21.txt */
#define WFC_MAX_CELL_ID 21

/* Número máximo de puntos de acceso que caben en el array */
#define WFC_MAX_CELLS 200

/* Tamaño máximo del nombre de un fichero (incluye el '\0' final) */
#define WFC_MAX_FILE_NAME 80

/* Variables globales (solo visibles dentro de este fichero) */

/* Array con los puntos de acceso recolectados hasta el momento */
static struct wifi_cell cells[WFC_MAX_CELLS];

/* Número de posiciones del array que están ocupadas */
static int num_cells = 0;

/*
 * wificollector_quit()
 * Pregunta al usuario si de verdad quiere salir del programa.
 * Devuelve 1 si el usuario confirma y 0 si decide seguir.
 */
int wificollector_quit(void)
{
	int answer;

	answer = input_ask_yes_no(
		"¿Está seguro de que desea salir del programa? [s/N]: ");

	if (answer == INP_YES)
	{
		printf("¡Hasta pronto!\n");
		return 1;
	}

	return 0;
}

/*
 * print_added_cell()
 * Confirma que se ha añadido un punto de acceso al array y lo imprime.
 */
static void print_added_cell(const char file_name[], int position)
{
	printf("Datos leídos de %s (añadidos a la posición %d del array)\n",
		file_name, position);
	cell_print(cells[position]);
	printf("\n");
}

/*
 * collect_one_cell()
 * Abre el fichero info_cell_N.txt y añade al array todos los puntos de acceso
 * que contiene, hasta que se acabe el fichero o se llene el array.
 */
static void collect_one_cell(int cell_id)
{
	char file_name[WFC_MAX_FILE_NAME];
	cell_read_status_t status = CEL_READ_OK;
	FILE *file;
	int added = 0;

	snprintf(file_name, WFC_MAX_FILE_NAME, "info_cell_%d.txt", cell_id);
	file = fopen(file_name, "r");
	if (file == NULL)
	{
		printf("Error: no se pudo abrir el fichero %s\n\n", file_name);
		return;
	}

	while (status == CEL_READ_OK && num_cells < WFC_MAX_CELLS)
	{
		status = cell_read_block(file, cells, num_cells);
		if (status == CEL_READ_OK)
		{
			print_added_cell(file_name, num_cells);
			num_cells++;
			added++;
		}
	}
	fclose(file);

	if (status == CEL_READ_ERROR)
	{
		printf("Error: formato incorrecto en %s (se ignora el resto)\n\n",
			file_name);
	}
	else if (status == CEL_READ_OK)
	{
		/* El bucle terminó con un bloque correcto: el array está lleno */
		printf("Aviso: el array está lleno (%d posiciones). No se añaden "
			"más datos.\n\n", WFC_MAX_CELLS);
	}
	else if (added == 0)
	{
		printf("El fichero %s no contiene datos\n\n", file_name);
	}
}

/*
 * wificollector_collect()
 * Pide un número de celda, añade al array los datos de su fichero y pregunta
 * si se quiere añadir otra celda. Repite mientras el usuario responda "s".
 */
void wificollector_collect(void)
{
	int cell_id;
	int add_another = INP_YES;

	while (add_another == INP_YES)
	{
		cell_id = input_ask_number("¿Qué celda quiere recolectar? (1 - 21): ",
			WFC_MIN_CELL_ID, WFC_MAX_CELL_ID);
		if (cell_id == INP_EOF)
		{
			return;
		}

		collect_one_cell(cell_id);

		add_another = input_ask_yes_no(
			"¿Desea añadir otro punto de acceso? [s/N]: ");
	}
}
