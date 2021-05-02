#ifndef OPENGL_SHADER_HPP
#define OPENGL_SHADER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader {
   public:
    enum Type
    {
        Vertex = 0,
        Fragment
    };

    ~Shader();

    [[nodiscard]] static Shader from_string(const Type t, const std::string &text);

    [[nodiscard]] static Shader from_file(const Type t, const std::string &path);

    [[nodiscard]] GLuint id() const noexcept;

    [[nodiscard]] bool valid() const noexcept;

    [[nodiscard]] Type type() const noexcept;

   private:
    Shader();

    Type m_type;
    GLuint m_id;
};

#endif
