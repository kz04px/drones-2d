#include "draw_world.hpp"
#include <camera.hpp>
#include <drones/world.hpp>
#include <renderer/line.hpp>
#include <renderer/point.hpp>
#include <renderer/quad.hpp>
#include <renderer/renderer.hpp>
#include <renderer/triangle.hpp>
#include "draw_drone.hpp"

void draw_world(const Camera &camera, const World &world, const bool debug) {
    RenderAPI::begin(camera);

    const auto parallax = -0.04f * camera.position;

    // Target
    {
        auto target = Point();
        target.position = world.target + parallax;
        target.colour = colour::red;
        target.radius = 0.03f;
        RenderAPI::draw(target, 6);
    }

    // Draw bounds - Left
    {
        auto line = Quad();
        line.vertices[0] = {camera.left(), camera.bottom()};
        line.vertices[1] = {camera.left(), camera.top()};
        line.vertices[2] = {world.bounds[0], world.bounds[2]};
        line.vertices[3] = {world.bounds[0], world.bounds[3]};
        line.colour = {27, 2, 9};
        RenderAPI::draw(line, 10);
    }

    // Draw bounds - Right
    {
        auto line = Quad();
        line.vertices[0] = {world.bounds[1], world.bounds[3]};
        line.vertices[1] = {world.bounds[1], world.bounds[2]};
        line.vertices[2] = {camera.right(), camera.top()};
        line.vertices[3] = {camera.right(), camera.bottom()};
        line.colour = {27, 2, 9};
        RenderAPI::draw(line, 10);
    }

    // Draw bounds - Top
    {
        auto line = Quad();
        line.vertices[0] = {world.bounds[0], world.bounds[2]};
        line.vertices[1] = {camera.left(), camera.top()};
        line.vertices[2] = {camera.right(), camera.top()};
        line.vertices[3] = {world.bounds[1], world.bounds[2]};
        line.colour = {27, 2, 9};
        RenderAPI::draw(line, 10);
    }

    // Draw bounds - Bottom
    {
        auto line = Quad();
        line.vertices[0] = {camera.left(), camera.bottom()};
        line.vertices[1] = {world.bounds[0], world.bounds[3]};
        line.vertices[2] = {world.bounds[1], world.bounds[3]};
        line.vertices[3] = {camera.right(), camera.bottom()};
        line.colour = {27, 2, 9};
        RenderAPI::draw(line, 10);
    }

    // Plants
    for (const auto &plant : world.plants) {
        const auto depth_offset = -plant.position.y / 10.0f;
        auto position = plant.position + parallax;

        // Don't parallax over the horizon
        position.y = std::min(0.0f, position.y);

        // More parallax for closer trees
        position.x *= 1.0f - plant.position.y;

        switch (plant.type) {
            case 0:
            case 1: {
                auto trunk = Quad();
                trunk.vertices[0] = glm::vec2{-0.02f, 0.0f};
                trunk.vertices[1] = glm::vec2{-0.02f, 0.3f};
                trunk.vertices[2] = glm::vec2{0.02f, 0.3f};
                trunk.vertices[3] = glm::vec2{0.02f, 0.0f};
                trunk.colour = colour::brown;
                trunk.translation = position;
                RenderAPI::draw(trunk, 1 + depth_offset);

                auto leaf = Quad();
                leaf.vertices[0] = plant.scale * glm::vec2{-0.2f, 0.0f};
                leaf.vertices[1] = plant.scale * glm::vec2{-0.2f, 0.4f};
                leaf.vertices[2] = plant.scale * glm::vec2{0.2f, 0.4f};
                leaf.vertices[3] = plant.scale * glm::vec2{0.2f, 0.0f};
                leaf.colour = plant.colour;
                leaf.translation = position + glm::vec2{0.0f, 0.3f};
                RenderAPI::draw(leaf, 1 + depth_offset);
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
                trunk.translation = position;
                RenderAPI::draw(trunk, 1 + depth_offset);

                auto leaf = Triangle();
                leaf.vertices[0] = plant.scale * glm::vec2{-0.2f, 0.0f};
                leaf.vertices[1] = plant.scale * glm::vec2{0.0f, 0.8f};
                leaf.vertices[2] = plant.scale * glm::vec2{0.2f, 0.0f};
                leaf.colour = plant.colour;
                leaf.translation = position + glm::vec2{0.0f, 0.2f};
                RenderAPI::draw(leaf, 1 + depth_offset);
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
                leaf.translation = position;
                RenderAPI::draw(leaf, 1 + depth_offset);
                break;
            }
            default:
                break;
        }
    }

    // Clouds
    for (const auto &cloud : world.clouds) {
        const auto position = cloud.position + (cloud.front ? 2.0f : 0.0f) * parallax;

        switch (cloud.type) {
            case 0: {
                auto quad = Quad();
                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = position + 2.0f * parallax;
                RenderAPI::draw(quad, cloud.front ? 0.0f : -2.0f);
                break;
            }
            case 1: {
                auto quad = Quad();
                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = position + 2.0f * parallax;
                RenderAPI::draw(quad, cloud.front ? 0.0f : -2.0f);

                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = position + glm::vec2{cloud.scale, cloud.scale};
                RenderAPI::draw(quad, cloud.front ? 0.0f : -2.0f);

                break;
            }
            case 2: {
                auto quad = Quad();
                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = position;
                RenderAPI::draw(quad, cloud.front ? 0.0f : -2.0f);

                quad.vertices[0] = 0.8f * glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = 0.8f * glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = 0.8f * glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = 0.8f * glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = position + glm::vec2{cloud.scale, cloud.scale};
                RenderAPI::draw(quad, cloud.front ? 0.0f : -2.0f);

                quad.vertices[0] = glm::vec2{-cloud.scale, -cloud.scale};
                quad.vertices[1] = glm::vec2{-cloud.scale, cloud.scale};
                quad.vertices[2] = glm::vec2{cloud.scale, cloud.scale};
                quad.vertices[3] = glm::vec2{cloud.scale, -cloud.scale};
                quad.colour = cloud.colour;
                quad.translation = position + glm::vec2{1.5f * cloud.scale, 0.5f * cloud.scale};
                RenderAPI::draw(quad, cloud.front ? 0.0f : -2.0f);

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
        RenderAPI::draw(mountain, -1.0f);

        // Snow threshold
        if (peak_depth >= 1.0f) {
            auto peak = Triangle();
            peak.vertices[0] = glm::vec2{-ratio * peak_depth, height - peak_depth};
            peak.vertices[1] = glm::vec2{0.0f, height};
            peak.vertices[2] = glm::vec2{ratio * peak_depth, height - peak_depth};
            peak.colour = colour::grey;
            peak.translation = {x, 0.0f};
            RenderAPI::draw(peak, -0.9f);
        }
    }

    // Ground
    if (camera.bottom() < 0.0f) {
        auto ground = Quad();
        ground.vertices[0] = glm::vec2{world.bounds[0], world.bounds[3]};
        ground.vertices[1] = glm::vec2{world.bounds[0], 0.0f};
        ground.vertices[2] = glm::vec2{world.bounds[1], 0.0f};
        ground.vertices[3] = glm::vec2{world.bounds[1], world.bounds[3]};
        ground.colour = colour::grass;
        RenderAPI::draw(ground, -1);
    }

    // Sky
    if (camera.top() >= 0.0f) {
        auto sky = Quad();
        sky.vertices[0] = glm::vec2{world.bounds[0], 0.0f};
        sky.vertices[1] = glm::vec2{world.bounds[0], world.bounds[2]};
        sky.vertices[2] = glm::vec2{world.bounds[1], world.bounds[2]};
        sky.vertices[3] = glm::vec2{world.bounds[1], 0.0f};
        sky.colour = colour::sky_blue;
        RenderAPI::draw(sky, -3);
    }

    // Drones
    for (const auto &drone : world.drones) {
        draw_drone(drone, parallax, debug);

        if (debug) {
            // Draw direction to target
            const auto dir = world.target - drone.position;
            const auto dist_to_target = glm::length(dir);

            auto line = Line();
            line.vertices[0] = {0.0f, 0.0f};
            line.vertices[1] = std::min(0.05f, dist_to_target) * glm::normalize(dir);
            line.translation = drone.position + parallax;
            line.colour = colour::green;
            line.thickness = 0.002f;
            RenderAPI::draw(line, 6);
        }
    }

    RenderAPI::draw_text("kz04px", 0, -100, 1.0f, 20.0f);
    RenderAPI::draw_text("Vali <3", 0, -101, 1.0f, 20.0f);

    RenderAPI::end();
}
