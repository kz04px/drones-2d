#include <events/mouse_event.hpp>
#include <window/window.hpp>
#include "application.hpp"

void Application::on_mouse_move(MouseMoveEvent &e) {
    if (m_drag_camera) {
        const auto diff_x = static_cast<float>(e.dx()) / m_window->width();
        const auto diff_y = static_cast<float>(-e.dy()) / m_window->height();
        m_camera.position -= glm::vec2{diff_x, diff_y} * m_camera.size;
    }
}
