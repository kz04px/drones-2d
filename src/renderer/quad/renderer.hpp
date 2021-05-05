#ifndef QUAD_RENDERER_HPP
#define QUAD_RENDERER_HPP

#include <glm/glm.hpp>
#include "../colour.hpp"
#include "../program.hpp"
#include "../statistics.hpp"

class Triangle;
class Point;
class Line;
class Quad;

class QuadRenderer {
   public:
    struct VertexData {
        glm::vec3 position = {};
        Colour colour = {};
    };

    QuadRenderer();

    ~QuadRenderer();

    void draw(const Triangle &triangle, const int layer = 0);

    void draw(const Point &line, const int layer = 0);

    void draw(const Line &line, const int layer = 0);

    void draw(const Quad &quad, const int layer = 0);

    void flush();

    glm::mat4x4 m_view;

   private:
    constexpr static int m_max_buffer_size = 128;
    Program m_program;
    GLuint m_vao;
    GLuint m_vbo;
    int m_buffer_index;
    VertexData m_data[m_max_buffer_size];
    Statistics m_statistics;
};

#endif
