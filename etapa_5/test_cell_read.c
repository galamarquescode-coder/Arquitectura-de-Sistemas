#include <stdio.h>
#include "cell.h"

/* Capacidad del array de prueba */
#define TST_MAX_CELLS 10

/*
 * main()
 * Programa de prueba de cell_read_block(): lee todos los bloques del fichero
 * info_cell_1.txt, los imprime y cuenta cuántos hay.
 */
int main(void)
{
	struct wifi_cell cells[TST_MAX_CELLS];
	cell_read_status_t status;
	FILE *file;
	int count = 0;

	file = fopen("info_cell_1.txt", "r");
	if (file == NULL)
	{
		printf("Error: no se pudo abrir info_cell_1.txt\n");
		return 1;
	}

	status = CEL_READ_OK;
	while (status == CEL_READ_OK && count < TST_MAX_CELLS)
	{
		status = cell_read_block(file, cells, count);
		if (status == CEL_READ_OK)
		{
			cell_print(cells[count]);
			count++;
		}
	}

	if (status == CEL_READ_ERROR)
	{
		printf("Error: formato incorrecto en el fichero\n");
	}
	printf("Bloques leídos: %d\n", count);

	fclose(file);
	return 0;
}
