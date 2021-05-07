#include "../line.hpp"
#include "../quad.hpp"
#include "renderer.hpp"
// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

void QuadRenderer::draw(const Line &line, const float layer) {
    const auto up = glm::vec2{0.0f, 1.0f};
    const auto diff = line.vertices[1] - line.vertices[0];
    const auto length = glm::distance(line.vertices[0], line.vertices[1]);

    auto quad = Quad();
    quad.vertices[0] = line.vertices[0] + glm::vec2{0.5f * -line.thickness, 0.0f};
    quad.vertices[1] = line.vertices[0] + glm::vec2{0.5f * -line.thickness, length};
    quad.vertices[2] = line.vertices[0] + glm::vec2{0.5f * line.thickness, length};
    quad.vertices[3] = line.vertices[0] + glm::vec2{0.5f * line.thickness, 0.0f};
    quad.colour = line.colour;
    quad.rotation = glm::orientedAngle(glm::normalize(diff), up);
    quad.translation = line.translation;
    draw(quad, layer);
}
