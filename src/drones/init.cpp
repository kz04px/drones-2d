#include <utils.hpp>
#include "world.hpp"

void World::init() {
    // Set target
    target = {0.0f, 1.5f};

    // Add drones
    for (int i = 0; i < num_children; ++i) {
        auto drone = Drone();
        drone.network.set([]() { return utils::rand_between(-1.0f, 1.0f); });
        drones.emplace_back(drone);
    }
}
