#include <iostream>
#include <omp.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    omp_set_num_threads(12);
    int n = omp_get_num_threads();
    std::cout << n << std::endl;

#pragma omp parallel for
    for (int i = 0; i < 12; ++i) {
        std::cout << "Hello, I am " << i << " thread!" << std::endl;
    }

    return 0;
}