#ifndef LAYER_H
#define LAYER_H

#include "neuron.h"
#include <vector>
#include <functional>

class Layer {
public:
    Layer(int num_neurons, int num_inputs_per_neuron, std::function<double(double)> activation_func);
    std::vector<double> forward(const std::vector<double>& inputs);
    void backpropagate(const std::vector<double>& outputs, const std::vector<double>& prev_layer_outputs, double learning_rate);

    std::vector<Neuron>& getNeurons() { return neurons; }

private:
    std::vector<Neuron> neurons;
};

#endif // LAYER_H
#pragma once
