#ifndef DRAW_WORLD_HPP
#define DRAW_WORLD_HPP

#include <memory>

class Renderer;
class World;
class Camera;

void draw_world(std::unique_ptr<Renderer> &renderer,
                const Camera &camera,
                const World &world,
                const bool debug = false);

#endif
