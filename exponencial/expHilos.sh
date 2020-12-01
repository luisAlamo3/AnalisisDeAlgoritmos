#!/bin/bash
nombre="expHilos"
codigo="${nombre}.c"
out="${nombre}"
aux="tiempo.c"
numeros="10millones.txt"
n="1000000 2000000 3000000 4000000 5000000 6000000 7000000 8000000 9000000 10000000"
back="/back/${nombre}"
rm -r ${back} &>/dev/null
if [[ ! -d ${back} ]]; then
    mkdir -p .${back}
fi

gcc ${codigo} ${aux} -o $out -lpthread

for num in $n; do
    ./${out} ${num} < ${numeros} >> .${back}/${nombre}${num}
done
