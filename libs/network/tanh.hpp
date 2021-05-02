#ifndef NETWORK_TANH_HPP
#define NETWORK_TANH_HPP

#include <array>
#include <cmath>

template <std::size_t size>
[[nodiscard]] auto tanh(const std::array<float, size> &input) {
    std::array<float, size> output;
    for (std::size_t i = 0; i < size; ++i) {
        output[i] = tanh(input[i]);
    }
    return output;
}

#endif
