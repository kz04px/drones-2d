#ifndef EVENTS_MANAGER_HPP
#define EVENTS_MANAGER_HPP

#include <cassert>
#include <map>
#include <memory>
#include <vector>
#include "event.hpp"

class EventManager {
   public:
    EventManager() {
    }

    [[nodiscard]] static EventManager *instance() {
        static EventManager instance_;
        return &instance_;
    }

    void push_back(const Event &e) noexcept {
        queue_.push_back(e);
    }

    [[nodiscard]] bool empty() const noexcept {
        return queue_.size() == 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return queue_.size();
    }

    void clear() noexcept {
        queue_.clear();
    }

    void register_callback(const EventType &ev, const std::function<void(Event &)> &func) {
        callbacks_[ev].push_back(func);
    }

    void update() noexcept {
        while (!queue_.empty()) {
            const Event e = queue_.back();
            for (const auto &callback : callbacks_[e.type()]) {
                callback(e);
            }
        }
        /*
        for (const Event &e : queue_) {
            for (const auto &callback : callbacks_[e.type()]) {
                callback(e);
            }
        }
        */
    }

    EventManager(EventManager const &);

    EventManager &operator=(EventManager const &);

   private:
    std::map<EventType, std::vector<const std::function<void(Event &)> &>> callbacks_;
    std::vector<Event> queue_;
};

#endif
