#include "world.hpp"

[[nodiscard]] int World::count_completed() const noexcept {
    int count = 0;

    for (std::size_t i = 0; i < drones.size(); ++i) {
        const auto &drone = drones[i];

        const auto out_of_bounds = drone.position.x < bounds[0] || drone.position.x > bounds[1] ||
                                   drone.position.y > bounds[2] || drone.position.y < bounds[3];
        const auto target_acquired = drone.time_on_target > 3.0f;

        if (out_of_bounds || target_acquired) {
            count++;
        }
    }

    return count;
}

[[nodiscard]] int World::count_successful() const noexcept {
    int count = 0;

    for (std::size_t i = 0; i < drones.size(); ++i) {
        const auto target_acquired = drones[i].time_on_target > 3.0f;

        if (target_acquired) {
            count++;
        }
    }

    return count;
}
