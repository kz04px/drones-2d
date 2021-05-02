#ifndef DRAW_DRONE_HPP
#define DRAW_DRONE_HPP

#include <memory>

class Renderer;
class Drone;

void draw_drone(std::unique_ptr<Renderer> &renderer, const Drone &drone, const bool debug = false);

#endif
