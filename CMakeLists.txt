cmake_minimum_required(VERSION 3.10)

# Project
project(Drone2D VERSION 1.0 LANGUAGES CXX)

if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

# Find packages
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Threads)

# Third party includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/)

# Flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add the executable
add_executable(
    main
    src/main.cpp

    src/application/application.cpp
    src/application/on_event.cpp
    src/application/on_key_press.cpp
    src/application/on_key_release.cpp
    src/application/on_mouse_down.cpp
    src/application/on_mouse_move.cpp
    src/application/on_mouse_scroll.cpp
    src/application/on_mouse_up.cpp
    src/application/on_window_close.cpp
    src/application/on_window_resize.cpp
    src/application/run.cpp
    src/application/worker.cpp

    src/renderer/program.cpp
    src/renderer/renderer.cpp
    src/renderer/shader.cpp

    src/window/window.cpp
    src/window/callback_cursor_position.cpp
    src/window/callback_mouse_scroll.cpp
    src/window/callback_keyboard.cpp
    src/window/callback_window_close.cpp
    src/window/callback_mouse_button.cpp
    src/window/callback_window_size.cpp

    # Drones
    src/drones/step.cpp
    src/drones/draw_drone.cpp
    src/drones/draw_world.cpp

    # Simulation
    src/simulation/count_completed.cpp
    src/simulation/draw_simulation.cpp
    src/simulation/init.cpp
    src/simulation/step.cpp
)

target_link_libraries(main glfw)
target_link_libraries(main GLEW)
target_link_libraries(main OpenGL)
target_link_libraries(main Threads::Threads)
