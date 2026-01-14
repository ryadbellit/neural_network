#include <matrix.hpp>

int main() {

    std::vector<double> data;

    for (int i = 0; i < 100; i++) {
        data.push_back(i);
    }

    Matrix matrix(10, 10, data);

    std::vector<double> data2;

    for (int i = 100; i >= 0; i--) {
        data2.push_back(i);
    }

    Matrix matrix2(10, 10, data2);

    Matrix matrix3 = *(matrix - matrix2);

    std::cout << matrix << std::endl;
    std::cout << matrix2 << std::endl;
    std::cout << matrix3 << std::endl;

    std::cout << matrix.relu() << std::endl;
}