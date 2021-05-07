#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glm/glm.hpp>
#include <string>
#include "colour.hpp"
#include "program.hpp"
#include "statistics.hpp"
// Renderers
#include "quad/renderer.hpp"
#include "text/renderer.hpp"

class Camera;
class Triangle;
class Point;
class Line;
class Quad;
class Atlas;

class RenderAPI {
   public:
    RenderAPI();

    ~RenderAPI();

    [[nodiscard]] auto statistics() const noexcept {
        return m_statistics;
    }

    [[nodiscard]] std::pair<int, int> predict_size(const std::string &text, const float height);

    void init();

    void begin(const Camera &camera);

    void begin(const glm::mat4 &mat);

    void end();

    void flush();

    void draw(const Triangle &triangle, const float layer = 0.0f);

    void draw(const Point &line, const float layer = 0.0f);

    void draw(const Line &line, const float layer = 0.0f);

    void draw(const Quad &quad, const float layer = 0.0f);

    void draw_text(const std::string &text, const float x, const float y, const float height, const float layer = 0.0f);

    void clear();

    void clear_colour(const int r, const int g, const int b, const int a = 255);

    void clear_colour(const float r, const float g, const float b, const float a = 1.0f);

    void enable_wireframe();

    void disable_wireframe();

    void toggle_wireframe();

   private:
    void draw_quad(const glm::vec3 &pos, const glm::vec2 &size, const Colour &c);

    Statistics m_statistics;
    QuadRenderer m_quad_renderer;
    TextRenderer m_text_renderer;
    glm::mat4x4 m_view;
    bool m_wireframe;
};

#endif
