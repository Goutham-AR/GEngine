#pragma once

#include <common.hh>

#include <string>
#include <functional>
#include <ostream>

namespace GE
{

enum class EventType
{
    None = 0,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowMoved,

    AppTick,
    AppUpdate,
    AppRender,

    KeyPressed,
    KeyReleased,
    KeyTyped,

    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

#define TO_STRING(eventType) #eventType

enum EventCategory
{
    EC_None = 0,
    EC_App = BIT(0),
    EC_Input = BIT(1),
    EC_KeyBoard = BIT(2),
    EC_Mouse = BIT(3),
    EC_MouseButton = BIT(4)
};

class GE_PUBLIC Event
{
    friend class EventDispatcher;

public:
    [[nodiscard]] virtual EventType getEventType() const = 0;
    [[nodiscard]] virtual const char* getName() const = 0;
    [[nodiscard]] virtual int getCategoryFlags() const = 0;
    [[nodiscard]] virtual std::string toString() const { return getName(); }

    [[nodiscard]] inline bool isInCategory(EventCategory category) const
    {
        return getCategoryFlags() & category;
    }

    [[nodiscard]] bool isHandled() const { return m_handled; }
    void setHandled(bool value) { m_handled = value; }

protected:
    bool m_handled = false;
};

class EventDispatcher
{
    template <typename T>
    using EventFn = std::function<bool(T&)>;

public:
    explicit EventDispatcher(Event& event)
        : m_event{event}
    {
    }

    template <typename T>
    bool dispatchEvent(EventFn<T> func)
    {
        if (m_event.getEventType() == T::getStaticType())
        {
            m_event.m_handled = func(*reinterpret_cast<T*>(&m_event));
            return true;
        }
        return false;
    }

private:
    Event& m_event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& event)
{
    return os << event.toString();
}

}