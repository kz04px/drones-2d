#include <cassert>
#include <iostream>
#include <utils.hpp>
#include "simulation.hpp"
// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

void Simulation::step(const float dt, const bool print) {
    // Skip if paused
    if (paused) {
        return;
    }

    // Update the drones
    for (std::size_t i = 0; i < world.drones.size(); ++i) {
        auto &drone = world.drones[i];
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
        drone.engines[0].rotation = 0.3f * std::clamp(outputs[1], -1.0f, 1.0f);
        drone.engines[1].throttle = std::clamp(outputs[2], 0.0f, 1.0f);
        drone.engines[1].rotation = 0.3f * std::clamp(outputs[3], -1.0f, 1.0f);

        const auto force = glm::rotate(drone.thrust(), -drone.rotation) + drone.mass * world.gravity;

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
        drone_data[i].score += 1.0f / (1.0f + dist_to_target) * dt;

        // Score - Off balance
        drone_data[i].score -= 0.02f * std::abs(drone.rotation) * dt;

        // Time on target
        drone_data[i].time_on_target += on_target ? dt : 0.0f;

        // Distance travelled
        drone_data[i].distance_travelled += speed * dt;
    }

    world.time += dt;
    world.frame++;

    const auto completed = count_completed() == num_children;
    const auto successful = count_successful() >= num_parents;
    const auto out_of_time = world.time >= 100.0f;

    // Exit if we aren't ready
    if (!completed && !successful && !out_of_time) {
        return;
    }

    float total_score = 0.0f;

    // Update the final stats
    for (std::size_t i = 0; i < world.drones.size(); ++i) {
        // Energy used
        // drone_data[i].score -= 0.001f * world.drones[i].energy_used;

        // Distance travelled
        // drone_data[i].score -= world.drones[i].distance_travelled;

        // Track totals
        total_score += drone_data[i].score;
    }

    // Parent toggles
    bool parent_bools[num_children];
    for (std::size_t i = 0; i < world.drones.size(); ++i) {
        parent_bools[i] = false;
    }

    // Find the parent indices
    std::vector<std::size_t> parents_idx;
    for (int i = 0; i < num_parents; ++i) {
        // Find the best scoring non-parent
        std::size_t best_idx = 0;
        for (std::size_t j = 0; j < world.drones.size(); ++j) {
            if (!parent_bools[j] && drone_data[j].score > drone_data[best_idx].score) {
                best_idx = j;
            }
        }

        assert(!parent_bools[best_idx]);

        parents_idx.push_back(best_idx);
        parent_bools[best_idx] = true;
    }

    assert(parents_idx.size() == num_parents);

    // Create The Next Generation in place
    for (std::size_t i = 0; i < world.drones.size(); ++i) {
        world.drones[i].position = {0.0f, 0.0f};
        world.drones[i].velocity = {0.0f, 0.0f};
        world.drones[i].acceleration = {0.0f, 0.0f};
        world.drones[i].rotation = 0.0f;
        world.drones[i].angular_velocity = 0.0f;

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
        world.drones[i].network = world.drones.at(parent1_idx).network;

        // Cross with parent 2
        if (parent1_idx != parent2_idx) {
            world.drones[i].network.cross(world.drones.at(parent2_idx).network);
        }

        // Jiggle brain weights
        world.drones[i].network.offset([]() {
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
        std::cout << "Frames: " << world.frame << "\n";
        std::cout << "Time: " << world.time << "\n";
        std::cout << "Parents:";
        for (const auto idx : parents_idx) {
            const auto score = drone_data.at(idx).score;
            std::cout << " " << idx << "(" << score << ")";
        }
        std::cout << "\n";
        std::cout << "Children:";
        for (int i = 0; i < num_children && i < 8; ++i) {
            std::cout << " " << i << "(" << drone_data.at(i).score << ")";
        }
        std::cout << "\n";
        std::cout << "Average: " << total_score / num_children << "\n";
        std::cout << "\n";
    }

    // Reset the world
    world.frame = 0;
    world.time = 0.0f;
    target = glm::vec2{utils::rand_between(-3.0f, 3.0f), utils::rand_between(-3.0f, 3.0f)};
    // target = glm::vec2{utils::rand_between(-1.5f, 1.5f), utils::rand_between(2.0f, 3.0f)};
    // target = {1.5f, 1.5f};
    for (auto &data : drone_data) {
        data = DroneData();
    }

    generation++;
}
