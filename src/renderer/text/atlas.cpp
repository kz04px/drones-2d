#include "atlas.hpp"
#include <algorithm>

constexpr int max_width = 1024;

Atlas::Atlas() {
}

Atlas::~Atlas() {
}

void Atlas::load_truefont(FT_Face &face, const int font_size) {
    FT_Set_Pixel_Sizes(face, 0, font_size);
    FT_GlyphSlot g = face->glyph;

    unsigned int roww = 0;
    unsigned int rowh = 0;

    // Determine the texture atlas dimensions
    for (int i = 32; i < 128; ++i) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            continue;
        }

        // Wrap around onto a new line
        if (roww + g->bitmap.width + 1 >= max_width) {
            width = std::max(width, roww);
            height += rowh;
            roww = 0;
            rowh = 0;
        }

        roww += g->bitmap.width + 1;
        rowh = std::max(rowh, g->bitmap.rows);
    }

    width = std::max(width, roww);
    height += rowh;

    // How tall should a line be?
    line_height = face->size->metrics.height >> 6;

    // How high is the origin from the lower point?
    origin_height =
        (face->bbox.yMin >> 6) * static_cast<float>(line_height) / ((face->bbox.yMax >> 6) - (face->bbox.yMin >> 6));

    // Bind
    glBindTexture(GL_TEXTURE_2D, id);

    // 1 byte alignment when uploading texture data
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Create
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

    // Clamping to edges is important to prevent artifacts when scaling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Linear filtering usually looks best for text
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Current texture coordinates
    int tx = 0;
    int ty = 0;
    rowh = 0;

    // Create atlas from font
    for (int i = 32; i < 128; i++) {
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            continue;
        }

        // Wrap around onto a new line
        if (tx + g->bitmap.width + 1 >= max_width) {
            ty += rowh;
            rowh = 0;
            tx = 0;
        }

        // Load character bitmap into the atlas
        glTexSubImage2D(
            GL_TEXTURE_2D, 0, tx, ty, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

        character_info[i].ax = g->advance.x >> 6;
        character_info[i].ay = g->advance.y >> 6;

        character_info[i].bw = g->bitmap.width;
        character_info[i].bh = g->bitmap.rows;

        character_info[i].bl = g->bitmap_left;
        character_info[i].bt = g->bitmap_top;

        character_info[i].tx = static_cast<float>(tx) / width;
        character_info[i].ty = static_cast<float>(ty) / height;

        character_info[i].tw = static_cast<float>(g->bitmap.width) / width;
        character_info[i].th = static_cast<float>(g->bitmap.rows) / height;

        rowh = std::max(rowh, g->bitmap.rows);
        tx += g->bitmap.width + 1;
    }
}

[[nodiscard]] CharacterInformation Atlas::info(const char c) const noexcept {
    return character_info[static_cast<int>(c)];
}
