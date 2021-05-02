#ifndef SIMULATION_WORLD_HPP
#define SIMULATION_WORLD_HPP

#include <vector>
#include "drone.hpp"

struct World {
    std::vector<Drone> drones = {};
    glm::vec2 gravity = {0.0f, -9.81f};
    int frame = 0;
    float time = 0.0f;

    void step(const float dt);
};

#endif
