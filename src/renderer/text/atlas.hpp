#ifndef RENDERER_TEXT_ATLAS_HPP
#define RENDERER_TEXT_ATLAS_HPP

#include "../texture.hpp"
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H

struct CharacterInformation {
    // Advance x & y
    float ax = 0.0f;
    float ay = 0.0f;

    // Bitmap width & height
    float bw = 0.0f;
    float bh = 0.0f;

    // Bitmap left & top
    float bl = 0.0f;
    float bt = 0.0f;

    // Texture x & y coordinates
    float tx = 0.0f;
    float ty = 0.0f;

    // Texture width & height
    float tw = 0.0f;
    float th = 0.0f;
};

struct Atlas : public Texture {
    CharacterInformation character_info[128] = {};
    int line_height = 0;
    int origin_height = 0;

    Atlas();

    ~Atlas();

    void load_truefont(FT_Face &face, const int font_size);

    [[nodiscard]] CharacterInformation info(const char c) const noexcept;
};

#endif
