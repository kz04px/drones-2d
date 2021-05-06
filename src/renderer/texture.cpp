#include "texture.hpp"

Texture::Texture() : id{}, width{}, height{}, channels{} {
    glCreateTextures(GL_TEXTURE_2D, 1, &id);
}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::bind() const noexcept {
    glBindTexture(GL_TEXTURE_2D, id);
}
