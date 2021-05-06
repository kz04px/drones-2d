#ifndef DRONES_ENGINE_HPP
#define DRONES_ENGINE_HPP

#include <cmath>
#include <glm/glm.hpp>

struct Engine {
    float rotation = 0.0f;
    float gimbal = 0.0f;
    float power = 10.0f;
    float throttle = 0.0f;

    [[nodiscard]] auto force() const noexcept {
        return power * throttle;
    }

    /*
     * This is in drone coordinates
     */
    [[nodiscard]] auto direction() const noexcept {
        return glm::vec2{sin(rotation), cos(rotation)};
    }
};

#endif
