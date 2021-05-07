#include "../point.hpp"
#include "../quad.hpp"
#include "renderer.hpp"
// GLM
#include <glm/glm.hpp>

void QuadRenderer::draw(const Point &point, const float layer) {
    auto quad = Quad();
    quad.vertices[0] = point.position + glm::vec2{-point.radius, -point.radius};
    quad.vertices[1] = point.position + glm::vec2{-point.radius, point.radius};
    quad.vertices[2] = point.position + glm::vec2{point.radius, point.radius};
    quad.vertices[3] = point.position + glm::vec2{point.radius, -point.radius};
    quad.colour = point.colour;
    draw(quad, layer);
}
