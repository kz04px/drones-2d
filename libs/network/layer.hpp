#ifndef NETWORK_LAYER_HPP
#define NETWORK_LATER_HPP

#include <array>
#include <cstddef>
#include <fstream>

template <std::size_t a, std::size_t b>
struct Layer {
    static constexpr std::size_t dim_in = a;
    static constexpr std::size_t dim_out = b;

    void load(std::ifstream &fs) {
        for (std::size_t i = 0; i < dim_in; ++i) {
            for (std::size_t j = 0; j < dim_out; ++j) {
                fs.read(reinterpret_cast<char *>(&weights[i][j]), sizeof(float));
            }
        }

        for (std::size_t j = 0; j < dim_out; ++j) {
            fs.read(reinterpret_cast<char *>(&biases[j]), sizeof(float));
        }
    }

    [[nodiscard]] auto run(const std::array<float, dim_in> &inputs) const noexcept {
        std::array<float, dim_out> outputs;
        for (std::size_t j = 0; j < dim_out; ++j) {
            outputs[j] = biases[j];
            for (std::size_t i = 0; i < dim_in; ++i) {
                outputs[j] += inputs[i] * weights[i][j];
            }
        }
        return outputs;
    }

    float weights[dim_in][dim_out] = {};
    float biases[dim_out] = {};
};

#endif
