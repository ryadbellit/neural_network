#include <layer.hpp>
#include <array>

Matrix Layer::forward(const Matrix& input) {
    
    Matrix output = (input * weights) + biases;

    Matrix result(output.getRows(), output.getColumns());

    switch (type) {
        case Activation::RELU:
            result = output.relu();
            break;
        case Activation::SOFTMAX:
            result = output.stable_softmax();
            break;
        case Activation::NONE:
            result = output;
            break;
    }

    this->lastInput = input;
    this->lastOutput = result;

    return result;

}

double Layer::loss(const Matrix& result, int answer) {
    constexpr double epsilon = 1e-15;

    return -std::log(result(0, answer) == 0 ? epsilon : result(0, answer));
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