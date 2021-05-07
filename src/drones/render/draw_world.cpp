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
        line.vertices[2] = {world.bounds[0], world.bounds[2]};
        line.vertices[3] = {world.bounds[0], world.bounds[3]};
        line.colour = {27, 2, 9};
        renderer->draw(line, 10);
    }

    // Draw bounds - Right
    {
        auto line = Quad();
        line.vertices[0] = {world.bounds[1], world.bounds[3]};
        line.vertices[1] = {world.bounds[1], world.bounds[2]};
        line.vertices[2] = {camera.right(), camera.top()};
        line.vertices[3] = {camera.right(), camera.bottom()};
        line.colour = {27, 2, 9};
        renderer->draw(line, 10);
    }

    // Draw bounds - Top
    {
        auto line = Quad();
        line.vertices[0] = {world.bounds[0], world.bounds[2]};
        line.vertices[1] = {camera.left(), camera.top()};
        line.vertices[2] = {camera.right(), camera.top()};
        line.vertices[3] = {world.bounds[1], world.bounds[2]};
        line.colour = {27, 2, 9};
        renderer->draw(line, 10);
    }

    // Draw bounds - Bottom
    {
        auto line = Quad();
        line.vertices[0] = {camera.left(), camera.bottom()};
        line.vertices[1] = {world.bounds[0], world.bounds[3]};
        line.vertices[2] = {world.bounds[1], world.bounds[3]};
        line.vertices[3] = {camera.right(), camera.bottom()};
        line.colour = {27, 2, 9};
        renderer->draw(line, 10);
    }

    // Plants
    for (const auto &plant : world.plants) {
        const auto depth_offset = -plant.position.y / 10.0f;

        switch (plant.type) {
            case 0:
            case 1: {
                auto trunk = Quad();
                trunk.vertices[0] = glm::vec2{-0.02f, 0.0f};
                trunk.vertices[1] = glm::vec2{-0.02f, 0.3f};
                trunk.vertices[2] = glm::vec2{0.02f, 0.3f};
                trunk.vertices[3] = glm::vec2{0.02f, 0.0f};
                trunk.colour = colour::brown;
                trunk.translation = plant.position;
                renderer->draw(trunk, 1 + depth_offset);

                auto leaf = Quad();
                leaf.vertices[0] = plant.scale * glm::vec2{-0.2f, 0.0f};
                leaf.vertices[1] = plant.scale * glm::vec2{-0.2f, 0.4f};
                leaf.vertices[2] = plant.scale * glm::vec2{0.2f, 0.4f};
                leaf.vertices[3] = plant.scale * glm::vec2{0.2f, 0.0f};
                leaf.colour = plant.colour;
                leaf.translation = plant.position + glm::vec2{0.0f, 0.3f};
                renderer->draw(leaf, 1 + depth_offset);
                break;
            }
            case 2:
            case 3:
            case 4: {
                auto trunk = Quad();
                trunk.vertices[0] = glm::vec2{-0.02f, 0.0f};
                trunk.vertices[1] = glm::vec2{-0.02f, 0.2f};
                trunk.vertices[2] = glm::vec2{0.02f, 0.2f};
                trunk.vertices[3] = glm::vec2{0.02f, 0.0f};
                trunk.colour = colour::brown;
                trunk.translation = plant.position;
                renderer->draw(trunk, 1 + depth_offset);

                auto leaf = Triangle();
                leaf.vertices[0] = plant.scale * glm::vec2{-0.2f, 0.0f};
                leaf.vertices[1] = plant.scale * glm::vec2{0.0f, 0.8f};
                leaf.vertices[2] = plant.scale * glm::vec2{0.2f, 0.0f};
                leaf.colour = plant.colour;
                leaf.translation = plant.position + glm::vec2{0.0f, 0.2f};
                renderer->draw(leaf, 1 + depth_offset);
                break;
            }
            case 6:
            case 7:
            case 8:
            case 9:
            case 10: {
                auto leaf = Triangle();
                leaf.vertices[0] = plant.scale * glm::vec2{-0.1f, 0.0f};
                leaf.vertices[1] = plant.scale * glm::vec2{0.0f, 0.15f};
                leaf.vertices[2] = plant.scale * glm::vec2{0.1f, 0.0f};
                leaf.colour = plant.colour;
                leaf.translation = plant.position;
                renderer->draw(leaf, 1 + depth_offset);
                break;
            }
            default:
                break;
        }
    }

    // Clouds
    for (const auto &cloud : world.clouds) {
        switch (cloud.type) {
            case 0: {
                auto quad = Quad();
                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = cloud.position;
                renderer->draw(quad, cloud.front ? 0.0f : -2.0f);
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
                renderer->draw(quad, cloud.front ? 0.0f : -2.0f);

                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = cloud.position + glm::vec2{cloud.scale, cloud.scale};
                renderer->draw(quad, cloud.front ? 0.0f : -2.0f);

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
                renderer->draw(quad, cloud.front ? 0.0f : -2.0f);

                quad.vertices[0] = 0.8f * glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = 0.8f * glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = 0.8f * glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = 0.8f * glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = cloud.position + glm::vec2{cloud.scale, cloud.scale};
                renderer->draw(quad, cloud.front ? 0.0f : -2.0f);

                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = cloud.position + glm::vec2{1.5f * cloud.scale, 0.5f * cloud.scale};
                renderer->draw(quad, cloud.front ? 0.0f : -2.0f);

                break;
            }
            default:
                break;
        }
    }

    // Mountains
    const std::pair<float, float> mountains[] = {
        {-11.0, 0.9f},
        {-5.0, 0.5f},
        {-3.0, 1.0f},
        {2.0, 0.7f},
        {8.0, 1.2f},
    };

    for (const auto &[x, scale] : mountains) {
        const auto snow_line = 2.5f;
        const auto width = 3.0f * scale;
        const auto height = 4.0f * scale;
        const auto peak_depth = height - snow_line;
        const auto ratio = width / height;

        auto mountain = Triangle();
        mountain.vertices[0] = glm::vec2{-width, 0.0f};
        mountain.vertices[1] = glm::vec2{0.0f, height};
        mountain.vertices[2] = glm::vec2{width, 0.0f};
        mountain.colour = colour::dark_grey;
        mountain.translation = {x, 0.0f};
        renderer->draw(mountain, -1.0f);

        // Snow threshold
        if (peak_depth >= 1.0f) {
            auto peak = Triangle();
            peak.vertices[0] = glm::vec2{-ratio * peak_depth, height - peak_depth};
            peak.vertices[1] = glm::vec2{0.0f, height};
            peak.vertices[2] = glm::vec2{ratio * peak_depth, height - peak_depth};
            peak.colour = colour::grey;
            peak.translation = {x, 0.0f};
            renderer->draw(peak, -0.9f);
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
        renderer->draw(sky, -3);
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
