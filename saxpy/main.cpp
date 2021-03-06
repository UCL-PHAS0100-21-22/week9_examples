#include <iostream>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main() {

    const int N = 250 * 1024 * 1024; // 250 * 1024 * 1024 floats ~ 1 GB

    const float a = 3.0f;

    float *result = new float[N];
    float *x = new float[N];
    float *y = new float[N];

    auto start = high_resolution_clock::now();

    for(int i=0; i<N; ++i) {
        x[i] = 2.0f;
        y[i] = 1.0f;
    }

    for(int i=0; i<N; ++i) {
        result[i] = a*x[i] + y[i];
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << result[0] << std::endl;
    std::cout << "Time for " << N << " iterations: " << duration.count() << std::endl;

    delete [] result;
    delete [] x;
    delete [] y;

    return 0;
}
