# FFMSP
Proyecto semestral para el "Far From Most Strings Problem"
## Integrantes:
 - Ricardo Andrés Charris Jiménez
 - Benjamin Alonso Espinoza Henriquez
 - Sebastian Andres Rosas Urra

### Instrucciones de compilación y ejecución:

#### Para la compilacion del programa usar

Para el algoritmo evolutivo:
```bash
g++ -o algEvolutivo mainAlgEvolutivo.cpp greedy1.cpp control_functions.cpp
```
Para el algoritmo de optimizacion con colonias de hormigas:
```bash
g++ -o ACOElite mainACOElite.cpp control_functions.cpp greedy1.cpp acoElite.cpp
```
o alternativamente para ambos:
```bash
make
```

#### Para ejecutar el programa usar 

Para el algoritmo evolutivo:
```bash
./algEvolutivo -i <instancia-problema> -t <t max en seg> -th <threshold> -a <grado-determinismo> -psize <size-poblacion>  -tsize <size-torneo> -mrate <grado-mutacion> -tuning <para activar el tuning>
```
Para el algoritmo de optimizacion con colonias de hormigas:
```bash
./ACOElite -i <instancia-problema> -t <t max en seg> -th <threshold> -a <grado-determinismo> -ant <cantidad-hormigas> -e <factor-evaporacion> -tuning <para activar el tuning>
```

#### Ejemplos de uso:

Sin tuning:

```bash
./algEvolutivo -i 100-300-001.txt -th 0.8 -t 10 -a 0.96 -psize 50 -tsize 5 -mrate 0.05
```
```bash
./ACOElite -i 100-300-001.txt -th 0.8 -t 10 -a 0.96 -ant 750 -e 0.6
```

Con tuning:

```bash
./algEvolutivo -i 100-300-001.txt -th 0.8 -t 10 -a 0.96 -psize 50 -tsize 5 -mrate 0.05 -tuning
```
```bash
./ACOElite -i 100-300-001.txt -th 0.8 -t 10 -a 0.96 -ant 750 -e 0.6 -tuning
```

## Tuning Realizado
Para este proyecto se realizo tuning con irace para encontrar los mejores parametros posibles segun cada threshold, los resultados de estos se pueden encontrar en las carpetas de tuning (tuning< th >), en los archivos "outputTuningAcoElite".