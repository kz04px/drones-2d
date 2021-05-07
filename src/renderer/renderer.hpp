#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <glm/glm.hpp>
#include <string>
#include "colour.hpp"
#include "statistics.hpp"

class Camera;
class Triangle;
class Point;
class Line;
class Quad;
class Atlas;

namespace RenderAPI {

extern Statistics statistics;

[[nodiscard]] std::pair<int, int> predict_size(const std::string &text, const float height);

void init();

void destroy();

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

void draw_quad(const glm::vec3 &pos, const glm::vec2 &size, const Colour &c);

}  // namespace RenderAPI

#endif
