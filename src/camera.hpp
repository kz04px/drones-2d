#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
   public:
    Camera() : m_position{}, m_size{1.0f, 1.0f}, m_zoom{} {
    }

    [[nodiscard]] glm::mat4 matrix() const noexcept {
        return glm::ortho(left(), right(), bottom(), top(), 10.0f, -10.0f);
    }

    [[nodiscard]] glm::vec2 position() const noexcept {
        return m_position;
    }

    [[nodiscard]] float width() const noexcept {
        return m_size.x;
    }

    [[nodiscard]] float height() const noexcept {
        return m_size.y;
    }

    [[nodiscard]] float aspect() const noexcept {
        return width() / height();
    }

    [[nodiscard]] float left() const noexcept {
        return m_position.x - m_size.x / 2;
    }

    [[nodiscard]] float right() const noexcept {
        return m_position.x + m_size.x / 2;
    }

    [[nodiscard]] float top() const noexcept {
        return m_position.y + m_size.y / 2;
    }

    [[nodiscard]] float bottom() const noexcept {
        return m_position.y - m_size.y / 2;
    }

    [[nodiscard]] float zoom() const noexcept {
        return m_zoom;
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
        m_size.x = m_size.y * aspect;
    }

    void zoom_in() noexcept {
        // m_zoom++;
        m_size *= 0.90f;
    }

    void zoom_out() noexcept {
        // m_zoom--;
        m_size /= 0.90f;
    }

    Camera operator+=(const glm::vec2 offset) noexcept {
        m_position += offset;
        return *this;
    }

    Camera operator-=(const glm::vec2 offset) noexcept {
        m_position -= offset;
        return *this;
    }

   public:
    glm::vec2 m_position;
    glm::vec2 m_size;
    int m_zoom;
};

#endif
