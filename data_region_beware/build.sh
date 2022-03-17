#!/bin/bash

nvc++ -Minfo=accel -ta=tesla:managed data_region.cpp -o data_region_managed
nvc++ -Minfo=accel -ta=tesla data_region.cpp -o data_region_unmanaged
nvc++ -Minfo=accel -ta=tesla no_data_region.cpp -o no_data_region