#include <cassert>
#include <events/mouse_event.hpp>
#include "window.hpp"

void callback_mouse_button(GLFWwindow *window, int button, int action, int) {
    assert(window);

    auto data = (Window::Data *)glfwGetWindowUserPointer(window);

    if (action == GLFW_PRESS) {
        MouseDownEvent event(data->mouse_x, data->mouse_y, button);
        data->callback(event);
    } else if (action == GLFW_RELEASE) {
        MouseUpEvent event(data->mouse_x, data->mouse_y, button);
        data->callback(event);
    } else {
    }
}
