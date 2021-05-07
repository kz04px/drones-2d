#ifndef DRAW_DRONE_HPP
#define DRAW_DRONE_HPP

#include <glm/glm.hpp>

class Drone;

void draw_drone(const Drone &drone, const glm::vec2 offset, const bool debug = false);

#endif
