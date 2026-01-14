#include "matrix.hpp"

int main() {

    std::vector<double> data;
    bool negative = false;
    int rows = 50;
    int columns = 3;

    for (int i = 0; i < rows * columns; i++) {
        data.push_back(i * (negative ? -1 : 1));
        negative = !negative;
    }

    Matrix matrix(rows, columns, data);

    std::cout << matrix << std::endl;

    std::cout << matrix.relu() << std::endl;
}