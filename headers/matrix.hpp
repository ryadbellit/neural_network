#include <vector>
#include <iostream>

class Matrix {
public:

    Matrix() : rows(0), columns(0), data_(std::vector<double>()) {}
    Matrix(const int rows, const int columns, const double def_val = 0.0) : rows(rows), columns(columns),  
        data_(std::vector<double>(columns * rows, def_val)) {}

    Matrix(const int rows, const int columns, const std::vector<double>& data) : rows(rows), columns(columns), data_(data) {}
    Matrix(const Matrix& matrix) : Matrix(matrix.rows, matrix.columns, matrix.data_) {}
    Matrix(Matrix&& other) noexcept : rows(other.rows), columns(other.columns), data_(std::move(other.data_)) {
        other.rows = 0;
        other.columns = 0;
    }

    int getRows() const { return rows; }
    int getColumns() const { return columns; }
    int size() const { return columns * rows; }
    std::pair<int, int> dim() const { return {rows, columns}; }

    double& operator()(int rows, int columns);
    double operator()(const int rows, const int columns) const;

    Matrix operator*(double scale) const;
    Matrix operator/(double scale) const;

    Matrix& operator*=(double scale);
    Matrix& operator/=(double scale);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    
    
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    bool operator==(const Matrix& other) const noexcept;

    Matrix relu() const;
    Matrix reluDerivative() const;
    Matrix softmax() const;
    Matrix stable_softmax() const;
    double sum() const;
    void fill(double val);
    Matrix transpose() const;
    void fillRandom(double lower = -10, double upper = 10);
    double maxValue() const;
    Matrix elementMultiplication(const Matrix& other);
    Matrix elementDivision(const Matrix& other);

private:
    int rows;
    int columns;
    std::vector<double> data_;

};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
