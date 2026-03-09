#include "matrix.hpp"

namespace Helper {

    double loss(const Matrix& result, int answer);

    Matrix oneHotEncoding(const int label, const int numLabels);

    void ReLU(Matrix& matrix);
    void softmax(Matrix& matrix);
}
