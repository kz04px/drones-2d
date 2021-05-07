#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera {
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 size = {5.0f, 5.0f};

    [[nodiscard]] glm::mat4 matrix() const noexcept {
        return glm::ortho(left(), right(), bottom(), top(), 20.0f, -20.0f);
    }

    [[nodiscard]] float aspect() const noexcept {
        return size.x / size.y;
    }

    [[nodiscard]] float left() const noexcept {
        return position.x - size.x / 2;
    }

    [[nodiscard]] float right() const noexcept {
        return position.x + size.x / 2;
    }

    [[nodiscard]] float top() const noexcept {
        return position.y + size.y / 2;
    }

    [[nodiscard]] float bottom() const noexcept {
        return position.y - size.y / 2;
    }

    [[nodiscard]] std::pair<float, float> project(const float x, const float y) const noexcept {
        const auto new_x = 2.0f * x - 1.0f;
        const auto new_y = 2.0f * y - 1.0f;
        const auto asd = glm::vec4{new_x, new_y, 0.0f, 1.0f};
        const auto zzz = glm::inverse(matrix()) * asd;
        return {zzz.x / zzz.w, -zzz.y / zzz.w};
    }

    void resize(const float w, const float h) noexcept {
        const float aspect = w / h;
        size.x = size.y * aspect;
    }
};

#endif
