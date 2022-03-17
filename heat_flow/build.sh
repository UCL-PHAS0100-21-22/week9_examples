#!/bin/bash

nvc++ -Minfo=accel -ta=tesla:managed -o heat_flow main.cpp
nvc++ -Minfo=accel -ta=multicore -o heat_flow_multicore main.cpp
nvc++ -fopenmp -o heat_flow_openmp main_openmp.cpp