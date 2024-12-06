#include "neural_network.h"
#include <iostream>

NeuralNetwork::NeuralNetwork(const std::vector<int>& layer_sizes, std::vector<std::function<double(double)>> activation_funcs)
    : activation_funcs(activation_funcs) {
    for (size_t i = 0; i < layer_sizes.size() - 1; ++i) {
        layers.push_back(Layer(layer_sizes[i + 1], layer_sizes[i], activation_funcs[i]));
    }
}

std::vector<double> NeuralNetwork::forward(const std::vector<double>& inputs) {
    std::vector<double> outputs = inputs;
    for (auto& layer : layers) {
        outputs = layer.forward(outputs);
    }
    return outputs;
}

void NeuralNetwork::train(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& outputs, double learning_rate, int epochs) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = 0; i < inputs.size(); ++i) {
            std::vector<double> prediction = forward(inputs[i]);
            std::vector<double> error(outputs[i].size());
            for (size_t j = 0; j < outputs[i].size(); ++j) {
                error[j] = outputs[i][j] - prediction[j];  // Calculate error
            }
            // Backpropagation through layers
            for (int l = layers.size() - 1; l >= 0; --l) {
                layers[l].backpropagate(error, inputs[i], learning_rate);
            }
        }
    }
}
