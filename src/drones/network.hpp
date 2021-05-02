#ifndef SIMULATION_NETWORK_HPP
#define SIMULATION_NETWORK_HPP

#include <array>
#include <fstream>
#include <functional>
#include <network/layer.hpp>
#include <network/sigmoid.hpp>
#include <network/tanh.hpp>

struct Network {
    using Layer1Type = Layer<7, 9>;
    using Layer2Type = Layer<9, 4>;

    void load(std::ifstream &fs) {
        layer1.load(fs);
        layer2.load(fs);
    }

    [[nodiscard]] auto run() const noexcept {
        const auto a = tanh(layer1.run(inputs));
        const auto b = tanh(layer2.run(a));
        return b;
    }

    void cross(const Network &other) noexcept {
        // Layer 1
        for (std::size_t i = 0; i < Layer1Type::dim_in; ++i) {
            for (std::size_t j = 0; j < Layer1Type::dim_out; ++j) {
                if (rand() % 2) {
                    layer1.weights[i][j] = other.layer1.weights[i][j];
                }
            }
        }
        for (std::size_t j = 0; j < Layer1Type::dim_out; ++j) {
            if (rand() % 2) {
                layer1.biases[j] = other.layer1.biases[j];
            }
        }

        // Layer 2
        for (std::size_t i = 0; i < Layer2Type::dim_in; ++i) {
            for (std::size_t j = 0; j < Layer2Type::dim_out; ++j) {
                if (rand() % 2) {
                    layer2.weights[i][j] = other.layer2.weights[i][j];
                }
            }
        }
        for (std::size_t j = 0; j < Layer2Type::dim_out; ++j) {
            if (rand() % 2) {
                layer2.biases[j] = other.layer2.biases[j];
            }
        }
    }

    void set(const std::function<float()> &func) {
        // Layer 1
        for (std::size_t i = 0; i < Layer1Type::dim_in; ++i) {
            for (std::size_t j = 0; j < Layer1Type::dim_out; ++j) {
                layer1.weights[i][j] = func();
            }
        }
        for (std::size_t j = 0; j < Layer1Type::dim_out; ++j) {
            layer1.biases[j] = func();
        }

        // Layer 2
        for (std::size_t i = 0; i < Layer2Type::dim_in; ++i) {
            for (std::size_t j = 0; j < Layer2Type::dim_out; ++j) {
                layer2.weights[i][j] = func();
            }
        }
        for (std::size_t j = 0; j < Layer2Type::dim_out; ++j) {
            layer2.biases[j] = func();
        }
    }

    void offset(const std::function<float()> &func) {
        // Layer 1
        for (std::size_t i = 0; i < Layer1Type::dim_in; ++i) {
            for (std::size_t j = 0; j < Layer1Type::dim_out; ++j) {
                layer1.weights[i][j] += func();
            }
        }
        for (std::size_t j = 0; j < Layer1Type::dim_out; ++j) {
            layer1.biases[j] += func();
        }

        // Layer 2
        for (std::size_t i = 0; i < Layer2Type::dim_in; ++i) {
            for (std::size_t j = 0; j < Layer2Type::dim_out; ++j) {
                layer2.weights[i][j] += func();
            }
        }
        for (std::size_t j = 0; j < Layer2Type::dim_out; ++j) {
            layer2.biases[j] += func();
        }
    }

    std::array<float, Layer1Type::dim_in> inputs;
    Layer1Type layer1 = {};
    Layer2Type layer2 = {};
};

#endif
