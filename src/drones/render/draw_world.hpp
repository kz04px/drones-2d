#ifndef DRAW_WORLD_HPP
#define DRAW_WORLD_HPP

class World;
class Camera;

void draw_world(const Camera &camera, const World &world, const bool debug = false);

#endif
