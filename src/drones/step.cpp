#include "world.hpp"
// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

void World::step(const float dt) {
    for (auto &drone : drones) {
        // if (drone.destroyed) {
        //     continue;
        // }

        const auto force = glm::rotate(drone.thrust(), -drone.rotation) + drone.mass * gravity;

        // a = F/m
        drone.acceleration = force / drone.mass;

        // s = ut + 1/2at^2
        drone.position += drone.velocity * dt + 0.5f * drone.acceleration * dt * dt;

        // v = u + at
        drone.velocity += drone.acceleration * dt;

        // τ = Iα (torque = moment of inertia & angular acceleration)
        drone.angular_velocity += drone.torque() * dt;
        drone.rotation += drone.angular_velocity * dt;

        // Drag
        drone.velocity *= 0.99f;

        /*
        // Can't fall through the Earth
        if (drone.position.y < 0.0f) {
            drone.position.y = 0.0f;
            drone.velocity.x = 0.0f;
            drone.velocity.y = std::max(0.0f, drone.velocity.y);
            drone.rotation = 0.0f;
        }
        */
    }

    time += dt;
    frame++;
}
