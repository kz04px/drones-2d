#include <cassert>
#include <events/mouse_event.hpp>
#include "window.hpp"

void callback_cursor_position(GLFWwindow *window, double xpos, double ypos) {
    assert(window);

    auto data = (Window::Data *)glfwGetWindowUserPointer(window);
    data->mouse_x = xpos;
    data->mouse_y = ypos;

    static int last_x = xpos;
    static int last_y = ypos;
    const int dx = xpos - last_x;
    const int dy = ypos - last_y;
    last_x = xpos;
    last_y = ypos;

    MouseMoveEvent event(xpos, ypos, dx, dy);
    data->callback(event);
}
