#pragma once
#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "layer.h"
#include <vector>
#include <functional>

class NeuralNetwork {
public:
    NeuralNetwork(const std::vector<int>& layer_sizes, std::vector<std::function<double(double)>> activation_funcs);

    std::vector<double> forward(const std::vector<double>& inputs);
    void train(const std::vector<std::vector<double>>& inputs, const std::vector<std::vector<double>>& outputs, double learning_rate, int epochs);

private:
    std::vector<Layer> layers;
    std::vector<std::function<double(double)>> activation_funcs;
};

#endif // NEURAL_NETWORK_H
