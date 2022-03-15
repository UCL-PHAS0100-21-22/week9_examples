#!/bin/bash -l

# Batch script to run a GPU job under SGE.

# Request a number of GPU cards, in this case 2 (the maximum)
#$ -l gpu=1

# Request ten minutes of wallclock time (format hours:minutes:seconds).
#$ -l h_rt=0:10:0

# Request 1 gigabyte of RAM (must be an integer followed by M, G, or T)
#$ -l mem=10G

# Set the name of the job.
#$ -N PHAS0100-gpu

# Set the working directory to the submission directory.
#$ -cwd

# load the cuda module (in case you are running a CUDA program)
module unload compilers mpi
module load compilers/nvidia/hpc-sdk/22.2

# Run the application - the line below is just a random example.
nvidia-smi