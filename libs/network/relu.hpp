#ifndef NETWORK_RELU_HPP
#define NETWORK_RELU_HPP

#include <array>

template <std::size_t size>
[[nodiscard]] auto ReLU(const std::array<float, size> &input) {
    std::array<float, size> output;
    for (std::size_t i = 0; i < size; ++i) {
        output[i] = std::max(0.0f, input[i]);
    }
    return output;
}

#endif
