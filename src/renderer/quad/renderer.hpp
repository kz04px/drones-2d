#ifndef QUAD_RENDERER_HPP
#define QUAD_RENDERER_HPP

#include <glm/glm.hpp>
#include "../colour.hpp"
#include "../program.hpp"

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

    void draw(const Triangle &triangle, const float layer = 0.0f);

    void draw(const Point &line, const float layer = 0.0f);

    void draw(const Line &line, const float layer = 0.0f);

    void draw(const Quad &quad, const float layer = 0.0f);

    void flush();

    glm::mat4x4 m_view;

   private:
    constexpr static int m_max_buffer_size = 128;
    Program m_program;
    GLuint m_vao;
    GLuint m_vbo;
    int m_buffer_index;
    VertexData m_data[m_max_buffer_size];
};

#endif
