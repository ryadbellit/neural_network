#include "layer.hpp"
#include "helper.hpp"
#include <array>

Matrix Layer::forward(const Matrix& input) {
    
    Matrix result;
    lastInput = input;
    lastOutput = (input * weights) + biases;

    switch (activationFunction) {
        case Activation::RELU:
            Helper::ReLU(lastOutput);
            break;
        case Activation::SOFTMAX:
            Helper::softmax(lastInput);
            break;
        case Activation::NONE:
            result = lastOutput;
            break;
    }

    lastOutput = result;
    return result;

}

Matrix Layer::backward(const Matrix& outputGradient, const double learningRate) {
    return outputGradient * learningRate;
}

Matrix Layer::applyActivationDerivative(const Matrix& matrix) {
    return matrix;
}