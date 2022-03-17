#include <iostream>

int main() {
  float A[1000];

  #pragma acc data copy(A)
  {
    #pragma acc parallel loop
    for( int iter = 1; iter < 1000 ; iter++){
      A[iter] = 1.0;
    }

    A[10] = 2.0;
  }

  std::cout << A[10] << std::endl;
}
