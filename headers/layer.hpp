#include <matrix.hpp>

class Layer {
public:

    Matrix weights;
    Matrix biases;
    Matrix lastInput;

    Matrix forward(const Matrix& input);
    Matrix backward(const Matrix& outputGradient, const double learningRate);
};