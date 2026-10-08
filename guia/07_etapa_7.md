# Etapa 7 · Pruebas, estilo y entrega

> **Objetivo:** convertir un programa que "funciona en mi ordenador" en una entrega que **cumple todos los requisitos** y que puedes defender. Esta etapa vale tanto como las anteriores: la nota se pierde aquí si no se hace con cuidado.
> **Dificultad:** baja, pero **meticulosa**. **Tiempo orientativo:** 1 sesión (¡no el último día!).

## 7.1 Probar con redirección de entrada (y automatizarlo)

Hasta ahora has probado escribiendo. Un programa de terminal se puede probar **sin teclado**, redirigiendo un fichero a su entrada:

```
./main < tests/01_ejemplo_enunciado.in
```

Cada línea del `.in` es lo que habrías tecleado. La salida **no** muestra lo que "escribes" (no hay eco), por eso los prompts aparecen pegados. Si guardas la salida buena como "esperada", puedes **comparar** automáticamente con `diff`:

```
./main < tests/01_ejemplo_enunciado.in | diff - tests/01_ejemplo_enunciado.out
```

Si `diff` no imprime nada, la salida es idéntica. La carpeta `etapa_7_entrega_final/tests/` incluye tres pruebas y un script que las ejecuta todas:

```
sh tests/run_tests.sh
```

| Prueba | Qué comprueba |
|---|---|
| `01_ejemplo_enunciado` | El ejemplo exacto del mensaje de la Fase I |
| `02_robustez_teclado` | Basura en el menú, números, sí/no, línea de 200 caracteres, fichero correcto tras errores |
| `03_fin_de_entrada` | La entrada se acaba sin salir del programa (Ctrl+D): no debe colgarse |
| *(extra en el script)* | Llenar el array hasta 200 |

> **Cuidado con esto:** los `.out` esperados los generó **mi** programa y los he revisado a mano, pero son una *foto* de que "hoy se comporta así". Si cambias un mensaje a propósito, regenera con `sh tests/run_tests.sh --update` **después de comprobar** que el cambio es el que querías. Esta herramienta detecta *regresiones* (algo que antes funcionaba y se rompe), no te dice que el comportamiento original sea el correcto.

**Tu tarea:** escribe **al menos dos pruebas propias** nuevas (por ejemplo, un fichero `info_cell_N.txt` roto copiado a otro nombre y recolectado, o recolectar las 21 celdas y hacer `display_all`).

## 7.2 Matriz de robustez

El enunciado enumera los casos que "no deben romper el programa". Compruébalos **todos**, en **todas** las preguntas que haga el programa:

| Caso del enunciado | Dónde probarlo | Esperado |
|---|---|---|
| Letras cuando se espera un número | Menú, celda de `collect`, celda de `display` | Error y repregunta |
| Cadena vacía / línea vacía | Menú, celdas, **todas** las preguntas sí/no | Error y repregunta |
| Número fuera de rango | Menú (1-10), celdas (1-21) | Error y repregunta |
| Nombre de fichero incorrecto | `collect` con un `info_cell_N.txt` ausente | Mensaje y vuelve al menú |
| Fichero vacío | `collect` con un fichero vacío | "No contiene datos" |
| Fichero con formato incorrecto/truncado | `collect` con una copia dañada | Error, conserva lo leído antes |
| Línea muy larga | Cualquier pregunta con 200+ caracteres | Un solo error; la siguiente lectura sale bien |
| Fin de entrada (Ctrl+D) | Cualquier pregunta | Termina sin colgarse |
| Array lleno | `collect` repetido | Aviso y sin desbordar |

## 7.3 Revisión de estilo (el `company_require_style`)

Haz este repaso con el código final. Los comandos se ejecutan en la carpeta del proyecto.

**Automático.** Ejecuta estos cuatro comandos en la carpeta del proyecto. **Los cuatro deben terminar sin mostrar nada** (salvo el último, que debe mostrar un `OK` por cada `.h`):

```
# 1) Cero advertencias al compilar desde cero
make clean && make 2>&1 | grep -i warning

# 2) Ninguna línea de más de 80 caracteres (el tabulador cuenta como 4)
awk '{ gsub(/\t/, "    "); if (length($0) > 80) print FILENAME": "FNR }' *.c *.h

# 3) Ninguna sangría con espacios (la guía exige tabuladores)
grep -nP '^ {2,}' *.c *.h

# 4) Cada .h compila por sí solo, es decir, incluye lo imprescindible (regla E6)
for h in *.h; do printf '#include "%s"\nint main(void)\n{\n\treturn 0;\n}\n' $h | gcc -Wall -I. -x c -fsyntax-only - && echo "OK $h"; done
```

Sobre el comando 3: las líneas de comentario del estilo ` * texto` empiezan por **un** solo espacio, y eso es correcto; por eso se busca "dos o más espacios".

> El `awk` cuenta **bytes**, no caracteres. Si una línea con tildes (`á`, `ñ`...) sale marcada pero a simple vista mide ≤ 80, comprueba en tu editor con la raya de la columna 80.

**A ojo (marca cada punto):**

