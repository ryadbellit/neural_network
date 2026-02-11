#include <matrix.hpp>

#include <algorithm>
#include <random>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <stdexcept>
#include <omp.h>


double& Matrix::operator()(int rows, int columns) {
    if (rows >= this->rows || columns >= this->columns || rows < 0 || columns < 0) {
        throw std::out_of_range("Position is out of bounds.");
    }
    return data_[rows * this->columns + columns];
}

double Matrix::operator()(const int rows, const int columns) const {
    if (rows >= this->rows || columns >= this->columns || rows < 0 || columns < 0) {
        throw std::out_of_range("Position is out of bounds.");
    }
    return data_[rows * this->columns + columns];
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (this->columns != other.rows) {
        throw std::invalid_argument("Invalid matrices dimensions");
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

Matrix Matrix::operator+(const Matrix& other) const {
    if (dim() != other.dim()) {
        throw std::invalid_argument("Matrices should have the same dimensions");
    }

    Matrix result = Matrix(this->rows, this->columns);

    std::transform(this->data_.begin(), this->data_.end(),
                    other.data_.begin(), result.data_.begin(),
                    std::plus<double>());

    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (dim() != other.dim()) {
        throw std::invalid_argument("Matrices should have the same dimensions");
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

        int offset = r * columns;

        for (int c = 0; c < columns; c++) {
            result.data_[c * rows + r] = data_[offset + c];
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


bool Matrix::operator==(const Matrix& other) const noexcept {

    if (this->dim() != other.dim()) {
        return false;
    }

    return this->data_ == other.data_;
}

Matrix& Matrix::operator=(const Matrix& other) noexcept { // no except needed for std::move()

    if (this != &other) {
        this->rows = other.rows;
        this->columns = other.columns;
        this->data_ = std::move(other.data_);
    }

    return *this;
}

void Matrix::fillRandom(double lower, double upper) {

    static std::mt19937 generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> distribution(lower, upper);

    std::generate(data_.begin(), data_.end(), [&]() { return distribution(generator); } );
}

Matrix Matrix::elementMultiplication(const Matrix& other) {

    if (dim() != other.dim()) {
        throw std::invalid_argument("Matrices should have the same dimensions");
    }
    
    Matrix result(*this);

    std::transform(this->data_.begin(), this->data_.end(),
                other.data_.begin(), result.data_.begin(),
                std::multiplies<double>());

    return result;
}

Matrix Matrix::elementDivision(const Matrix& other) {

    if (dim() != other.dim()) {
        throw std::invalid_argument("Matrices should have the same dimensions");
    }
    
    Matrix result(*this);

    std::transform(this->data_.begin(), this->data_.end(),
                other.data_.begin(), result.data_.begin(),
                std::divides<double>());

    return result;
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