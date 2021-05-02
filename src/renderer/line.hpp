#ifndef RENDERER_LINE_HPP
#define RENDERER_LINE_HPP

#include <glm/glm.hpp>
#include "colour.hpp"

struct Line {
    glm::vec2 vertices[2] = {};
    glm::vec2 translation = {};
    Colour colour = {};
    float thickness = 0.01f;
};

#endif
