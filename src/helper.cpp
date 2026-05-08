#include "helper.hpp"
#include "algorithm"
#include <cmath>

double Helper::loss(const Matrix& result, const int answer) {
    constexpr double epsilon = 1e-15;

    return -std::log(result(0, answer) == 0 ? epsilon : result(0, answer));
}

Matrix Helper::oneHotEncoding(const int label, const int numLabels) {
    Matrix encoded(1, numLabels);
    encoded(0, label) = 1.0;

    return encoded;
}

void Helper::ReLU(Matrix& matrix) {
    std::transform(matrix.getData().begin(), matrix.getData().end(), matrix.getData().begin(),
                    [](double val) { return std::max(val, 0.0); });
}

void Helper::softmax(Matrix& matrix) {

    const int rows = matrix.getRows();
    const int columns = matrix.getColumns();

    for (int i = 0; i < rows; i++) {

        int offset = i * columns;
        double rowMax = matrix.getData()[offset];

        for (int j = 1; j < columns; j++) {
            rowMax = std::max(rowMax, matrix.getData()[offset + j]);
        }

        double rowSum = 0.0;
        for (int j = 0; j < columns; j++) {
            double e_x = std::exp(matrix.getData()[offset + j] - rowMax);
            matrix.getData()[offset + j] = e_x;
            rowSum += e_x;
        }

        for (int j = 0; j < columns; j++) {
            matrix.getData()[offset + j] /= rowSum;
        }
    }

}
