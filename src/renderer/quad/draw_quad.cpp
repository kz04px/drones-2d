#include "../quad.hpp"
#include "renderer.hpp"
// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

void QuadRenderer::draw(const Quad &quad, const float layer) {
    if (m_buffer_index + 6 > m_max_buffer_size) {
        flush();
    }

    const auto p1 = glm::vec3{glm::rotate(quad.vertices[0], -quad.rotation) + quad.translation, -layer};
    const auto p2 = glm::vec3{glm::rotate(quad.vertices[1], -quad.rotation) + quad.translation, -layer};
    const auto p3 = glm::vec3{glm::rotate(quad.vertices[2], -quad.rotation) + quad.translation, -layer};
    const auto p4 = glm::vec3{glm::rotate(quad.vertices[3], -quad.rotation) + quad.translation, -layer};

    // Triangle 1
    m_data[m_buffer_index + 0].position = p1;
    m_data[m_buffer_index + 0].colour = quad.colour;
    m_data[m_buffer_index + 1].position = p2;
    m_data[m_buffer_index + 1].colour = quad.colour;
    m_data[m_buffer_index + 2].position = p3;
    m_data[m_buffer_index + 2].colour = quad.colour;
    // Triangle 2
    m_data[m_buffer_index + 3].position = p1;
    m_data[m_buffer_index + 3].colour = quad.colour;
    m_data[m_buffer_index + 4].position = p3;
    m_data[m_buffer_index + 4].colour = quad.colour;
    m_data[m_buffer_index + 5].position = p4;
    m_data[m_buffer_index + 5].colour = quad.colour;

    m_buffer_index += 6;
}
