#include <cassert>
#include <iostream>
#include <utils.hpp>
#include "world.hpp"
// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

void World::step(const float dt, const bool print) {
    // Update the drones
    for (std::size_t i = 0; i < drones.size(); ++i) {
        auto &drone = drones[i];
        const auto diff = target - drone.position;

        // Update inputs
        drone.network.inputs[0] = diff.x;
        drone.network.inputs[1] = diff.y;
        drone.network.inputs[2] = drone.velocity.x * dt;
        drone.network.inputs[3] = drone.velocity.y * dt;
        drone.network.inputs[4] = sin(drone.rotation);
        drone.network.inputs[5] = cos(drone.rotation);
        drone.network.inputs[6] = drone.angular_velocity * dt;

        // Run network
        const auto outputs = drone.network.run();

        // Update drone stuff
        drone.engines[0].throttle = std::clamp(outputs[0], 0.0f, 1.0f);
        drone.engines[0].rotation = 0.3f * outputs[1];
        drone.engines[1].throttle = std::clamp(outputs[2], 0.0f, 1.0f);
        drone.engines[1].rotation = 0.3f * outputs[3];

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

        const auto speed = glm::length(drone.velocity);
        const auto dist_to_target = glm::length(target - drone.position);
        const auto on_target = dist_to_target < 0.1f && speed < 0.1f;

        // Score - Distance to target
        drones[i].score += 1.0f / (1.0f + dist_to_target) * dt;

        // Score - Off balance
        drones[i].score -= 0.02f * std::abs(drone.rotation) * dt;

        // Time on target
        drones[i].time_on_target += on_target ? dt : 0.0f;

        // Distance travelled
        drones[i].distance_travelled += speed * dt;
    }

    // Update the clouds
    for (auto &cloud : clouds) {
        cloud.position += dt * cloud.velocity;

        // Wrap around
        const auto x_min = bounds[0] - 4.0f;
        const auto x_max = bounds[1] + 4.0f;
        if (cloud.position.x > x_max + cloud.scale) {
            cloud.position =
                glm::vec2{x_min - cloud.scale - 1.0f, utils::rand_between(0.5f * bounds[2], 1.0f * bounds[2])};
        }
    }

    time += dt;
    frame++;

    const auto completed = count_completed() == num_children;
    const auto successful = count_successful() >= num_parents;
    const auto out_of_time = time >= 100.0f;

    // Exit if we aren't ready
    if (!completed && !successful && !out_of_time) {
        return;
    }

    float total_score = 0.0f;

    // Update the final stats
    for (std::size_t i = 0; i < drones.size(); ++i) {
        // Energy used
        // drones[i].score -= 0.001f * drones[i].energy_used;

        // Distance travelled
        // drones[i].score -= drones[i].distance_travelled;

        // Track totals
        total_score += drones[i].score;
    }

    // Parent toggles
    bool parent_bools[num_children];
    for (std::size_t i = 0; i < drones.size(); ++i) {
        parent_bools[i] = false;
    }

    // Find the parent indices
    std::vector<std::size_t> parents_idx;
    for (int i = 0; i < num_parents; ++i) {
        // Find the best scoring non-parent
        std::size_t best_idx = 0;
        for (std::size_t j = 0; j < drones.size(); ++j) {
            if (!parent_bools[j] && drones[j].score > drones[best_idx].score) {
                best_idx = j;
            }
        }

        assert(!parent_bools[best_idx]);

        parents_idx.push_back(best_idx);
        parent_bools[best_idx] = true;
    }

    assert(parents_idx.size() == num_parents);

    // Create The Next Generation in place
    for (std::size_t i = 0; i < drones.size(); ++i) {
        // Is this a parent?
        const bool is_parent = parent_bools[i];

        // Parents survive unmodified
        if (is_parent) {
            continue;
        }

        const auto parent1_idx = parents_idx.at(rand() % num_parents);
        const auto parent2_idx = parents_idx.at(rand() % num_parents);

        assert(parent1_idx != i);
        assert(parent2_idx != i);

        // Copy parent 1 brain
        drones[i].network = drones.at(parent1_idx).network;

        // Cross with parent 2
        if (parent1_idx != parent2_idx) {
            drones[i].network.cross(drones.at(parent2_idx).network);
        }

        // Jiggle brain weights
        drones[i].network.offset([]() {
            if (rand() % 10 == 0) {
                return utils::rand_between(-0.1f, 0.1f);
            } else {
                return 0.0f;
            }
        });
    }

    // Print updates
    if (print && (generation < 10 || generation % 10 == 0)) {
        std::cout << "Generation: " << generation << "\n";
        std::cout << "Success? " << (successful ? "true" : "false") << "\n";
        std::cout << "Out of time? " << (out_of_time ? "true" : "false") << "\n";
        std::cout << "Parents: " << num_parents << "\n";
        std::cout << "Children: " << num_children << "\n";
        std::cout << "Frames: " << frame << "\n";
        std::cout << "Time: " << time << "\n";
        std::cout << "Parents:";
        for (const auto idx : parents_idx) {
            const auto score = drones.at(idx).score;
            std::cout << " " << idx << "(" << score << ")";
        }
        std::cout << "\n";
        std::cout << "Children:";
        for (int i = 0; i < num_children && i < 8; ++i) {
            std::cout << " " << i << "(" << drones.at(i).score << ")";
        }
        std::cout << "\n";
        std::cout << "Average: " << total_score / num_children << "\n";
        std::cout << "\n";
    }

    // Reset the world
    frame = 0;
    time = 0.0f;
    target = glm::vec2{0.5f * utils::rand_between(bounds[0], bounds[1]), utils::rand_between(2.0f, 0.6f * bounds[2])};

    for (auto &drone : drones) {
        drone.position = {0.0f, -1.5f};
        drone.velocity = {0.0f, 0.0f};
        drone.acceleration = {0.0f, 0.0f};
        drone.rotation = 0.0f;
        drone.angular_velocity = 0.0f;
        drone.score = 0.0f;
        drone.time_on_target = 0.0f;
        drone.distance_travelled = 0.0f;
    }

    generation++;
}
