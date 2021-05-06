#include <drones/render/draw_world.hpp>
#include <glm/glm.hpp>
#include <mutex>
#include <renderer/quad.hpp>
#include <renderer/renderer.hpp>
#include <thread>
#include <window/window.hpp>
#include "application.hpp"
#include "worker.hpp"

void Application::run() {
    std::mutex mutex;

    // Create worker thread
    auto thread = std::thread(&worker, std::ref(m_world), std::ref(mutex), std::ref(m_sim_speed), std::ref(m_quit));

    while (!m_quit) {
        // Events
        m_window->poll_events();

        // Clear
        m_renderer->clear();

        const auto render_sim = m_sim_speed < 4;

        // Render world
        if (render_sim) {
            std::lock_guard<std::mutex> guard(mutex);
            draw_world(m_renderer, m_camera, m_world, m_debug);
        }

        bool render_overlay = true;

        // Render overlay
        if (render_overlay) {
            const auto generation_string = "Generation: " + std::to_string(m_world.generation + 1);
            const auto speed_string = "Speed: " + std::to_string(m_sim_speed + 1);
            const auto generation_size = m_renderer->predict_size(generation_string, 20.0f);
            const auto speed_size = m_renderer->predict_size(speed_string, 20.0f);
            const auto screen_view = glm::ortho(0.0f,
                                                static_cast<float>(m_window->width()),
                                                0.0f,
                                                static_cast<float>(m_window->height()),
                                                20.0f,
                                                -20.0f);

            m_renderer->begin(screen_view);
            {
                // Render stats background
                const float x = 0.0f;
                const float y = m_window->height();
                const float w = std::max(generation_size.first, speed_size.first);
                const float h = generation_size.second + speed_size.second;

                auto quad = Quad();
                quad.vertices[0] = glm::vec2{x, y - h};
                quad.vertices[1] = glm::vec2{x, y};
                quad.vertices[2] = glm::vec2{x + w, y};
                quad.vertices[3] = glm::vec2{x + w, y - h};
                quad.colour = colour::black;
                m_renderer->draw(quad, 11);
            }
            m_renderer->end();

            m_renderer->begin(screen_view);
            {
                // Render stats
                int y = m_window->height() - generation_size.second;
                m_renderer->draw_text(generation_string, 0, y, 20.0f, 12);
                y -= speed_size.second;
                m_renderer->draw_text(speed_string, 0, y, 20.0f, 12);
            }

            // Are we paused?
            if (m_world.paused) {
                const auto str = "Paused";
                const auto size = m_renderer->predict_size(str, 48.0f);
                const auto x = m_window->width() / 2 - size.first / 2;
                const auto y = m_window->height() - size.second;
                m_renderer->draw_text(str, x, y, 48.0f, 12);
            }

            // Are we rendering the sim?
            if (!render_sim) {
                const auto str = "Rendering disabled in fast mode";
                const auto size = m_renderer->predict_size(str, 20.0f);
                const auto x = m_window->width() / 2 - size.first / 2;
                const auto y = m_window->height() / 2 - size.second / 2;
                m_renderer->draw_text(str, x, y, 20.0f, 12);
            }
            m_renderer->end();
        }

        // Swap buffers
        m_window->swap();
    }

    thread.join();
}
