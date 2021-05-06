#include "renderer.hpp"
#include "../shader.hpp"

TextRenderer::TextRenderer() : m_program{}, m_statistics{}, m_ft{}, m_atlas{}, m_vao{}, m_vbo{} {
    // Program
    auto vs = Shader::from_string(Shader::Type::Vertex,
                                  "#version 430                                        \n"
                                  "                                                    \n"
                                  "layout(location = 0) uniform mat4 view;             \n"
                                  "                                                    \n"
                                  "layout(location = 0) in vec3 vertices;              \n"
                                  "layout(location = 1) in vec2 texcoord;              \n"
                                  "                                                    \n"
                                  "layout(location = 0) out vec2 texpos;               \n"
                                  "                                                    \n"
                                  "void main() {                                       \n"
                                  "    gl_Position = view * vec4(vertices, 1.0);       \n"
                                  "    texpos = texcoord;                              \n"
                                  "}                                                   \n");

    auto fs = Shader::from_string(Shader::Type::Fragment,
                                  "#version 430                                                      \n"
                                  "                                                                  \n"
                                  "layout(location = 1) uniform sampler2D tex;                       \n"
                                  "                                                                  \n"
                                  "layout(location = 0) in vec2 texpos;                              \n"
                                  "                                                                  \n"
                                  "layout(location = 0) out vec4 FragColor;                          \n"
                                  "                                                                  \n"
                                  "void main() {                                                     \n"
                                  "    FragColor = vec4(1.0, 0.0, 0.0, texture(tex, texpos).r);      \n"
                                  "}                                                                 \n");

    m_program.attach(vs);
    m_program.attach(fs);
    m_program.link();
    m_program.detach(vs);
    m_program.detach(fs);

    m_program.use();

    // VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // VBO
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Vertices
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<GLvoid *>(offsetof(VertexData, position)));

    // Texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<GLvoid *>(offsetof(VertexData, uv)));

    if (!m_program.valid()) {
        throw "Text program invalid";
    }

    // Initialize FreeType2
    if (FT_Init_FreeType(&m_ft)) {
        throw "FT_Init_FreeType failed";
    }

    FT_Face face;

    // Load a font
    if (FT_New_Face(m_ft, "./fonts/RobotoMono-Regular.ttf", 0, &face)) {
        throw "Can't open font";
    }

    m_atlas.load_truefont(face, 16);

    if (m_atlas.height <= 0 || m_atlas.width <= 0) {
        throw "Atlas height <= 0 || m_atlas.width <= 0";
    }

    FT_Done_Face(face);
}

TextRenderer::~TextRenderer() {
    FT_Done_FreeType(m_ft);
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

[[nodiscard]] std::pair<int, int> TextRenderer::predict_size(const std::string &text) {
    const float scale = 1.0f;
    float w = 0.0f;

    for (const auto c : text) {
        const auto info = m_atlas.info(c);
        w += info.ax * scale;
    }

    return {w, m_atlas.line_height};
}
