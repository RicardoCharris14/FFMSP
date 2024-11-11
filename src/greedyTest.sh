#!/bin/bash

# Definimos el valor de t
t=0.85
a=0.9
time=10
# Definimos el directorio de entrada
input_dir="FFMS_all_instances"

# Ejecutamos greedy para cada archivo de entrada
for input_file in $input_dir/*; do
    ./localSearch -i "$input_file" -t $time -th $t -a $a >> "results085.csv"

done

