// Adapted from John Urbaniac's OpenACC temperature example
// From Pittsburgh Supercomputing Center

#include <iostream>
#include <cmath>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

typedef double real;

const int COLUMNS = 1000;
const int ROWS = 1000;

// Largest permitted change in temp (should take 3400 steps)
const real MAX_TEMP_ERROR = 0.01;
const int MAX_ITERATIONS = 4000;

void initialise(real *array);
void track_progress(const int iterations, const real *temp);

inline int idx(const int i, const int j) {
  return i*(ROWS+2) + j;
}

int main() {
    const int TOTAL_SIZE = (ROWS+2)*(COLUMNS+2);
    real * temperature = new real[TOTAL_SIZE];
    real * temperature_last = new real[TOTAL_SIZE];

    initialise(temperature);
    initialise(temperature_last);

    auto start = high_resolution_clock::now();

    int iterations = 0;
    real dt = MAX_TEMP_ERROR + 1.0;
    while (dt > MAX_TEMP_ERROR && iterations <= MAX_ITERATIONS) {
#pragma omp parallel for collapse(2)
        for(int i=1; i<ROWS+1; ++i) {
            for(int j=1; j<COLUMNS+1; ++j) {
                temperature[idx(i,j)] = 0.25*(
                      temperature_last[idx(i+1,j)]
                    + temperature_last[idx(i-1,j)]
                    + temperature_last[idx(i,j-1)]
                    + temperature_last[idx(i,j+1)]
                );
            }
        }

        dt = 0.0;

#pragma omp parallel for collapse(2) reduction(max:dt)
        for(int i=1; i<ROWS+1; ++i) {
            for(int j=1; j<COLUMNS+1; ++j) {
                dt = std::max(std::abs(temperature[idx(i,j)] - temperature_last[idx(i,j)]), dt);
                temperature_last[idx(i,j)] = temperature[idx(i,j)];
            }
        }

        if(iterations % 300 == 0) {
            track_progress(iterations, temperature);
        }

        iterations += 1;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "Max error: " << dt << std::endl;
    std::cout << "Total time for " << iterations-1 << " iterations: " << duration.count() << " ms" << std::endl;
}

void initialise(real *array) {
    // Initialise interior to 0
    for(int i=1; i<ROWS+1; ++i) {
        for(int j=1; j<COLUMNS+1; ++j) {
            array[idx(i,j)] = 0.0;
        }
    }

    // Initialise boundaries
    for(int i=0; i < ROWS+2; ++i) {
        array[idx(i,0)] = 0.0;
        array[idx(i,COLUMNS+1)] = (100.0/ROWS)*i;
    }
    for(int j=0; j < COLUMNS+2; ++j) {
        array[idx(0,j)] = 0.0;
        array[idx(ROWS+1,j)] = (100.0/COLUMNS)*j;
    }
}

void track_progress(const int iterations, const real *temp) {
    std::cout << "----- Iteration number: " << iterations << "-----" << std::endl;
    for(int i=ROWS-5; i<ROWS+1; ++i) {
        std::cout << "[" << i << ", " << i << "]: " << temp[idx(i,i)] << std::endl;
    }
}
