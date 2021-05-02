#include "window.hpp"
#include <cassert>
#include <events/keyboard_event.hpp>
#include <events/mouse_event.hpp>
#include <events/window_event.hpp>
#include <iostream>

Window::Window() {
    const auto success = glfwInit();
    if (!success) {
        std::cerr << "glfwInit() failure" << std::endl;
        std::exit(1);
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    m_window = std::unique_ptr<GLFWwindow, glfwDeleter>(
        glfwCreateWindow(m_data.width, m_data.height, "Drone Evolution", nullptr, nullptr));

    if (!m_window.get()) {
        std::exit(1);
    }

    glfwMakeContextCurrent(m_window.get());

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPointSize(10.0);
    glLineWidth(2.0);

    glfwSetWindowUserPointer(m_window.get(), &m_data);

    // Set callbacks -- Window
    glfwSetWindowSizeCallback(m_window.get(), callback_window_size);
    glfwSetWindowCloseCallback(m_window.get(), callback_window_close);
    // Set callbacks -- Mouse
    glfwSetCursorPosCallback(m_window.get(), callback_cursor_position);
    glfwSetMouseButtonCallback(m_window.get(), callback_mouse_button);
    glfwSetScrollCallback(m_window.get(), callback_mouse_scroll);
    // Set callbacks -- Keyboard
    glfwSetKeyCallback(m_window.get(), callback_keyboard);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "glewInit error" << std::endl;
    }
}

Window::~Window() {
    glfwTerminate();
}

void Window::on_event(Event &e) {
}

void Window::poll_events() {
    glfwPollEvents();
}

void Window::resize(const int w, const int h) {
    glViewport(0, 0, w, h);
}

void Window::swap() {
    glfwSwapBuffers(m_window.get());
}

void Window::hide_mouse() {
    glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::show_mouse() {
    glfwSetInputMode(m_window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::set_cursor_position(const int x, const int y) {
    glfwSetCursorPos(m_window.get(), x, y);
}

void Window::set_title(const std::string &title) {
    glfwSetWindowTitle(m_window.get(), title.c_str());
}
