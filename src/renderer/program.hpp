#ifndef OPENGL_PROGRAM_HPP
#define OPENGL_PROGRAM_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class Shader;

class Program {
   public:
    Program();

    ~Program();

    void link();

    bool valid() const;

    void attach(const Shader &shader);

    void detach(const Shader &shader);

    void use() const;

    GLuint id() const;

   private:
    GLuint m_id;
    std::vector<GLuint> m_shaders;
    bool m_linked;
};

#endif
