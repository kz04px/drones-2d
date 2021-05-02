#include <cassert>
#include <events/keyboard_event.hpp>
#include "window.hpp"

int glfw_to_key(const int key) {
    return key;
}

void callback_keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    assert(window);

    auto data = (Window::Data *)glfwGetWindowUserPointer(window);

    const int nkey = glfw_to_key(key);

    if (action == GLFW_PRESS) {
        KeyPressEvent event(nkey, scancode, mods);
        data->callback(event);
    } else if (action == GLFW_RELEASE) {
        KeyReleaseEvent event(nkey, scancode, mods);
        data->callback(event);
    } else if (action == GLFW_REPEAT) {
        KeyRepeatEvent event(nkey, scancode, mods);
        data->callback(event);
    } else {
        assert(false);
    }
}
