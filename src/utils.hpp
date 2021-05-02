#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>

namespace utils {

[[nodiscard]] constexpr float deg_to_rad(const float degrees) {
    return degrees * 0.0174532925f;
}

[[nodiscard]] constexpr float rad_to_deg(const float radians) {
    return radians * 57.2957795131f;
}

[[nodiscard]] static float rand_between(const float a, const float b) {
    return (b - a) * static_cast<float>(rand()) / RAND_MAX + a;
}

}  // namespace utils

#endif
