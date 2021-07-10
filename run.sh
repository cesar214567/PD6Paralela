#!/bin/bash

#SBATCH --job-name=matrix_mult # nombre del job
#SBATCH -c 4 #numero de cores
#SBATCH --mem-per-cpu=32gb #tamano de memoria del job en ejecucion

mpirun -np 1 /home/stephano.wurttele/PD6Paralela/a.out --oversubscribe
# mpirun -np 4 /home/stephano.wurttele/PD6Paralela/a.out
# mpirun -np 8 /home/stephano.wurttele/PD6Paralela/a.out
# mpirun -np 16 /home/stephano.wurttele/PD6Paralela/a.out
