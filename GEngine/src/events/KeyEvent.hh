#pragma once

#include "Event.hh"
#include "window/KeyCode.hh"

#include <sstream>

namespace GE
{

class GE_PUBLIC KeyEvent : public Event
{

public:
    [[nodiscard]] int getCategoryFlags() const override { return EC_KeyBoard | EC_Input; }
    [[nodiscard]] KeyCode getKeyCode() const { return m_keyCode; }

protected:
    explicit KeyEvent(KeyCode keyCode)
        : m_keyCode{keyCode}
    {
    }

    KeyCode m_keyCode;
};

class GE_PUBLIC KeyPressedEvent : public KeyEvent
{
public:
    explicit KeyPressedEvent(KeyCode keyCode, int count)
        : KeyEvent{keyCode},
          m_count{count}
    {
    }

    [[nodiscard]] int getCount() const { return m_count; }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "KeyPressedEvent: " << toGLFW(m_keyCode) << " (" << m_count << " repeats)";
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::KeyPressed; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(KeyPressed); }

private:
    int m_count;
};

class GE_PUBLIC KeyReleasedEvent : public KeyEvent
{
public:
    explicit KeyReleasedEvent(KeyCode keyCode)
        : KeyEvent{keyCode}
    {
    }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "KeyReleasedEvent: " << toGLFW(m_keyCode);
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::KeyReleased; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(KeyReleased); }
};

class GE_PUBLIC KeyTypedEvent : public KeyEvent
{
public:
    explicit KeyTypedEvent(KeyCode keyCode)
        : KeyEvent{keyCode}
    {
    }

    [[nodiscard]] std::string toString() const override
    {
        std::stringstream sstream;
        sstream << "KeyTypedEvent: " << toGLFW(m_keyCode);
        return sstream.str();
    }

    static EventType getStaticType() { return EventType::KeyTyped; }
    [[nodiscard]] EventType getEventType() const override { return getStaticType(); }
    [[nodiscard]] const char* getName() const override { return TO_STRING(KeyTyped); }
};

}