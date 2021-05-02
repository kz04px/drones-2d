#include <cassert>
#include <events/window_event.hpp>
#include "window.hpp"

void callback_window_close(GLFWwindow *window) {
    assert(window);

    auto data = (Window::Data *)glfwGetWindowUserPointer(window);

    WindowCloseEvent event;
    data->callback(event);
}
