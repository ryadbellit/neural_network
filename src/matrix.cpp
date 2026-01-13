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
    

    return Matrix(other.rows, other.columns);
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

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    auto [r, c] = matrix.dim(); // Utilisation de votre fonction dim()
    
    os << "Matrix(" << r << "x" << c << "):\n";
    
    for (int i = 0; i < r; ++i) {
        os << "[ ";
        for (int j = 0; j < c; ++j) {
            // std::setw(8) assure que chaque nombre occupe 8 caractères
            // pour que les colonnes soient bien alignées
            os << std::setw(8) << matrix(i, j) << " ";
        }
        os << "]\n";
    }
    return os;
}