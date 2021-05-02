#include <chrono>
#include <iostream>
#include <simulation/simulation.hpp>
#include "application/application.hpp"

int main(int argc, char **argv) {
#ifndef NDEBUG
    std::cout << "Debug build!\n\n";
#endif

    bool benchmark = false;

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-benchmark") {
            benchmark = true;
        }
    }

    if (benchmark) {
        constexpr int frames = 200000;
        Simulation sim;
        sim.paused = false;
        sim.init();

        const auto t0 = std::chrono::steady_clock::now();
        for (int i = 0; i < frames; ++i) {
            sim.step(1.0f / 60, false);
        }
        const auto t1 = std::chrono::steady_clock::now();
        const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);

        std::cout << "Generations: " << sim.generation << "\n";
        std::cout << "Frames: " << frames << "\n";
        std::cout << "ms: " << diff.count() << "\n";
        std::cout << "ms/frame: " << static_cast<float>(diff.count()) / frames << "\n";
        std::cout << "frames/ms: " << static_cast<float>(frames) / diff.count() << "\n";
        return 0;
    }

    try {
        Application app;
        app.run();
    } catch (...) {
        return 1;
    }

    return 0;
}
