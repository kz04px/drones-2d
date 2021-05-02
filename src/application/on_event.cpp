#include <events/event.hpp>
#include <events/keyboard_event.hpp>
#include <events/mouse_event.hpp>
#include <events/window_event.hpp>
#include "application.hpp"

void Application::on_event(Event &e) {
    switch (e.type()) {
        // Mouse
        case EventType::MouseMoveEvent:
            on_mouse_move(static_cast<MouseMoveEvent &>(e));
            break;
        case EventType::MouseDownEvent:
            on_mouse_down(static_cast<MouseDownEvent &>(e));
            break;
        case EventType::MouseUpEvent:
            on_mouse_up(static_cast<MouseUpEvent &>(e));
            break;
        case EventType::MouseScrollEvent:
            on_mouse_scroll(static_cast<MouseScrollEvent &>(e));
            break;
        // Keyboard
        case EventType::KeyPressEvent:
            on_key_press(static_cast<KeyPressEvent &>(e));
            break;
        case EventType::KeyReleaseEvent:
            on_key_release(static_cast<KeyReleaseEvent &>(e));
            break;
        // Window
        case EventType::WindowCloseEvent:
            on_window_close(static_cast<WindowCloseEvent &>(e));
            break;
        case EventType::WindowResizeEvent:
            on_window_resize(static_cast<WindowResizeEvent &>(e));
            break;
        default:
            break;
    }
}
