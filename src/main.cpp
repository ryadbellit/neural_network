#include "matrix.hpp"
#include <vector>
#include <iostream>

int main() {

    std::vector<double> data;

    for (int i = 0; i < 100; i++) {
        data.push_back(i);
    }

    Matrix matrix(data, 10, 10);

}