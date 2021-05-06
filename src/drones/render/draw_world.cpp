#include "draw_world.hpp"
#include <camera.hpp>
#include <drones/world.hpp>
#include <renderer/line.hpp>
#include <renderer/point.hpp>
#include <renderer/quad.hpp>
#include <renderer/renderer.hpp>
#include <renderer/triangle.hpp>
#include "draw_drone.hpp"

void draw_world(std::unique_ptr<RenderAPI> &renderer, const Camera &camera, const World &world, const bool debug) {
    renderer->begin(camera);

    // Target
    {
        auto target = Point();
        target.position = world.target;
        target.colour = colour::red;
        target.radius = 0.01f;
        renderer->draw(target, 6);
    }

    // Draw bounds - Left
    {
        auto line = Quad();
        line.vertices[0] = {camera.left(), camera.bottom()};
        line.vertices[1] = {camera.left(), camera.top()};
        line.vertices[2] = {-10.0f, 10.0f};
        line.vertices[3] = {-10.0f, -10.0f};
        line.colour = {27, 2, 9};
        renderer->draw(line, 10);
    }

    // Draw bounds - Right
    {
        auto line = Quad();
        line.vertices[0] = {10.0f, -10.0f};
        line.vertices[1] = {10.0f, 10.0f};
        line.vertices[2] = {camera.right(), camera.top()};
        line.vertices[3] = {camera.right(), camera.bottom()};
        line.colour = {27, 2, 9};
        renderer->draw(line, 10);
    }

    // Draw bounds - Top
    {
        auto line = Quad();
        line.vertices[0] = {-10.0f, 10.0f};
        line.vertices[1] = {camera.left(), camera.top()};
        line.vertices[2] = {camera.right(), camera.top()};
        line.vertices[3] = {10.0f, 10.0f};
        line.colour = {27, 2, 9};
        renderer->draw(line, 10);
    }

    // Draw bounds - Bottom
    {
        auto line = Quad();
        line.vertices[0] = {camera.left(), camera.bottom()};
        line.vertices[1] = {-10.0f, -10.0f};
        line.vertices[2] = {10.0f, -10.0f};
        line.vertices[3] = {camera.right(), camera.bottom()};
        line.colour = {27, 2, 9};
        renderer->draw(line, 10);
    }

    // Trees
    for (int i = -10; i <= 10; ++i) {
        {
            auto trunk = Quad();
            trunk.vertices[0] = glm::vec2{-0.02f, 0.0f};
            trunk.vertices[1] = glm::vec2{-0.02f, 0.5f};
            trunk.vertices[2] = glm::vec2{0.02f, 0.5f};
            trunk.vertices[3] = glm::vec2{0.02f, 0.0f};
            trunk.colour = colour::brown;
            trunk.translation = glm::vec2{i, 0.0f};
            renderer->draw(trunk, 0);
        }
        {
            auto leaf = Quad();
            leaf.vertices[0] = glm::vec2{-0.2f, -0.2f};
            leaf.vertices[1] = glm::vec2{-0.2f, 0.2f};
            leaf.vertices[2] = glm::vec2{0.2f, 0.2f};
            leaf.vertices[3] = glm::vec2{0.2f, -0.2f};
            leaf.colour = colour::dark_green;
            leaf.translation = glm::vec2{i, 0.5f};
            renderer->draw(leaf, 1);
        }
    }

    // Clouds
    for (const auto cloud : world.clouds) {
        switch (cloud.type) {
            case 0: {
                auto quad = Quad();
                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = cloud.position;
                renderer->draw(quad, 0);
                break;
            }
            case 1: {
                auto quad = Quad();
                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = cloud.position;
                renderer->draw(quad, 0);

                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = cloud.position + glm::vec2{cloud.scale, cloud.scale};
                renderer->draw(quad, 0);

                break;
            }
            case 2: {
                auto quad = Quad();
                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = cloud.position;
                renderer->draw(quad, 0);

                quad.vertices[0] = 0.8f * glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = 0.8f * glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = 0.8f * glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = 0.8f * glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = cloud.position + glm::vec2{cloud.scale, cloud.scale};
                renderer->draw(quad, 0);

                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = cloud.position + glm::vec2{1.5f * cloud.scale, 0.5f * cloud.scale};
                renderer->draw(quad, 0);

                break;
            }
            default:
                break;
        }
    }

    // Ground
    if (camera.bottom() < 0.0f) {
        auto ground = Quad();
        ground.vertices[0] = glm::vec2{camera.left(), camera.bottom()};
        ground.vertices[1] = glm::vec2{camera.left(), 0.0f};
        ground.vertices[2] = glm::vec2{camera.right(), 0.0f};
        ground.vertices[3] = glm::vec2{camera.right(), camera.bottom()};
        ground.colour = colour::grass;
        renderer->draw(ground, -1);
    }

    // Sky
    if (camera.top() >= 0.0f) {
        auto sky = Quad();
        sky.vertices[0] = glm::vec2{camera.left(), 0.0f};
        sky.vertices[1] = glm::vec2{camera.left(), camera.top()};
        sky.vertices[2] = glm::vec2{camera.right(), camera.top()};
        sky.vertices[3] = glm::vec2{camera.right(), 0.0f};
        sky.colour = colour::sky_blue;
        renderer->draw(sky, -1);
    }

    // Drones
    for (const auto &drone : world.drones) {
        draw_drone(renderer, drone, debug);

        if (debug) {
            // Draw direction to target
            const auto dir = world.target - drone.position;
            const auto dist_to_target = glm::length(dir);

            auto line = Line();
            line.vertices[0] = {0.0f, 0.0f};
            line.vertices[1] = std::min(0.05f, dist_to_target) * glm::normalize(dir);
            line.translation = drone.position;
            line.colour = colour::green;
            line.thickness = 0.002f;
            renderer->draw(line, 6);
        }
    }

    // Meter
    {
        const float spacer = 0.1f;
        const float bottom = std::floor(camera.bottom());
        const float top = std::ceil(camera.top());
        const int steps = (top - bottom) / spacer;
        for (int i = 0; i < steps; ++i) {
            auto line = Line();
            line.vertices[0] = glm::vec2{0.0f, 0.0f};
            line.vertices[1] = glm::vec2{0.1f, 0.0f};
            line.thickness = 0.002f;
            line.translation = glm::vec2{camera.left(), bottom + i * spacer};
            line.colour = colour::red;
            renderer->draw(line);
        }
    }

    renderer->end();
}