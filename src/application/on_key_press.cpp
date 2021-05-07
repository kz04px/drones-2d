#include <events/keyboard_event.hpp>
#include <iostream>
#include <renderer/renderer.hpp>
#include "application.hpp"

void Application::on_key_press(KeyPressEvent &e) {
    switch (e.key()) {
        case 256:  // Esc
            m_quit = true;
            break;
        case 32:  // Space
            std::cout << "Toggle pause: " << (m_world.paused ? "off" : "on") << std::endl;
            m_world.paused = !m_world.paused;
            break;
        case 290:  // F1
            m_debug = !m_debug;
            std::cout << "Debug: " << (m_debug ? "ON" : "OFF") << "\n\n";
            break;
        case 291:  // F2
            std::cout << "Debug: " << (m_debug ? "ON" : "OFF") << "\n";
            std::cout << "FPS: -\n";
            std::cout << "Draw calls: " << RenderAPI::statistics.draw_calls << "\n";
            std::cout << "Triangles: " << RenderAPI::statistics.num_triangles << "\n";
            std::cout << "\n";
            break;
        case 292:  // F3
            std::cout << "Toggle wireframe" << std::endl;
            RenderAPI::toggle_wireframe();
            break;
        case 293:  // F4
            std::cout << "Reset camera" << std::endl;
            m_camera.position = glm::vec2{0.0f, 0.0f};
            break;
        case 49:  // 1
            std::cout << "Speed 1" << std::endl;
            m_sim_speed = 0;
            break;
        case 50:  // 2
            std::cout << "Speed 2" << std::endl;
            m_sim_speed = 1;
            break;
        case 51:  // 3
            std::cout << "Speed 3" << std::endl;
            m_sim_speed = 2;
            break;
        case 52:  // 4
            std::cout << "Speed 4" << std::endl;
            m_sim_speed = 3;
            break;
        case 53:  // 5
            std::cout << "Speed 5" << std::endl;
            m_sim_speed = 4;
            break;
        default:
            std::cout << "Unused key: " << e.key() << std::endl;
            break;
    }
}
