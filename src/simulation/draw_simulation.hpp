#ifndef DRAW_SIMULATION_HPP
#define DRAW_SIMULATION_HPP

#include <memory>

class RenderAPI;
class Simulation;
class Camera;

void draw_simulation(std::unique_ptr<RenderAPI> &renderer,
                     const Camera &camera,
                     const Simulation &simulation,
                     const bool debug = false);

#endif
