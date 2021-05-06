#include <glm/gtc/type_ptr.hpp>
#include "renderer.hpp"
// Trash
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

void TextRenderer::draw(const std::string &text, float x, float y, const int layer) {
    const float scale = 1.0f;
    VertexData coords[6 * text.length()];
    int idx = 0;

    // Loop through all characters
    for (const auto c : text) {
        // Get character info
        const auto info = m_atlas.info(c);

        // Calculate the vertex and texture coordinates
        const float x2 = x + info.bl * scale;
        const float y2 = y + (info.bt - info.bh - m_atlas.origin_height) * scale;
        const float w = info.bw * scale;
        const float h = info.bh * scale;

        // Advance the cursor to the start of the next character
        x += info.ax * scale;

        // Skip glyphs that have no pixels
        if (!w || !h) {
            continue;
        }

        const float section_width = info.tw;
        const float section_height = info.th;

        // Triangle 1
        coords[idx + 0].position = {x2, y2, -layer};
        coords[idx + 1].position = {x2, y2 + h, -layer};
        coords[idx + 2].position = {x2 + w, y2 + h, -layer};
        coords[idx + 0].uv = {info.tx, info.ty + section_height};
        coords[idx + 1].uv = {info.tx, info.ty};
        coords[idx + 2].uv = {info.tx + section_width, info.ty};

        // Triangle 2
        coords[idx + 3].position = {x2, y2, -layer};
        coords[idx + 4].position = {x2 + w, y2 + h, -layer};
        coords[idx + 5].position = {x2 + w, y2, -layer};
        coords[idx + 3].uv = {info.tx, info.ty + section_height};
        coords[idx + 4].uv = {info.tx + section_width, info.ty};
        coords[idx + 5].uv = {info.tx + section_width, info.ty + section_height};

        idx += 6;
    }

    m_program.use();

    glBindTexture(GL_TEXTURE_2D, m_atlas.id);

    {
        const auto loc = glGetUniformLocation(m_program.id(), "view");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m_view));
    }

    // Bind
    glBindVertexArray(m_vao);

    // Buffer data
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, idx * sizeof(VertexData), coords, GL_DYNAMIC_DRAW);

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, idx);
}
