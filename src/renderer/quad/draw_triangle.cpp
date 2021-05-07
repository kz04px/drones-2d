#include "../triangle.hpp"
#include "renderer.hpp"
// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

void QuadRenderer::draw(const Triangle &triangle, const float layer) {
    if (m_buffer_index + 3 > m_max_buffer_size) {
        flush();
    }

    const auto p1 = glm::vec3{glm::rotate(triangle.vertices[0], -triangle.rotation) + triangle.translation, -layer};
    const auto p2 = glm::vec3{glm::rotate(triangle.vertices[1], -triangle.rotation) + triangle.translation, -layer};
    const auto p3 = glm::vec3{glm::rotate(triangle.vertices[2], -triangle.rotation) + triangle.translation, -layer};

    // Triangle 1
    m_data[m_buffer_index + 0].position = p1;
    m_data[m_buffer_index + 0].colour = triangle.colour;
    m_data[m_buffer_index + 1].position = p2;
    m_data[m_buffer_index + 1].colour = triangle.colour;
    m_data[m_buffer_index + 2].position = p3;
    m_data[m_buffer_index + 2].colour = triangle.colour;

    m_buffer_index += 3;
}
