# FFMSP

Integrantes:
Ricardo Andrés Charris Jiménez
Benjamin Alonso Espinoza Henriquez
Sebastian Andres Rosas Urra

Instrucciones de compilación y ejecución:

Compilar: g++ main.cpp greedy1.cpp control_functions.cpp

Si se quiere ejecutar sin aleatoriedad, usar:
Ejecutar: <archivo_ejecutable> -i <path_dataset> -th <threshold>
Si se quiere ejecutar con aleatoriedad, usar:
Ejecutar: <archivo_ejecutable> -i <path_dataset> -th <threshold> -a <grado_determinismno>

Donde, archivo_ejecutable, es el archivo ejecutable producto de la compilacion, path_dataset, es el path al dataset a usar, threshold, es el grado de coincidencia entre 0 y 1 que se le pide a la solucion respecto a las cadenas del dataset, grado_determinismo, numero entre 0 y 1, donde 1 es perfectamente determinista y 0 es perfectamente aleatorio.

