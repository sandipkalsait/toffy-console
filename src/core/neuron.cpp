#include "neuron.h"
#include <iostream>
#include <numeric>

std::random_device Neuron::rd;
std::default_random_engine Neuron::generator(rd());
std::uniform_real_distribution<double> Neuron::distribution(-1.0, 1.0);

Neuron::Neuron(int num_inputs, std::function<double(double)> activation_func)
    : activation_func(activation_func), bias(distribution(generator)) {
    for (int i = 0; i < num_inputs; ++i) {
        weights.push_back(distribution(generator));  // Random weights initialization
    }
}

double Neuron::forward(const std::vector<double>& inputs) {
    double sum = bias;
    for (size_t i = 0; i < inputs.size(); ++i) {
        sum += inputs[i] * weights[i];
    }
    output = activation_func(sum);  // Apply activation function
    return output;
}

void Neuron::updateWeights(double learning_rate, const std::vector<double>& prev_layer_outputs) {
    for (size_t i = 0; i < prev_layer_outputs.size(); ++i) {
        weights[i] -= learning_rate * prev_layer_outputs[i];  // Gradient descent update
    }
    bias -= learning_rate;  // Update bias
}
