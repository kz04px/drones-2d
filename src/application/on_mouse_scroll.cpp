#include <events/mouse_event.hpp>
#include "application.hpp"

void Application::on_mouse_scroll(MouseScrollEvent &e) {
    if (e.amount() > 0) {
        m_camera.size *= 0.9f;
    } else if (e.amount() < 0) {
        m_camera.size /= 0.9f;
    }
}
