#include "draw_drone.hpp"
#include <drones/drone.hpp>
#include <renderer/renderer.hpp>
// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

void draw_drone(std::unique_ptr<Renderer> &renderer, const Drone &drone, const bool debug) {
    const auto wing_dip = 0.01f;

    // Body
    {
        auto body = Quad();
        body.vertices[0] = glm::vec2{-0.08f, -0.04f};
        body.vertices[1] = glm::vec2{-0.07f, 0.04f};
        body.vertices[2] = glm::vec2{0.07f, 0.04f};
        body.vertices[3] = glm::vec2{0.08f, -0.04f};
        body.translation = drone.position;
        body.colour = {drone.r, drone.g, drone.b};
        body.rotation = drone.rotation;
        renderer->draw(body, 4);
    }

    // Wings
    {
        auto wings = Quad();
        wings.vertices[0] = glm::vec2{-drone.wing_length, -wing_dip};
        wings.vertices[1] = glm::vec2{-drone.wing_length, wing_dip};
        wings.vertices[2] = glm::vec2{drone.wing_length, wing_dip};
        wings.vertices[3] = glm::vec2{drone.wing_length, -wing_dip};
        wings.translation = drone.position;
        wings.colour = {0.2f, 0.2f, 0.2f};
        wings.rotation = drone.rotation;
        renderer->draw(wings, 3);
    }

    // Exhaust 1
    {
        const auto wing_tip = drone.position + glm::rotate(glm::vec2{-drone.wing_length, -wing_dip}, -drone.rotation);
        const auto length = drone.engines[0].throttle * 0.1f;

        auto exhaust = Triangle();
        exhaust.vertices[0] = glm::vec2{-0.012f, -0.04f};
        exhaust.vertices[1] = glm::vec2{0.012f, -0.04f};
        exhaust.vertices[2] = glm::vec2{0.0f, -length};
        exhaust.translation = wing_tip;
        exhaust.colour = colour::red;
        exhaust.rotation = drone.rotation + drone.engines[0].rotation;
        renderer->draw(exhaust, 4);
    }

    // Exhaust 2
    {
        const auto wing_tip = drone.position + glm::rotate(glm::vec2{drone.wing_length, -wing_dip}, -drone.rotation);
        const auto length = drone.engines[1].throttle * 0.1f;

        auto exhaust = Triangle();
        exhaust.vertices[0] = glm::vec2{-0.012f, -0.04f};
        exhaust.vertices[1] = glm::vec2{0.012f, -0.04f};
        exhaust.vertices[2] = glm::vec2{0.0f, -length};
        exhaust.translation = wing_tip;
        exhaust.colour = colour::red;
        exhaust.rotation = drone.rotation + drone.engines[1].rotation;
        renderer->draw(exhaust, 4);
    }

    // Engine 1
    {
        const auto wing_tip = drone.position + glm::rotate(glm::vec2{-drone.wing_length, -wing_dip}, -drone.rotation);

        auto engine = Quad();
        engine.vertices[0] = glm::vec2{-0.015f, -0.04f};
        engine.vertices[1] = glm::vec2{-0.01f, 0.04f};
        engine.vertices[2] = glm::vec2{0.01f, 0.04f};
        engine.vertices[3] = glm::vec2{0.015f, -0.04f};
        engine.translation = wing_tip;
        engine.colour = {0.8f, 0.8f, 0.8f};
        engine.rotation = drone.rotation + drone.engines[0].rotation;
        renderer->draw(engine, 4);
    }

    // Engine 2
    {
        const auto wing_tip = drone.position + glm::rotate(glm::vec2{drone.wing_length, -wing_dip}, -drone.rotation);

        auto engine = Quad();
        engine.vertices[0] = glm::vec2{-0.015f, -0.04f};
        engine.vertices[1] = glm::vec2{-0.01f, 0.04f};
        engine.vertices[2] = glm::vec2{0.01f, 0.04f};
        engine.vertices[3] = glm::vec2{0.015f, -0.04f};
        engine.translation = wing_tip;
        engine.colour = {0.8f, 0.8f, 0.8f};
        engine.rotation = drone.rotation + drone.engines[1].rotation;
        renderer->draw(engine, 4);
    }

    // Engine 1 throttle
    {
        const auto wing_tip = drone.position + glm::rotate(glm::vec2{-drone.wing_length, -wing_dip}, -drone.rotation);

        auto throttle = Quad();
        throttle.vertices[0] = 0.5f * glm::vec2{-0.015f, -0.04f};
        throttle.vertices[1] = 0.5f * glm::vec2{-0.01f, 0.04f};
        throttle.vertices[2] = 0.5f * glm::vec2{0.01f, 0.04f};
        throttle.vertices[3] = 0.5f * glm::vec2{0.015f, -0.04f};
        throttle.translation = wing_tip;
        throttle.colour = Colour(drone.engines[0].throttle, 0.0f, 0.0f);
        throttle.rotation = drone.rotation + drone.engines[0].rotation;
        renderer->draw(throttle, 5);
    }

    // Engine 2 throttle
    {
        const auto wing_tip = drone.position + glm::rotate(glm::vec2{drone.wing_length, -wing_dip}, -drone.rotation);

        auto throttle = Quad();
        throttle.vertices[0] = 0.5f * glm::vec2{-0.015f, -0.04f};
        throttle.vertices[1] = 0.5f * glm::vec2{-0.01f, 0.04f};
        throttle.vertices[2] = 0.5f * glm::vec2{0.01f, 0.04f};
        throttle.vertices[3] = 0.5f * glm::vec2{0.015f, -0.04f};
        throttle.translation = wing_tip;
        throttle.colour = Colour(drone.engines[1].throttle, 0.0f, 0.0f);
        throttle.rotation = drone.rotation + drone.engines[1].rotation;
        renderer->draw(throttle, 5);
    }

    if (debug) {
        // Velocity
        if (drone.velocity != glm::vec2{0.0f, 0.0f}) {
            auto velocity = Line();
            velocity.vertices[0] = glm::vec2{0.0f, 0.0f};
            velocity.vertices[1] = std::min(0.02f, glm::length(drone.velocity)) * glm::normalize(drone.velocity);
            velocity.colour = colour::red;
            velocity.translation = drone.position;
            velocity.thickness = 0.001f;
            renderer->draw(velocity, 5);
        }

        // Acceleration
        if (drone.acceleration != glm::vec2{0.0f, 0.0f}) {
            auto acceleration = Line();
            acceleration.vertices[0] = glm::vec2{0.0f, 0.0f};
            acceleration.vertices[1] =
                std::min(0.02f, glm::length(drone.acceleration)) * glm::normalize(drone.acceleration);
            acceleration.colour = colour::blue;
            acceleration.translation = drone.position;
            acceleration.thickness = 0.001f;
            renderer->draw(acceleration, 5);
        }
    }
}
