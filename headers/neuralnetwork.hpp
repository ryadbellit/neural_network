#include "layer.hpp"

class NeuralNetwork {
public:
    NeuralNetwork() = default;
    void addLayer(const Layer& layer);
    Matrix forward(Matrix& input);
    void backward() const;

private:
    std::vector<Layer> layers;
};