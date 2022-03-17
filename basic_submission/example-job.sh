#!/bin/bash -l

# Request ten minutes of wallclock time (format hours:minutes:seconds).
#$ -l h_rt=0:10:0

# Request 1 gigabyte of RAM (must be an integer followed by M, G, or T)
#$ -l mem=10G

# Set the name of the job.
#$ -N PHAS0100

# Set the working directory to the submission directory.
#$ -cwd

echo -n "This script is running on "
hostname