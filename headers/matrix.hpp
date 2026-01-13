#include <vector>
#include <iostream>
#include <optional>
#include <utility>
class Matrix {
public:

    Matrix(const int rows, const int columns, const double def_val = 0.0) : rows(rows), columns(columns),  
        data_(std::vector<double>(columns * rows, def_val)) {}

    Matrix(const int rows, const int columns, const std::vector<double>& data) : rows(rows), columns(columns), data_(data) {}

    Matrix(const Matrix& matrix) : Matrix(matrix.rows, matrix.columns, matrix.data_) {}

    int getColumns() const { return columns; }
    int getRows() const { return rows; }
    std::pair<double, double> dim() const { return {rows, columns}; }

    double& operator()(int rows, int columns);
    double operator()(int rows, int columns) const;
    std::optional<Matrix> operator*(const Matrix& other) const;
    Matrix operator*(double scale) const;
    std::optional<Matrix> operator+(const Matrix& other) const;
    std::optional<Matrix> operator-(const Matrix& other) const;
    
    Matrix scale(double scale);
    double sum() const;
    

private:
    int rows;
    int columns;
    std::vector<double> data_;

};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
