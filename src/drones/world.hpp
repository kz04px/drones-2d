#ifndef DRONES_WORLD_HPP
#define DRONES_WORLD_HPP

#include <vector>
#include "drone.hpp"

struct World {
    std::vector<Drone> drones = {};
    glm::vec2 gravity = {0.0f, -9.81f};
    glm::vec2 target = {0.0f, 0.0f};
    float time = 0.0f;
    int frame = 0;
    int num_parents = 4;
    int num_children = 50;
    int generation = 0;
    bool paused = true;

    void init();

    void step(const float dt, const bool print = true);

    [[nodiscard]] int count_completed() const noexcept;

    [[nodiscard]] int count_successful() const noexcept;
};

#endif
