RECOLECTOR DE REDES INALAMBRICAS - ENTREGA 1
Arquitectura de Sistemas 2026-2027

Equipo (escriban aqui los nombres y NIA de los 3 miembros):
  - <nombre 1>
  - <nombre 2>
  - <nombre 3>
Grupo reducido: <grupo>

NOTA: esto es una PLANTILLA. Revisenla y adaptenla: el README debe describir
lo que hace VUESTRO proyecto, con vuestras palabras.

1. COMPILAR Y EJECUTAR
   make          (compila con gcc -Wall, sin errores ni advertencias)
   ./main        (arranca el programa; los ficheros info_cell_N.txt deben
                  estar en el mismo directorio desde el que se ejecuta)
   make clean    (borra los ficheros generados)

2. OPERACIONES IMPLEMENTADAS EN ESTA ENTREGA
   [1] wificollector_quit        Salir (pide confirmacion).
   [2] wificollector_collect     Anade al array los puntos de acceso de un
                                 fichero info_cell_N.txt (N entre 1 y 21).
   [9] wificollector_display     Imprime los puntos de acceso de una celda.
   [10] wificollector_display_all Imprime todos los puntos de acceso.
   El resto de opciones del menu se muestran, pero responden "todavia no
   implementada" (se haran en entregas posteriores).

3. ORGANIZACION DEL CODIGO
   main.c            Menu principal y bucle del programa.
   input.c / .h      Lectura robusta del teclado (numeros y si/no).
   cell.c / .h       Estructura wifi_cell, impresion y lectura de un bloque
                     de un fichero info_cell_N.txt.
   wificollector.c/.h Operaciones del menu y array de puntos de acceso.

4. DECISIONES DE DISENO
   - Array de tamano fijo (200 elementos) y cadenas de maximo 80 caracteres.
   - Toda lectura del teclado se hace con fgets + sscanf (nunca scanf).
   - Si se vuelve a recolectar una celda, sus datos se anaden otra vez
     (el enunciado solo pide ignorar duplicados en wificollector_import).
   - Si el array se llena, se avisa y no se anade nada mas.
   - Si se acaba la entrada de datos (Ctrl+D), el programa termina sin colgarse.
   - Respuestas si/no: se aceptan s, S, n y N; cualquier otra cosa se repite.

5. PRUEBAS
   sh tests/run_tests.sh     Ejecuta las pruebas automaticas (tests/*.in).

6. LIMITACIONES CONOCIDAS
   <anoten aqui lo que no funciona o lo que mejorarian>
