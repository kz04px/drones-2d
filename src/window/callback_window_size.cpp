#include <cassert>
#include <events/window_event.hpp>
#include "window.hpp"

void callback_window_size(GLFWwindow *window, int width, int height) {
    assert(window);

    auto data = (Window::Data *)glfwGetWindowUserPointer(window);
    data->width = width;
    data->height = height;

    WindowResizeEvent event(width, height);
    data->callback(event);
}
