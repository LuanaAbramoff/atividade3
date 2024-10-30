#!/bin/bash
#SBATCH --job-name=ex3
#SBATCH --output=ex3.txt
#SBATCH --ntasks=4
#SBATCH --mem=1024MB
#SBATCH --time=00:05:00

mpirun -np 4 ./ex3