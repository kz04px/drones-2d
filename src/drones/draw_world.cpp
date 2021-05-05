#include "draw_world.hpp"
#include <camera.hpp>
#include <drones/world.hpp>
#include <renderer/line.hpp>
#include <renderer/quad.hpp>
#include <renderer/renderer.hpp>
#include <renderer/triangle.hpp>
#include "draw_drone.hpp"

void draw_world(std::unique_ptr<RenderAPI> &renderer, const Camera &camera, const World &world, const bool debug) {
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
}
