#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Texture {
    Texture();

    ~Texture();

    void bind() const noexcept;

    GLuint id;
    unsigned int width;
    unsigned int height;
    int channels;
};

#endif
