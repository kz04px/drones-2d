#include "renderer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <camera.hpp>
#include "shader.hpp"
// Shapes
#include "line.hpp"
#include "point.hpp"
#include "quad.hpp"
#include "triangle.hpp"

RenderAPI::RenderAPI() : m_statistics{}, m_quad_renderer{}, m_text_renderer{}, m_view{}, m_wireframe{false} {
}

RenderAPI::~RenderAPI() {
}

void RenderAPI::init() {
    clear_colour(0.0f, 0.0f, 0.0f, 1.0f);
}

void RenderAPI::begin(const Camera &camera) {
    m_view = camera.matrix();
    m_quad_renderer.m_view = m_view;
    m_text_renderer.m_view = m_view;
}

void RenderAPI::begin(const glm::mat4 &mat) {
    m_view = mat;
    m_quad_renderer.m_view = m_view;
    m_text_renderer.m_view = m_view;
}

void RenderAPI::end() {
    m_quad_renderer.flush();
}

void RenderAPI::clear() {
    m_statistics = Statistics();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderAPI::clear_colour(const int r, const int g, const int b, const int a) {
    clear_colour(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void RenderAPI::clear_colour(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void RenderAPI::draw(const Quad &quad, const int layer) {
    m_quad_renderer.draw(quad, layer);
}

void RenderAPI::draw(const Triangle &triangle, const int layer) {
    m_quad_renderer.draw(triangle, layer);
}

void RenderAPI::draw(const Point &point, const int layer) {
    m_quad_renderer.draw(point, layer);
}

void RenderAPI::draw(const Line &line, const int layer) {
    m_quad_renderer.draw(line, layer);
}

void RenderAPI::draw_text(const std::string &text, const float x, const float y, const float height, const int layer) {
    m_text_renderer.draw(text, x, y, height, layer);
}

void RenderAPI::enable_wireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_wireframe = true;
}

void RenderAPI::disable_wireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    m_wireframe = false;
}

void RenderAPI::toggle_wireframe() {
    if (m_wireframe) {
        disable_wireframe();
    } else {
        enable_wireframe();
    }
}

[[nodiscard]] std::pair<int, int> RenderAPI::predict_size(const std::string &text, const float height) {
    return m_text_renderer.predict_size(text, height);
}
