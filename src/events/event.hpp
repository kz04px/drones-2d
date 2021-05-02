#ifndef EVENT_HPP
#define EVENT_HPP

#include <functional>
#include <string>

enum class EventType
{
    NoneEvent = 0,
    MouseDownEvent,
    MouseUpEvent,
    MouseMoveEvent,
    MouseScrollEvent,
    KeyPressEvent,
    KeyRepeatEvent,
    KeyReleaseEvent,
    WindowMoveEvent,
    WindowResizeEvent,
    WindowCloseEvent,
    WindowMinimiseEvent
};

enum EventGroup
{
    NoneGroup = 0,
    EngineGroup = 1,
    InputGroup = 2,
    MouseGroup = 4,
    KeyboardGroup = 8,
    WindowGroup = 16
};

class Event {
   public:
    virtual ~Event() {
    }
    virtual EventType type() const = 0;
    virtual int groups() const = 0;
    virtual std::string string() const = 0;

   protected:
    bool handled_ = false;
};

inline std::ostream &operator<<(std::ostream &os, const Event &e) {
    os << e.string();
    return os;
}

#endif
