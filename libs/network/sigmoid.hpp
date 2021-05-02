#ifndef NETWORK_SIGMOID_HPP
#define NETWORK_SIGMOID_HPP

#include <array>
#include <cmath>

template <std::size_t size>
[[nodiscard]] auto sigmoid(const std::array<float, size> &input) {
    std::array<float, size> output;
    for (std::size_t i = 0; i < size; ++i) {
        output[i] = 1.0f / (1.0f + std::exp(-input[i]));
    }
    return output;
}

#endif
