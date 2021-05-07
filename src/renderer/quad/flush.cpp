#include <glm/gtc/type_ptr.hpp>
#include <renderer/renderer.hpp>
#include "renderer.hpp"

void QuadRenderer::flush() {
    if (m_buffer_index == 0) {
        return;
    }

#ifndef NDEBUG
    if (m_buffer_index > m_max_buffer_size) {
        m_buffer_index = 0;
        return;
    }
#endif

    // Statistics
    RenderAPI::statistics.draw_calls++;
    RenderAPI::statistics.num_triangles += m_buffer_index / 3;

    m_program.use();

    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(m_view));

    // Bind
    glBindVertexArray(m_vao);

    // Buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_buffer_index * sizeof(m_data[0]), m_data, GL_STATIC_DRAW);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, m_buffer_index);

    // Reset
    m_buffer_index = 0;
}
