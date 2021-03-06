#include <chrono>
#include <condition_variable>
#include <drones/world.hpp>
#include <mutex>
#include <thread>

static const int target_fps[5] = {
    10,
    60,
    120,
    240,
    0,
};

void worker(World &sim, std::mutex &mutex, int &speed, bool &paused, bool &quit) {
    // Create simulation
    sim.init();

    while (!quit) {
        while (paused && !quit) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        const auto t0 = std::chrono::steady_clock::now();
        {
            std::lock_guard<std::mutex> guard(mutex);
            sim.step(1.0f / 60);
        }
        const auto t1 = std::chrono::steady_clock::now();

        if (target_fps[speed]) {
            const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
            const int fps = target_fps[speed];
            const auto max_frame_time = std::chrono::milliseconds(1000 / fps);
            const auto wait_for = max_frame_time - diff;

            if (wait_for.count() > 0) {
                std::this_thread::sleep_for(wait_for);
            }
        }
    }
}
