#include <matrix.hpp>

#include <algorithm>
#include <random>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <omp.h>

inline double& Matrix::operator()(int rows, int columns) {
    if (rows >= this->rows || columns >= this->columns || rows < 0 || columns < 0) {
        throw std::out_of_range("Position is out of bounds.");
    }
    return data_[rows * this->columns + columns];
}

inline double Matrix::operator()(int rows, int columns) const {
    if (rows > this->rows || columns > this->columns || rows < 0 || columns < 0) {
        throw std::out_of_range("Position is out of bounds.");
    }
    return data_[rows * this->columns + columns];
}


std::optional<Matrix> Matrix::operator*(const Matrix& other) const {
    if (this->columns != other.rows) {
        return std::nullopt;
    }
    
    Matrix result = Matrix(this->rows, other.columns);

    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < columns; k++) {

            double val = this->data_[i * this->columns + k];

            int rowResult = i * other.columns;
            int rowOther = k * other.columns;

            for (int j = 0; j < other.columns; j++) {
                result.data_[rowResult + j] += val * other.data_[rowOther + j];
            }
        }
    }

    return result;
}

std::optional<Matrix> Matrix::operator+(const Matrix& other) const {
    if (this->columns != other.columns || this->rows != other.rows) {
        return std::nullopt;
    }

    Matrix result = Matrix(this->rows, this->columns);

    std::transform(this->data_.begin(), this->data_.end(),
                    other.data_.begin(), result.data_.begin(),
                    std::plus<double>());

    return result;
}

std::optional<Matrix> Matrix::operator-(const Matrix& other) const {
    if (this->columns != other.columns || this->rows != other.rows) {
        return std::nullopt;
    }

    Matrix result = Matrix(this->rows, this->columns);

    std::transform(this->data_.begin(), this->data_.end(),
                    other.data_.begin(), result.data_.begin(),
                    std::minus<double>());

    return result;
}

Matrix Matrix::operator*(double scale) const {

    Matrix result = Matrix(this->rows, this->columns);

    std::transform(data_.begin(), data_.end(), result.data_.begin(),
                   [scale](double val) { return val * scale; });

    return result;
}

Matrix Matrix::operator/(double scale) const {
    Matrix result = Matrix(this->rows, this->columns);

    std::transform(data_.begin(), data_.end(), result.data_.begin(),
                   [scale](double val) { return val / scale; });

    return result;
}

double Matrix::sum() const {
    return std::accumulate(data_.begin(), data_.end(), 0.0);
}

void Matrix::fill(double val = 0) {
    std::fill(data_.begin(), data_.end(), val);
}

Matrix Matrix::transpose() const {
    Matrix result(columns, rows);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            result(c, r) = (*this)(r, c);
        }
    }

    return result;
    
}

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
    constexpr double epsilon = 1e-9;

    for (int i = 0; i < rows; i++) {

        double rowSum = 0.0;
        int offset = i * columns;

        for (int j = 0; j < columns; j++) {
            double e_x = std::exp(data_[offset + j]);
            result.data_[offset + j] = e_x;
            rowSum += e_x;
        }

        for (int j = 0; j < columns; j++) {
            result.data_[offset + j] /= (rowSum + epsilon); // Add epsilon to avoid division by 0
        }
    }

    return result;
}

Matrix Matrix::stable_softmax() const {

    Matrix result = Matrix(this->rows, this->columns);
    constexpr double epsilon = 1e-9;

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
            result.data_[offset + j] /= (rowSum + epsilon);
        }
    }

    return result;
}


bool Matrix::operator==(const Matrix& other) const {
    if (this->dim() != other.dim()) {
        return false;
    }

    return this->data_ == other.data_;
}

Matrix& Matrix::operator=(const Matrix& other) {
    
    if (this == &other) {
        return *this;
    }

    this->rows = other.rows;
    this->columns = other.columns;
    this->data_ = other.data_;

    return *this;
}

void Matrix::fillRandom(double lower, double upper) {

    static std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(lower, upper);

    std::generate(data_.begin(), data_.end(), [&]() { return distribution(generator); } );
}

double Matrix::maxValue() const {
    return *std::max_element(data_.begin(), data_.end());
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    auto [r, c] = matrix.dim();
    
    os << "Matrix(" << r << "x" << c << "):\n";
    
    for (int i = 0; i < r; i++) {
        os << "[ ";
        for (int j = 0; j < c; j++) {
            os << std::setw(10) << matrix(i, j) << " ";
        }
        os << "]\n";
    }

    return os;

}