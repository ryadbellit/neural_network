#include <vector>

class Matrix {
public:

    Matrix(const int cols, const int rows, const double def_val = 0) : columns(cols), rows(rows) {
        data_ = std::vector<double>(cols * rows, def_val);
    }

    Matrix(const Matrix& matrix) : columns(matrix.columns), rows(matrix.rows), data_(matrix.data_) {}

    Matrix(const std::vector<double>& data, const int cols, const int rows) : data_(data) {}

    int getColumns() const { return columns; }
    int getRows() const { return rows; }
    std::vector<double> getData() { return data_; }

private:
    std::vector<double> data_;
    int columns, rows;

};