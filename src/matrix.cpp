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

    if (scale == 0) {
        throw std::invalid_argument("Division by 0");
    }
    
    Matrix result = Matrix(this->rows, this->columns);

    std::transform(data_.begin(), data_.end(), result.data_.begin(),
                   [scale](double val) { return val / scale; });

    return result;
}

Matrix& Matrix::operator*=(double scale) {
    std::transform(data_.begin(), data_.end(), data_.begin(),
                   [scale](double val) { return val * scale; });
    return *this;
}

Matrix& Matrix::operator/=(double scale) {
    if (scale == 0) {
        throw std::invalid_argument("Division by 0");
    }
    std::transform(data_.begin(), data_.end(), data_.begin(),
                   [scale](double val) { return val / scale; });

    return *this;
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

bool Matrix::operator==(const Matrix& other) const noexcept {

    if (this->dim() != other.dim()) {
        return false;
    }

    return this->data_ == other.data_;
}

Matrix& Matrix::operator=(const Matrix& other) {

    if (this != &other) {
        this->rows = other.rows;
        this->columns = other.columns;
        this->data_ = other.data_;
    }

    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        rows = other.rows;
        columns = other.columns;
        other.rows = 0;
        other.columns = 0;
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

Matrix& Matrix::operator+=(const Matrix& other) {
    std::transform(data_.begin(), data_.end(), other.data_.begin(), data_.begin(), std::plus<double>());
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    std::transform(data_.begin(), data_.end(), other.data_.begin(), data_.begin(), std::minus<double>());
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
    if (this->columns != other.rows) {
        throw std::invalid_argument("Invalid matrices dimensions");
    }

    Matrix result(this->rows, other.columns);

    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        for (int k = 0; k < columns; k++) {
            double val = this->data_[i * this->columns + k];
            for (int j = 0; j < other.columns; j++) {
                result.data_[i * other.columns + j] += val * other.data_[k * other.columns + j];
            }
        }
    }

    *this = std::move(result); 
    return *this;
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