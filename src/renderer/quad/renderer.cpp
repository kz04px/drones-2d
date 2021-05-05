#include "renderer.hpp"
#include "../shader.hpp"

QuadRenderer::QuadRenderer() {
    // Program
    auto vs = Shader::from_string(Shader::Type::Vertex,
                                  "#version 430                                  \n"
                                  "                                              \n"
                                  "layout(location = 0) uniform mat4 view;       \n"
                                  "                                              \n"
                                  "layout(location = 0) in vec3 vertices;        \n"
                                  "layout(location = 1) in vec4 colour;          \n"
                                  "                                              \n"
                                  "layout(location = 0) out vec4 out_weow;       \n"
                                  "                                              \n"
                                  "void main() {                                 \n"
                                  "    gl_Position = view * vec4(vertices, 1.0); \n"
                                  "    out_weow = colour;                        \n"
                                  "}                                               ");

    auto fs = Shader::from_string(Shader::Type::Fragment,
                                  "#version 430                             \n"
                                  "                                         \n"
                                  "layout(location = 0) in vec4 out_weow;   \n"
                                  "                                         \n"
                                  "layout(location = 0) out vec4 FragColor; \n"
                                  "                                         \n"
                                  "void main() {                            \n"
                                  "    FragColor = out_weow;                \n"
                                  "}                                          ");

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

    // Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<GLvoid *>(offsetof(VertexData, position)));

    // Colours
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), reinterpret_cast<GLvoid *>(offsetof(VertexData, colour)));

    if (!m_program.valid()) {
        throw;
    }
}

QuadRenderer::~QuadRenderer() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}
