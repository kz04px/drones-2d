#include <camera.hpp>
#include <drones/draw_world.hpp>
#include <renderer/line.hpp>
#include <renderer/point.hpp>
#include <renderer/quad.hpp>
#include <renderer/renderer.hpp>
#include <simulation/simulation.hpp>

void draw_simulation(std::unique_ptr<RenderAPI> &renderer,
                     const Camera &camera,
                     const Simulation &simulation,
                     const bool debug) {
    renderer->begin(camera);

    // Target
    {
        auto target = Point();
        target.position = simulation.target;
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

    if (debug) {
        // Draw direction to target
        for (const auto &drone : simulation.world.drones) {
            const auto dir = simulation.target - drone.position;
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

    // World
    draw_world(renderer, camera, simulation.world, debug);

    renderer->end();
}
