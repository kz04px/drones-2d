#ifndef WINDOW_EVENT_HPP_INCLUDED
#define WINDOW_EVENT_HPP_INCLUDED

#include "event.hpp"

class WindowResizeEvent : public Event {
   public:
    WindowResizeEvent(const int w, const int h) : m_width(w), m_height(h) {
    }

    [[nodiscard]] EventType type() const override {
        return EventType::WindowResizeEvent;
    }

    [[nodiscard]] int groups() const override {
        return EventGroup::WindowGroup;
    }

    [[nodiscard]] std::string string() const override {
        return "WindowResizeEvent";
    }

    [[nodiscard]] int width() const {
        return m_width;
    }

    [[nodiscard]] int height() const {
        return m_height;
    }

   private:
    int m_width;
    int m_height;
};

class WindowCloseEvent : public Event {
   public:
    WindowCloseEvent() {
    }

    [[nodiscard]] EventType type() const override {
        return EventType::WindowCloseEvent;
    }

    [[nodiscard]] int groups() const override {
        return EventGroup::WindowGroup;
    }

    [[nodiscard]] std::string string() const override {
        return "WindowCloseEvent";
    }

   private:
};

#endif
