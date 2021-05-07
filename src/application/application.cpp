#include "application.hpp"
#include <events/window_event.hpp>
#include <renderer/renderer.hpp>
#include <window/window.hpp>

Application::Application()
    : m_window{new Window()},
      m_world{},
      m_camera{},
      m_sim_speed{1},
      m_drag_camera{false},
      m_debug{true},
      m_quit{false} {
    srand(time(0));
    m_window->set_callback(std::bind(&Application::on_event, this, std::placeholders::_1));
    auto event = WindowResizeEvent(m_window->width(), m_window->height());
    on_event(event);
    RenderAPI::init();
    RenderAPI::clear_colour(0.01f, 0.008f, 0.04f);
}

Application::~Application() {
    RenderAPI::destroy();
}
