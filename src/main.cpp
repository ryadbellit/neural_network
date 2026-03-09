#include "helper.hpp"

#include <chrono>
#include <omp.h>

int main() {

    //omp_set_num_threads(8);

    int rows = 10;
    int columns = 10;

    Matrix matrix(rows, columns);
    Matrix matrix2(rows, columns);

    matrix.fillRandom();
    matrix2.fillRandom();

}