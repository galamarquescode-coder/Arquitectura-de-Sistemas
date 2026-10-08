# Apéndice · Chuleta de las funciones de C que has usado

| Función | Cabecera | Qué hace | Ojo con... |
|---|---|---|---|
| `printf(fmt, ...)` | `<stdio.h>` | Escribe texto con formato en pantalla | El formato debe coincidir con el tipo (`%d` int, `%s` cadena, `%f` double) |
| `fgets(buf, size, f)` | `<stdio.h>` | Lee una línea (como mucho `size - 1` caracteres) | Guarda el `\n`; devuelve `NULL` al acabar |
| `getchar()` | `<stdio.h>` | Lee **un** carácter del teclado | Devuelve `int` (para poder valer `EOF`) |
| `sscanf(texto, fmt, ...)` | `<stdio.h>` | Extrae datos de una cadena | Devuelve **cuántos** convirtió; necesita `&` en los números; limita `%s` con anchura |
| `snprintf(buf, size, fmt, ...)` | `<stdio.h>` | Como `printf` pero escribiendo en una cadena | `size` evita desbordamientos |
| `fopen(nombre, modo)` | `<stdio.h>` | Abre un fichero (`"r"` leer) | Devuelve `NULL` si falla: **siempre** comprobar |
| `fclose(f)` | `<stdio.h>` | Cierra el fichero | Una por cada `fopen` que haya funcionado |
| `strlen(s)` | `<string.h>` | Longitud de una cadena (sin el `'\0'`) | Recorre toda la cadena: no la llames en bucles innecesariamente |
| `strcpy(dest, orig)` | `<string.h>` | Copia una cadena | **No** comprueba el tamaño del destino |
| `strcmp(a, b)` | `<string.h>` | Compara cadenas | Devuelve **0** si son iguales (no `1`) |

**Operadores y construcciones**

| Elemento | Resumen |
|---|---|
| `&x` | "Dirección de `x`": dónde escribir un resultado (`sscanf`) |
| `==` frente a `=` | `==` compara; `=` asigna. Confundirlos es un clásico |
| `a[i]`, `a[0]`…`a[n-1]` | Un array de `n` elementos va de la posición `0` a la `n-1` |
| `x.campo` | Acceso a un campo de una `struct` |
| `x = y` (structs) | Copia **todos** los campos, también los arrays internos |
| `+=`, `++` | `a += b` es `a = a + b`; `i++` suma 1 a `i` |
| `enum` | Nombres para una serie de enteros |
| `static` (función o global) | Solo visible dentro de ese `.c` |
| `const` en un parámetro | Promesa de no modificarlo |

**Mensajes del compilador que ya sabes leer**

| Mensaje | Significado habitual |
|---|---|
| `implicit declaration of function 'x'` | Falta `#include` o el prototipo de `x` |
| `unused variable 'x'` | Declaraste `x` y no la usas |
| `format '%d' expects argument of type 'int'` | El formato de `printf` no coincide con el dato |
| `undefined reference to 'x'` | (Enlazador) `x` está declarada pero no hay ningún `.o` que la defina |
| `missing separator` | (Make) La receta no empieza con un tabulador |
| `control reaches end of non-void function` | Una función con tipo de retorno puede acabar sin `return` |
