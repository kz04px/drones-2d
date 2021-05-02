#ifndef OPENGL_WINDOW_HPP
#define OPENGL_WINDOW_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

struct glfwDeleter {
    void operator()(GLFWwindow *wnd) {
        glfwDestroyWindow(wnd);
    }
};

struct Event;

class Window {
   public:
    struct Data {
        int width = 1024;
        int height = 768;
        double mouse_x = 0.0;
        double mouse_y = 0.0;
        bool fullscreen = false;
        std::function<void(Event &)> callback;
    };

    Window();

    ~Window();

    void on_event(Event &e);

    void poll_events();

    void resize(const int w, const int h);

    void swap();

    void hide_mouse();

    void show_mouse();

    void set_cursor_position(const int x, const int y);

    void set_title(const std::string &title);

    void set_callback(const std::function<void(Event &)> &func) {
        m_data.callback = func;
    }

    [[nodiscard]] int width() const noexcept {
        return m_data.width;
    }

    [[nodiscard]] int height() const noexcept {
        return m_data.height;
    }

    [[nodiscard]] bool fullscreen() const noexcept {
        return m_data.fullscreen;
    }

   private:
    std::unique_ptr<GLFWwindow, glfwDeleter> m_window;
    Data m_data;
};

void callback_cursor_position(GLFWwindow *window, double xpos, double ypos);
void callback_keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void callback_mouse_button(GLFWwindow *window, int button, int action, int mods);
void callback_mouse_scroll(GLFWwindow *window, double xoffset, double yoffset);
void callback_window_close(GLFWwindow *window);
void callback_window_size(GLFWwindow *window, int width, int height);

#endif
