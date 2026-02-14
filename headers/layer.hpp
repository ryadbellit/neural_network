#include <matrix.hpp>
#include <cmath>

enum class Activation { RELU, SOFTMAX, NONE };

class Layer {
public:
    
    Layer(int inputSize, int outputSize, Activation act = Activation::NONE) : 
        weights(inputSize, outputSize), biases(1, outputSize), 
        lastInput(0, 0), lastOutput(0, 0), type(act) {
        
        double bound;
        
        switch (type) {
            case Activation::RELU:
                bound = heInitialization(inputSize);
                break;
            case Activation::SOFTMAX:
                bound = xavierInitialization(inputSize, outputSize);
                break;
            case Activation::NONE:
                bound = xavierInitialization(inputSize, outputSize);
                break;
        }

        weights.fillRandom(-bound, bound);
        biases.fill(0.0);
    }

    Matrix forward(const Matrix& input);
    Matrix backward(const Matrix& outputGradient, const double learningRate);
    double loss(const Matrix& result, int answer);
    Matrix getWeights() const { return weights; }
    Matrix getBiases() const { return biases; }
    
private:
    Matrix weights;
    Matrix biases;

    Matrix lastInput;
    Matrix lastOutput;

    Activation type;

    inline double xavierInitialization(int inputSize, int outputSize) {
        return std::sqrt(2.0 / (inputSize + outputSize));
    }

    inline double heInitialization(int inputSize) {
        return std::sqrt(2.0 / inputSize);
    }

    Matrix applyActivation(const Matrix& matrix);
    Matrix applyActivationDerivative(const Matrix& matrix);
};