#!/bin/bash -l
#SBATCH -J tuning
#SBATCH -o output."%j".out
#SBATCH -e output."%j".err
#SBATCH -p long

srun -p main --output=output irace & 