#!/bin/bash

# Definimos el valor de t
t=0.85
a=0.95
time=10
psize=50
# Definimos el directorio de entrada
input_dir="FFMS_all_instances"

# Ejecutamos greedy para cada archivo de entrada
for input_file in $input_dir/*; do
    ./algEvolutivo -i "$input_file" -t $time -th $t -a $a -psize $psize -tuning >> "results085.csv"

done