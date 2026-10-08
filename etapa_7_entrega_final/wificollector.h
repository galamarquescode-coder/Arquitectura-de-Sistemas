#ifndef _WIFICOLLECTOR_H_
#define _WIFICOLLECTOR_H_

/* Pregunta si se quiere salir. Devuelve 1 si el usuario confirma, 0 si no */
int wificollector_quit(void);

/* Lee los puntos de acceso de ficheros info_cell_N.txt y los guarda */
void wificollector_collect(void);

/* Imprime los puntos de acceso guardados de la celda que elija el usuario */
void wificollector_display(void);

/* Imprime todos los puntos de acceso guardados */
void wificollector_display_all(void);

#endif /* _WIFICOLLECTOR_H_ */
