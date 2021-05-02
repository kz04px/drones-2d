#ifndef RENDERER_TRIANGLE_HPP
#define RENDERER_TRIANGLE_HPP

#include <glm/glm.hpp>
#include "colour.hpp"

struct Triangle {
    glm::vec2 vertices[3] = {};
    glm::vec2 translation = {};
    Colour colour = {};
    float rotation = 0.0f;
};

#endif
