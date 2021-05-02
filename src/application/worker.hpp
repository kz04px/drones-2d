#ifndef APPLICATION_WORKER_HPP
#define APPLICATION_WORKER_HPP

#include <mutex>

struct Simulation;

void worker(Simulation &sim, std::mutex &mutex, int &speed, bool &quit);

#endif
