#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <camera.hpp>
#include <memory>
#include <simulation/simulation.hpp>

struct Event;
struct KeyPressEvent;
struct KeyReleaseEvent;
struct WindowCloseEvent;
struct WindowResizeEvent;
struct MouseDownEvent;
struct MouseMoveEvent;
struct MouseUpEvent;
struct MouseScrollEvent;
class RenderAPI;
class Window;

class Application {
   public:
    Application();

    ~Application();

    void run();

    void on_event(Event &e);

    void on_key_press(KeyPressEvent &e);

    void on_key_release(KeyReleaseEvent &e);

    void on_window_close(WindowCloseEvent &e);

    void on_window_resize(WindowResizeEvent &e);

    void on_mouse_down(MouseDownEvent &e);

    void on_mouse_up(MouseUpEvent &e);

    void on_mouse_move(MouseMoveEvent &e);

    void on_mouse_scroll(MouseScrollEvent &e);

   private:
    std::unique_ptr<Window> m_window;
    std::unique_ptr<RenderAPI> m_renderer;
    Simulation m_simulation;
    Camera m_camera;
    int m_sim_speed;
    bool m_drag_camera;
    bool m_debug;
    bool m_quit;
};

#endif
