#include <layer.hpp>
#include <array>

Matrix Layer::forward(const Matrix& input) {
    
    Matrix output = (input * weights) + biases;

    Matrix result(output.getRows(), output.getColumns());
    lastInput = input;
    lastOutput = output;

    switch (activationFunction) {
        case Activation::RELU:
            //result = output.relu();
            break;
        case Activation::SOFTMAX:
            //result = output.stable_softmax();
            break;
        case Activation::NONE:
            result = output;
            break;
    }

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