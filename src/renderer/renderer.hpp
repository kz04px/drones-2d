#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glm/glm.hpp>
#include <string>
#include "colour.hpp"
#include "program.hpp"
#include "statistics.hpp"
// Shapes
#include "line.hpp"
#include "point.hpp"
#include "quad.hpp"
#include "triangle.hpp"

class Camera;

struct VertexData {
    glm::vec3 position = {};
    Colour colour = {};
};

class Renderer {
   public:
    Renderer();

    ~Renderer();

    [[nodiscard]] auto statistics() const noexcept {
        return m_statistics;
    }

    void init();

    void begin(const Camera &camera);

    void end();

    void flush();

    void draw(const Triangle &triangle, const int layer = 0);

    void draw(const Point &line, const int layer = 0);

    void draw(const Line &line, const int layer = 0);

    void draw(const Quad &quad, const int layer = 0);

    void clear();

    void clear_colour(const int r, const int g, const int b, const int a = 255);

    void clear_colour(const float r, const float g, const float b, const float a = 1.0f);

    void draw_text(const std::string &text, const int x, const int y);

    void enable_wireframe();

    void disable_wireframe();

    void toggle_wireframe();

   private:
    void draw_quad(const glm::vec3 &pos, const glm::vec2 &size, const Colour &c);

    Program m_program;
    GLuint m_vao;
    GLuint m_vbo;
    Statistics m_statistics;
    constexpr static int m_max_buffer_size = 128;
    int m_buffer_index;
    VertexData m_data[m_max_buffer_size];
    bool m_wireframe;
};

#endif
