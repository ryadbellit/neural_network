#include <matrix.hpp>

enum class Activation { RELU, SOFTMAX, NONE };

class Layer {
public:
    
    Layer(int inputSize, int outputSize, Activation act = Activation::NONE) : 
        weights(inputSize, outputSize), biases(1, outputSize), 
        lastInput(0, 0), lastOutput(0, 0), type(act) {
        
        double scale;
        switch (type) {
            case Activation::RELU:
                scale = std::sqrt(2.0 / inputSize); // Xavier initialization
                break;
            case Activation::SOFTMAX:
                scale = std::sqrt(2.0 / inputSize + outputSize); // He initialization
                break;
            case Activation::NONE:
                scale = 0.5;
                break;
        }

        weights.fillRandom(-scale, scale);
        biases.fill(0.01);
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

    Activation type;

    Matrix applyActivation(const Matrix& matrix);
    Matrix applyActivationDerivative(const Matrix& matrix);
};