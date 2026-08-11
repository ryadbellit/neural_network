#include "matrix.hpp"
#include <cmath>

enum class Activation { RELU, SOFTMAX, NONE };

class Layer {
public:
    
    Layer(const int inputSize, const int outputSize, const Activation act = Activation::NONE) : 
        weights(inputSize, outputSize), biases(1, outputSize), lastInput(), lastOutput(), activationFunction(act) {
        
        double bound;
        
        switch (activationFunction) {
            case Activation::RELU:
                bound = heInitialization(inputSize);
                break;
            case Activation::SOFTMAX:
            case Activation::NONE:
                bound = xavierInitialization(inputSize, outputSize);
                break;
        }

        weights.fillRandom(-bound, bound);
        biases.fill(0.0);
    }

    Matrix forward(const Matrix& input);
    Matrix backward(const Matrix& outputGradient, const double learningRate);
    Matrix getWeights() const { return weights; }
    Matrix getBiases() const { return biases; }
    
private:
    Matrix weights;
    Matrix biases;

    Matrix lastInput;
    Matrix lastOutput;

    Activation activationFunction;

    inline double xavierInitialization(const int inputSize, const int outputSize) const {
        return std::sqrt(2.0 / (inputSize + outputSize));
    }

    inline double heInitialization(const int inputSize) const {
        return std::sqrt(2.0 / inputSize);
    }

    Matrix applyActivationDerivative(const Matrix& matrix);
};