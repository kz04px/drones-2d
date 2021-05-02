#include <events/window_event.hpp>
#include <window/window.hpp>
#include "application.hpp"

void Application::on_window_resize(WindowResizeEvent &e) {
    m_window->resize(e.width(), e.height());
    m_camera.resize(e.width(), e.height());
}
