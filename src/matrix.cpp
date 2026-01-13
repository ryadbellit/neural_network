#include <matrix.hpp>
#include <algorithm>
#include <numeric>
#include <iomanip>

inline double& Matrix::operator()(int rows, int columns) {
    if (rows > this->rows || columns > this->columns || rows < 0 || columns < 0) {
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
                result.data_[rowResult + j] = val * other.data_[rowOther + j];
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
    return std::accumulate(data_.begin(), data_.end(), 0);
}

void Matrix::fill(double val = 0) {
    std::fill(data_.begin(), data_.end(), val);
}

Matrix Matrix::traspose() const {
    Matrix result(columns, rows);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            result(c, r) = (*this)(r, c);
        }
    }

    return result;
    
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    auto [r, c] = matrix.dim();
    
    os << "Matrix(" << r << "x" << c << "):\n";
    
    for (int i = 0; i < r; ++i) {
        os << "[ ";
        for (int j = 0; j < c; ++j) {
            os << std::setw(8) << matrix(i, j) << " ";
        }
        os << "]\n";
    }
    return os;
}