#include <stdio.h>
#include "cell.h"

/* Número de líneas de texto que ocupa un bloque en un fichero info_cell */
#define CEL_LINES_PER_BLOCK 9

/* Datos que sscanf debe convertir en total por bloque ("n1/n2" cuenta 2) */
#define CEL_FIELDS_PER_BLOCK 10

/*
 * cell_print()
 * Imprime una celda en una sola línea. Ejemplo de salida:
 * Cell 1: 00:01:38:1F:CB:3E "PTNET" Master 2 on 70/70 2.417000 -33
 */
void cell_print(struct wifi_cell cell)
{
	printf("Cell %d: %s \"%s\" %s %d %s %d/%d %f %d\n",
		cell.cell_id, cell.address, cell.essid, cell.mode, cell.channel,
		cell.encryption, cell.quality, cell.quality_max, cell.frequency,
		cell.signal_level);
}

/*
 * read_block_lines()
 * Lee del fichero las 9 líneas de un bloque y las guarda en "lines".
 * Devuelve CEL_READ_OK si las leyó todas, CEL_READ_END si el fichero ya
 * estaba acabado antes de la primera línea y CEL_READ_ERROR si se acaba a
 * mitad de un bloque.
 */
static cell_read_status_t read_block_lines(FILE *file,
	char lines[][CEL_MAX_STR])
{
	int i;

	for (i = 0; i < CEL_LINES_PER_BLOCK; i++)
	{
		if (fgets(lines[i], CEL_MAX_STR, file) == NULL)
		{
			if (i == 0)
			{
				return CEL_READ_END;
			}
			return CEL_READ_ERROR;
		}
	}

	return CEL_READ_OK;
}

/*
 * cell_read_block()
 * Lee el siguiente bloque de 9 líneas del fichero ya abierto "file" y, si es
 * correcto, lo guarda en cells[position]. El que llama debe asegurarse de que
 * "position" es una posición válida del array.
 * Devuelve CEL_READ_OK, CEL_READ_END (no quedan bloques) o CEL_READ_ERROR.
 */
cell_read_status_t cell_read_block(FILE *file, struct wifi_cell cells[],
	int position)
{
	char lines[CEL_LINES_PER_BLOCK][CEL_MAX_STR];
	struct wifi_cell cell;
	cell_read_status_t status;
	int converted;

	status = read_block_lines(file, lines);
	if (status != CEL_READ_OK)
	{
		return status;
	}

	/* Cada sscanf devuelve cuántos datos pudo convertir de su línea */
	converted = sscanf(lines[0], "Cell %d", &cell.cell_id);
	converted += sscanf(lines[1], "Address: %79s", cell.address);
	converted += sscanf(lines[2], "ESSID:\"%79[^\"]\"", cell.essid);
	converted += sscanf(lines[3], "Mode:%79s", cell.mode);
	converted += sscanf(lines[4], "Channel:%d", &cell.channel);
	converted += sscanf(lines[5], "Encryption key:%79s", cell.encryption);
	converted += sscanf(lines[6], "Quality=%d/%d", &cell.quality,
		&cell.quality_max);
	converted += sscanf(lines[7], "Frequency:%lf", &cell.frequency);
	converted += sscanf(lines[8], "Signal level=%d", &cell.signal_level);

	if (converted != CEL_FIELDS_PER_BLOCK)
	{
		return CEL_READ_ERROR;
	}

	cells[position] = cell;
	return CEL_READ_OK;
}
