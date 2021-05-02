#include <mutex>
#include <renderer/renderer.hpp>
#include <simulation/draw_simulation.hpp>
#include <thread>
#include <window/window.hpp>
#include "application.hpp"
#include "worker.hpp"

void Application::run() {
    std::mutex mutex;

    // Create worker thread
    auto thread =
        std::thread(&worker, std::ref(m_simulation), std::ref(mutex), std::ref(m_sim_speed), std::ref(m_quit));

    while (!m_quit) {
        // Events
        m_window->poll_events();

        // Clear
        m_renderer->clear();

        // Render
        if (m_sim_speed < 4) {
            std::lock_guard<std::mutex> guard(mutex);
            draw_simulation(m_renderer, m_camera, m_simulation, m_debug);
        }

        // Swap buffers
        m_window->swap();
    }

    thread.join();
}
