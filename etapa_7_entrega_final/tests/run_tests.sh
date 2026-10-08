#!/bin/sh
# Ejecuta cada tests/*.in como si se escribiera por teclado y compara la salida
# con el fichero .out esperado. Uso:   sh tests/run_tests.sh
# Para (re)generar los .out esperados:  sh tests/run_tests.sh --update
cd "$(dirname "$0")/.." || exit 1
make > /dev/null || { echo "No compila"; exit 1; }

failed=0
for input in tests/*.in; do
    expected="${input%.in}.out"
    if [ "$1" = "--update" ]; then
        ./main < "$input" > "$expected"
        echo "ACTUALIZADO $expected"
        continue
    fi
    if ./main < "$input" | diff -q - "$expected" > /dev/null; then
        echo "OK      $input"
    else
        echo "FALLA   $input   (compare con: ./main < $input | diff - $expected)"
        failed=1
    fi
done

# Prueba extra: llenar el array (200 posiciones) no debe romper el programa
# (opción 2, luego 69 veces "celda 1 + s", una más con "n", y salir)
{ printf '2\n'; for i in $(seq 1 69); do printf '1\ns\n'; done; \
  printf '1\nn\n1\ns\n'; } > /tmp/lleno.in
output=$(./main < /tmp/lleno.in)
if echo "$output" | grep -q "array está lleno" \
    && ! echo "$output" | grep -q "posición 200 del array"; then
    echo "OK      array lleno (200 posiciones)"
else
    echo "FALLA   array lleno"
    failed=1
fi

exit $failed
