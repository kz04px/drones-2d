#include <events/window_event.hpp>
#include "application.hpp"

void Application::on_window_close(WindowCloseEvent &) {
    m_quit = true;
}
