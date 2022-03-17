#!/bin/bash

nvc++ -Minfo=accel -ta=tesla:managed main.cpp -o saxpy
nvc++ -Minfo=accel -ta=multicore main.cpp -o saxpy_multicore
