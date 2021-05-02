#ifndef MOUSE_EVENT_HPP_INCLUDED
#define MOUSE_EVENT_HPP_INCLUDED

#include "event.hpp"

class MouseDownEvent : public Event {
   public:
    MouseDownEvent(const int x, const int y, const int button) : m_x(x), m_y(y), m_button(button) {
    }

    [[nodiscard]] EventType type() const override {
        return EventType::MouseDownEvent;
    }

    [[nodiscard]] int groups() const override {
        return EventGroup::InputGroup | EventGroup::MouseGroup;
    }

    [[nodiscard]] std::string string() const override {
        return "MouseDownEvent";
    }

    [[nodiscard]] int x() const {
        return m_x;
    }

    [[nodiscard]] int y() const {
        return m_y;
    }

    [[nodiscard]] int button() const {
        return m_button;
    }

   private:
    int m_x;
    int m_y;
    int m_button;
};

class MouseUpEvent : public Event {
   public:
    MouseUpEvent(const int x, const int y, const int button) : m_x(x), m_y(y), m_button(button) {
    }

    [[nodiscard]] EventType type() const override {
        return EventType::MouseUpEvent;
    }

    [[nodiscard]] int groups() const override {
        return EventGroup::InputGroup | EventGroup::MouseGroup;
    }

    [[nodiscard]] std::string string() const override {
        return "MouseUpEvent";
    }

    [[nodiscard]] int x() const {
        return m_x;
    }

    [[nodiscard]] int y() const {
        return m_y;
    }

    [[nodiscard]] int button() const {
        return m_button;
    }

   private:
    int m_x;
    int m_y;
    int m_button;
};

class MouseMoveEvent : public Event {
   public:
    MouseMoveEvent(const int x, const int y, const int dx, const int dy) : m_x(x), m_y(y), m_dx{dx}, m_dy{dy} {
    }

    [[nodiscard]] EventType type() const override {
        return EventType::MouseMoveEvent;
    }

    [[nodiscard]] int groups() const override {
        return EventGroup::InputGroup | EventGroup::MouseGroup;
    }

    [[nodiscard]] std::string string() const override {
        return "MouseMoveEvent";
    }

    [[nodiscard]] int x() const noexcept {
        return m_x;
    }

    [[nodiscard]] int y() const noexcept {
        return m_y;
    }

    [[nodiscard]] int dx() const noexcept {
        return m_dx;
    }

    [[nodiscard]] int dy() const noexcept {
        return m_dy;
    }

   private:
    int m_x;
    int m_y;
    int m_dx;
    int m_dy;
};

class MouseScrollEvent : public Event {
   public:
    MouseScrollEvent(const double amount) : m_amount(amount) {
    }

    [[nodiscard]] EventType type() const noexcept override {
        return EventType::MouseScrollEvent;
    }

    [[nodiscard]] int groups() const noexcept override {
        return EventGroup::InputGroup | EventGroup::MouseGroup;
    }

    [[nodiscard]] std::string string() const noexcept override {
        return "MouseScrollEvent";
    }

    [[nodiscard]] double amount() const noexcept {
        return m_amount;
    }

   private:
    double m_amount;
};

#endif
