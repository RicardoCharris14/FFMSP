import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import friedmanchisquare

# Datos proporcionados (valores para cada dataset)
datasets = [
    [98.340, 86.570, 98.920, 99.890],  # Dataset 1
    [99.860, 94.090, 99.930, 99.980],  # Dataset 2
    [99.970, 95.690, 100.000, 100.000], # Dataset 3
    [187.180, 156.600, 188.950, 193.510], # Dataset 4
    [196.370, 171.060, 197.350, 193.630], # Dataset 5
    [198.480, 177.660, 198.920, 196.960], # Dataset 6
    [53.640, 17.090, 55.460, 57.980], # Dataset 7
    [52.280, 7.930, 53.870, 52.860], # Dataset 8
    [52.180, 5.050, 53.570, 49.550], # Dataset 9
    [59.240, 20.800, 61.950, 67.090], # Dataset 10
    [42.500, 6.640, 44.950, 40.140], # Dataset 11
    [35.370, 3.280, 36.850, 32.580], # Dataset 12
    [1.800, 0.050, 2.660, 5.100], # Dataset 13
    [0.090, 0.000, 0.170, 0.250], # Dataset 14
    [0.040, 0.000, 0.050, 0.040], # Dataset 15
    [0.710, 0.070, 1.430, 1.680], # Dataset 16
    [0.000, 0.000, 0.020, 0.020], # Dataset 17
    [0.000, 0.000, 0.000, 0.000], # Dataset 18
]

# Algoritmos
algorithms = ["Greedy", "A-Greedy", "Búsqueda Local", "Genético"]

# Calcular rankings para cada dataset
rankings = []
for data in datasets:
    ranking = np.argsort(np.argsort(data)) + 1  # Menor valor = mejor ranking
    rankings.append(ranking)

# Convertir rankings a numpy array
rankings = np.array(rankings)

# Calcular el ranking promedio de cada algoritmo
average_ranks = np.mean(rankings, axis=0)

# Reflejar los datos con respecto a un eje vertical
center = np.mean(average_ranks)  # Eje central
reflected_ranks = center - (average_ranks - center)  # Reflejar los valores

# Prueba de Friedman
stat, p_value = friedmanchisquare(*rankings.T)

# Prueba de Nemenyi (diferencia crítica)
alpha = 0.05
nemenyi_q_values = {2: 1.960, 3: 2.343, 4: 2.569, 5: 2.728, 6: 2.850}
q_alpha = nemenyi_q_values[len(algorithms)]
cd = q_alpha * np.sqrt((len(algorithms) * (len(algorithms) + 1)) / (6 * len(datasets)))

# Colores para las líneas verticales
colors = ['red', 'green', 'blue', 'orange', 'purple', 'brown', 'cyan', 'magenta']

# Graficar el diagrama de diferencias críticas
plt.figure(figsize=(10, 5))
plt.title("Diagrama de diferencias criticas", fontsize=14)

# Ordenar algoritmos por ranking promedio reflejado
sorted_indices = np.argsort(reflected_ranks)
sorted_ranks = reflected_ranks[sorted_indices]
sorted_algorithms = np.array(algorithms)[sorted_indices]

# Dibujar puntos y etiquetas
x_positions = sorted_ranks
plt.scatter(x_positions, np.zeros(len(average_ranks)), color='blue', zorder=2)
for x, label in zip(x_positions, sorted_algorithms):
    offsetx = 0.05 if label == "Genético" else 0
    offset = -0.05 if label == "Genético" else -0.1  # Desplazar el texto del Algoritmo Genético hacia arriba
    plt.text(x + offsetx, offset, label, ha='center', fontsize=10, fontweight='bold', color='blue')  # Etiquetas bajo los puntos

# Dibujar líneas de diferencia significativa a diferentes alturas
line_height = 0.1  # Altura inicial de las líneas
height_increment = 0.1  # Incremento de altura entre líneas
for i in range(len(sorted_ranks)):
    for j in range(i + 1, len(sorted_ranks)):
        diff = abs(sorted_ranks[i] - sorted_ranks[j])
        if diff > cd:
            # Línea horizontal entre los puntos
            plt.plot([sorted_ranks[i], sorted_ranks[j]], 
                     [line_height, line_height], color='red', lw=2, zorder=1)
            # Líneas verticales desde los puntos hasta la línea horizontal
            color_index = (i + j) % len(colors)  # Elegir color basado en índice
            plt.plot([sorted_ranks[i], sorted_ranks[i]], 
                     [0, line_height], color=colors[color_index], lw=1, linestyle='--', zorder=1)
            plt.plot([sorted_ranks[j], sorted_ranks[j]], 
                     [0, line_height], color=colors[color_index], lw=1, linestyle='--', zorder=1)
            line_height += height_increment  # Incrementar la altura para la siguiente línea

# Configuración del gráfico
plt.yticks([])
plt.xlabel("Ranking promedio reflejado (menor es mejor)", fontsize=12)
plt.grid(axis='x', linestyle='--', alpha=0.6)
plt.tight_layout()
plt.show()
