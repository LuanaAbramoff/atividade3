#!/bin/bash
#SBATCH --job-name=ex6
#SBATCH --output=ex6.txt
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=4
#SBATCH --mem=1024MB
#SBATCH --time=00:05:00

mpirun -np 4 ./ex6