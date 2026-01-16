#include <layer.hpp>

Matrix Layer::forward(const Matrix& input) {

    auto firstProduct = input * weights;
    if (!firstProduct) {
        throw std::runtime_error("Matrix sizes are not compatible");
    }
    
    auto z = firstProduct.value() + biases;

    if (!z) {
        throw std::runtime_error("Biases size is not compatible");
    }

    Matrix result(z.value().getRows(), z.value().getColumns());

    switch (type) {
        case Activation::RELU:
            result = z.value().relu();
            break;
        case Activation::SOFTMAX:
            result = z.value().stable_softmax();
            break;
        case Activation::NONE:
            result = z.value();
            break;
    }

    this->lastInput = input;
    this->lastOutput = result;

    return result;

}

Matrix Layer::backward(const Matrix& outputGradient, const double learningRate) {
    return outputGradient * learningRate;
}

Matrix Layer::applyActivation(const Matrix& matrix) {
    return matrix;
}

Matrix Layer::applyActivationDerivative(const Matrix& matrix) {
    return matrix;
}