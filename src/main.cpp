#include "matrix.hpp"
#include <vector>
#include <iostream>

void main() {

    std::vector<double> data;

    for (int i = 0; i < 100; i++) {
        data.push_back(i);
    }

    Matrix matrix(data, 10, 10);

    for (double num : matrix.getData()) {
        std::cout << num << std::endl;
    }
}