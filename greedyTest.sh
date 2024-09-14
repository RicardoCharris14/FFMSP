#!/bin/bash

# Definimos el valor de t
t=0.85
a=0.5
# Definimos el directorio de entrada
input_dir="../FFMS_all_instances"

# Ejecutamos greedy para cada archivo de entrada
for input_file in $input_dir/*; do
    ./greedy -i "$input_file" -th $t -a $a >> "results.csv"

done