#include <matrix.hpp>

#include <chrono>


int main() {

    int rows = 1000;
    int columns = 1000;

    Matrix matrix(rows * 10, columns * 10);
    Matrix matrix2(rows * 10, columns * 10);

    matrix.fillRandom();
    matrix2.fillRandom();

    auto start = std::chrono::steady_clock::now();

    Matrix matrix3 = *(matrix * matrix2);

    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);


    std::cout << "Fini!" << std::endl;
    std::cout << "Temps : " << duration.count() << "secondes" << std::endl;

}