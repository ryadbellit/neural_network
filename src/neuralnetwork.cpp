#include "neuralnetwork.hpp"

/*
Matrix Matrix::relu() const {
    
    Matrix result = Matrix(this->rows, this->columns);

    std::transform(data_.begin(), data_.end(), result.data_.begin(),
                   [](double val) { return std::max(val, 0.0); });

    return result;
}

Matrix Matrix::reluDerivative() const {

    Matrix result = Matrix(this->rows, this->columns);

    std::transform(data_.begin(), data_.end(), result.data_.begin(),
                   [](double val) { return val > 0 ? 1.0 : 0.0 ; });

    return result;
}

Matrix Matrix::softmax() const {

    Matrix result = Matrix(this->rows, this->columns);

    for (int i = 0; i < rows; i++) {

        double rowSum = 0.0;
        int offset = i * columns;

        for (int j = 0; j < columns; j++) {
            double e_x = std::exp(data_[offset + j]);
            result.data_[offset + j] = e_x;
            rowSum += e_x;
        }

        for (int j = 0; j < columns; j++) {
            result.data_[offset + j] /= (rowSum);
        }
    }

    return result;
}

Matrix Matrix::stable_softmax() const {

    Matrix result = Matrix(this->rows, this->columns);

    for (int i = 0; i < rows; i++) {

        int offset = i * columns;
        double rowMax = data_[offset];

        for (int j = 1; j < columns; j++) {
            rowMax = std::max(rowMax, data_[offset + j]);
        }

        double rowSum = 0.0;
        for (int j = 0; j < columns; j++) {
            double e_x = std::exp(data_[offset + j] - rowMax);
            result.data_[offset + j] = e_x;
            rowSum += e_x;
        }

        for (int j = 0; j < columns; j++) {
            result.data_[offset + j] /= rowSum;
        }
    }

    return result;
}
*/