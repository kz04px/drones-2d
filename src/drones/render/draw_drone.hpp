#ifndef DRAW_DRONE_HPP
#define DRAW_DRONE_HPP

#include <glm/glm.hpp>
#include <memory>

class RenderAPI;
class Drone;

void draw_drone(std::unique_ptr<RenderAPI> &renderer,
                const Drone &drone,
                const glm::vec2 offset,
                const bool debug = false);

#endif
