#include <stdio.h>
#include <string.h>
#include "cell.h"

/*
 * main()
 * Programa de prueba de cell_print(): rellena una celda a mano y la imprime.
 * Debe imprimir exactamente:
 * Cell 1: 00:01:38:1F:CB:3E "PTNET" Master 2 on 70/70 2.417000 -33
 */
int main(void)
{
	struct wifi_cell cell;

	cell.cell_id = 1;
	strcpy(cell.address, "00:01:38:1F:CB:3E");
	strcpy(cell.essid, "PTNET");
	strcpy(cell.mode, "Master");
	cell.channel = 2;
	strcpy(cell.encryption, "on");
	cell.quality = 70;
	cell.quality_max = 70;
	cell.frequency = 2.417;
	cell.signal_level = -33;

	cell_print(cell);

	return 0;
}
