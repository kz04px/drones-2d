#include <renderer/colour.hpp>
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

    // Add clouds
    for (int i = 0; i < bounds[1] - bounds[0]; ++i) {
        const auto r = utils::rand_between(0.65f, 0.7f);
        const auto g = utils::rand_between(0.65f, 0.7f);
        const auto b = utils::rand_between(0.65f, 0.7f);

        auto cloud = Cloud();
        cloud.type = rand() % 3;
        cloud.colour = Colour{r, g, b};
        cloud.position = {utils::rand_between(bounds[0], bounds[1]),
                          utils::rand_between(0.5f * bounds[2], 0.8f * bounds[2])};
        cloud.velocity = {utils::rand_between(0.45f, 0.55f), 0.0f};
        cloud.scale = utils::rand_between(0.4f, 0.5f);
        clouds.emplace_back(cloud);
    }
}
