#include "layer.h"
#include <iostream>

Layer::Layer(int num_neurons, int num_inputs_per_neuron, std::function<double(double)> activation_func) {
    for (int i = 0; i < num_neurons; ++i) {
        neurons.push_back(Neuron(num_inputs_per_neuron, activation_func));
    }
}

std::vector<double> Layer::forward(const std::vector<double>& inputs) {
    std::vector<double> outputs;
    for (auto& neuron : neurons) {
        outputs.push_back(neuron.forward(inputs));
    }
    return outputs;
}

void Layer::backpropagate(const std::vector<double>& outputs, const std::vector<double>& prev_layer_outputs, double learning_rate) {
    for (size_t i = 0; i < neurons.size(); ++i) {
        neurons[i].updateWeights(learning_rate, prev_layer_outputs);
    }
}
