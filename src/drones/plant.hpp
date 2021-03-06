#ifndef DRONES_TREE_HPP
#define DRONES_TREE_HPP

#include <glm/glm.hpp>
#include <renderer/colour.hpp>

struct Plant {
    Colour colour = {0.7f, 0.7f, 0.7f};
    glm::vec2 position = {0.0f, 0.0f};
    float scale = 1.0f;
    int type = 0;
};

#endif
