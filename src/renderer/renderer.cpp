#include "renderer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <camera.hpp>
#include <memory>
#include "program.hpp"
#include "shader.hpp"
// Renderers
#include "quad/renderer.hpp"
#include "text/renderer.hpp"
// Shapes
#include "line.hpp"
#include "point.hpp"
#include "quad.hpp"
#include "triangle.hpp"

namespace RenderAPI {

std::unique_ptr<QuadRenderer> quad_renderer;
std::unique_ptr<TextRenderer> text_renderer;
Statistics statistics = {};
bool wireframe = false;

void init() {
    quad_renderer = std::make_unique<QuadRenderer>();
    text_renderer = std::make_unique<TextRenderer>();

    clear_colour(0.0f, 0.0f, 0.0f, 1.0f);
}

void destroy() {
    quad_renderer.reset();
    text_renderer.reset();
}

void begin(const Camera &camera) {
    const auto view = camera.matrix();
    quad_renderer->m_view = view;
    text_renderer->m_view = view;
}

void begin(const glm::mat4 &mat) {
    quad_renderer->m_view = mat;
    text_renderer->m_view = mat;
}

void end() {
    quad_renderer->flush();
}

void clear() {
    statistics = Statistics();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void clear_colour(const int r, const int g, const int b, const int a) {
    clear_colour(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

void clear_colour(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
}

void draw(const Quad &quad, const float layer) {
    quad_renderer->draw(quad, layer);
}

void draw(const Triangle &triangle, const float layer) {
    quad_renderer->draw(triangle, layer);
}

void draw(const Point &point, const float layer) {
    quad_renderer->draw(point, layer);
}

void draw(const Line &line, const float layer) {
    quad_renderer->draw(line, layer);
}

void draw_text(const std::string &text, const float x, const float y, const float height, const float layer) {
    text_renderer->draw(text, x, y, height, layer);
}

void enable_wireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    wireframe = true;
}

void disable_wireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    wireframe = false;
}

void toggle_wireframe() {
    if (wireframe) {
        disable_wireframe();
    } else {
        enable_wireframe();
    }
}

[[nodiscard]] std::pair<int, int> predict_size(const std::string &text, const float height) {
    return text_renderer->predict_size(text, height);
}

}  // namespace RenderAPI
