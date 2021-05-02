#include <utils.hpp>
#include "simulation.hpp"

void Simulation::init() {
    // Set target
    target = {0.0f, 1.5f};

    // Add drones
    for (int i = 0; i < num_children; ++i) {
        auto drone = Drone();
        drone.network.set([]() { return utils::rand_between(-1.0f, 1.0f); });
        world.drones.emplace_back(drone);

        drone_data.push_back(DroneData());
    }
}
