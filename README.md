# FFMSP
Proyecto semestral para el "Far From Most Strings Problem"
## Integrantes:
 - Ricardo Andrés Charris Jiménez
 - Benjamin Alonso Espinoza Henriquez
 - Sebastian Andres Rosas Urra

### Instrucciones de compilación y ejecución:

Compilar: 

Para la compilacion del programa se puede usar
```bash
g++ -o algEvolutivo mainAlgEvolutivo.cpp greedy1.cpp control_functions.cpp
```
o alternativamente

```bash
make
```

Para ejecutar el programa usar 

```bash
./algEvolutivo -i <instancia-problema> -t <t max en seg> -th <threshold> -a <grado-determinismo> -psize <size-poblacion>  -tsize <size-torneo> -mrate <grado-mutacion> -tuning <para activar el tuning>
```

Ejemplos de uso:

Sin tuning:

```bash
./algEvolutivo -i 100-300-001.txt -th 0.8 -t 10 -a 0.96 -psize 50 -tsize 5 -mrate 0.05
```

Con tuning:

```bash
./algEvolutivo -i 100-300-001.txt -th 0.8 -t 10 -a 0.96 -psize 50 -tsize 5 -mrate 0.05 -tuning
```
