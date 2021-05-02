#ifndef KEYBOARD_EVENT_HPP_INCLUDED
#define KEYBOARD_EVENT_HPP_INCLUDED

#include "event.hpp"

class KeyPressEvent : public Event {
   public:
    KeyPressEvent(int key, int scancode, int mods) : m_key(key), m_scancode(scancode), m_mods(mods) {
    }

    [[nodiscard]] EventType type() const override {
        return EventType::KeyPressEvent;
    }

    [[nodiscard]] int groups() const override {
        return EventGroup::InputGroup | EventGroup::KeyboardGroup;
    }

    [[nodiscard]] std::string string() const override {
        return "KeyPressEvent";
    }

    [[nodiscard]] int key() const {
        return m_key;
    }

    [[nodiscard]] int scancode() const {
        return m_scancode;
    }

    [[nodiscard]] int mods() const {
        return m_mods;
    }

   private:
    int m_key;
    int m_scancode;
    int m_mods;
};

class KeyReleaseEvent : public Event {
   public:
    KeyReleaseEvent(int key, int scancode, int mods) : m_key(key), m_scancode(scancode), m_mods(mods) {
    }

    [[nodiscard]] EventType type() const override {
        return EventType::KeyReleaseEvent;
    }

    [[nodiscard]] int groups() const override {
        return EventGroup::InputGroup | EventGroup::KeyboardGroup;
    }

    [[nodiscard]] std::string string() const override {
        return "KeyReleaseEvent";
    }

    [[nodiscard]] int key() const {
        return m_key;
    }

    [[nodiscard]] int scancode() const {
        return m_scancode;
    }

    [[nodiscard]] int mods() const {
        return m_mods;
    }

   private:
    int m_key;
    int m_scancode;
    int m_mods;
};

class KeyRepeatEvent : public Event {
   public:
    KeyRepeatEvent(int key, int scancode, int mods) : m_key(key), m_scancode(scancode), m_mods(mods) {
    }

    [[nodiscard]] EventType type() const override {
        return EventType::KeyRepeatEvent;
    }

    [[nodiscard]] int groups() const override {
        return EventGroup::InputGroup | EventGroup::KeyboardGroup;
    }

    [[nodiscard]] std::string string() const override {
        return "KeyRepeatEvent";
    }

    [[nodiscard]] int key() const {
        return m_key;
    }

    [[nodiscard]] int scancode() const {
        return m_scancode;
    }

    [[nodiscard]] int mods() const {
        return m_mods;
    }

   private:
    int m_key;
    int m_scancode;
    int m_mods;
};

#endif
