#ifndef DRONES_CLOUD_HPP
#define DRONES_CLOUD_HPP

#include <glm/glm.hpp>
#include <renderer/colour.hpp>

struct Cloud {
    Colour colour = {0.7f, 0.7f, 0.7f};
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 velocity = {0.0f, 0.0f};
    float scale = 0.5f;
    int type = 0;
};

#endif
