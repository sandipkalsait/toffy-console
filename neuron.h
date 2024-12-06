#pragma once
#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <functional>
#include <random>
#include <cmath>

class Neuron {
public:
    Neuron(int num_inputs, std::function<double(double)> activation_func);

    double forward(const std::vector<double>& inputs);
    void updateWeights(double learning_rate, const std::vector<double>& prev_layer_outputs);

    double getOutput() const { return output; }

private:
    std::vector<double> weights;  // Weights for each input
    double bias;
    double output;
    std::function<double(double)> activation_func;  // Activation function

    static std::random_device rd;
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution;
};

#endif // NEURON_H