- [ ] Toda función de un `.c` (también las `static`) lleva su comentario encima
- [ ] Todo `#define`, `struct`, campo de `struct`, `enum` y variable global está documentado
- [ ] Ninguna función ocupa más de dos pantallas (idealmente, una)
- [ ] Llaves Allman (`{` en su propia línea), espacio tras `if`/`for`/`while`/`return`, espacio alrededor de los operadores
- [ ] Nombres en minúsculas con `_` (funciones/variables) y MAYÚSCULAS (macros), con prefijo de módulo en lo público
- [ ] Ningún número "mágico" suelto: los tamaños son macros
- [ ] Los `.h` tienen guarda y solo lo público; los `.c` incluyen primero su propio `.h`
- [ ] Lo privado es `static`; las globales, juntas arriba y `static`
- [ ] No queda ningún `printf` de depuración ni código comentado

## 7.4 El README

El enunciado pide un archivo de texto `README`. Hay una **plantilla** en `etapa_7_entrega_final/README.txt` con la estructura (cómo compilar y ejecutar, qué operaciones hay, organización del código, decisiones de diseño, pruebas, limitaciones). **Es una plantilla: reescríbela con vuestras palabras** y con los nombres de los miembros del equipo. Un buen README responde en un minuto a: *¿cómo lo compilo? ¿qué hace? ¿qué decisiones tomasteis donde el enunciado no era claro? ¿qué falta?*

## 7.5 Empaquetar y probar la entrega

El enunciado pide un archivo comprimido con: **archivos de entrada, código fuente, `Makefile` y `README`**, y que se compile con `make` y se ejecute con `./main`.

```
make clean                       # no entregues ejecutables ni .o
cd ..
zip -r entrega1.zip wificollector/
```

**Prueba la entrega como la recibiría el profesor:**

```
mkdir /tmp/prueba && cd /tmp/prueba
unzip ~/entrega1.zip
cd wificollector
make
./main
```

Y, sobre todo: **repite esto en un laboratorio o máquina virtual de la UC3M**. El enunciado dice que, si no compila ni ejecuta allí, *"su trabajo no será considerado válido"*. Las diferencias típicas entre tu ordenador y el laboratorio son la versión de `gcc` y las rutas de los ficheros de datos.

**Lista de entrega:**

- [ ] `make` desde cero compila sin errores **ni advertencias**
- [ ] `./main` arranca y el ejemplo del enunciado sale igual
- [ ] Los 21 `info_cell_N.txt` van **dentro** del `.zip`
- [ ] El `README` está reescrito y firmado por el equipo
- [ ] Probado en el laboratorio / máquina virtual de la UC3M
- [ ] Subido a Aula Global **antes** de las 23:55 del viernes 16 de octubre (con margen)

## 7.6 Mirando hacia delante: qué cambia en las entregas 2 y 3

Según el enunciado:

| Entrega | Novedades | Qué parte de tu código cambia |
|---|---|---|
| 2 (13 nov) | Arrays **dinámicos** (empiezan en 5, `realloc` de 5 en 5), `wificollector_sort`; borrar un elemento desplazando a la izquierda | `cells` y `num_cells` pasan a ser puntero + contador + capacidad; `collect` necesita comprobar "¿cabe?" y crecer |
| 3 (11 dic) | **Listas** enlazadas, `import`/`export` con ficheros binarios; liberar toda la memoria | Cambia la estructura de datos entera; aparece `free` |

Lo que has hecho bien ahora **se reutiliza casi entero**: `input`, `cell_read_block`, `cell_print`, el menú. Eso es lo bueno de haber separado en módulos: solo `wificollector.c` tendrá que cambiar de verdad. Y es aquí donde los punteros dejarán de ser "magia" para ser herramienta.

## 7.7 Autoevaluación: ¿puedes hacerlo sin la IA?

Esta es la prueba de verdad del objetivo que te marcaste. Responde **sin mirar** el código ni la guía; luego comprueba.

**Preguntas de concepto**

1. ¿Qué devuelve `sscanf("12x", "%d %c", &n, &c)` y por qué lo usamos para validar un entero?
2. ¿Por qué `char line[80]` solo admite 79 caracteres de texto?
3. ¿Qué diferencia hay entre `%s` y `%79s` en `sscanf`? ¿Y entre `%s` y `%[^"]`?
4. ¿Qué ocurriría si `collect_one_cell` no comprobara `num_cells < WFC_MAX_CELLS`?
5. ¿Qué significa `static` en una función? ¿Y en una variable global?
6. ¿Por qué se pasa `size` a `input_read_line` si ya está declarado el array?
7. ¿Qué error obtienes si declaras una función en un `.h` pero nunca la escribes? ¿Y si la escribes pero se te olvida el `#include` del `.h`?

**Ejercicios de programación (en papel o en el editor, con límite de tiempo)**

1. Escribe `input_read_line` desde cero en 10 minutos.
2. Escribe un `Makefile` para este proyecto desde cero en 10 minutos.
3. **Reto de ampliación:** implementa `wificollector_select_best` (opción 4): muestra el punto de acceso de mejor calidad (el mayor `quality`). Es un recorrido como el de `display_all`, pero recordando cuál es el mejor hasta el momento. ¿Qué haces si el array está vacío?
4. Escribe una función que cuente cuántas redes **sin cifrar** (`encryption` igual a `"off"`) hay guardadas. (Pista: `strcmp` de `<string.h>` compara cadenas; devuelve 0 si son iguales.)
5. Cambia la capacidad del array a 50. ¿Cuántas líneas de código tienes que tocar? ¿Por qué la regla C1 de la guía tiene sentido?

> Si un ejercicio te sale a la primera, ya dominas esa parte. Si no, no pasa nada: vuelve a la etapa correspondiente y repítela **sin** el desplegable.
