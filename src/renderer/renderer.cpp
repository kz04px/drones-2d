#include "renderer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <camera.hpp>
#include <iostream>
#include <memory>
#include "shader.hpp"
// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

Renderer::Renderer() {
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
        std::cerr << "RIP\n";
        std::exit(1);
    }
}

Renderer::~Renderer() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

void Renderer::init() {
    clear_colour(0.0f, 0.0f, 0.0f, 1.0f);
}

void Renderer::begin(const Camera &camera) {
    m_program.use();
    const auto view = camera.matrix();
    glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(view));
}

void Renderer::end() {
    flush();
}

void Renderer::flush() {
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
    m_statistics.draw_calls++;
    m_statistics.num_triangles += m_buffer_index / 3;

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

void Renderer::clear() {
    m_statistics = Statistics();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::clear_colour(const int r, const int g, const int b, const int a) {
    clear_colour(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void Renderer::clear_colour(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void Renderer::draw(const Quad &quad, const int layer) {
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

void Renderer::draw(const Triangle &triangle, const int layer) {
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

void Renderer::draw(const Point &point, const int layer) {
    auto quad = Quad();
    quad.vertices[0] = point.position + glm::vec2{-point.radius, -point.radius};
    quad.vertices[1] = point.position + glm::vec2{-point.radius, point.radius};
    quad.vertices[2] = point.position + glm::vec2{point.radius, point.radius};
    quad.vertices[3] = point.position + glm::vec2{point.radius, -point.radius};
    quad.colour = point.colour;
    draw(quad, layer);
}

void Renderer::draw(const Line &line, const int layer) {
    /*
    const auto length = glm::distance(line.vertices[0], line.vertices[1]);

    auto quad = Quad();
    quad.vertices[0] = line.vertices[0] + glm::vec2{0.5f * -line.thickness, 0.0f};
    quad.vertices[1] = line.vertices[0] + glm::vec2{0.5f * -line.thickness, length};
    quad.vertices[2] = line.vertices[0] + glm::vec2{0.5f * line.thickness, length};
    quad.vertices[3] = line.vertices[0] + glm::vec2{0.5f * line.thickness, 0.0f};
    quad.colour = line.colour;
    quad.rotation = glm::angle(glm::normalize(line.vertices[1]), glm::normalize(line.vertices[0]));
    quad.translation = line.translation;
    draw(quad, layer);
    */

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

void Renderer::draw_text(const std::string &, const int, const int) {
}

void Renderer::enable_wireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_wireframe = true;
}

void Renderer::disable_wireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_wireframe = false;
}

void Renderer::toggle_wireframe() {
    if (m_wireframe) {
        disable_wireframe();
    } else {
        enable_wireframe();
    }
}
