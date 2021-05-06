#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <glm/glm.hpp>
#include <string>
#include "../program.hpp"
#include "../statistics.hpp"
#include "atlas.hpp"
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

class TextRenderer {
   public:
    struct VertexData {
        glm::vec3 position;
        glm::vec2 uv;
    };

    TextRenderer();

    ~TextRenderer();

    void draw(const std::string &text, float x, float y, const int layer = 0);

    glm::mat4x4 m_view;

   private:
    Program m_program;
    Statistics m_statistics;
    FT_Library m_ft;
    Atlas m_atlas;
    GLuint m_vao;
    GLuint m_vbo;
};

#endif
