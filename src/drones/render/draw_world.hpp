#ifndef DRAW_WORLD_HPP
#define DRAW_WORLD_HPP

#include <memory>

class RenderAPI;
class World;
class Camera;

void draw_world(std::unique_ptr<RenderAPI> &renderer,
                const Camera &camera,
                const World &world,
                const bool debug = false);

#endif
