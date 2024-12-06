#pragma once
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <cmath>

// ReLU Activation Function
inline double relu(double x) {
    return x > 0 ? x : 0;
}

// Sigmoid Activation Function
inline double sigmoid(double x) {
    return 1.0 / (1.0 + std::exp(-x));
}

// Tanh Activation Function
inline double tanh(double x) {
    return std::tanh(x);
}

#endif // ACTIVATION_H
