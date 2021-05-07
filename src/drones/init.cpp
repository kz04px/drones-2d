#include <renderer/colour.hpp>
#include <utils.hpp>
#include "world.hpp"

void World::init() {
    const auto world_width = bounds[1] - bounds[0];
    const auto cloud_density = 2.0f;
    const auto plant_density = 4.0f;

    // Set target
    target = {0.0f, 1.5f};

    // Add drones
    for (int i = 0; i < num_children; ++i) {
        auto drone = Drone();
        drone.network.set([]() { return utils::rand_between(-1.0f, 1.0f); });
        drone.position = {0.0f, -0.3f};
        drones.emplace_back(drone);
    }

    // Add clouds
    for (int i = 0; i < cloud_density * world_width; ++i) {
        const auto r = utils::rand_between(0.7f, 0.75f);
        const auto g = utils::rand_between(0.7f, 0.75f);
        const auto b = utils::rand_between(0.7f, 0.75f);

        auto cloud = Cloud();
        cloud.type = rand() % 3;
        cloud.colour = Colour{r, g, b};
        cloud.position = {utils::rand_between(bounds[0], bounds[1]),
                          utils::rand_between(0.5f * bounds[2], 1.0f * bounds[2])};
        cloud.velocity = {utils::rand_between(0.45f, 0.55f), 0.0f};
        cloud.scale = utils::rand_between(0.4f, 0.5f);
        cloud.front = rand() % 2;

        // Background clouds are slower, smaller, lower, and darker
        if (!cloud.front) {
            cloud.velocity.x *= 0.5f;
            cloud.scale *= 0.75f;
            cloud.position.y *= 0.8f;
            cloud.colour = {0.9f * r, 0.9f * g, 0.9f * b};
        }

        clouds.emplace_back(cloud);
    }

    // Add plants
    for (int i = 0; i < plant_density * world_width; ++i) {
        const auto r = utils::rand_between(0.0f, 0.1f);
        const auto g = utils::rand_between(0.7f, 0.9f);
        const auto b = utils::rand_between(0.0f, 0.1f);

        auto plant = Plant();
        plant.type = rand() % 10;
        plant.colour = Colour{r, g, b};
        plant.position = {utils::rand_between(bounds[0], bounds[1]), utils::rand_between(-0.01f, -0.1f)};
        plant.scale = utils::rand_between(0.8f, 1.1f);
        plants.emplace_back(plant);
    }
}
