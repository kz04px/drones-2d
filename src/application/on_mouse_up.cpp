#include <camera.hpp>
#include <events/mouse_event.hpp>
#include "application.hpp"
// GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

void Application::on_mouse_up(MouseUpEvent &e) {
    switch (e.button()) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            m_drag_camera = false;
            break;
        default:
            break;
    }
}
