#ifndef _INPUT_H_
#define _INPUT_H_

/* Valor que devuelve input_ask_number() cuando se acaba la entrada de datos */
#define INP_EOF (-1)

/* Respuesta negativa de input_ask_yes_no() */
#define INP_NO 0

/* Respuesta afirmativa de input_ask_yes_no() */
#define INP_YES 1

/* Lee una línea del teclado sin el salto de línea. Devuelve 0 si no hay */
int input_read_line(char line[], int size);

/* Pide un entero entre min y max (incluidos) hasta que el usuario acierta */
int input_ask_number(const char question[], int min, int max);

/* Hace una pregunta de tipo sí/no. Devuelve INP_YES o INP_NO */
int input_ask_yes_no(const char question[]);

#endif /* _INPUT_H_ */
