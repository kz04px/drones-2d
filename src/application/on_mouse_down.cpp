#include <events/mouse_event.hpp>
#include "application.hpp"

void Application::on_mouse_down(MouseDownEvent &e) {
    switch (e.button()) {
        case 0:  // Left
            break;
        case 1:  // Right
            break;
        case 2:  // Middle
            m_drag_camera = true;
            break;
        default:
            break;
    }
}
