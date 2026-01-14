#include <matrix.hpp>

#include <algorithm>
#include <random>
#include <numeric>
#include <iomanip>
#include <chrono>

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

Matrix Matrix::softmax() const {
    Matrix result = Matrix(this->rows, this->columns);

    for (int i = 0; i < size(); i++) {
        result.data_[i] = std::pow(std::numbers::e, data_[i]);
    }

    result = result * (1 / result.sum());

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

double Matrix::determinant() const {
    if (rows != columns) {
        return 0;
    }
}


std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    auto [r, c] = matrix.dim();
    
    os << "Matrix(" << r << "x" << c << "):\n";
    
    for (int i = 0; i < r; i++) {
    for (int i = 0; i < r; i++) {
        os << "[ ";
        for (int j = 0; j < c; j++) {
            os << std::setw(10) << matrix(i, j) << " ";
        }
        os << "]\n";
    }
    return os;
}