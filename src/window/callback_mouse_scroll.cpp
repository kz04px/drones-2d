#include <cassert>
#include <events/mouse_event.hpp>
#include "window.hpp"

void callback_mouse_scroll(GLFWwindow *window, double, double yoffset) {
    assert(window);

    auto data = (Window::Data *)glfwGetWindowUserPointer(window);

    MouseScrollEvent event(yoffset);
    data->callback(event);
}
