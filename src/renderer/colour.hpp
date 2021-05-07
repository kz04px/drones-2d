#ifndef RENDERER_COLOUR_HPP
#define RENDERER_COLOUR_HPP

struct Colour {
    constexpr Colour() : r{0.0f}, g{0.0f}, b{0.0f}, a{1.0f} {
    }

    constexpr Colour(const int red, const int green, const int blue, const int alpha = 255)
        : r{red / 255.0f}, g{green / 255.0f}, b{blue / 255.0f}, a{alpha / 255.0f} {
    }

    constexpr Colour(const float red, const float green, const float blue, const float alpha = 1.0f)
        : r{red}, g{green}, b{blue}, a{alpha} {
    }

    float r;
    float g;
    float b;
    float a;
};

namespace colour {

constexpr Colour black = Colour(0.0f, 0.0f, 0.0f);
constexpr Colour white = Colour(1.0f, 1.0f, 1.0f);
constexpr Colour red = Colour(1.0f, 0.0f, 0.0f);
constexpr Colour green = Colour(0.0f, 1.0f, 0.0f);
constexpr Colour blue = Colour(0.0f, 0.0f, 1.0f);
constexpr Colour sky_blue = Colour(0.529f, 0.808f, 0.922f);
constexpr Colour yellow = Colour(1.0f, 1.0f, 0.0f);
constexpr Colour grass = Colour(21, 97, 17);
constexpr Colour brown = Colour(139, 69, 19);
constexpr Colour dark_green = Colour(0, 100, 0);
constexpr Colour grey = Colour(200, 200, 200);
constexpr Colour dark_grey = Colour(100, 100, 100);

}  // namespace colour

#endif
