#ifndef RENDERER_POINT_HPP
#define RENDERER_POINT_HPP

#include <glm/glm.hpp>
#include "colour.hpp"

struct Point {
    glm::vec2 position = {};
    Colour colour = {};
    float radius = 0.0f;
};

#endif
