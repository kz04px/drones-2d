#ifndef DRAW_DRONE_HPP
#define DRAW_DRONE_HPP

#include <memory>

class RenderAPI;
class Drone;

void draw_drone(std::unique_ptr<RenderAPI> &renderer, const Drone &drone, const bool debug = false);

#endif
