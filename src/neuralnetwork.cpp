#include "neuralnetwork.hpp"

void NeuralNetwork::addLayer(const Layer& layer) {
    layers.push_back(layer);
}

Matrix NeuralNetwork::forward(Matrix& input) {
    Matrix result;
    for (auto& layer : layers) {
        result = layer.forward(input);
    }

    return result;
}

void NeuralNetwork::backward() const {
    
}