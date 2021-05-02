#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <drones/world.hpp>
#include <glm/glm.hpp>
#include <vector>

struct DroneData {
    float score = 0.0f;
    float time_on_target = 0.0f;
    float distance_travelled = 0.0f;
};

struct Simulation {
    World world = {};
    std::vector<DroneData> drone_data = {};
    int num_parents = 4;
    int num_children = 50;
    glm::vec2 target = {0.0f, 0.0f};
    int generation = 0;
    bool paused = true;

    void init();

    void step(const float dt, const bool print = true);

    [[nodiscard]] int count_completed() const noexcept;

    [[nodiscard]] int count_successful() const noexcept;
};

#endif
