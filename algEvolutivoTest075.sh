#!/bin/bash

# Definimos el valor de t
t=0.75
a=0.84
time=10
psize=88
tsize=3
mrate=0.13
# Definimos el directorio de entrada
input_dir="FFMS_all_instances"

# Ejecutamos greedy para cada archivo de entrada
for input_file in $input_dir/*; do
    echo instancia "$input_file"
    ./algEvolutivo -i "$input_file" -t $time -th $t -a $a -psize $psize -tsize $tsize -mrate $mrate >> "results075.csv"
done