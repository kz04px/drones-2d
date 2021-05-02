#include "simulation.hpp"

[[nodiscard]] int Simulation::count_completed() const noexcept {
    int count = 0;

    for (std::size_t i = 0; i < world.drones.size(); ++i) {
        const auto &drone = world.drones[i];

        const auto out_of_bounds = drone.position.x < -10.0f || drone.position.x > 10.0f || drone.position.y < -10.0f ||
                                   drone.position.y > 10.0f;
        const auto target_acquired = drone_data[i].time_on_target > 3.0f;

        if (out_of_bounds || target_acquired) {
            count++;
        }
    }

    return count;
}

[[nodiscard]] int Simulation::count_successful() const noexcept {
    int count = 0;

    for (std::size_t i = 0; i < world.drones.size(); ++i) {
        const auto target_acquired = drone_data[i].time_on_target > 3.0f;

        if (target_acquired) {
            count++;
        }
    }

    return count;
}
