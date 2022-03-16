Required modules:
```
module unload compilers mpi
module load compilers/nvidia/hpc-sdk/22.2
```

To compile:
```
nvc++ -acc -ta=tesla -Minfo=accel -o saxpy main.cpp
```

Replace `tesla` with `multicore` for CPU.
