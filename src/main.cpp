#include <matrix.hpp>

int main() {

    int rows = 10;
    int columns = 3;

    Matrix matrix(rows, columns);

    matrix.fillRandom();

    std::cout << matrix << std::endl;
    matrix = matrix.softmax();

    std::cout << matrix << std::endl;

    Matrix matrix2(matrix.transpose());

    std::cout << matrix2 << std::endl;

    

}