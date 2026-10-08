#ifndef _CELL_H_
#define _CELL_H_

#include <stdio.h>

/* Tamaño máximo de las cadenas de texto de una celda (incluye el '\0') */
#define CEL_MAX_STR 80

/*
 * struct wifi_cell
 * Datos de un punto de acceso: un bloque de un fichero info_cell_N.txt.
 */
struct wifi_cell
{
	int cell_id;                 /* Identificador de celda (la N de "Cell N") */
	char address[CEL_MAX_STR];   /* Dirección MAC, p. ej. 00:01:38:1F:CB:3E */
	char essid[CEL_MAX_STR];     /* Nombre de la red, sin las comillas */
	char mode[CEL_MAX_STR];      /* Modo: Master, Ad-Hoc, Managed... */
	int channel;                 /* Canal */
	char encryption[CEL_MAX_STR];/* Cifrado: "on" u "off" */
	int quality;                 /* Calidad actual (el n1 de n1/n2) */
	int quality_max;             /* Calidad máxima (el n2 de n1/n2) */
	double frequency;            /* Frecuencia en GHz */
	int signal_level;            /* Nivel de señal en dBm */
};

/*
 * cell_read_status_t
 * Resultado de intentar leer un bloque de un fichero.
 */
typedef enum
{
	CEL_READ_OK,    /* Se leyó un bloque completo y correcto */
	CEL_READ_END,   /* No quedan más bloques: fin del fichero */
	CEL_READ_ERROR  /* El bloque está incompleto o tiene mal formato */
} cell_read_status_t;

/* Imprime una celda en una línea: Cell 1: <MAC> "<ESSID>" <modo> ... */
void cell_print(struct wifi_cell cell);

/* Lee el siguiente bloque del fichero y lo guarda en cells[position] */
cell_read_status_t cell_read_block(FILE *file, struct wifi_cell cells[],
	int position);

#endif /* _CELL_H_ */
