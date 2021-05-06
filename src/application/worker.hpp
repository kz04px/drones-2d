#ifndef APPLICATION_WORKER_HPP
#define APPLICATION_WORKER_HPP

#include <mutex>

struct World;

void worker(World &sim, std::mutex &mutex, int &speed, bool &quit);

#endif
