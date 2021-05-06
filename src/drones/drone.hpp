#ifndef DRONES_DRONE_HPP
#define DRONES_DRONE_HPP

#include <glm/glm.hpp>
#include "engine.hpp"
#include "network.hpp"

struct Drone {
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 velocity = {0.0f, 0.0f};
    glm::vec2 acceleration = {0.0f, 0.0f};
    float angular_velocity = 0.0f;
    float rotation = 0.0f;
    // Brain
    Network network;
    // Attributes
    Engine engines[2] = {};
    float wing_length = 0.15f;
    float mass = 1.5f;
    float r = 0.7f;
    float g = 0.7f;
    float b = 0.7f;
    // Stats
    float score = 0.0f;
    float time_on_target = 0.0f;
    float distance_travelled = 0.0f;

    /*
     * This is in drone coordinates
     */
    [[nodiscard]] glm::vec2 thrust() const noexcept {
        const auto left = engines[0].force() * engines[0].direction();
        const auto right = engines[1].force() * engines[1].direction();
        return left + right;
    }

    /*
     * Torque
     */
    [[nodiscard]] auto torque() const noexcept {
        auto cross = [](const glm::vec2 &v1, const glm::vec2 &v2) {
            // x y z
            // a b 0
            // c d 0
            return v1.x * v2.y - v1.y * v2.x;
        };

        constexpr float ratio = 0.8f;
        const auto left = engines[0].force() * cross(engines[0].direction(), glm::vec2{-1.0f, 0.0f});
        const auto right = engines[1].force() * cross(engines[1].direction(), glm::vec2{1.0f, 0.0f});
        return ratio * (left + right);
    }

    /*
     * Which way is up?
     */
    [[nodiscard]] auto up() const noexcept {
        return glm::vec2{sin(rotation), cos(rotation)};
    }

    /*
     * Which way is down?
     */
    [[nodiscard]] auto down() const noexcept {
        return -up();
    }
};

#endif
