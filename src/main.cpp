#include <matrix.hpp>

#include <chrono>
#include <omp.h>

int main() {

    omp_set_num_threads(8);

    int rows = 1000 ;
    int columns = 1000;

    Matrix matrix(rows, columns);
    Matrix matrix2(rows, columns);

    matrix.fillRandom();
    matrix2.fillRandom();

    auto start = std::chrono::steady_clock::now();

    std::cout << matrix.stable_softmax().sum() << std::endl;

    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

    std::cout << "Fini!" << std::endl;
    std::cout << "Temps : " << duration.count() << " secondes" << std::endl;

}